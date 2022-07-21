#include "Common.hlsl"

struct VertexInput
{
    float4 Position : POSITION0;
    float4 Color : COLOR0;
    float4 Normal : NORMAL0;
};
struct PixelInput
{
    float4 Position : SV_POSITION;
    float4 Color : COLOR0;
    float4 Normal : NORMAL0;
    float3 wPostion : POSITION0;
};

PixelInput VS(VertexInput input)
{
   
    PixelInput output;
    output.Color = input.Color;
    //  o           =  i X W
    output.Position = mul(input.Position, World);
    output.wPostion = output.Position.xyz;
    output.Position = mul(output.Position, ViewProj);
    input.Normal.w = 0.0f;
    output.Normal = mul(input.Normal, World);
    return output;
}

float4 PS(PixelInput input) : SV_TARGET
{
    float4 BaseColor = input.Color;
    //BaseColor.rgb = Kd.rgb;
    float3 DirectionLight = DirLighting(normalize(input.Normal.xyz), input.wPostion);
    
    //                      (r*r, g*g, b*b)
    BaseColor.rgb = saturate(BaseColor.rgb * DirectionLight);
    
    return BaseColor;
}