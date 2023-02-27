#pragma once

#include "Input.h"
#include "WinApp.h"
#include "DirectXCommon.h"
#include "Object3d.h"
#include "Model.h"
#include "Sprite.h"
#include "ImGuiManager.h"
#include "Vector3.h"

class GameScene
{
public:
	GameScene();
	~GameScene();

public:
	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="dXCommon"></param>
	void Initialize(DirectXCommon* dXCommon, WinApp* winApp, SpriteCommon& spriteCommon, Input* input);

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw(DirectXCommon* dXCommon);

	/// <summary>
	/// 解放
	/// </summary>
	void Finalize();

	/// <summary>
	/// オブジェクトの初期化
	/// </summary>
	/// <param name="dXCommon"></param>
	void ObjectInitialize(DirectXCommon* dXCommon);

	/// <summary>
	/// オブジェクトの更新
	/// </summary>
	void ObjectUpdate();

	/// <summary>
	/// オブジェクトの描画
	/// </summary>
	void ObjectDraw(DirectXCommon* dXCommon);

	/// <summary>
	/// オブジェクトの解放
	/// </summary>
	void ObjectFinalize();

	/// <summary>
	/// スプライト初期化
	/// </summary>
	void SpriteInitialize(DirectXCommon* dXCommon, SpriteCommon& spriteCommon);

	/// <summary>
	/// スプライトの描画
	/// </summary>
	void GameDraw(DirectXCommon* dXCommon);

	/// <summary>
	/// スプライトの解放
	/// </summary>
	void SpriteFinalize();

private:
	// 入力
	Input* input = nullptr;
	// モデル
	Model* Model[5];
	// オブジェクト
	Object3d* object3d[5];
	// スプライト
	Sprite* sprite = nullptr;
	Sprite hP;
	SpriteCommon spriteCommon_;

	DirectXCommon* dXCommon = nullptr;
	ImGuiManager* imGuiManager = nullptr;

	XMFLOAT3 position[5]{};
	XMFLOAT3 rotation[5]{};
	XMFLOAT3 scale[5]{};

	bool isPush_D = false;
	bool isPush_A = false;

	int playerHp = 3;
	int time = 0;
};
