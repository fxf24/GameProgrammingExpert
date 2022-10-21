#include "Common.hlsl"

struct VertexInput
{
    float4 Position : POSITION0;
    float2 Uv : UV0;
};
struct PixelInput
{
    float4 Position : SV_POSITION;
    float2 Uv : UV0;
};

PixelInput VS(VertexInput input)
{
   
    PixelInput output;
    output.Uv = input.Uv;
    //  o           =  i X W
    output.Position = mul(input.Position, World);
    return output;
}

float4 PS(PixelInput input) : SV_TARGET
{
    
    float4 BaseColor = DiffuseMapping(input.Uv);
    //float avg = BaseColor.r + BaseColor.g + BaseColor.b;
    //avg /= 3.0f;
    //float3 temp = avg;
    ////세피아
    //BaseColor.r = dot(temp.rgb, float3(0.393f, 0.769f, 0.189f));
    //BaseColor.g = dot(temp.rgb, float3(0.349f, 0.686f, 0.168f));
    //BaseColor.b = dot(temp.rgb, float3(0.272f, 0.534f, 0.131f));
    
     //흑과 백으로 나누기
    //if (any(BaseColor.rgb))
    //{
    //    BaseColor.r = 1.0f;
    //    BaseColor.g = 1.0f;
    //    BaseColor.b = 1.0f;
    //}
    //else
    //{
    //    BaseColor.r = 0.0f;
    //    BaseColor.g = 0.0f;
    //    BaseColor.b = 0.0f;
    //}
    
    //BaseColor.r *= 5.0f;
    //BaseColor.g *= 5.0f;
    //BaseColor.b *= 5.0f;
    
    //BaseColor.r = floor(BaseColor.r);
    //BaseColor.g = floor(BaseColor.g);
    //BaseColor.b = floor(BaseColor.b);
    
    //BaseColor.r /= 5.0f;
    //BaseColor.g /= 5.0f;
    //BaseColor.b /= 5.0f;
       
    //모노
    //BaseColor.rgb = BaseColor.r * 0.3f + BaseColor.g * 0.59f + BaseColor.b * 0.11f;

    //색 반전
    //BaseColor.rgb = (1.0f - BaseColor.rgb);
    
    return BaseColor;
}