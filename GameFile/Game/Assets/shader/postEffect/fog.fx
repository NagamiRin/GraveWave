
cbuffer cb : register(b0)
{
    float4x4 mvp;
    float4 mulColor;
};
struct VSInput
{
    float4 pos : POSITION;
    float2 uv : TEXCOORD0;
};

struct PSInput
{
    float4 pos : SV_POSITION;
    float2 uv : TEXCOORD0;
};


Texture2D<float4> colorTexture : register(t0);
Texture2D<float4> zprepassTexture : register(t1);
sampler Sampler : register(s0);

PSInput VSMain(VSInput In)
{
    PSInput psIn;
    psIn.pos = mul(mvp, In.pos);
    psIn.uv = In.uv;
    return psIn;
}
float4 PSMain(PSInput In) : SV_Target0
{
    float zprepass = zprepassTexture.Sample(Sampler, In.uv).b;
    float4 color = colorTexture.Sample(Sampler, In.uv);
    float4 fogColor = float4(0.5f, 0.5f, 0.5f, 1.0f);

	
    if (zprepass < 400.0f)
    {
        return color;
    }
    else if (zprepass > 700.0f)
    {
        return fogColor;
    }

    float t = 1-(zprepass - 400.0f) / (700.0f - 400.0f);
    
    
    color.xyz = lerp(fogColor.xyz, color.xyz, t);
	
    return color;
}
