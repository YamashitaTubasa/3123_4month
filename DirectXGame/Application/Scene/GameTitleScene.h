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
	void Initialize(DirectXCommon* dXCommon, WinApp* winApp, SpriteCommon& spriteCommon) ;

	/// <summary>
	/// 更新
	/// </summary>
	void Update() ;

	/// <summary>
	/// 描画
	/// </summary>
	void Draw(DirectXCommon* dXCommon) ;

	/// <summary>
	/// 解放
	/// </summary>
	void Finalize() ;

private:
	// 入力
	Input* input = nullptr;
	// スプライト
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