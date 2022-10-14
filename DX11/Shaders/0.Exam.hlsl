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
    
    //광원과 법선의 내적값
    float d = saturate(dot(-Light, Nor));
    
<<<<<<< HEAD
    //태양 그리기
    if (d > 0.9995f)
    {
        return float4(1, 1, 1, 1);
    }
    
   // return float4(d * 0.3f, d * 0.3f, d * 0.7f, 1);
    
    //큐브맵에서 가져온 색
    BaseColor = TextureSky.Sample(SamplerD, input.Uv);
    
    BaseColor.rgb += float3(d * 0.3f, d * 0.3f, d * 0.3f);
    
=======
    if (d > 0.9995f)
    {
        return float4(1, 1, 1, 1);
    }  
    
    //큐브맵에서 가져온 색
    BaseColor = TextureSky.Sample(SamplerD, input.Uv);
    BaseColor.rgb += float3(d * 0.3f, d * 0.3f, d * 0.7f);
>>>>>>> 6b1bb4def680a2802e1f5abfe12097f77107fa9b
    return BaseColor;
}