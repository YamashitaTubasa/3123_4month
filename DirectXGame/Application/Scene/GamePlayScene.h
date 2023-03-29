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
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "RailCamera.h"

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
	void Initialize(SpriteCommon& spriteCommon) ;

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
	//XMFLOAT3 ConversionVec(Vector3 vec);
	//Vector3 ConversionVec(XMFLOAT3 xVec);
	//正面ベクトル取得
	Vector3 GetFront(Vector3 a, Vector3 b);
	Vector3 GetRight(Vector3 a, Vector3 b);
	Vector3  GetLeft(Vector3 a, Vector3 b);

	//補間で使うデータ
	//start → end を5秒で完了させる
	Vector3 start;		//スタート地点
	Vector3 p2;	//制御点その1
	Vector3 p3;	//制御点その2
	Vector3 p4;
	Vector3 end;	//ゴール地点

	//				p1 - p2 - p3 - p4 を通るスプライン曲線を考える
	//					先頭(p0)と最後(p5)に制御点を追加している
	//								p0	p1	p2	p3	p4	p5
	std::vector<Vector3> points{ start,start,p2,p3,p4,end,end };

	float timeRate;						//何％時間が進んだか

private:
	// 入力
	Input* input = nullptr;
	// モデル
	Model* playerModel;
	Model* skyModel;
	// オブジェクト
	//Object3d* player;
	Object3d* player;
	Object3d* sky;
	//カメラ
	ViewProjection* viewProjection = nullptr;
	RailCamera* railCamera = nullptr;
	//座標
	WorldTransform* worldTransform = nullptr;
	// スプライト
	Sprite* sprite = nullptr;
	Sprite hP;
	SpriteCommon spriteCommon_;

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