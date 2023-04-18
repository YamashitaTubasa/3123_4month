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

	//�萔�o�b�t�@�p�f�[�^�\����(3D�ϊ��s��)
	struct ConstBufferDataTransform {
		Matrix4 mat;
	};

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
		{{ -50.0f, -50.0f, 0.0f },{0.0f,1.0f}}, // ����
		{{ -50.0f,  50.0f, 0.0f },{0.0f,0.0f}}, // ����
		{{  50.0f, -50.0f, 0.0f },{1.0f,1.0f}}, // �E��
		{{  50.0f,  50.0f, 0.0f },{1.0f,0.0f}}, // �E��
	};

	//std::vector = �ϒ��z��
	std::vector<uint16_t> indices = {
		0,1,2,
		1,2,3,
	};

	//�������s�N�Z����
	const size_t textureWidth = 256;
	//�c�����s�N�Z����
	const size_t textureHeight = 256;
	//�z��̗v�f��
	const size_t imageDataCount = textureWidth * textureHeight;
	//�摜�C���[�W�f�[�^�z��
	Vector4* imageData = new Vector4[imageDataCount];

	ComPtr<ID3D12RootSignature> rootSignature;
	ComPtr<ID3D12PipelineState> pipelineState;
	ComPtr<ID3D12Resource> vertBuff;
	ComPtr<ID3D12Resource> indexBuff;

	//�e�N�X�`���o�b�t�@�̐���
	ID3D12Resource *texBuff = nullptr;

	//�萔�o�b�t�@�̐���(����)
	ComPtr<ID3D12Resource> constBuffTransform;
	ConstBufferDataTransform *constMapTransform = nullptr;

	ComPtr<ID3D12Resource> constBuffMaterial;
	//ComPtr<ConstBufferDataMaterial> constMapMaterial;
	ConstBufferDataMaterial* constMapMaterial = nullptr;

	//�f�X�N���v�^�q�[�v�𐶐�
	ID3D12DescriptorHeap *srvHeap = nullptr;

	// ���_�o�b�t�@�r���[�̍쐬
	D3D12_VERTEX_BUFFER_VIEW vbView{};

	//�C���f�b�N�X�o�b�t�@�r���[�̍쐬
	D3D12_INDEX_BUFFER_VIEW ibView{};

	//�e�N�X�`���T���v���[�̐ݒ�
	D3D12_STATIC_SAMPLER_DESC samplerDesc{};

public:
	DirectXCommon* GetDXCommon() const { return dXCommon_; }

private:
	DirectXCommon* dXCommon_ = nullptr;
};


