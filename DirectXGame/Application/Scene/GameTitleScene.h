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
// ゲームタイトルシーン
//====================//
class GameTitleScene 
{
public:
	GameTitleScene();
	~GameTitleScene();

public:
	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="dXCommon"></param>
	void Initialize() ;

	/// <summary>
	/// 更新
	/// </summary>
	void Update() ;

	/// <summary>
	/// 描画
	/// </summary>
	void Draw() ;

	/// <summary>
	/// 解放
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