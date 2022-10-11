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
    
     //������ �ٶ󺸴� ����
    float3 Light = normalize(DirLight);
    //��ü���� ������ ����(��)
    float3 Nor = normalize(input.Uv.xyz);
    
    //������ ������ ������
    float d = saturate(dot(-Light, Nor));
    
    if (d > 0.9995f)
    {
        return float4(1, 1, 1, 1);
    }  
    
    //ť��ʿ��� ������ ��
    BaseColor = TextureSky.Sample(SamplerD, input.Uv);
    BaseColor.rgb += float3(d * 0.3f, d * 0.3f, d * 0.7f);
    return BaseColor;
}