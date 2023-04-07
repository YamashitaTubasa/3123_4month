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
#include "Player.h"
#include "Enemy.h"
#include <sstream>

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

	/// 敵発生
	void EnemyOcurrence(const Vector3& v);

	//敵発生データの読み込み
	void LoadEnemyPopData();

	//敵発生コマンドの更新
	void UpdateEnemyPopCommands();

	void LoadEffect(SpriteCommon& spriteCommon);

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
	Model* skyModel;
	Model* stageModel;
	// オブジェクト
	Player* player;
	Enemy* enemy;
	Object3d* sky;
	Object3d* stage;
	//カメラ
	ViewProjection* viewProjection = nullptr;
	RailCamera* railCamera = nullptr;
	//座標
	WorldTransform* worldTransform = nullptr;
	// スプライト
	Sprite* sprite = nullptr;
	Sprite hP;
	Sprite effectL[6];
	Sprite effectR[6];
	SpriteCommon spriteCommon_;

	DirectXCommon* dXCommon = nullptr;
	ImGuiManager* imGuiManager = nullptr;
	ParticleManager* ParticleMan = nullptr;
	WinApp* winApp = nullptr;

	Vector3 position[5]{};
	Vector3 rotation[5]{};
	Vector3 scale[5]{};

	//敵
	std::list<std::unique_ptr<Enemy>> enemys_;

	//敵の打ち出すまでの時間
	float enemyDalayTimer = 0.0f;

	bool isWait_ = false;

	int waitTimer = 300;

	//敵発生コマンド
	std::stringstream enemyPopCommands;

	bool isPush_D = false;
	bool isPush_A = false;

	int playerHp = 3;

	const float PI = 3.141592;

	float alpha = 1;
};