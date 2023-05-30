#include "PostEffect.hlsli"

Texture2D<float4> tex : register(t0);
SamplerState smp : register(s0);

float4 main(VSOutput input) : SV_TARGET
{
    
    //// UV指定したピクセルの色をサンプリング
    //float4 texcolor = tex.Sample(smp, input.uv) * color;
    //float luminance = 1.0f; // 輝度
    //float setU, setV;
    //float4 col = float4(0, 0, 0, 1);
    ////========================= ブラー =========================//
    //    float blur = 4.0;
    //    luminance = 1.0f;
    //    if (isBlur == false) {
    //        if (blur >= 0.0f) {
    //            blur--;
    //        }
    //    }
    //    setU = blur / 1280.0f;
    //    setV = blur / 720.0f;
        
    //    float shift = 0.005;

    //    col += tex.Sample(smp, input.uv + float2(-shift, -shift));
    //    col += tex.Sample(smp, input.uv + float2(0.0f, -shift));
    //    col += tex.Sample(smp, input.uv + float2(shift, -shift));
    //    col += tex.Sample(smp, input.uv + float2(-shift, 0.0f));
    //    col += tex.Sample(smp, input.uv + float2(0.0f, 0.0f));
    //    col += tex.Sample(smp, input.uv + float2(shift, 0.0f));
    //    col += tex.Sample(smp, input.uv + float2(-shift, shift));
    //    col += tex.Sample(smp, input.uv + float2(0.0f, shift));
    //    col += tex.Sample(smp, input.uv + float2(shift, shift));
        
    //    col.rgb /= 9.0f;
    //    col.a = 1;
    
    float luminance = 1.0f; // 輝度
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