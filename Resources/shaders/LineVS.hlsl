#include "Line.hlsli"

VSOutput main(float4 pos : POSITION)
{
	VSOutput output; // �s�N�Z���V�F�[�_�[�ɓn���l
	output.svpos = mul(mul(mul(projection, view), matWorld), pos);
	return output;
}