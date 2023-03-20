#pragma once

#include "Input.h"
#include "WinApp.h"
#include "DirectXCommon.h"
#include "Object3d.h"
#include "Model.h"
#include "Sprite.h"
#include "SpriteCommon.h"
#include "ImGuiManager.h"
#include "Vector3.h"
#include "ParticleManager.h"
#include "GameBaseScene.h"
#include "ViewProjection.h"

//====================//
// ゲームプレイシーン
//====================//
class GamePlayScene
{
public:
	GamePlayScene();
	~GamePlayScene();

public:
	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="dXCommon"></param>
	void Initialize();

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw() ;

	/// <summary>
	/// 解放
	/// </summary>
	void Finalize();
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
	//カメラ
	ViewProjection* viewProjection = nullptr;
	// スプライト
	SpriteCommon* spriteCommon_ = nullptr;

	DirectXCommon* dXCommon = nullptr;
	ImGuiManager* imGuiManager = nullptr;
	ParticleManager* ParticleMan = nullptr;
	WinApp* winApp = nullptr;

	XMFLOAT3 position[5]{};
	XMFLOAT3 rotation[5]{};
	XMFLOAT3 scale[5]{};

	bool isPush_D = false;
	bool isPush_A = false;

	int playerHp = 3;
	int time = 0;

	const float PI = 3.141592;
};