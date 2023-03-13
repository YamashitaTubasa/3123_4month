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

public:// �T�u�N���X
// �萔�o�b�t�@�p�f�[�^�\����
	struct ConstBufferDataViewProjection {
		Matrix4 view;       // ���[���h �� �r���[�ϊ��s��
		Matrix4 projection; // �r���[ �� �v���W�F�N�V�����ϊ��s��
		Vector3 cameraPos;  // �J�������W�i���[���h���W�j
	};
public:

	// �ÓI������
	static void StaticInitialize(ID3D12Device* device);

	/// ������
	void Initialize();

	/// ���_���W�̎擾
	static const Vector3& GetEye() { return eye; }

	// �萔�o�b�t�@�̎擾
	ID3D12Resource* GetBuff() { return constBuff.Get(); }

	/// ���_���W�̐ݒ�
	static void SetEye(Vector3 eye);

	/// �����_���W�̎擾
	static const Vector3& GetTarget() { return target; }

	/// �����_���W�̐ݒ�
	static void SetTarget(Vector3 target);

	static const Matrix4& GetMatView() { return matView; }

	static const Matrix4& GetMatProjection() { return matProjection; }

	//�萔�o�b�t�@����
	void CreateConstBuffer();

	//�}�b�s���O
	void Map();

	/// �s����X�V����
	void UpdateMatrix();
	//���W�X�V
	void Update();

	//�ÓI�����o�ϐ�
private:
	static Matrix4 matView;
	// �ˉe�s��
	static Matrix4 matProjection;
	// ���_���W
	static Vector3 eye;
	// �����_���W
	static Vector3 target;
	// ������x�N�g��
	static Vector3 up;

private:
#pragma region �ˉe�s��̐ݒ�
	float PI = 3.141592;
	// ������������p
	float fovAngleY = 45.0f * PI / 180.0f;
	// �r���[�|�[�g�̃A�X�y�N�g��
	float aspectRatio = (float)16 / 9;
	// �[�x���E�i��O���j
	float nearZ = 0.1f;
	// �[�x���E�i�����j
	float farZ = 1000.0f;
#pragma endregion

	// �f�o�C�X�i�؂�Ă���j
	static Microsoft::WRL::ComPtr<ID3D12Device> device_;

	// �萔�o�b�t�@
	ComPtr<ID3D12Resource> constBuff;

	// �}�b�s���O�ς݃A�h���X
	ConstBufferDataViewProjection* constMap = nullptr;

};
