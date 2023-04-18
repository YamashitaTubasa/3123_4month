#include "PostEffect.hlsli"

Texture2D<float4> tex : register(t0);
SamplerState smp : register(s0);

float4 main(VSOutput input) : SV_TARGET
{
    // UV�w�肵���s�N�Z���̐F���T���v�����O
    float4 texcolor = tex.Sample(smp, input.uv) * color;
    float luminance = 1.0f; // �P�x
    float setU;
    float setV;

	// �����Y�f�B�X�g�[�V����
	//float distortion = ;
	//input.uv = distortion;
    
    //========================= �u���[ =========================//
    if (isBlur == true) {
        luminance = 1.0f;
        setU = 3.0f / 1280.0f;
        setV = 3.0f / 720.0f;

        // �E�̃J���[���T���v�����O����
        texcolor += tex.Sample(smp, input.uv + float2(setU, 0.0f));

        // ���̃J���[���T���v�����O����
        texcolor += tex.Sample(smp, input.uv + float2(-setU, 0.0f));

        // ��̃J���[���T���v�����O����
        texcolor += tex.Sample(smp, input.uv + float2(0.0f, -setV));

        // ���̃J���[���T���v�����O����
        texcolor += tex.Sample(smp, input.uv + float2(0.0f, setV));

        // �E���̃J���[���T���v�����O����
        texcolor += tex.Sample(smp, input.uv + float2(setU, setV));

        // �E��̃J���[���T���v�����O����
        texcolor += tex.Sample(smp, input.uv + float2(setU, -setV));

        // �����̃J���[���T���v�����O����
        texcolor += tex.Sample(smp, input.uv + float2(-setU, setV));

        // ����̃J���[���T���v�����O����
        texcolor += tex.Sample(smp, input.uv + float2(-setU, -setV));

        texcolor /= 10.0f;
    }

	// �A���t�@��1�����ďo��
	return float4(texcolor.rgb * luminance, alpha);
}