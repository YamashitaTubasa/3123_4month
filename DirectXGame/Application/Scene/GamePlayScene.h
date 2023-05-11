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
#include "Line.h"
#include "PostEffect.h"

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
	void Initialize(SpriteCommon& spriteCommon);

	/// <summary>
	/// 更新
	/// </summary>
	void Update(SpriteCommon& spriteCommon);

	/// <summary>
	/// 描画
	/// </summary>
	void Draw(SpriteCommon& spriteCommon);

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

	void TitleReset();

	static int GetScene() { return sceneNum; }

	void CreatThreeLine(std::vector<Vector3>& points);

	//補間で使うデータ
	//start → end を5秒で完了させる
	Vector3 start;		//スタート地点
	Vector3 p2;	//制御点その1
	Vector3 p3;	//制御点その2
	Vector3 p4;
	Vector3 p5;
	Vector3 p6;
	Vector3 p7;
	Vector3 p8;
	Vector3 p9;
	Vector3 end;	//ゴール地点

	//				p1 - p2 - p3 - p4 を通るスプライン曲線を考える
	//					先頭(p0)と最後(p5)に制御点を追加している
	//								p0	p1	p2	p3	p4	p5
	std::vector<Vector3> points{start,start,p2,p3,p4,p5,p6,p7,p8,p9,end,end};

	float timeRate;						//何％時間が進んだか

public:
	const bool& GetStartE() { return isStartE; }

private:
	// 入力
	Input* input = nullptr;
	// モデル
	Model* floorModel;
	Model* skyModel;
	Model* lineModel[3];
	// オブジェクト
	Player* player;
	Enemy* enemy;
	Object3d* floor;
	Object3d* sky;
	Line* line[3];
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
	Sprite gaugeFlame;
	Sprite gauge;
	Sprite board;
	Sprite effectL[6];
	Sprite effectR[6];
	Sprite title;
	Sprite clear;
	Sprite over;
	Sprite back;
	Sprite spaButton;
	Sprite airRing;
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

	PostEffect* postEffect_ = nullptr;

	Vector3 position[5]{};
	Vector3 rotation[5]{};
	Vector3 scale[5]{};

	//敵
	std::list<std::unique_ptr<Enemy>> enemys_;

	//敵の打ち出すまでの時間
	float enemyDalayTimer = 0.0f;

	bool isWait_ = false;

	int waitTimer = 300;

	//ゲージ
	Vector2 gaugeScale = { 3,25 };

	Vector3 gaugePosition = { 50,167.5f,0 };

	//攻撃エフェクト
	Vector2 airScale = { 0,0 };

	Vector3 airPosition = { 0,0,0 };

	//敵発生コマンド
	std::stringstream enemyPopCommands;

	const float PI = 3.141592;

	float alpha = 1;

	static int sceneNum;


	bool isMaxGauge = false;

	bool isRing = false;
	bool isBack = false; // ダメージ演出フラグ
	float backT = 0.0f; // ダメージ演出タイマー
	bool isStartE = false; // startEffectフラグ
	float startE = 0.0f; // startEffect
	bool isGClearE = false; // gClearEffectフラグ
	float gClearE = 0.0f; // gClearEffect
	bool isGOverE = false; // gOverEffectフラグ
	float gOverE = 0.0f; // gOverEffect
	int isDeadT = 0.0f;
	float pAlpha = 1.0f; // ポストエフェクトアルファ
	Vector4 pColor = { 0,0,0,1 };

	float calRes = 0.0f;

	int titleT = 0.0f;
	bool isTitleT = false;
	bool isPlayerE = true;
	bool isClearStaging = false; // クリア演出のフラグ
	int cStagingT = 0.0f; // クリア演出のタイマー
};