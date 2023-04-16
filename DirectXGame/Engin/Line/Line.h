#pragma once
#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"
#include "Matrix4.h"
#include <DirectXMath.h>
#include <vector>

#include "WinApp.h"
#include "DirectXCommon.h"
#include "stdint.h"



class Line {
public:
	//static SpriteCommon* GetInstance();

public:
	// �萔�o�b�t�@�p�f�[�^�\����(�}�e���A��)
	struct ConstBufferDataMaterial {
		Vector4 color_; // �F(RGBA)
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
	struct VertexPosUv {
		Vector3 pos;
		Vector2 uv;
	};

	// ���_�f�[�^
	std::vector<VertexPosUv> vertices = {
		{{ -0.4f, -0.7f, 0.0f },{0.0f,1.0f}}, // ����
		{{ -0.4f, +0.7f, 0.0f },{0.0f,0.0f}}, // ����
		{{ +0.4f, -0.7f, 0.0f },{1.0f,1.0f}}, // �E��
		{{ +0.4f, +0.7f, 0.0f },{1.0f,0.0f}}, // �E��
	};

	//std::vector = �ϒ��z��
	std::vector<uint16_t> indices = {
		0,1,2,
		1,2,3,
	};

	ComPtr<ID3D12RootSignature> rootSignature;
	ComPtr<ID3D12PipelineState> pipelineState;
	ComPtr<ID3D12Resource> vertBuff;
	ComPtr<ID3D12Resource> indexBuff;

	//�萔�o�b�t�@�̐���(����)
	ComPtr<ID3D12Resource> constBuffTransform;
	//ComPtr<ConstBufferDataTransform> constMapTransform;

	ComPtr<ID3D12Resource> constBuffMaterial;
	//ComPtr<ConstBufferDataMaterial> constMapMaterial;
	ConstBufferDataMaterial* constMapMaterial = nullptr;

	// ���_�o�b�t�@�r���[�̍쐬
	D3D12_VERTEX_BUFFER_VIEW vbView{};

	//�C���f�b�N�X�o�b�t�@�r���[�̍쐬
	D3D12_INDEX_BUFFER_VIEW ibView{};

public:
	DirectXCommon* GetDXCommon() const { return dXCommon_; }

private:
	DirectXCommon* dXCommon_ = nullptr;
};


