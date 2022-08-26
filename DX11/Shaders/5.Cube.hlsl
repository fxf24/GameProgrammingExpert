#include "Common.hlsl"

struct VertexInput
{
    float4 Position : POSITION0;
    float2 Uv : UV0;
    float4 Normal : NORMAL0;
    float Weights : WEIGHTS0;
};
struct PixelInput
{
    float4 Position : SV_POSITION;
    float2 Uv : UV0;
    float4 Normal : NORMAL0;
    float3 wPostion : POSITION0;
    float Weights : WEIGHTS0;
};

PixelInput VS(VertexInput input)
{
   
    PixelInput output;
    output.Uv = input.Uv;
    //  o           =  i X W
    output.Position = mul(input.Position, World);
    output.wPostion = output.Position.xyz;
    output.Position = mul(output.Position, ViewProj);
    input.Normal.w = 0.0f;
    output.Normal = mul(input.Normal, World);
    output.Weights = input.Weights;
    return output;
}

float4 PS(PixelInput input) : SV_TARGET
{
    
    float4 BaseColor = TextureD.Sample(SamplerD, input.Uv);
    float4 BaseColor2 = TextureN.Sample(SamplerN, input.Uv);
    BaseColor = BaseColor * input.Weights 
    + BaseColor2 * (1 - input.Weights);
    
    //BaseColor.rgb = Kd.rgb;
    float3 DirectionLight = DirLighting(normalize(input.Normal.xyz), input.wPostion);
    
    //                        ( r*0.6 ,g*0.3, b*0.1)
    BaseColor.rgb = saturate(BaseColor.rgb * DirectionLight);
    
    return BaseColor;
}