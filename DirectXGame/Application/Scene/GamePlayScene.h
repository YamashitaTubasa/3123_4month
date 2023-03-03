#pragma once

#include "Input.h"
#include "WinApp.h"
#include "DirectXCommon.h"
#include "Object3d.h"
#include "Model.h"
#include "Sprite.h"
#include "ImGuiManager.h"
#include "Vector3.h"
#include "ParticleManager.h"
#include "ViewProjection.h"

class GamePlayScene
{
public:
	GamePlayScene();
	~GamePlayScene();

public:
	/// <summary>
	/// ������
	/// </summary>
	/// <param name="dXCommon"></param>
	void Initialize(DirectXCommon* dXCommon, WinApp* winApp, SpriteCommon& spriteCommon, Input* input);

	/// <summary>
	/// �X�V
	/// </summary>
	void Update();

	/// <summary>
	/// �`��
	/// </summary>
	void Draw(DirectXCommon* dXCommon);

	/// <summary>
	/// ���
	/// </summary>
	void Finalize();
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
	Model* skyModel;
	// �I�u�W�F�N�g
	Object3d* player;
	Object3d* tester;
	Object3d* sky;
	//�J����
	ViewProjection* viewProjection = nullptr;
	// �X�v���C�g
	Sprite* sprite = nullptr;
	Sprite hP;
	SpriteCommon spriteCommon_;

	DirectXCommon* dXCommon = nullptr;
	ImGuiManager* imGuiManager = nullptr;
	ParticleManager* ParticleMan = nullptr;

	XMFLOAT3 position[5]{};
	XMFLOAT3 rotation[5]{};
	XMFLOAT3 scale[5]{};

	bool isPush_D = false;
	bool isPush_A = false;

	int playerHp = 3;
	int time = 0;

	const float PI = 3.141592;
};