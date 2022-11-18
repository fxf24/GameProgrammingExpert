#include "Common.hlsl"

struct VertexInput
{
    float4 Position : POSITION0;
    float2 Size : SIZE0;
    float3 Velocity : VELOCITY0;
};
struct VertexOutput
{
    float3 Position : POSITION0;
    float2 Size : SIZE0;
};

struct PixelInput
{
    float4 Position : SV_POSITION;
    float2 Uv : UV0;
};

cbuffer VS_Data : register(b10)
{
    float duration;
    float time;
    float gravity;
    float padding1;
}
VertexOutput VS(VertexInput input)
{
    VertexOutput output;
    
    input.Velocity.y -= gravity * time;
    output.Position = mul(input.Position, World);
     //���ν�Ƽ������ ������
    output.Position += (input.Velocity * time);
    output.Size = input.Size;
    
    return output;
}

static const float2 TEXCOORD[4] =
{
    float2(0.0f, 1.0f),
    float2(0.0f, 0.0f),
    float2(1.0f, 1.0f),
    float2(1.0f, 0.0f)
};
[maxvertexcount(4)]
void GS(point VertexOutput input[1], inout TriangleStream<PixelInput> output)
{
    //�Ѱ��� ���� �װ��� ������
    
    // ���庯ȯ�� �� �������Ǻ�ȯ
    
    float3 up = GSViewUp;
    float3 forward = GSViewForward;
    float3 right = normalize(cross(up, forward));
    
    float2 halfSize = input[0].Size * 0.5f;
    
    float4 vertices[4];
    //input[0].Position.xyz (������ǥ,����)
    
    //���� �Ʒ�
   // vertices[0] = float4(input[0].Position.xyz - halfSize.x * right - halfSize.y * up, 1.0f);
    vertices[0] = float4(input[0].Position.xyz - right * halfSize.x - up * halfSize.y, 1.0f);
    // �� ��
    vertices[1] = float4(input[0].Position.xyz - right * halfSize.x + up * halfSize.y, 1.0f);
    // �� �Ʒ�
    vertices[2] = float4(input[0].Position.xyz + right * halfSize.x - up * halfSize.y, 1.0f);
    // �� ��
    vertices[3] = float4(input[0].Position.xyz + right * halfSize.x + up * halfSize.y, 1.0f);
    
    PixelInput pixelInput;
    
    [unroll(4)]
    for (int i = 0; i < 4; i++)
    {
        //���忡�� �ٽ� ndc���� ��ȯ
        pixelInput.Position = mul(vertices[i], GSViewProj);
        pixelInput.Uv = TEXCOORD[i];
        
        output.Append(pixelInput);
    }
    
}

float4 PS(PixelInput input) : SV_TARGET
{
    
    float4 BaseColor = DiffuseMapping(input.Uv);
       
    if (BaseColor.a == 0)
        discard;
    return BaseColor;
}