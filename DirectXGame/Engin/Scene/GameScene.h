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
	void ObjectInitialize();

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

	//XMFLOAT3変換
	XMFLOAT3 ConversionVec(Vector3 vec);
	Vector3 ConversionVec(XMFLOAT3 xVec);
	//正面ベクトル取得
	XMFLOAT3 GetFront(XMFLOAT3 a, XMFLOAT3 b);
	XMFLOAT3 GetRight(XMFLOAT3 a, XMFLOAT3 b);
	XMFLOAT3 GetLeft(XMFLOAT3 a, XMFLOAT3 b);

private:
	// 入力
	Input* input = nullptr;
	// モデル
	Model* playerModel;
	Model* skyModel;
	// オブジェクト
	Object3d* player;
	Object3d* tester;
	Object3d* sky;
	// スプライト
	Sprite* sprite = nullptr;
	Sprite title;
	Sprite gameClear;
	Sprite gameOver;
	Sprite hP;
	Sprite hP1;
	SpriteCommon spriteCommon_;

	Player* pl = nullptr;

	// パーティクル
	ParticleManager* particleMan = nullptr;

	DirectXCommon* dXCommon = nullptr;

	ImGuiManager* imGuiManager = nullptr;

	const float PI = 3.141592;

	Quaternion playerRote;

	int time = 0;
};