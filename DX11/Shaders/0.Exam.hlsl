#include "Common.hlsl"

struct VertexInput
{
    float4 Position : POSITION0;
};
struct PixelInput
{
    float4 Position : SV_POSITION;
    float3 Uv : UV0;
};

PixelInput VS(VertexInput input)
{
   
    PixelInput output;
    output.Uv = normalize(input.Position.xyz);
    
    //  o           =  i X W
    output.Position = mul(input.Position, World);
    output.Position = mul(output.Position, ViewProj);
    return output;
}

float4 PS(PixelInput input) : SV_TARGET
{
    float4 BaseColor = float4(1, 1, 1, 1);
    
     //광원이 바라보는 방향
    float3 Light = normalize(DirLight);
    //물체에서 나오는 방향(구)
    float3 Nor = normalize(input.Uv.xyz);
    
    float d = saturate(dot(-Light, Nor));
    
    d = pow(d, 20.0f);
    //return float4(d, d, d, 1);
    
    
    BaseColor = TextureSky.Sample(SamplerD, input.Uv);
    BaseColor.rgb = BaseColor.rgb + d;
    return BaseColor;
}