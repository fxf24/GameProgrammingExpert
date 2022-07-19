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
    float3 DirectionLight = normalize(float3(1, -1, 0));
    float3 Normal = normalize(input.Normal);
    float Diffuse = saturate(dot(-DirectionLight, Normal));
    
    float3 RecflectLight = reflect(DirectionLight, Normal);
    float3 ViewDir = normalize(ViewPos.xyz - input.wPostion.xyz);
    float Specular = saturate(dot(ViewDir, RecflectLight));
    Specular = pow(Specular, 10.0f);
    //Specular *= 0.5f;
    //Diffuse = saturate(dot(ViewDir, Normal));
    
    //            a   + d
    BaseColor *= 0.2f + Diffuse + Specular;
    
    
    return BaseColor;
}