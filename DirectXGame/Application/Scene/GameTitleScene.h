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
#include "GameBaseScene.h"

//====================//
// �Q�[���^�C�g���V�[��
//====================//
class GameTitleScene 
{
public:
	GameTitleScene();
	~GameTitleScene();

public:
	/// <summary>
	/// ������
	/// </summary>
	/// <param name="dXCommon"></param>
	void Initialize(DirectXCommon* dXCommon, WinApp* winApp, SpriteCommon& spriteCommon) ;

	/// <summary>
	/// �X�V
	/// </summary>
	void Update() ;

	/// <summary>
	/// �`��
	/// </summary>
	void Draw(DirectXCommon* dXCommon) ;

	/// <summary>
	/// ���
	/// </summary>
	void Finalize() ;

private:
	// ����
	Input* input = nullptr;
	// �X�v���C�g
	Sprite* sprite = nullptr;
	Sprite Title;
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
};