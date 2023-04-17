#include "Line.hlsli"

//float4 main() : SV_TARGET
//{
//	return color;
//}

//-----04_01_UV���W-----//
//float4 main(VSOutput input) : SV_TARGET
//{
//	return float4(input.uv,0,1);
//}

//-----04_02_�e�N�X�`���}�b�s���O-----//
Texture2D<float4> tex: register(t0);
SamplerState smp: register(s0);

float4 main(VSOutput input) : SV_TARGET{
	return float4(tex.Sample(smp,input.uv));
}

