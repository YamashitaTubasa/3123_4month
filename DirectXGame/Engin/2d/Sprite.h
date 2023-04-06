#pragma once

#include <Windows.h>
#include <D3dx12.h>
#include <DirectXMath.h>
#include <d3dcompiler.h>
#include <cassert>
#include <DirectXTex.h>
#include <wrl.h>
#include <array>
#include"Vector2.h"
#include"Vector3.h"
#include"Vector4.h"
#include"Matrix4.h"

#include "DirectXCommon.h"

#pragma comment(lib, "d3dcompiler.lib")

using namespace DirectX;
using namespace Microsoft::WRL;
using namespace std;



// �p�C�v���C���Z�b�g
struct PipelineSet {
	// �p�C�v���C���X�e�[�g�I�u�W�F�N�g
	ComPtr<ID3D12PipelineState> pipelinestate;
	// ���[�g�V�O�l�`��
	ComPtr<ID3D12RootSignature> rootsignature;
};

// �X�v���C�g�̋��ʃf�[�^
struct SpriteCommon {
	// �p�C�v���C���Z�b�g
	PipelineSet pipelineSet;
	// �ˉe�s��
	Matrix4 matProjection{};
	// �e�N�X�`���p�f�X�N���v�^�q�[�v�̐���
	ComPtr<ID3D12DescriptorHeap> descHeap;
	// SRV�̍ő喇��
	static const size_t kMaxSRVCount = 512;
	// �e�N�X�`���\�[�X(�e�N�X�`���o�b�t�@)�̔z��
	ComPtr<ID3D12Resource> texBuff[kMaxSRVCount];
	// �e�N�X�`���o�b�t�@�擾
	ID3D12Resource* GetTexBuffer(uint32_t index) const { return texBuff[index].Get(); }
};

// �X�v���C�g
class Sprite
{
public://�T�u�N���X
	// �萔�o�b�t�@�p�f�[�^�\����B0
	struct ConstBufferDataB0
	{
		Vector4 color;
		Matrix4 mat;	// �R�c�ϊ��s��
	};

	// ���_�f�[�^
	struct VertexPosUv {
		Vector3 pos;
		Vector2 uv;
	};
public:
	Sprite();
	~Sprite();

	/// �X�v���C�g���ʃf�[�^����
	SpriteCommon SpriteCommonCreate(ID3D12Device* dev, int window_width, int window_height);

	/// 3D�I�u�W�F�N�g�p�p�C�v���C������
	PipelineSet SpriteCreateGraphicsPipeline(ID3D12Device* device);

	/// �X�v���C�g���ʃe�N�X�`���ǂݍ���
	void LoadTexture(SpriteCommon& spriteCommon, UINT texnumber, 
		const wchar_t* filename, ID3D12Device* dev);

	/// �X�v���C�g����
	void SpriteCreate(ID3D12Device* dev, int window_width, int window_height, 
		UINT texNumber, const SpriteCommon& spriteCommon, Vector2 anchorpoint, bool isFlipX, bool FlipY);

	/// �X�v���C�g�P�̒��_�o�b�t�@�̓]��
	void SpriteTransferVertexBuffer(const Sprite& sprite, const SpriteCommon& spriteCommon, uint32_t texIndex_ = UINT32_MAX);

	/// �X�v���C�g�P�̍X�V
	void SpriteUpdate(Sprite& sprite, const SpriteCommon& spriteCommon);

	/// �`��O����
	static void PreDraw(ID3D12GraphicsCommandList* cmdList, const SpriteCommon& spriteCommon);

	/// �`��㏈��
	static void PostDraw();

	/// �X�v���C�g�P�̕`��
	void SpriteDraw(ID3D12GraphicsCommandList* cmdList_, const SpriteCommon& spriteCommon, 
		ID3D12Device* dev,D3D12_VERTEX_BUFFER_VIEW& vbView);

