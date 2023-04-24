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
#include "Enemy.h"
#include <sstream>
#include "PlayerAttack.h"

//====================//
// ゲームプレイシーン
//====================//

class CollisionManager;
class Player;

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
	void Draw(SpriteCommon& spriteCommon) ;

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

	void Reset();

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

public:
	const bool& GetSartE() { return isStartE; }

private:
	// 入力
	Input* input = nullptr;
	// モデル
	Model* skyModel;
	Model* stageModel;
	Model* lineModel;
	// オブジェクト
	Player* player;
	PlayerAttack* playerAttack;
	Enemy* enemy;
	Object3d* sky;
	Object3d* stage;
	Object3d* line;
	//カメラ
	ViewProjection* viewProjection = nullptr;
	RailCamera* railCamera = nullptr;
	XMViewProjection* xmViewProjection = nullptr;
	//座標
	WorldTransform* worldTransform = nullptr;
	//当たり判定
	CollisionManager* collisionManager = nullptr;

	// スプライト
	Sprite* sprite = nullptr;
	Sprite hP[3];
	Sprite effectL[6];
	Sprite effectR[6];
	Sprite title;
	Sprite clear;
	Sprite over;
	Sprite back;
	SpriteCommon spriteCommon_;

	DirectXCommon* dXCommon = nullptr;
	ImGuiManager* imGuiManager = nullptr;
	//パーティクル
	Particle* particle_1 = nullptr;
	ParticleManager* pm_1 = nullptr;
	Particle* particle_2 = nullptr;
	ParticleManager* pm_2 = nullptr;
	Particle* p_dmg = nullptr;
	ParticleManager* pm_dmg = nullptr;
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

	const float PI = 3.141592;

	float alpha = 1;

	int sceneNum = 0;
	bool isBack = false; // ダメージ演出フラグ
	float backT = 0.0f; // ダメージ演出タイマー
	bool isStartE = false; // startEffectフラグ
	float startE = 0.0f; // startEffect
	int isDeadT = 0.0f;
};