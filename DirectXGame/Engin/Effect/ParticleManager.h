#pragma once

#include "Particle.h"
#include "XMViewProjection.h"
#include <Windows.h>
#include <wrl.h>
#include <d3d12.h>
#include <DirectXMath.h>
#include <d3dx12.h>

/// 3D�I�u�W�F�N�g
class ParticleManager
{
private: // �G�C���A�X
	// Microsoft::WRL::���ȗ�
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	// DirectX::���ȗ�
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;

public: // �T�u�N���X
	// �萔�o�b�t�@�p�f�[�^�\����
	struct ConstBufferData
	{
		//XMFLOAT4 color;	// �F (RGBA)
		XMMATRIX mat;	// �R�c�ϊ��s��
		XMMATRIX matBillboard;	//�r���{�[�h�s��
	};
public: // �ÓI�����o�֐�
	/// �ÓI������
	static void StaticInitialize(ID3D12Device* device);

	/// �`��O����
	static void PreDraw(ID3D12GraphicsCommandList* cmdList);

	/// �`��㏈��
	static void PostDraw();

	/// 3D�I�u�W�F�N�g����
	static ParticleManager* Create();

private: // �ÓI�����o�ϐ�
	// �f�o�C�X
	static ID3D12Device* device_;
	// �R�}���h���X�g
	static ID3D12GraphicsCommandList* cmdList;
	// ���[�g�V�O�l�`��
	static ComPtr<ID3D12RootSignature> rootsignature;
	// �p�C�v���C���X�e�[�g�I�u�W�F�N�g
	static ComPtr<ID3D12PipelineState> pipelinestate;

private:// �ÓI�����o�֐�

	/// �O���t�B�b�N�p�C�v���C������
	static void InitializeGraphicsPipeline();

public: // �����o�֐�
	bool Initialize();
	/// ���t���[������
	void Update();

	/// �`��
	void Draw();

	/// �p�[�e�B�N������
	void Fire(Particle* particle, const float& setpos, const float& setvel, const float& setacc, const int& setnum, const XMFLOAT2& setscale);

private: // �����o�ϐ�
	ComPtr<ID3D12Resource> constBuff; // �萔�o�b�t�@
	//�X�P�[��
	XMFLOAT3 scale = { 1,1,1 };

	//DirectXMath���g����ViewProjection
	XMViewProjection* xmViewProjection;
	//�p�[�e�B�N��
	Particle* particle;

public://setter
	//�p�[�e�B�N�����f��
	void SetParticleModel(Particle* particlemodel) { this->particle = particlemodel; }
	//�J����
	void SetXMViewProjection(XMViewProjection* xmViewProjection) { this->xmViewProjection = xmViewProjection; }
};