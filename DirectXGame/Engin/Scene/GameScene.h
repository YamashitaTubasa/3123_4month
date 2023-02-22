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
	/// 初期化
	/// </summary>
	/// <param name="dXCommon"></param>
	void Initialize(DirectXCommon* dXCommon, WinApp* winApp, SpriteCommon& spriteCommon);

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
	void ObjectInitialize(Object3d* object,Model* model, const string& filename);

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
	/// スプライトの更新
	/// </summary>
	void SpriteUpdate();

	/// <summary>
	/// スプライトの描画
	/// </summary>
	void TitleDraw(DirectXCommon* dXCommon);
	void GameDraw(DirectXCommon* dXCommon);
	void GameClearDraw(DirectXCommon* dXCommon);
	void GameOverDraw(DirectXCommon* dXCommon);

	/// <summary>
	/// スプライトの解放
	/// </summary>
	void SpriteFinalize();

	// パーティクルの初期化
	void ParticleInitialize();

	void ParticleUpdate();

	void ParticleDraw(DirectXCommon* dXCommon);

	/// <summary>
	/// ゲームのリセット
	/// </summary>
	void GameReset();

	/// <summary>
	/// 当たり判定
	/// </summary>
	int CheckCollision(XMFLOAT3 object, XMFLOAT3 scale);

private:
	// 入力
	Input* input = nullptr;
	// モデル
	Model* model[5];
	// オブジェクト
	Object3d* object3d[5];
	// スプライト
	Sprite* sprite = nullptr;
	Sprite title;
	Sprite gameClear;
	Sprite gameOver;
	Sprite hP;
	Sprite hP1;
	SpriteCommon spriteCommon_;

	// パーティクル
	ParticleManager* particleMan = nullptr;

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
