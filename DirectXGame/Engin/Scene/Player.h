#pragma once

#include "Input.h"
#include "WinApp.h"
#include "DirectXCommon.h"
#include "Object3d.h"
#include "Model.h"
#include "Vector3.h"

using namespace DirectX;

class Player
{
public:
	Player();
	~Player();

public:
	/// <summary>
	/// ������
	/// </summary>
	/// <param name="dXCommon"></param>
	void Initialize(WinApp* winApp);

	/// <summary>
	/// �X�V
	/// </summary>
	void Update();

	/// <summary>
	/// �`��
	/// </summary>
	void Draw();

	//XMFLOAT3�ϊ�
	XMFLOAT3 ConversionVec(Vector3 vec);
	Vector3 ConversionVec(XMFLOAT3 xVec);
	//���ʃx�N�g���擾
	XMFLOAT3 GetFront(XMFLOAT3 a, XMFLOAT3 b);
	XMFLOAT3 GetRight(XMFLOAT3 a, XMFLOAT3 b);
	XMFLOAT3 GetLeft(XMFLOAT3 a, XMFLOAT3 b);

private:
	// ����
	Input* input = nullptr;
	// ���f��
	Model* playerModel;
	// �I�u�W�F�N�g
	Object3d* player;
};