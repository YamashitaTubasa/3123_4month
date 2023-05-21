#include "PostEffect.hlsli"

Texture2D<float4> tex : register(t0);
SamplerState smp : register(s0);

float4 main(VSOutput input) : SV_TARGET
{
    // UV�w�肵���s�N�Z���̐F���T���v�����O
    float4 texcolor = tex.Sample(smp, input.uv) * color;
    float luminance = 1.0f; // �P�x
    float setU, setV;

    //========================= �u���[ =========================//
    if (isBlur == true ) {
        float blur = 4.0;
        luminance = 1.0f;
        if (isBlur == false) {
            if (blur >= 0.0f) {
                blur--;
            }
        }
        setU = blur / 1280.0f;
        setV = blur / 720.0f;

        texcolor += tex.Sample(smp, input.uv + float2(setU, 0.0f));
        texcolor += tex.Sample(smp, input.uv + float2(-setU, 0.0f));
        texcolor += tex.Sample(smp, input.uv + float2(0.0f, -setV));
        texcolor += tex.Sample(smp, input.uv + float2(0.0f, setV));
        texcolor += tex.Sample(smp, input.uv + float2(setU, setV));
        texcolor += tex.Sample(smp, input.uv + float2(setU, -setV));
        texcolor += tex.Sample(smp, input.uv + float2(-setU, setV));
        texcolor += tex.Sample(smp, input.uv + float2(-setU, -setV));

        texcolor /= 10.0f;
    }

	// �A���t�@��1�����ďo��
	return float4(texcolor.rgb * luminance, alpha);
}