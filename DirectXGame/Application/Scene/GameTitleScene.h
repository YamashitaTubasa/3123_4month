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
	void Initialize() ;

	/// <summary>
	/// �X�V
	/// </summary>
	void Update() ;

	/// <summary>
	/// �`��
	/// </summary>
	void Draw() ;

	/// <summary>
	/// ���
	/// </summary>
	void Finalize() ;

private:
	Input* input = nullptr;
	Sprite* sprite = nullptr;
	DirectXCommon* dXCommon = nullptr;
	ImGuiManager* imGuiManager = nullptr;
	ParticleManager* ParticleMan = nullptr;
	Object3d* object3d = nullptr;
	Model* model = nullptr;
};