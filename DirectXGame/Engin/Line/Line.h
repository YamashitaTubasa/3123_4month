#pragma once
#include "Vector3.h"
#include "Matrix4.h"
#include <DirectXMath.h>
#include <vector>

#include "WinApp.h"
#include "DirectXCommon.h"

class Line {
public:
	//static SpriteCommon* GetInstance();

public:
	// �萔�o�b�t�@�p�f�[�^�\����(�}�e���A��)
	struct ConstBufferDataMaterial {
		Matrix4 color; // �F(RGBA)
	};

	////�萔�o�b�t�@�p�f�[�^�\����(Material)
	//struct ConstBufferDataTransform {
	//	XMMATRIX mat; //3D�ϊ��s��
	//};

public:
	// ������
	void Initialize();

	// �X�V
	void Update();

	// �`��
	void Draw();

public:
	Line() = default;
	~Line() = default;

private:
	// ���_�f�[�^
	Vector3 vertices[4] = {
		{ -0.5f, -0.5f, 0.0f }, // ����
		{ -0.5f, +0.5f, 0.0f }, // ����
		{ +0.5f, -0.5f, 0.0f }, // �E��
		{ -0.5f, -0.5f, 0.0f },
	};

	ComPtr<ID3D12RootSignature> rootSignature;
	ComPtr<ID3D12PipelineState> pipelineState;
	ComPtr<ID3D12Resource> vertBuff;

	//�萔�o�b�t�@�̐���(����)
	ComPtr<ID3D12Resource> constBuffTransform;
	//ComPtr<ConstBufferDataTransform> constMapTransform;

	// ���_�o�b�t�@�r���[�̍쐬
	D3D12_VERTEX_BUFFER_VIEW vbView{};

public:
	DirectXCommon* GetDXCommon() const { return dXCommon_; }

private:
	DirectXCommon* dXCommon_ = nullptr;
};


