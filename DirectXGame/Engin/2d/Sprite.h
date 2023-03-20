#pragma once

#include "SpriteCommon.h"

//============//
// �X�v���C�g //
//============//
class Sprite
{
private:
	using XMFLOAT3 = DirectX::XMFLOAT3;

public:
	// ������
	void Initialize();

	// �X�V
	void Update();

	// �`��
	void Draw();

public:
	Sprite() = default;
	~Sprite() = default;

private:
	// ���_�f�[�^
	XMFLOAT3 vertices[4] = {
		{ -0.5f, -0.5f, 0.0f }, // ����
		{ -0.5f, +0.5f, 0.0f }, // ����
		{ +0.5f, -0.5f, 0.0f }, // �E��
	};

private:
	SpriteCommon* spriteCommon = nullptr;
};