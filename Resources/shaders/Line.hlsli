cbuffer cbuff0 : register(b0)
{
	matrix matWorld; // �R�c�ϊ��s��
};

cbuffer cbuff1 : register(b1)
{
	matrix view;       // ���[���h �� �r���[�ϊ��s��
	matrix projection; // �r���[ �� �v���W�F�N�V�����ϊ��s��
	vector cameraPos;  // �J�������W�i���[���h���W�j
};

// ���_�V�F�[�_�[����s�N�Z���V�F�[�_�[�ւ̂����Ɏg�p����\����
struct VSOutput
{
	float4 svpos : SV_POSITION; // �V�X�e���p���_���W
};
