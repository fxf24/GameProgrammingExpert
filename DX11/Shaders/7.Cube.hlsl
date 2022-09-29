#include "Common.hlsl"

struct VertexInput
{
    float4 Position : POSITION0;
    float2 Size : SIZE0;
};
struct PixelInput
{
    float4 Position : SV_POSITION;
    float2 Size : SIZE0;
};

PixelInput VS(VertexInput input)
{
   
    PixelInput output;
    output.Size = input.Size;
    //  o           =  i X W
    output.Position = mul(input.Position, World);
    return output;
}

void GS()
{
    //�Ѱ��� ���� 4���� ������
    
    // ���庯ȯ�� �� �������Ǻ�ȯ
    //output.Position = mul(input.Position, view);
    //output.Position = mul(input.Position, proj);
    
}

float4 PS(PixelInput input) : SV_TARGET
{
    
    float4 BaseColor = float4(1, 1, 1, 1);
    
    if(Kd.w == 1.0f)
    {
        BaseColor = TextureD.Sample(SamplerD, input.Size);
    }
       
    
    return BaseColor;
}