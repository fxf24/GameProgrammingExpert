#include "Common.hlsl"


struct VertexInput
{
    float4 Position : POSITION0;
    float2 Uv : UV0;
    float3 Normal : NORMAL0;
    float3 Tangent : TANGENT0;
	//������ȯ���� ���̴� ���
    float4 Indices : INDICES0;
    float4 Weights : WEIGHTS0;
};

struct PixelInput
{
    float4 Position : SV_POSITION;
    float3 wPosition : POSITION0;
    float2 Uv : UV0;
    float3 Normal : NORMAL;
    float3 Tangent : TANGENT;
    float3 Binormal : BINORMAL;
};

PixelInput VS(VertexInput input)
{
    PixelInput output;
    
    //World = offset * World;
    
    
     [branch]
    if (input.Weights.x)
        output.Position = mul(input.Position, SkinWorld(input.Indices, input.Weights));
    else
        output.Position = mul(input.Position, World);
    
    output.wPosition = output.Position;
    output.Position = mul(output.Position, ViewProj);
    output.Uv = input.Uv;
    output.Normal = mul(input.Normal, (float3x3) World);
    output.Tangent = mul(input.Tangent, (float3x3) World);
    output.Binormal = cross(output.Normal, output.Tangent);
    return output;
}

float4 PS(PixelInput input) : SV_TARGET
{
    float4 BaseColor;
    
    if(Kd.w == 1.0)
    BaseColor = TextureD.Sample(SamplerD, input.Uv);
    else
    BaseColor = float4(1, 1, 1, 1);
    
    float3 DirectionLight = DirLighting(normalize(input.Normal.xyz), input.wPosition);
    
    //                        ( r*0.6 ,g*0.3, b*0.1)
    BaseColor.rgb = saturate(BaseColor.rgb * DirectionLight);
    
    return BaseColor;
}