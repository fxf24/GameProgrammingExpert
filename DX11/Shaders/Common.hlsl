cbuffer VS_W : register(b0)
{
    matrix World;
}
cbuffer VS_VP : register(b1)
{
    matrix ViewProj;
}

cbuffer GS_VP : register(b0)
{
    matrix GSViewProj;
}
cbuffer GS_View : register(b1)
{
    float4 GSViewPos;
}
cbuffer GS_View : register(b2)
{
    float4 GSViewUp;
}
cbuffer GS_View : register(b3)
{
    float4 GSViewForward;
}



//���̷���
#define MAX_BONE 256
cbuffer VS_Bones : register(b2)
{
    matrix Bones[MAX_BONE];
}

cbuffer PS_ViewPos : register(b0)
{
    float4 ViewPos;
}

cbuffer PS_Material : register(b1)
{
    float4 Ka;
    float4 Kd;
    float4 Ks;
    float4 Ke;
    float Shininess;
    float Opacity;
    float2 MaterialPadding;
}

cbuffer PS_DirLight : register(b2)
{
    float4 DirLight;
    float4 DirColor;
}

//Texture3D a;

Texture2D TextureN : register(t0);
SamplerState SamplerN : register(s0);

Texture2D TextureD : register(t1);
SamplerState SamplerD : register(s1);

Texture2D TextureS : register(t2);
SamplerState SamplerS : register(s2);

Texture2D TextureE : register(t3);
SamplerState SamplerE : register(s3);

TextureCube TextureSky : register(t4);
SamplerState SamplerSky : register(s4);

matrix SkinWorld(float4 indices, float4 weights)
{
    matrix transform = 0; //�����
    transform += mul(weights.x, Bones[(uint) indices.x]);
    transform += mul(weights.y, Bones[(uint) indices.y]);
    transform += mul(weights.z, Bones[(uint) indices.z]);
    transform += mul(weights.w, Bones[(uint) indices.w]);
    return transform;
}



float3 DirLighting(float3 Normal, float3 wPostion)
{
    float3 DirectionLight = normalize(DirLight.xyz);
    float Diffuse = saturate(dot(-DirectionLight, Normal));
    
    float3 RecflectLight = reflect(DirectionLight, Normal);
    float3 ViewDir = normalize(ViewPos.xyz - wPostion);
    float Specular = saturate(dot(ViewDir, RecflectLight));
    Specular = pow(Specular, Shininess);
    
    float3 D = Diffuse * Kd.rgb;
    float3 S = Specular * Ks.rgb;
    return D + S + Ka.rgb;
}

float4 DiffuseMapping(float2 Uv)
{
    [flatten]
    if (Ka.a)
        return TextureD.Sample(SamplerD, Uv);
    
    return float4(1, 1, 1, 1);
}

float3 NormalMapping(float3 T, float3 B, float3 N, float2 Uv)
{
    T = normalize(T);
    B = normalize(B);
    N = normalize(N);
    
    [flatten]
    if (Ka.a)
    {
        float3 normal = TextureN.Sample(SamplerN, Uv).rgb;
        
        float3x3 TBN = float3x3(T, B, N);
        N = normal * 2.0f - 1.0f;
        N = normalize(mul(N, TBN));
    }
    return N;
}