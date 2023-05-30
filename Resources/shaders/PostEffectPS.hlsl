#include "PostEffect.hlsli"

Texture2D<float4> tex : register(t0);
SamplerState smp : register(s0);

float4 main(VSOutput input) : SV_TARGET
{
    float luminance = 1.0f; // ‹P“x
    float shiftWidth = 0.003;
    float shiftNum = 5;

    float4 col = tex.Sample(smp, input.uv) * color;
    float num = 0;

    if (isBlur == true)
    {
        for (float py = -shiftNum / 2; py <= shiftNum / 2; py++)
        {
            for (float px = -shiftNum / 2; px <= shiftNum / 2; px++)
            {
                col += tex.Sample(smp, input.uv + float2(px, py) * shiftWidth) * color;
                num++;
            }
        }
        col.rgb /= num;
    }
    
    return float4(col.rgb * luminance, alpha);
}