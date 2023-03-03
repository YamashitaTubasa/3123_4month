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

	static void Update();

public:
	/// <summary>
	/// ������
	/// </summary>
	void Initialize(int window_width, int window_height);
	/// <summary>
	/// �s����X�V����
	/// </summary>
	


	/// <summary>
	/// ���_���W�̎擾
	/// </summary>
	/// <returns>���W</returns>
	static const XMFLOAT3& GetEye() { return eye; }

	/// <summary>
	/// ���_���W�̐ݒ�
	/// </summary>
	/// <param name="position">���W</param>
	static void SetEye(XMFLOAT3 eye);

	/// <summary>
	/// �����_���W�̎擾
	/// </summary>
	/// <returns>���W</returns>
	static const XMFLOAT3& GetTarget() { return target; }

	/// <summary>
	/// �����_���W�̐ݒ�
	/// </summary>
	/// <param name="position">���W</param>
	static void SetTarget(XMFLOAT3 target);

	static const XMMATRIX& GetMatView() { return matView; }

	static const XMMATRIX& GetMatProjection() { return matProjection; }
};
