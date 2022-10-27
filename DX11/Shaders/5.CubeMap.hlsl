#include "Common.hlsl"

struct VertexInput
{
    float4 Position : POSITION0;
    float2 Uv : UV0;
    float4 Normal : NORMAL0;
    float Weights : WEIGHTS0;
};

struct GeometryInput
{
    float4 Position : SV_POSITION;
    float3 wPosition : POSITION0;
    float2 Uv : UV0;
    float4 Normal : NORMAL0;
    float Weights : WEIGHTS0;
};

struct PixelInput
{
    uint TargetIndex : SV_RenderTargetArrayIndex;
    float4 Position : SV_POSITION;
    float2 Uv : UV0;
    float4 Normal : NORMAL0;
    float3 wPosition : POSITION0;
    float Weights : WEIGHTS0;
};

GeometryInput VS(VertexInput input)
{
   
    GeometryInput output;
    output.Uv = input.Uv;
    //  o           =  i X W
    output.Position = mul(input.Position, World);
    output.wPosition = output.Position.xyz;
    //output.Position = mul(output.Position, ViewProj);
    input.Normal.w = 0.0f;
    output.Normal = mul(input.Normal, World);
    output.Weights = input.Weights;
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
            output.Position = mul(output.Position, CubeViews[i]);
            output.Position = mul(output.Position, CubeProjection);
            output.Uv = input[vertex].Uv;
            output.wPosition = input[vertex].Position;
            output.Normal = input[vertex].Normal;
            output.Weights = input[vertex].Weights;
            stream.Append(output);
        }
        
        stream.RestartStrip();
    }
}

float4 PS(PixelInput input) : SV_TARGET
{
    
    float4 BaseColor = TextureD.Sample(SamplerD, input.Uv);
   
    float4 BaseColor2 = TextureN.Sample(SamplerN, input.Uv);
    BaseColor = BaseColor * input.Weights + BaseColor2 * (1 - input.Weights);
    
    
    float3 Normal = normalize(input.Normal);
    
    BaseColor = Lighting(BaseColor, input.Uv, Normal, input.wPosition);
    
    return BaseColor;
}