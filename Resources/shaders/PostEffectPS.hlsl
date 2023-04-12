#include "PostEffect.hlsli"

Texture2D<float4> tex : register(t0);
SamplerState smp : register(s0);

float4 main(VSOutput input) : SV_TARGET
{
	// UV�w�肵���s�N�Z���̐F���T���v�����O
	float4 texcolor = tex.Sample(smp, input.uv + float2(1.0f,1.0f));

	// �A���t�@��1�����ďo��
	return float4(texcolor.rgb * 1.0, 1);
}