cbuffer VS_W : register(b0)
{
    matrix World;
}
cbuffer VS_VP : register(b1)
{
    matrix ViewProj;
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

Texture2D TextureN : register(t0);
SamplerState SamplerN : register(s0);

Texture2D TextureD : register(t1);
SamplerState SamplerD : register(s1);

Texture2D TextureS : register(t2);
SamplerState SamplerS : register(s2);

Texture2D TextureE : register(t3);
SamplerState SamplerE : register(s3);

float3 DirLighting(float3 Normal, float3 wPosition)
{
    float3 DirectionLight = normalize(float3(1, -1, 0));
    float Diffuse = saturate(dot(-DirectionLight, Normal));
    
    float3 RecflectLight = reflect(DirectionLight, Normal);
    float3 ViewDir = normalize(ViewPos.xyz - wPosition);
    float Specular = saturate(dot(ViewDir, RecflectLight));
    Specular = pow(Specular, Shininess);
    
    float3 D = Diffuse * Kd.rgb;
    float3 S = Specular * Ks.rgb;
    return D + S + Ka.rgb;
}