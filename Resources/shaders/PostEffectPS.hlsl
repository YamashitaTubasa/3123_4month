#include "PostEffect.hlsli"

Texture2D<float4> tex : register(t0);
SamplerState smp : register(s0);

float4 main(VSOutput input) : SV_TARGET
{
    // UV指定したピクセルの色をサンプリング
    float4 texcolor = tex.Sample(smp, input.uv) * color;
    float luminance = 1.0f; // 輝度
    float setU;
    float setV;

	// レンズディストーション
	//float distortion = ;
	//input.uv = distortion;
    
    //========================= ブラー =========================//
    if (isBlur == true) {
        luminance = 1.0f;
        setU = 3.0f / 1280.0f;
        setV = 3.0f / 720.0f;

        // 右のカラーをサンプリングする
        texcolor += tex.Sample(smp, input.uv + float2(setU, 0.0f));

        // 左のカラーをサンプリングする
        texcolor += tex.Sample(smp, input.uv + float2(-setU, 0.0f));

        // 上のカラーをサンプリングする
        texcolor += tex.Sample(smp, input.uv + float2(0.0f, -setV));

        // 下のカラーをサンプリングする
        texcolor += tex.Sample(smp, input.uv + float2(0.0f, setV));

        // 右下のカラーをサンプリングする
        texcolor += tex.Sample(smp, input.uv + float2(setU, setV));

        // 右上のカラーをサンプリングする
        texcolor += tex.Sample(smp, input.uv + float2(setU, -setV));

        // 左下のカラーをサンプリングする
        texcolor += tex.Sample(smp, input.uv + float2(-setU, setV));

        // 左上のカラーをサンプリングする
        texcolor += tex.Sample(smp, input.uv + float2(-setU, -setV));

        texcolor /= 10.0f;
    }

	// アルファに1を入れて出力
	return float4(texcolor.rgb * luminance, alpha);
}