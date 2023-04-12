#include "PostEffect.hlsli"

Texture2D<float4> tex : register(t0);
SamplerState smp : register(s0);

float4 main(VSOutput input) : SV_TARGET
{
	// UV指定したピクセルの色をサンプリング
	float4 texcolor = tex.Sample(smp, input.uv + float2(1.0f,1.0f));

	// アルファに1を入れて出力
	return float4(texcolor.rgb * 1.0, 1);
}