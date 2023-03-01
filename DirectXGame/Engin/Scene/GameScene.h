#pragma once

#include "Input.h"
#include "WinApp.h"
#include "DirectXCommon.h"
#include "Object3d.h"
#include "Model.h"
#include "Sprite.h"
#include "ParticleManager.h"
#include "ImGuiManager.h"
#include "Vector3.h"
#include "Player.h"
#include "Quaternion.h"

class GameScene
{
private:
	enum Scene {
		Title,
		Scene_1,
		GameClear,
		GameOver
	};
	Scene scene;

public:
	GameScene();
	~GameScene();

public:
	/// <summary>
	/// ������
	/// </summary>
	/// <param name="dXCommon"></param>
	void Initialize(DirectXCommon* dXCommon, WinApp* winApp, SpriteCommon& spriteCommon);

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

	/// <summary>
	/// �I�u�W�F�N�g�̏�����
	/// </summary>
	/// <param name="dXCommon"></param>
	void ObjectInitialize();

	/// <summary>
	/// �I�u�W�F�N�g�̍X�V
	/// </summary>
	void ObjectUpdate();

	/// <summary>
	/// �I�u�W�F�N�g�̕`��
	/// </summary>
	void ObjectDraw(DirectXCommon* dXCommon);

	/// <summary>
	/// �I�u�W�F�N�g�̉��
	/// </summary>
	void ObjectFinalize();

	/// <summary>
	/// �X�v���C�g������
	/// </summary>
	void SpriteInitialize(DirectXCommon* dXCommon, SpriteCommon& spriteCommon);

	/// <summary>
	/// �X�v���C�g�̍X�V
	/// </summary>
	void SpriteUpdate();

	/// <summary>
	/// �X�v���C�g�̕`��
	/// </summary>
	void TitleDraw(DirectXCommon* dXCommon);
	void GameDraw(DirectXCommon* dXCommon);
	void GameClearDraw(DirectXCommon* dXCommon);
	void GameOverDraw(DirectXCommon* dXCommon);

	/// <summary>
	/// �X�v���C�g�̉��
	/// </summary>
	void SpriteFinalize();

	// �p�[�e�B�N���̏�����
	void ParticleInitialize();

	void ParticleUpdate();

	void ParticleDraw(DirectXCommon* dXCommon);

	/// <summary>
	/// �Q�[���̃��Z�b�g
	/// </summary>
	void GameReset();

	/// <summary>
	/// �����蔻��
	/// </summary>
	int CheckCollision(XMFLOAT3 object, XMFLOAT3 scale);

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
	// �X�v���C�g
	Sprite* sprite = nullptr;
	Sprite title;
	Sprite gameClear;
	Sprite gameOver;
	Sprite hP;
	Sprite hP1;
	SpriteCommon spriteCommon_;

	Player* pl = nullptr;

	// �p�[�e�B�N��
	ParticleManager* particleMan = nullptr;

	DirectXCommon* dXCommon = nullptr;

	ImGuiManager* imGuiManager = nullptr;

	const float PI = 3.141592;

	Quaternion playerRote;

	int time = 0;
};