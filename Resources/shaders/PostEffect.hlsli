cbuffer cbuff0 : register(b0)
{
	float4 color;
	matrix mat;
};

// ���_�V�F�[�_�[����̏o�͍\����
struct VSOutput
{
	float4 svpos : SV_POSITION;
	float2 uv : TEXCOORD;
};