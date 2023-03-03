#pragma once

#include <d3dx12.h>
#include <d3d12.h>
#include <wrl.h>
#include "Matrix4.h"
#include "Vector3.h"
#include <DirectXMath.h>
#include <Windows.h>
#include <string>

using namespace DirectX;

/// <summary>
/// �r���[�v���W�F�N�V�����ϊ��f�[�^
/// </summary>
class ViewProjection {

private:
	// Microsoft::WRL::���ȗ�
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
private:
	// �}�b�s���O�ς݃A�h���X
	/*ConstBufferDataViewProjection* constMap = nullptr;*/


public: // �T�u�N���X

	// �萔�o�b�t�@�p�f�[�^�\����
	struct ConstBufferDataViewProjection {
		Matrix4 view;       // ���[���h �� �r���[�ϊ��s��
		Matrix4 projection; // �r���[ �� �v���W�F�N�V�����ϊ��s��
		Vector3 cameraPos;  // �J�������W�i���[���h���W�j
	};
#pragma endregion
private:
#pragma region �ˉe�s��̐ݒ�
	float PI = 3.141592;
	// ������������p
	float fovAngleY = 45.0f *  PI / 180.0f;
	// �r���[�|�[�g�̃A�X�y�N�g��
	float aspectRatio = (float)16 / 9;
	// �[�x���E�i��O���j
	float nearZ = 0.1f;
	// �[�x���E�i�����j
	float farZ = 1000.0f;
	// �萔�o�b�t�@
	ComPtr<ID3D12Resource> constBuffB0;
#pragma endregion
	//�ÓI�����o�ϐ�
private:
	static XMMATRIX matView;
	// �ˉe�s��
	static XMMATRIX matProjection;
	// ���_���W
	static XMFLOAT3 eye;
	// �����_���W
	static XMFLOAT3 target;
	// ������x�N�g��
	static XMFLOAT3 up;
	// �f�o�C�X
	static ID3D12Device* device;

public:
	/// <summary>
	/// ������
	/// </summary>
	void Initialize(int window_width, int window_height);
	/// <summary>
	/// �萔�o�b�t�@����
	/// </summary>
	bool CreateConstBuffer();
	/// <summary>
	/// �}�b�s���O����
	/// </summary>
	void Map();
	/// <summary>
	/// �s����X�V����
	/// </summary>
	void Update();
	/// <summary>
	/// �s���]������
	/// </summary>
	void InitializeGraphicsPipeline();
};
