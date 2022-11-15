#include "Common.hlsl"

struct VertexInput
{
    float4 Position : POSITION0;
    float4 Color : COLOR0;
    float4 Normal : NORMAL0;
};

struct GeometryInput
{
    
    float4 Position : SV_POSITION;
    float4 Color : COLOR0;
    float4 Normal : NORMAL0;
    float3 wPosition : POSITION0;
};



struct PixelInput
{
    uint TargetIndex : SV_RenderTargetArrayIndex;
    float4 Position : SV_POSITION;
    float4 Color : COLOR0;
    float4 Normal : NORMAL0;
    float3 wPosition : POSITION0;
};

GeometryInput VS(VertexInput input)
{
   
    GeometryInput output;
    output.Color = input.Color;
    //  o           =  i X W
    output.Position = mul(input.Position, World);
    output.wPosition = output.Position.xyz;
    //output.oPosition = input.Position.xyz;
    //output.Position = mul(output.Position, ViewProj);
    input.Normal.w = 0.0f;
    output.Normal = mul(input.Normal, World);
    return output;
}


[maxvertexcount(18)]
void GS(triangle GeometryInput input[3], inout TriangleStream<PixelInput> stream)
{
    int vertex = 0;
    PixelInput output;
    
    [unroll(6)]
    for (int i = 0; i < 6; i++)
    {
        output.TargetIndex = i;
        
        [unroll(3)]
        for (vertex = 0; vertex < 3; vertex++)
        {
            output.Position = input[vertex].Position;
            output.Position.xyz = mul(output.Position.xyz, (float3x3) (CubeViews[i]));
            output.Position = mul(output.Position, CubeProjection);
            output.Color = input[vertex].Color;
            output.Normal = input[vertex].Normal;
            output.wPosition = input[vertex].wPosition;
            stream.Append(output);
        }
        
        stream.RestartStrip();
    }
}

float4 PS(PixelInput input) : SV_TARGET
{
    float4 BaseColor = input.Color;
    
    float3 Normal = normalize(input.Normal);
    
    BaseColor = Lighting(BaseColor, float2(1, 1), Normal, input.wPosition);
    
    
    return BaseColor;
}