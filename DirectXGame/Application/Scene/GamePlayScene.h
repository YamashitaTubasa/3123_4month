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
#include "InvisibleEnemy.h"
#include <sstream>
#include "Line.h"
#include "PostEffect.h"
#include "Audio.h"

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

	//発生データの読み込み
	void LoadEnemy(int stageNum);
	void LoadStage(int stageNum);
	void LoadBuil(int stageNum);

	//フィーバーエフェクト
	void LoadEffect(SpriteCommon& spriteCommon);

	//攻撃エフェクト
	void LoadAttackEffect(SpriteCommon& spriteCommon);

	// フェードアウト処理
	void FadeOut(float pColor_, float fadeOutTimer_);
	void FadeIn(float pColor_, float fadeInTimer_);

	//ステージ選択
	void StageSelect();

	void Reset();

	static int GetScene() { return sceneNum; }
	static int GetTutorialStep() { return tutorialStep; }
	static bool GetIsBack() { return isBack; }
	static void SetIsBack(bool isBack_) { isBack = isBack_; }

	void CreatThreeLine(std::vector<Vector3>& points);

	void TutorialUpdate();

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
	std::vector<Vector3> pointsL;
	std::vector<Vector3> pointsR;

	float timeRate;						//何％時間が進んだか

private:
	// 入力
	Input* input = nullptr;
	// モデル
	Model* floorModel;
	Model* skyModel;
	Model* lineModel;
	Model* builModel01;
	Model* builModel02;
	Model* builModel03;
	Model* builModel04;
	Model* stageModel[11];

	// オブジェクト
	Player* player;
	Enemy* enemy;
	InvisibleEnemy* invEnemy;
	Object3d* floor;
	Object3d* sky;
	Object3d* buil;
	Object3d* stageObj[11];
	
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
	Sprite HPframe;
	Sprite gaugeFlame;
	Sprite gauge;
	Sprite diagonalFrame;
	Sprite board;
	Sprite effectL[6];
	Sprite effectR[6];
	Sprite title;
	Sprite clear;
	Sprite over;
	Sprite back;
	Sprite titleBack;
	Sprite stageBack;
	Sprite close;
	Sprite pause;
	Sprite spaButton;
	SpriteCommon spriteCommon_;
	Sprite attackEffect[8];
	Sprite lUi;
	Sprite rUi;
	Sprite spUi;


	//-----チュートリアルスプライト-----//

	//テキストボックス
	Sprite textBox;
	Sprite AorD;

	//攻撃方法(2ページ)
	Sprite attackMethod_First;
	Sprite attackMethod_Second;	//2回使う方

	//クリア方法
	Sprite clearMethod;

	//倒せない敵
	Sprite enemyCaution;
	Sprite enemyCaution_;

	//フィーバー終了(2ページ)
	Sprite feverEnd_First;
	Sprite feverEnd_Second;

	//フィーバー開始(2ページ)
	Sprite feverMode_First;
	Sprite feverMode_Second;
	Sprite feverMode_Third;

	//プレイヤーダメージ(2ページ)
	Sprite playerDamage_First;
	Sprite playerDamage_Second;

	//移動
	Sprite playerMove_First;
	Sprite playerMove_Second;	//2回使う方

	//最初の挨拶
	Sprite welcomeGame;

	Sprite pauseP;

	//---------------------------------//
	Audio* titleBGM = nullptr;
	//---------------------------------//

	DirectXCommon* dXCommon = nullptr;
	ImGuiManager* imGuiManager = nullptr;
	//パーティクル
	Particle* particle_1 = nullptr;
	ParticleManager* pm_1 = nullptr;
	Particle* particle_2 = nullptr;
	ParticleManager* pm_2 = nullptr;
	Particle* p_dmg = nullptr;
	ParticleManager* pm_dmg = nullptr;
	Particle* pBomb = nullptr;
	ParticleManager* pBombM = nullptr;
	Particle* pFire = nullptr;
	ParticleManager* pFireM = nullptr;
	WinApp* winApp = nullptr;

	PostEffect* postEffect_ = nullptr;

	Vector3 p{};
	Vector3 particleP{};
	int pTimer = 0;
	bool isP = false;
	
	Vector3 position[5]{};
	Vector3 rotation[5]{};
	Vector3 scale[5]{};

	std::list<std::unique_ptr<InvisibleEnemy>> invEnemys_;
	std::list<std::unique_ptr<Enemy>> enemys_;
	std::list<std::unique_ptr<Object3d>> buils_;

	//ゲージ
	Vector2 gaugeScale = { 3,10 };

	Vector3 gaugePosition = { 40,76,0 };

	//攻撃エフェクト
	Vector2 airScale = { 0,0 };

	Vector3 airPosition = { 0,0,0 };

	const float PI = 3.141592;

	float alpha = 1;

	bool isPushKey = false;

	static int sceneNum;


	bool isMaxGauge = false;
	static bool isBack;           // ダメージ演出フラグ
	int backT = 0;                // ダメージ演出タイマー
	bool isFadeOut = false;       // フェードアウト処理フラグ
	int fadeOut = 0;              // フェードアウト処理タイマー
	bool isFadeIn = false;        // フェードイン処理フラグ
	int fadeIn = 0;               // フェードイン処理タイマー
	int fadeTimer = 0;            // フェードアウト処理フラグ
	bool isFade = false;		  // フェードアウト処理タイマー
	bool isTitleT = false;        // タイトル画面の演出フラグ
	int titleT = 0;               // タイトル画面の演出タイマー
	bool isClearStaging = false;  // クリア演出フラグ
	int cStagingT = 0;            // クリア演出タイマー
	bool isOStaging = false;      // ゲームオーバー画面演出フラグ
	int oStagingT = 0;            // ゲームオーバー画面演出タイマー
	int isDeadT = 0;              // 敵を倒したかのフラグ
	float pAlpha = 1.0f;          // ポストエフェクトアルファ
	Vector4 pColor = { 0,0,0,1 }; // ポストエフェクトカラー
	int blurT = 0;                // ポストエフェクトブラータイマー
	bool isBlur = false;          // ポストエフェクトブラーフラグ

	float calRes = 0.0f;

	//ポーズ
	int selectPause;
	//チュートリアル
	static int tutorialStep;
	int tutoTime;
	bool isShowText;
	int tutoText;


	//タイトル画面のタイマー
	float titleTimer;

	//ステージ
	int stageNum;
	//セレクト画面
	float selectTime;
	int isMoveSel;
	Vector3 selPlayerTmp;
	Vector3 selEyeTmp;
	Vector3 selTargetTmp;
};