	/// �I������
	void Finalize();

public: // �Z�b�^�[
	// ���W�ݒ�
	void SetPosition(Vector3 position) { this->position = position; }
	// �T�C�Y�ݒ�
	void SetScale(Vector2 scale) { this->scale = scale; }
	// ��]
	void SetRotation(float rotation) { this->rotation = rotation; }
	// �ԍ�
	void SetTexNumber(UINT texNumber) { this->texNumber = texNumber; }
	// �F
	void SetColor(const Vector4& color) { this->color_ = color; }
	// �t���b�v
	void SetIsFlipX(bool isFlipX) { this->isFlipX_ = isFlipX; } // X
	void SetIsFlipY(bool isFlipY) { this->isFlipY_ = isFlipY; } // Y
	// �e�N�X�`��������W
	void SetTexLeftTop(const Vector2& texLeftTop) { this->texLeftTop_ = texLeftTop; }
	// �e�N�X�`���؂�o���T�C�Y
	void SetTexSize(const Vector2& texSize) { this->texSize_ = texSize; }

public: // �Q�b�^�[
	// ���W
	Vector3 GetPosition() const { return position; }
	// �T�C�Y
	Vector2 GetScale() const { return scale; }
	// ��]
	float GetRotation() const { return rotation; }
	// �ԍ�
	UINT GetTexNumber() const { return texNumber; }
	// �F
	Vector4 GetColor() const { return color_; }
	// �t���b�v
	bool GetIsFlipX() const { return isFlipX_; } // X
	bool GetIsFlipY() const { return isFlipY_; } // Y
	// �e�N�X�`��������W
	Vector2 GetTexLeftTop() const { return texLeftTop_; }
	// �e�N�X�`���؂�o���T�C�Y
	Vector2 GetTexSize() const { return texSize_; }

public:
	//���_�o�b�t�@
	ComPtr<ID3D12Resource> vertBuff;
	//���_�o�b�t�@�r���[
	D3D12_VERTEX_BUFFER_VIEW vbView{};
	D3D12_RESOURCE_DESC resDesc;

private:
	// DirectXCommon�̃C���X�^���X
	DirectXCommon* dXCommon = nullptr;
	SpriteCommon spriteCommon_;

	ComPtr<ID3D12GraphicsCommandList> cmdList;
	ComPtr<ID3D12DescriptorHeap> descHeap;
	//�萔�o�b�t�@
	ComPtr<ID3D12Resource> constBuffB0 = nullptr;
	// �}�b�s���O�ς݃A�h���X
	ConstBufferDataB0* constMap = nullptr;
	D3D12_DESCRIPTOR_HEAP_DESC srvHeapDesc = {};
	static const size_t kMaxSRVCount = 2056;
	// �e�N�X�`���o�b�t�@
	std::array<ComPtr<ID3D12Resource>, kMaxSRVCount> texBuffers_;

	// �e�N�X�`���ԍ�
	UINT texNumber = 0;
	uint32_t texIndex_ = 0;
	// ���W
	Vector3 position = { 0.0f, 0.0f, 0.0f };
	// �T�C�Y
	Vector2 scale = { 1.0f, 1.0f };
	// ��]
	Vector3 rotation_ = { 0.0f,0.0f,0.0f };
	// ���[���h�s��
	Matrix4 matWorld;
	// �A���J�[�|�C���g
	Vector2 anchorpoint = { 0.0f,0.0f };
	// �e�N�X�`��������W�ݒ�
	Vector2 texLeftTop_ = { 50.0f, 50.0f };
	// �e�N�X�`���؂�o���T�C�Y
	Vector2 texSize_ = { 100.0f, 100.0f };
	// �F
	Vector4 color_ = { 1,1,1,1 };

	// Z�����̉�]
	float rotation = 0.0f;
	// ���E���]
	bool isFlipX_ = false;
	// �㉺���]
	bool isFlipY_ = false;
	// ��\��
	bool isInvisible = false;
};

