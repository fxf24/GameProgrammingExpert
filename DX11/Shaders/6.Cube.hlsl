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
    
    float4 BaseColor = float4(1, 1, 1, 1);
    
    if(Kd.w == 1.0f)
    {
        BaseColor = TextureD.Sample(SamplerD, input.Uv);
    }
       
    
    return BaseColor;
}