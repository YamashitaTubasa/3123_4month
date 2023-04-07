#pragma once

#include "Sprite.h"
#include "WinApp.h"

class PostEffect : public Sprite
{
private:
	struct ConstBufferData {
		Vector4 color; // �F (RGBA)
		Matrix4 mat; //���W
	};

public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	PostEffect();

	/// <summary>
	/// ������
	/// </summary>
	void Initialize();

	/// <summary>
	/// �`��R�}���h
	/// </summary>
	/// <param name="cmdList">�R�}���h���X�g</param>
	void Draw(ID3D12GraphicsCommandList* cmdList);

	/// <summary>
	/// �V�[���`��O����
	/// </summary>
	/// <param name="cmdList">�R�}���h���X�g</param>
	void PreDrawScene(ID3D12GraphicsCommandList* cmdList);

	/// <summary>
	/// �V�[���`��㏈��
	/// </summary>
	/// <param name="cmdList">�R�}���h���X�g</param>
	void PostDrawScene(ID3D12GraphicsCommandList* cmdList);

	/// <summary>
	/// �p�C�v���C������
	/// </summary>
	void CreateGraphicsPipelineState();

public:
	void SetColor(const Vector4& color) { this->color_ = color; }
	Vector4 GetColor() const { return color_; }

private:
	// �e�N�X�`���o�b�t�@
	ComPtr<ID3D12Resource> texBuff;
	// SRV�p�f�X�N���v�^�q�[�v
	ComPtr<ID3D12DescriptorHeap> descHeapSRV;
	// �k�x�o�b�t�@
	ComPtr<ID3D12Resource> depthBuff;
	// RTV�p�f�X�N���v�^�q�[�v
	ComPtr<ID3D12DescriptorHeap> descHeapRTV;
	// DSV�p�f�X�N���v�^�q�[�v
	ComPtr<ID3D12DescriptorHeap> descHeapDSV;
	// �O���t�B�N�X�p�C�v���C��
	ComPtr<ID3D12PipelineState> pipelineState;
	// ���[�g�V�O�l�`��
	ComPtr<ID3D12RootSignature> rootSignature;
	ComPtr<ID3D12Device> device;
	ComPtr<ID3D12GraphicsCommandList> cmdList;

protected:
	// ��ʃN���A�J���[
	static const float clearColor[4];
	// ���_��
	static const int vertNum = 4; 
	// �F
	Vector4 color_ = { 1,1,1,1 };
};

