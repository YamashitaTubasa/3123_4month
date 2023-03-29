#pragma once

#include "DirectXCommon.h"
#include "WinApp.h"
#include <DirectXMath.h>
#include <d3dcompiler.h>
#include <string>

#pragma comment(lib, "d3dcompiler.lib")

//==================//
// �X�v���C�g���ʕ� //
//==================//
class SpriteCommon final
{
private:
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;

public:
	static SpriteCommon* GetInstance();

public:
	// �萔�o�b�t�@�p�f�[�^�\����(�}�e���A��)
	struct ConstBufferDataMaterial {
		XMFLOAT4 color; // �F(RGBA)
	};

public:
	// ������
	void Initialize();

	// �X�V
	void Update();

	// �`��
	void Draw();

private:
	SpriteCommon() = default;
	~SpriteCommon() = default;
	SpriteCommon(const SpriteCommon&) = delete;
	SpriteCommon& operator=(const SpriteCommon&) = delete;

private:
	//// ���_�f�[�^
	//XMFLOAT3 vertices[4] = {
	//	{ -0.5f, -0.5f, 0.0f }, // ����
	//	{ -0.5f, +0.5f, 0.0f }, // ����
	//	{ +0.5f, -0.5f, 0.0f }, // �E��
	//};

	ComPtr<ID3D12RootSignature> rootSignature;
	ComPtr<ID3D12PipelineState> pipelineState;

public:
	DirectXCommon* GetDXCommon() const { return dXCommon_; }

private:
	DirectXCommon* dXCommon_ = nullptr;
};