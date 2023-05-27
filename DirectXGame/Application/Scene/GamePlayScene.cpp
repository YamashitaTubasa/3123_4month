#include "GamePlayScene.h"
#include "spline.h"
#include <fstream>
#include "SphereCollider.h"
#include "CollisionManager.h"
#include "Player.h"
#include "WorldTransform.h"
#include "Spline.h"
int GamePlayScene::sceneNum = 0;
int GamePlayScene::tutorialStep = 0;
bool GamePlayScene::isBack = false;

GamePlayScene::GamePlayScene() {
}

GamePlayScene::~GamePlayScene() {
}

void GamePlayScene::Initialize(SpriteCommon& spriteCommon) {
	dXCommon = DirectXCommon::GetInstance();
	winApp = WinApp::GetInstance();
	input = Input::GetInstance();
	//当たり判定
	collisionManager = CollisionManager::GetInstance();

	railCamera = new RailCamera;
	xmViewProjection = new XMViewProjection();

	// ポストエフェクト
	postEffect_ = PostEffect::GetInstance();

	// OBJからモデルデータを読み込む
	//床
	floorModel = Model::LoadFromOBJ("floor");
	//天球
	skyModel = Model::LoadFromOBJ("skydome");

	builModel01 = Model::LoadFromOBJ("building_01");
	builModel02 = Model::LoadFromOBJ("building_02");
	builModel03 = Model::LoadFromOBJ("building_03");
	builModel04 = Model::LoadFromOBJ("ring");
	sphere = Model::LoadFromOBJ("triangle_mat");

	// 3Dオブジェクト生成
	//床
	floor = Object3d::Create();
	// オブジェクトにモデルをひも付ける
	floor->SetModel(floorModel);
	floor->SetPosition(Vector3(0, -80, 0));
	floor->SetScale(Vector3({ 1000, 1000, 1000 }));
	//天球
	sky = Object3d::Create();
	// オブジェクトにモデルをひも付ける
	sky->SetModel(skyModel);
	sky->SetScale(Vector3({ 1000, 1000, 1000 }));

	//player初期化
	player = new Player;
	player->PlayerInitialize();
	//半径分だけ足元から浮いた座標を球の中心にする
	player->SetCollider(new SphereCollider);

	//ステージモデル
	for (int i = 0; i < 11; i++) {
		std::unique_ptr<Object3d> newStage = std::make_unique<Object3d>();
		newStage->Initialize();
		newStage->SetModel(sphere);
		newStage->SetScale(Vector3{ 7,7,7 });
		if (i == 0) {
			newStage->SetPosition({ -597,-5,-660 });
		}
		else if(i == 1) {
			newStage->SetPosition({ -550 ,-5,-660 });
		}
		else if (i == 2) {
			newStage->SetPosition({ -502,-5,-660 });
		}
		else if(i == 3) {
			newStage->SetPosition({ -470 ,-5,-660 });
		}
		else if (i == 4) {
			newStage->SetPosition({ -425,-5,-660 });
		}
		else if (i == 5) {
			newStage->SetPosition({ -383,-5,-660 });
		}
		else if (i == 6) {
			newStage->SetPosition({ -345 ,-5,-660 });
		}
		else if (i == 7) {
			newStage->SetPosition({ -301 ,-5,-660 });
		}
		else if (i == 8) {
			newStage->SetPosition({ -259 ,-5,-660 });
		}
		else if (i == 9) {
			newStage->SetPosition({ -215 ,-5,-660 });
		}
		else if (i == 10) {
			newStage->SetPosition({ -177,-5,-660 });
		}
		else {
			newStage->SetPosition({ -550 ,-5,-660 });
		}
		stages_.push_back(std::move(newStage));
	}

	//パーティクル初期化
	particle_1 = Particle::LoadParticleTexture("effect1.png");
	pm_1 = ParticleManager::Create();
	particle_2 = Particle::LoadParticleTexture("effect2.png");
	pm_2 = ParticleManager::Create();
	p_dmg = Particle::LoadParticleTexture("dmg.png");
	pm_dmg = ParticleManager::Create();
	pBomb = Particle::LoadParticleTexture("dmg.png");
	pBombM = ParticleManager::Create();
	pFire = Particle::LoadParticleTexture("dmg.png");
	pFireM = ParticleManager::Create();
	//オブジェクトにモデルを紐付ける
	pm_1->SetParticleModel(particle_1);
	pm_2->SetParticleModel(particle_2);
	pm_dmg->SetParticleModel(p_dmg);
	pBombM->SetParticleModel(pBomb);
	pFireM->SetParticleModel(pFire);
	//カメラをセット
	pm_1->SetXMViewProjection(xmViewProjection);
	pm_2->SetXMViewProjection(xmViewProjection);
	pm_dmg->SetXMViewProjection(xmViewProjection);
	pBombM->SetXMViewProjection(xmViewProjection);
	pFireM->SetXMViewProjection(xmViewProjection);

	// スプライトの初期化
	// スプライト
	sprite = new Sprite();
	spriteCommon_ = sprite->SpriteCommonCreate(dXCommon->GetDevice(), 1280, 720);
	// スプライト用パイプライン生成呼び出し
	PipelineSet spritePipelineSet = sprite->SpriteCreateGraphicsPipeline(dXCommon->GetDevice());

	// HP
	for (int i = 0; i < 3; i++) {
		hP[i].LoadTexture(spriteCommon_, 3, L"Resources/lineHP_03.png", dXCommon->GetDevice());
		hP[i].SpriteCreate(dXCommon->GetDevice(), 63, 20, 3, spriteCommon, Vector2(0.0f, 0.0f), false, false);
		hP[i].SetPosition(Vector3(40.0f + (i * 66.0f), 40.0f, 0.0f));
		hP[i].SetScale(Vector2(63.0f * 1.0f, 20.0f * 1.0f));
		hP[i].SetRotation(0.0f);
		hP[i].SpriteTransferVertexBuffer(hP[i], spriteCommon, 3);
		hP[i].SpriteUpdate(hP[i], spriteCommon_);
	}

	//gaugeFlame
	gaugeFlame.LoadTexture(spriteCommon_, 20, L"Resources/HPframe_03.png", dXCommon->GetDevice());
	gaugeFlame.SpriteCreate(dXCommon->GetDevice(), 204, 24, 20, spriteCommon, Vector2(0.0f, 0.0f), false, false);
	gaugeFlame.SetPosition(Vector3(35.0f, 64.0f, 0.0f));
	gaugeFlame.SetScale(Vector2(204.0f, 24.0f));
	gaugeFlame.SetRotation(0.0f);
	gaugeFlame.SpriteTransferVertexBuffer(gaugeFlame, spriteCommon, 20);
	gaugeFlame.SpriteUpdate(gaugeFlame, spriteCommon_);

	//gauge
	gauge.LoadTexture(spriteCommon_, 21, L"Resources/gauge_02.png", dXCommon->GetDevice());
	gauge.SpriteCreate(dXCommon->GetDevice(), 110, 10, 21, spriteCommon, Vector2(0.0f, 0.5f), false, false);
	gauge.SetPosition(Vector3(gaugePosition.x, gaugePosition.y, gaugePosition.z));
	gauge.SetScale(Vector2(gaugeScale.x, gaugeScale.y));
	gauge.SetRotation(0.0f);
	gauge.SpriteTransferVertexBuffer(gauge, spriteCommon, 21);
	gauge.SpriteUpdate(gauge, spriteCommon_);

	//HPframe
	HPframe.LoadTexture(spriteCommon_, 22, L"Resources/HPframe_03.png", dXCommon->GetDevice());
	HPframe.SpriteCreate(dXCommon->GetDevice(), 204, 24, 22, spriteCommon, Vector2(0.0f, 0.0f), false, false);
	HPframe.SetPosition(Vector3(35.0f, 38.0f, 0.0f));
	HPframe.SetScale(Vector2(204.0f, 24.0f));
	HPframe.SetRotation(0.0f);
	HPframe.SpriteTransferVertexBuffer(HPframe, spriteCommon, 22);
	HPframe.SpriteUpdate(HPframe, spriteCommon_);

	//SpaceButton
	spaButton.LoadTexture(spriteCommon_, 23, L"Resources/space.png", dXCommon->GetDevice());
	spaButton.SpriteCreate(dXCommon->GetDevice(), 412, 95, 23, spriteCommon, Vector2(0.0f, 0.0f), false, false);
	spaButton.SetPosition(Vector3(440, 610, 0));
	spaButton.SetScale(Vector2(412, 95));
	spaButton.SetRotation(0.0f);
	spaButton.SpriteTransferVertexBuffer(spaButton, spriteCommon, 23);
	spaButton.SpriteUpdate(spaButton, spriteCommon_);

	//斜めフレーム
	/*diagonalFrame.LoadTexture(spriteCommon_, 24, L"Resources/DiaFrame_01.png", dXCommon->GetDevice());
	diagonalFrame.SetColor(Vector4(1, 1, 1, 1));
	diagonalFrame.SpriteCreate(dXCommon->GetDevice(), 204, 24, 24, spriteCommon, Vector2(0.0f, 0.0f), false, false);
	diagonalFrame.SetPosition(Vector3(35, 38, 0));*/
	//diagonalFrame.

	LoadEffect(spriteCommon);
	LoadAttackEffect(spriteCommon);

	//title
	title.LoadTexture(spriteCommon_, 17, L"Resources/RideLight.png", dXCommon->GetDevice());
	title.SpriteCreate(dXCommon->GetDevice(), 1280, 720, 17, spriteCommon, Vector2(0.0f, 0.0f), false, false);
	title.SetPosition(Vector3(730, 10, 0));
	title.SetScale(Vector2(640 * 1, 360 * 1));
	title.SetRotation(0.0f);
	title.SpriteTransferVertexBuffer(title, spriteCommon, 17);
	title.SpriteUpdate(title, spriteCommon_);
	//clear
	clear.LoadTexture(spriteCommon_, 18, L"Resources/GameClear.png", dXCommon->GetDevice());
	clear.SpriteCreate(dXCommon->GetDevice(), 1280, 720, 18, spriteCommon, Vector2(0.0f, 0.0f), false, false);
	clear.SetPosition(Vector3(0, 0, 0));
	clear.SetScale(Vector2(1280 * 1, 720 * 1));
	clear.SetRotation(0.0f);
	clear.SpriteTransferVertexBuffer(clear, spriteCommon, 18);
	clear.SpriteUpdate(clear, spriteCommon_);

	//over
	over.LoadTexture(spriteCommon_, 19, L"Resources/gameOver.png", dXCommon->GetDevice());
	over.SpriteCreate(dXCommon->GetDevice(), 1280, 720, 19, spriteCommon, Vector2(0.0f, 0.0f), false, false);
	over.SetPosition(Vector3(0, 0, 0));
	over.SetScale(Vector2(1280 * 1, 720 * 1));
	over.SetRotation(0.0f);
	over.SpriteTransferVertexBuffer(over, spriteCommon, 19);
	over.SpriteUpdate(over, spriteCommon_);

	//back
	back.LoadTexture(spriteCommon_, 35, L"Resources/back.png", dXCommon->GetDevice());
	back.SpriteCreate(dXCommon->GetDevice(), 1280, 720, 35, spriteCommon, Vector2(0.0f, 0.0f), false, false);
	back.SetPosition(Vector3(0, 0, 0));
	back.SetScale(Vector2(1280 * 1, 720 * 1));
	back.SetRotation(0.0f);
	back.SpriteTransferVertexBuffer(back, spriteCommon, 35);
	back.SpriteUpdate(back, spriteCommon_);

	//titleBack
	titleBack.LoadTexture(spriteCommon_, 24, L"Resources/titleBack_03.png", dXCommon->GetDevice());
	titleBack.SpriteCreate(dXCommon->GetDevice(), 360, 47, 24, spriteCommon, Vector2(0.5f, 0.5f), false, false);
	titleBack.SetColor(titleBack, Vector4(0.5, 0.5, 0.5, 0.9));
	titleBack.SetPosition(Vector3(650, 620, 0));
	titleBack.SetScale(Vector2(360, 47));
	titleBack.SetRotation(0.0f);
	titleBack.SpriteTransferVertexBuffer(titleBack, spriteCommon, 24);
	titleBack.SpriteUpdate(titleBack, spriteCommon_);

	//stageBack
	stageBack.LoadTexture(spriteCommon_, 25, L"Resources/stageSelectBack_02.png", dXCommon->GetDevice());
	stageBack.SpriteCreate(dXCommon->GetDevice(), 360, 47, 25, spriteCommon, Vector2(0.5f, 0.5f), false, false);
	stageBack.SetColor(stageBack, Vector4(0.5, 0.5, 0.5, 0.9));
	stageBack.SetPosition(Vector3(650, 550, 0));
	stageBack.SetScale(Vector2(360, 47));
	stageBack.SetRotation(0.0f);
	stageBack.SpriteTransferVertexBuffer(stageBack, spriteCommon, 25);
	stageBack.SpriteUpdate(stageBack, spriteCommon_);

	//close
	close.LoadTexture(spriteCommon_, 33, L"Resources/close.png", dXCommon->GetDevice());
	close.SpriteCreate(dXCommon->GetDevice(), 360, 47, 33, spriteCommon, Vector2(0.5f, 0.5f), false, false);
	close.SetColor(close, Vector4(0.1, 0.7, 0, 1));
	close.SetPosition(Vector3(650, 480, 0));
	close.SetScale(Vector2(360, 47));
	close.SetRotation(0.0f);
	close.SpriteTransferVertexBuffer(close, spriteCommon, 33);
	close.SpriteUpdate(close, spriteCommon_);

	//pause
	pause.LoadTexture(spriteCommon_, 34, L"Resources/black.png", dXCommon->GetDevice());
	pause.SpriteCreate(dXCommon->GetDevice(), 1280, 720, 34, spriteCommon, Vector2(0.0f, 0.0f), false, false);
	pause.SetAlpha(pause, 0.5);
	pause.SetPosition(Vector3(0, 0, 0));
	pause.SetScale(Vector2(1280, 720));
	pause.SetRotation(0.0f);
	pause.SpriteTransferVertexBuffer(pause, spriteCommon, 34);
	pause.SpriteUpdate(pause, spriteCommon_);

	//チュートリアル
	 
	//攻撃
	attackMethod_First.LoadTexture(spriteCommon_, 36, L"Resources/attackMethod.png", dXCommon->GetDevice());
	attackMethod_First.SpriteCreate(dXCommon->GetDevice(), 720, 240, 36, spriteCommon, Vector2(0.5f, 0.5f), false, false);
	attackMethod_First.SetColor(attackMethod_First, Vector4(1, 1, 1, 1));
	attackMethod_First.SetPosition(Vector3(650, 600, 0));
	attackMethod_First.SetScale(Vector2(720, 240));
	attackMethod_First.SetRotation(0.0f);
	attackMethod_First.SpriteTransferVertexBuffer(attackMethod_First, spriteCommon, 36);
	attackMethod_First.SpriteUpdate(attackMethod_First, spriteCommon_);

	//攻撃(2ページ目)
	attackMethod_Second.LoadTexture(spriteCommon_, 37, L"Resources/attackMethod_2page.png", dXCommon->GetDevice());
	attackMethod_Second.SpriteCreate(dXCommon->GetDevice(), 720, 240, 37, spriteCommon, Vector2(0.5f, 0.5f), false, false);
	attackMethod_Second.SetColor(attackMethod_Second, Vector4(1, 1, 1, 1));
	attackMethod_Second.SetPosition(Vector3(650, 600, 0));
	attackMethod_Second.SetScale(Vector2(720, 240));
	attackMethod_Second.SetRotation(0.0f);
	attackMethod_Second.SpriteTransferVertexBuffer(attackMethod_Second, spriteCommon, 37);
	attackMethod_Second.SpriteUpdate(attackMethod_Second, spriteCommon_);

	//クリア条件
	clearMethod.LoadTexture(spriteCommon_, 38, L"Resources/clear.png", dXCommon->GetDevice());
	clearMethod.SpriteCreate(dXCommon->GetDevice(), 720, 240, 38, spriteCommon, Vector2(0.5f, 0.5f), false, false);
	clearMethod.SetColor(clear, Vector4(1, 1, 1, 1));
	clearMethod.SetPosition(Vector3(650, 600, 0));
	clearMethod.SetScale(Vector2(720, 240));
	clearMethod.SetRotation(0.0f);
	clearMethod.SpriteTransferVertexBuffer(clearMethod, spriteCommon, 38);
	clearMethod.SpriteUpdate(clearMethod, spriteCommon_);

	//倒せない敵
	enemyCaution.LoadTexture(spriteCommon_, 39, L"Resources/enemyCaution.png", dXCommon->GetDevice());
	enemyCaution.SpriteCreate(dXCommon->GetDevice(), 720, 240, 39, spriteCommon, Vector2(0.5f, 0.5f), false, false);
	enemyCaution.SetColor(clear, Vector4(1, 1, 1, 1));
	enemyCaution.SetPosition(Vector3(650, 600, 0));
	enemyCaution.SetScale(Vector2(720, 240));
	enemyCaution.SetRotation(0.0f);
	enemyCaution.SpriteTransferVertexBuffer(enemyCaution, spriteCommon, 39);
	enemyCaution.SpriteUpdate(enemyCaution, spriteCommon_);

	//フィーバー終了
	feverEnd_First.LoadTexture(spriteCommon_, 40, L"Resources/feverEnd.png", dXCommon->GetDevice());
	feverEnd_First.SpriteCreate(dXCommon->GetDevice(), 720, 240, 40, spriteCommon, Vector2(0.5f, 0.5f), false, false);
	feverEnd_First.SetColor(clear, Vector4(1, 1, 1, 1));
	feverEnd_First.SetPosition(Vector3(650, 600, 0));
	feverEnd_First.SetScale(Vector2(720, 240));
	feverEnd_First.SetRotation(0.0f);
	feverEnd_First.SpriteTransferVertexBuffer(feverEnd_First, spriteCommon, 40);
	feverEnd_First.SpriteUpdate(feverEnd_First, spriteCommon_);

	//フィーバー終了(2ページ)
	feverEnd_Second.LoadTexture(spriteCommon_, 41, L"Resources/feverEnd_2page.png", dXCommon->GetDevice());
	feverEnd_Second.SpriteCreate(dXCommon->GetDevice(), 720, 240, 41, spriteCommon, Vector2(0.5f, 0.5f), false, false);
	feverEnd_Second.SetColor(clear, Vector4(1, 1, 1, 1));
	feverEnd_Second.SetPosition(Vector3(650, 600, 0));
	feverEnd_Second.SetScale(Vector2(720, 240));
	feverEnd_Second.SetRotation(0.0f);
	feverEnd_Second.SpriteTransferVertexBuffer(feverEnd_Second, spriteCommon, 41);
	feverEnd_Second.SpriteUpdate(feverEnd_Second, spriteCommon_);

	//フィーバー開始
	feverMode_First.LoadTexture(spriteCommon_, 42, L"Resources/feverMode.png", dXCommon->GetDevice());
	feverMode_First.SpriteCreate(dXCommon->GetDevice(), 720, 240, 42, spriteCommon, Vector2(0.5f, 0.5f), false, false);
	feverMode_First.SetColor(clear, Vector4(1, 1, 1, 1));
	feverMode_First.SetPosition(Vector3(650, 600, 0));
	feverMode_First.SetScale(Vector2(720, 240));
	feverMode_First.SetRotation(0.0f);
	feverMode_First.SpriteTransferVertexBuffer(feverMode_First, spriteCommon, 42);
	feverMode_First.SpriteUpdate(feverMode_First, spriteCommon_);

	//フィーバー開始(2ページ)
	feverMode_Second.LoadTexture(spriteCommon_, 43, L"Resources/feverMode_2page.png", dXCommon->GetDevice());
	feverMode_Second.SpriteCreate(dXCommon->GetDevice(), 720, 240, 43, spriteCommon, Vector2(0.5f, 0.5f), false, false);
	feverMode_Second.SetColor(clear, Vector4(1, 1, 1, 1));
	feverMode_Second.SetPosition(Vector3(650, 600, 0));
	feverMode_Second.SetScale(Vector2(720, 240));
	feverMode_Second.SetRotation(0.0f);
	feverMode_Second.SpriteTransferVertexBuffer(feverMode_Second, spriteCommon, 43);
	feverMode_Second.SpriteUpdate(feverMode_Second, spriteCommon_);

	//プレイヤーダメージ
	playerDamage_First.LoadTexture(spriteCommon_, 44, L"Resources/playerDamage.png", dXCommon->GetDevice());
	playerDamage_First.SpriteCreate(dXCommon->GetDevice(), 720, 240, 44, spriteCommon, Vector2(0.5f, 0.5f), false, false);
	playerDamage_First.SetColor(clear, Vector4(1, 1, 1, 1));
	playerDamage_First.SetPosition(Vector3(650, 600, 0));
	playerDamage_First.SetScale(Vector2(720, 240));
	playerDamage_First.SetRotation(0.0f);
	playerDamage_First.SpriteTransferVertexBuffer(playerDamage_First, spriteCommon, 44);
	playerDamage_First.SpriteUpdate(playerDamage_First, spriteCommon_);

	//プレイヤーダメージ
	playerDamage_Second.LoadTexture(spriteCommon_, 45, L"Resources/playerDamage_2page.png", dXCommon->GetDevice());
	playerDamage_Second.SpriteCreate(dXCommon->GetDevice(), 720, 240, 45, spriteCommon, Vector2(0.5f, 0.5f), false, false);
	playerDamage_Second.SetColor(clear, Vector4(1, 1, 1, 1));
	playerDamage_Second.SetPosition(Vector3(650, 600, 0));
	playerDamage_Second.SetScale(Vector2(720, 240));
	playerDamage_Second.SetRotation(0.0f);
	playerDamage_Second.SpriteTransferVertexBuffer(playerDamage_Second, spriteCommon, 45);
	playerDamage_Second.SpriteUpdate(playerDamage_Second, spriteCommon_);

	//プレイヤー移動
	playerMove_First.LoadTexture(spriteCommon_, 46, L"Resources/playerMove.png", dXCommon->GetDevice());
	playerMove_First.SpriteCreate(dXCommon->GetDevice(), 720, 240, 46, spriteCommon, Vector2(0.5f, 0.5f), false, false);
	playerMove_First.SetColor(clear, Vector4(1, 1, 1, 1));
	playerMove_First.SetPosition(Vector3(650, 600, 0));
	playerMove_First.SetScale(Vector2(720, 240));
	playerMove_First.SetRotation(0.0f);
	playerMove_First.SpriteTransferVertexBuffer(playerMove_First, spriteCommon, 46);
	playerMove_First.SpriteUpdate(playerMove_First, spriteCommon_);

	//プレイヤー移動
	playerMove_Second.LoadTexture(spriteCommon_, 47, L"Resources/playerMove_2page.png", dXCommon->GetDevice());
	playerMove_Second.SpriteCreate(dXCommon->GetDevice(), 720, 240, 47, spriteCommon, Vector2(0.5f, 0.5f), false, false);
	playerMove_Second.SetColor(clear, Vector4(1, 1, 1, 1));
	playerMove_Second.SetPosition(Vector3(650, 600, 0));
	playerMove_Second.SetScale(Vector2(720, 240));
	playerMove_Second.SetRotation(0.0f);
	playerMove_Second.SpriteTransferVertexBuffer(playerMove_Second, spriteCommon, 47);
	playerMove_Second.SpriteUpdate(playerMove_Second, spriteCommon_);

	//挨拶
	welcomeGame.LoadTexture(spriteCommon_, 48, L"Resources/welcomeGame.png", dXCommon->GetDevice());
	welcomeGame.SpriteCreate(dXCommon->GetDevice(), 720, 240, 48, spriteCommon, Vector2(0.5f, 0.5f), false, false);
	welcomeGame.SetColor(clear, Vector4(1, 1, 1, 1));
	welcomeGame.SetPosition(Vector3(650, 600, 0));
	welcomeGame.SetScale(Vector2(720, 240));
	welcomeGame.SetRotation(0.0f);
	welcomeGame.SpriteTransferVertexBuffer(welcomeGame, spriteCommon, 48);
	welcomeGame.SpriteUpdate(welcomeGame, spriteCommon_);

	//テキストボックス
	textBox.LoadTexture(spriteCommon_, 49, L"Resources/textBox.png", dXCommon->GetDevice());
	textBox.SpriteCreate(dXCommon->GetDevice(), 720, 240, 49, spriteCommon, Vector2(0.5f, 0.5f), false, false);
	textBox.SetColor(textBox, Vector4(1, 1, 1, 1));
	textBox.SetPosition(Vector3(650, 600, 0));
	textBox.SetScale(Vector2(720, 240));
	textBox.SetRotation(0.0f);
	textBox.SpriteTransferVertexBuffer(textBox, spriteCommon, 49);
	textBox.SpriteUpdate(textBox, spriteCommon_);

	AorD.LoadTexture(spriteCommon_, 50, L"Resources/AandD.png", dXCommon->GetDevice());
	AorD.SpriteCreate(dXCommon->GetDevice(), 720, 240, 50, spriteCommon, Vector2(0.5f, 0.5f), false, false);
	AorD.SetColor(AorD, Vector4(1, 1, 1, 1));
	AorD.SetPosition(Vector3(545, 720, 0));
	AorD.SetScale(Vector2(480, 180));
	AorD.SetRotation(0.0f);
	AorD.SpriteTransferVertexBuffer(AorD, spriteCommon, 50);
	AorD.SpriteUpdate(AorD, spriteCommon_);

	//レールカメラ初期化
	railCamera->Initialize();

	sceneNum = 0;
	selectPause = 1;
	stageNum = 1;
	tutorialStep = 0;
	tutoTime = 0;
	isShowText = false;
	tutoText = 0;
	selectTime = 0.0f;
	isMoveSel = 0;
	selPlayerTmp = { -550,-5,-700 };
	selEyeTmp = { -550,30,-780 };
	selTargetTmp = { -550,0,-700 };
}

void GamePlayScene::Update(SpriteCommon& spriteCommon) {
	switch (sceneNum) {
	case 0:
		// スタート画面フェードアウト演出
		FadeOut(0.01, 100);

		if (titleTimer <= 50)
		{
			player->worldTransform_.position_.y += MathFunc::easeInOutSine(titleTimer / 50) / 30;
		}
		else if (titleTimer <= 100)
		{
			player->worldTransform_.position_.y -= MathFunc::easeInOutSine((titleTimer - 50.0f) / 50) / 30;
		}
		else
		{
			titleTimer = 0;
		}
		//プレイヤー
		player->Update(points);
		railCamera->GetView()->target = { 0, -15, -750 };
		//カメラ更新
		railCamera->ViewUpdate();
		//天球
		floor->Update();
		sky->Update();

		if (titleTimer <= 50) {
			player->worldTransform_.position_.y += MathFunc::easeInOutSine(titleTimer / 50) / 30;
		}
		else if (titleTimer <= 100) {
			player->worldTransform_.position_.y -= MathFunc::easeInOutSine((titleTimer - 50.0f) / 50) / 30;
		}
		else {
			titleTimer = 0;
		}
		//プレイヤー
		player->Update(points);
		railCamera->GetView()->target = { 0, -15, -750 };
		//カメラ更新
		railCamera->ViewUpdate();
		//天球
		floor->Update();
		sky->Update();

		if (input->TriggerKey(DIK_SPACE)) {

			isTitleT = true;
		}
		if (isTitleT == true) {
			railCamera->TitleR(player);
			titleT++;
		}
		if (titleT >= 100) {
			Reset();
			sceneNum = 1;
			railCamera->SetPlayer(player);
			railCamera->SetEye(selEyeTmp);
			railCamera->SetTarget(selTargetTmp);
			player->SetPosition(selPlayerTmp);
			player->SetScale({ 1.5,1.5,1.5 });
		}
		titleTimer++;
		break;
	case 1://ステージ選択
		FadeOut(0.01, 100);
		//ステージ選択関数
		StageSelect();
		//天球
		sky->Update();
		floor->Update();
		//ステージ
		//天球
		floor->Update();
		sky->Update();
		for (const std::unique_ptr<Object3d>& stage : stages_) {
			stage->Update();
		}
		railCamera->ViewUpdate();
		break;

	case 2:
		// ゲーム画面フェードアウト演出
		FadeOut(0.01, 100);

		//デスフラグの立った敵を削除
		enemys_.remove_if([](std::unique_ptr < Enemy>& enemy_) {
			return enemy_->GetIsDead();
			});

		//チュートリアルステージならチュートリアルに移行
		if (stageNum == 1) {
			sceneNum = 6;
		}

		gauge.GetScale();

		if (isMaxGauge == true) {
			if (gaugeScale.x >= 4) {
				gaugeScale.x -= 0.8;
			}
			else {
				isMaxGauge = false;
			}
		}


		if (player->GetGaugeAdd() == true) {
			player->SetGaugeAdd(false);
			calRes = static_cast<float>(195) / (player->GetDivide() + 1);
			gaugeScale.x += calRes;

		}
		if (gaugeScale.x >= 195) {
			if (isMaxGauge == false) {
				isMaxGauge = true;
			}
		}

		gauge.SetScale(Vector2(gaugeScale.x, gaugeScale.y));
		gauge.SpriteTransferVertexBuffer(gauge, spriteCommon, 21);

		// ダメージを受けた時の画面演出
		if (isBack == true) {
			backT++;
		}
		if (backT >= 50.0f) {
			isBack = false;
			backT = 0.0f;
		}

		// 敵を倒した時の演出
		if (player->GetIsBurst() == true) {
			isDeadT++;
		}
		if (isDeadT >= 20.0f) {
			player->SetIsBurst(false);
			isDeadT = 0.0f;
		}
		if (player->GetIsBurst() == true) {
			pm_dmg->Fire(p_dmg, 50, { 0,0,0 }, 30.0f, 30.0f, 30.0f, 30.0f, 0, 0, 0, 0, 0.2f, 0.2f, 0, 0, 0, 3, { 4.0f, 0.0f });
		}

		// 加速時のブラー処理
		if (player->GetIsBurst() == true) {
			isBlur = true;
		}
		if (isBlur == true) {
			blurT++;
			postEffect_->SetBlur(true);
		}
		if (blurT >= 10) {
			isBlur = false;
			if (isBlur == false) {
				postEffect_->SetBlur(false);
			}
			if (player->GetFever() == false) {
				blurT = 0;
			}
		}
		for (const std::unique_ptr<Object3d>& buil : buils_) {
			buil->Update();
		}

		//敵キャラの更新
		for (const std::unique_ptr<Enemy>& enemy : enemys_) {
			enemy->SetGameScene(this);
			enemy->Update();
		}
		//敵キャラの更新
		for (const std::unique_ptr<InvisibleEnemy>& invEnemy : invEnemys_) {
			invEnemy->SetGameScene(this);
			invEnemy->Update();
		}

		//全ての衝突をチェック
		collisionManager->CheckAllCollisions();

		//パーティクル発生実験
		/*if (player->GetIsHit() == true)
		{
			pm_1->Fire(particle_1, 30, 0.2f, 0, 20, { 8.0f, 0.0f });
			pm_2->Fire(particle_2, 70, 0.2f, 0, 20, { 4.0f,0.0f });
		}*/

		//ポーズ画面
		if (input->TriggerKey(DIK_P) || input->TriggerKey(DIK_TAB)) {
			selectPause = 2;
			sceneNum = 5;
		}

		//ゲームオーバー
		if (player->GetHP() == 0) {
			isOStaging = true;
			oStagingT++;
		}
		if (isOStaging == true) {
			pBombM->Fire(pBomb, 50, { 0,0,0 }, 70.0f, 70.0f, 50.0f, 50.0f, 0, 0, 0, 0, 0.0f, 0.0f, 0, 0, 0, 5, { 5.0f, 40.0f });
		}
		if (oStagingT >= 40) {
			isOStaging = false;
			oStagingT = 0;
			sceneNum = 4;
			player->SetPosition({ 0,0,0 });
		}
		pBombM->Update();
			
		//クリア
		if (railCamera->GetIsEnd() == true) {
			cStagingT++;
			player->worldTransform_.rotation_.z = 0;
			isClearStaging = true;
			player->SetPosition(player->GetPosition() + Vector3(0, 0, 0.8));
			player->worldTransform_.UpdateMatrix();
			Vector3 behindVec = (railCamera->GetView()->target - railCamera->GetView()->eye) * -1;
			behindVec /= 80;
			railCamera->SetEye(railCamera->GetView()->eye + behindVec);

		}
		if (cStagingT >= 100) {
			sceneNum = 3;
			isClearStaging = false;
			Reset();
		}


		//カメラ更新
		if (railCamera->GetIsEnd() == false) {
			railCamera->Update(player, points);
			//プレイヤー
			player->Update(points);
		}
		if (isBack == true) {
			if (backT < 8) {
				railCamera->ShakeCamera();
			}
		}
		//ステージ
		//天球
		floor->Update();
		sky->Update();

		//パーティクル
		pm_1->Update();
		pm_2->Update();
		pm_dmg->Update();

		break;
		//クリア
	case 3:
		// クリア画面フェードアウト演出
		FadeOut(0.01, 100);

		//player->SetPosition({ 0,0,0 });
		if (input->TriggerKey(DIK_SPACE)) {
			Reset();
			sceneNum = 0;
		}
		break;
		//ゲームオーバー
	case 4:
		// ゲームオーバー画面フェードアウト演出
		FadeOut(0.01, 100);

		player->Update(points);

		pFireM->Fire(pFire, 55, { 0, 0,-790 }, 10.0f, 10.0f, -10.0f, -10.0f, 0, 0, 0, 0, 1.0f, 0, 0, 0, 0, 5, { 5.0f, 0.0f });
		pFireM->Update();

		if (input->TriggerKey(DIK_SPACE)) {
			Reset();
			sceneNum = 0;
		}
		break;
	case 5://ポーズ画面
		if (input->TriggerKey(DIK_W) || input->TriggerKey(DIK_UP)) {
			if (selectPause <= 1) {
				selectPause++;
				if (selectPause == 2) {
					titleBack.SetColor(titleBack, Vector4(0.5, 0.5, 0.5, 0.9));
					stageBack.SetColor(stageBack, Vector4(0.5, 0.5, 0.5, 0.9));
					close.SetColor(close, Vector4(1, 1, 0, 1));
				}
				else if (selectPause == 1) {
					titleBack.SetColor(titleBack, Vector4(0.5, 0.5, 0.5, 0.9));
					stageBack.SetColor(stageBack, Vector4(1, 1, 0, 1));
					close.SetColor(close, Vector4(0.5, 0.5, 0.5, 0.9));
				}
			}
		}
		if (input->TriggerKey(DIK_S) || input->TriggerKey(DIK_DOWN)) {
			if (selectPause > 0) {
				selectPause--;
				if (selectPause == 1) {
					titleBack.SetColor(titleBack, Vector4(0.5, 0.5, 0.5, 0.9));
					stageBack.SetColor(stageBack, Vector4(1, 1, 0, 1));
					close.SetColor(close, Vector4(0.5, 0.5, 0.5, 0.9));
				}
				else if (selectPause == 0) {
					titleBack.SetColor(titleBack, Vector4(1, 1, 0, 1));
					stageBack.SetColor(stageBack, Vector4(0.5, 0.5, 0.5, 0.9));
					close.SetColor(close, Vector4(0.5, 0.5, 0.5, 0.9));
				}
			}
		}
		//戻る
		if (input->TriggerKey(DIK_SPACE)) {
			if (selectPause <= 1) {
				Reset();
				if (selectPause == 1) {
					railCamera->SetEye(selEyeTmp);
					railCamera->SetTarget(selTargetTmp);
					player->SetPosition(selPlayerTmp);
					player->SetScale({ 1.5,1.5,1.5 });
				}
			}
			postEffect_->SetColor(Vector4(1, 1, 1, 1));
			sceneNum = selectPause;
		}
		if (input->TriggerKey(DIK_P) || input->TriggerKey(DIK_TAB)) {
			postEffect_->SetColor(Vector4(1, 1, 1, 1));
			sceneNum = 2;
		}
		break;
	case 6://チュートリアル
		if (isShowText == false) {
			FadeOut(0.01, 100);
			//デスフラグの立った敵を削除
			enemys_.remove_if([](std::unique_ptr < Enemy>& enemy_) {
				return enemy_->GetIsDead();
				});

			TutorialUpdate();

			gauge.GetScale();

			if (isMaxGauge == true) {
				if (gaugeScale.x >= 4) {
					gaugeScale.x -= 0.8;
				}
				else {
					isMaxGauge = false;
				}
			}


			if (player->GetGaugeAdd() == true) {
				player->SetGaugeAdd(false);
				calRes = static_cast<float>(195) / (player->GetDivide() + 1);
				gaugeScale.x += calRes;

			}
			if (gaugeScale.x >= 195) {
				if (isMaxGauge == false) {
					isMaxGauge = true;
				}
			}

			gauge.SetScale(Vector2(gaugeScale.x, gaugeScale.y));
			gauge.SpriteTransferVertexBuffer(gauge, spriteCommon, 21);

			// ダメージを受けた時の画面演出
			if (isBack == true) {
				backT++;
			}
			if (backT >= 50.0f) {
				isBack = false;
				backT = 0.0f;
			}

			// 敵を倒した時の演出
			if (player->GetIsBurst() == true) {
				isDeadT++;
			}
			if (isDeadT >= 20.0f) {
				player->SetIsBurst(false);
				isDeadT = 0.0f;
			}
			if (player->GetIsBurst() == true) {
				pm_dmg->Fire(p_dmg, 50, { 0,0,0 }, 30.0f, 30.0f, 30.0f, 30.0f, 0, 0, 0, 0, 0.2f, 0.2f, 0, 0, 0, 3, { 4.0f, 0.0f });
			}

			// 加速時のブラー処理
			if (player->GetIsBurst() == true) {
				isBlur = true;
			}
			if (isBlur == true) {
				blurT++;
				postEffect_->SetBlur(true);
			}
			if (blurT >= 10) {
				isBlur = false;
				if (isBlur == false) {
					postEffect_->SetBlur(false);
				}
				if (player->GetFever() == false) {
					blurT = 0;
				}
			}

			//敵キャラの更新
			for (const std::unique_ptr<Enemy>& enemy : enemys_) {
				enemy->SetGameScene(this);
				enemy->Update();
			}
			for (const std::unique_ptr<InvisibleEnemy>& invEnemy : invEnemys_) {
				invEnemy->SetGameScene(this);
				invEnemy->Update();
			}

			//全ての衝突をチェック
			collisionManager->CheckAllCollisions();

			//ポーズ画面
			if (input->TriggerKey(DIK_P) || input->TriggerKey(DIK_TAB)) {
				selectPause = 2;
				sceneNum = 5;
			}

			//ゲームオーバー
			if (player->GetHP() == 0) {
				sceneNum = 4;
			}
			//クリア
			if (railCamera->GetIsEnd() == true) {
				cStagingT++;
				player->worldTransform_.rotation_.z = 0;
				isClearStaging = true;
				player->SetPosition(player->GetPosition() + Vector3(0, 0, 0.8));
				player->worldTransform_.UpdateMatrix();
				Vector3 behindVec = (railCamera->GetView()->target - railCamera->GetView()->eye) * -1;
				behindVec /= 80;
				railCamera->SetEye(railCamera->GetView()->eye + behindVec);

			}
			if (cStagingT >= 100) {
				sceneNum = 3;
				isClearStaging = false;
				Reset();
			}


			//カメラ更新
			if (railCamera->GetIsEnd() == false) {
				railCamera->Update(player, points);
				//プレイヤー
				player->Update(points);
			}
			if (isBack == true) {
				if (backT < 8) {
					railCamera->ShakeCamera();
				}
			}
			//ステージ
			//天球
			floor->Update();
			sky->Update();

			//パーティクル
			pm_1->Update();
			pm_2->Update();
			pm_dmg->Update();
		}
		//テキスト
		else {
		if (isBlur == true) {
			postEffect_->SetBlur(false);
		}
			//welcome
			if (tutorialStep == 1) {
				if (tutoText == 0) {
					if (input->TriggerKey(DIK_SPACE)) {
						tutoText = 1;
					}
				}
				else {
					if (input->TriggerKey(DIK_SPACE)) {
						tutoText = 0;
						isShowText = false;
					}
				}
			}
			//敵(倒す)
			else if (tutorialStep == 2) {
				if (tutoText == 0) {
					if (input->TriggerKey(DIK_SPACE)) {
						tutoText = 1;
					}
				}
				else {
					if (input->TriggerKey(DIK_SPACE)) {
						isShowText = false;
						tutoText = 0;
						player->Update(points);
					}
				}
			}
			//スピードアップ
			else if (tutorialStep == 3) {
				if (input->TriggerKey(DIK_SPACE)) {
					isShowText = false;
				}
			}
			//敵(ダメージ)
			else if (tutorialStep == 4) {
				if (input->TriggerKey(DIK_SPACE)) {
					isShowText = false;
					player->Update(points);
				}
			}
			//HP
			else if (tutorialStep == 5) {
				if (tutoText == 0) {
					if (input->TriggerKey(DIK_SPACE)) {
						tutoText = 1;
					}
				}
				else if(tutoText == 1) {
					if (input->TriggerKey(DIK_SPACE)) {
						tutoText = 2;
					}
				}
				else {
					if (input->TriggerKey(DIK_SPACE)) {
						tutoText = 0;
						isShowText = false;
					}
				}
				if (tutoTime == 100) {
					tutoTime = 0;
				}
				tutoTime++;
			}
			//移動
			else if (tutorialStep == 6) {
				if (tutoText == 0) {
					if (input->TriggerKey(DIK_SPACE)) {
						tutoText = 1;
					}
				}
				else {
					if (input->TriggerKey(DIK_D) || input->TriggerKey(DIK_A)) {
						isShowText = false;
						tutoText = 0;
						player->Update(points);
					}
				}
			}
			//移動して攻撃
			else if (tutorialStep == 7) {
				if (input->TriggerKey(DIK_SPACE)) {
					isShowText = false;
					player->Update(points);
				}
			}
			//移動
			else if (tutorialStep == 8) {
				if (input->TriggerKey(DIK_D) || input->TriggerKey(DIK_A)) {
					isShowText = false;
					player->Update(points);
				}
			}
			//フィーバー
			else if (tutorialStep == 9) {
				if (tutoText == 0) {
					if (input->TriggerKey(DIK_SPACE)) {
						tutoText = 1;
					}
				}
				else {
					if (input->TriggerKey(DIK_SPACE)) {
						isShowText = false;
						tutoText = 0;
					}
				}
				if (tutoTime == 100) {
					tutoTime = 0;
				}
				tutoTime++;
			}
			//フィーバー終わり
			else if (tutorialStep == 10) {
				if (tutoText == 0) {
					if (input->TriggerKey(DIK_SPACE)) {
						tutoText = 1;
					}
				}
				else {
					if (input->TriggerKey(DIK_SPACE)) {
						isShowText = false;
						tutoText = 0;
					}
				}
				if (tutoTime == 100) {
					tutoTime = 0;
				}
				tutoTime++;
			}
		}


		break;

	}
}

void GamePlayScene::Draw(SpriteCommon& spriteCommon) {
#pragma endregion レール

	// 3Dオブジェクト描画前処理
	Line::PreDraw(dXCommon->GetCommandList());

	if (sceneNum == 2 || sceneNum == 5 || sceneNum == 6) {
		if (isClearStaging == false) {
			for (int i = 0; i < 3; i++) {
				line[i]->Draw(railCamera->GetView());
			}
		}
	}

	// 3Dオブジェクト描画後処理
	Line::PostDraw();

#pragma region 3Dオブジェクト描画

	// 3Dオブジェクト描画前処理
	Object3d::PreDraw(dXCommon->GetCommandList());

	sky->Draw(railCamera->GetView());
	if (sceneNum == 1) {
		for (const std::unique_ptr<Object3d>& stage : stages_) {
			stage->Draw(railCamera->GetView());
		}
	}

	if (sceneNum == 2 || sceneNum == 5 || sceneNum == 6) {
		floor->Draw(railCamera->GetView());
		for (const std::unique_ptr<Object3d>& buil : buils_) {
			buil->Draw(railCamera->GetView());
		}
		//敵キャラの描画
		for (const std::unique_ptr<Enemy>& enemy : enemys_) {
			enemy->Draw(railCamera->GetView());
		}
		//敵キャラの描画
		for (const std::unique_ptr<InvisibleEnemy>& invEnemy : invEnemys_) {
			invEnemy->Draw(railCamera->GetView());
		}
	}

	if (sceneNum == 1) {
		floor->Draw(railCamera->GetView());
	}

	// 3Dオブジェクト描画後処理
	Object3d::PostDraw();


#pragma region パーティクル描画

	// パーティクル描画前処理
	ParticleManager::PreDraw(dXCommon->GetCommandList());

	///==== パーティクル描画 ====///
	//パーティクル

	pm_1->Draw();
	pm_2->Draw();
	pm_dmg->Draw();
	if (sceneNum == 2) {
		pBombM->Draw();
	}
	if (sceneNum == 4) {
		pFireM->Draw();
	}

	// パーティクル描画後処理
	ParticleManager::PostDraw();

#pragma endregion

#pragma region スプライト描画

	// スプライト描画前処理
	Sprite::PreDraw(dXCommon->GetCommandList(), spriteCommon_);

	if (sceneNum == 4) {

	}

	///=== スプライト描画 ===///
	if (sceneNum == 0) {
		if (isTitleT == false) {
			title.SpriteDraw(dXCommon->GetCommandList(), spriteCommon_, dXCommon->GetDevice(), title.vbView);
			spaButton.SpriteDraw(dXCommon->GetCommandList(), spriteCommon_, dXCommon->GetDevice(), spaButton.vbView);
		}
	}
	else if (sceneNum == 2) {
		if (player->GetFever() == true) {
			effectR[player->GetFeverNum()].SpriteDraw(dXCommon->GetCommandList(), spriteCommon_, dXCommon->GetDevice(), effectR[player->GetFeverNum()].vbView);
			effectL[player->GetFeverNum()].SpriteDraw(dXCommon->GetCommandList(), spriteCommon_, dXCommon->GetDevice(), effectL[player->GetFeverNum()].vbView);
		}
		if (isBack == true) {
			back.SpriteDraw(dXCommon->GetCommandList(), spriteCommon_, dXCommon->GetDevice(), back.vbView);
		}
		HPframe.SpriteDraw(dXCommon->GetCommandList(), spriteCommon_, dXCommon->GetDevice(), HPframe.vbView);
		for (int i = 0; i < player->GetHP(); i++) {
			hP[i].SpriteDraw(dXCommon->GetCommandList(), spriteCommon_, dXCommon->GetDevice(), hP[i].vbView);
		}
		if (railCamera->GetIsEnd() == false) {
			if (player->GetAttackTime() <= 8 && player->GetIsAttack() == true) {
				attackEffect[player->GetAttackNum()].SpriteDraw(dXCommon->GetCommandList(), spriteCommon_, dXCommon->GetDevice(), attackEffect[player->GetAttackNum()].vbView);
			}
		}
		gaugeFlame.SpriteDraw(dXCommon->GetCommandList(), spriteCommon_, dXCommon->GetDevice(), gaugeFlame.vbView);
		gauge.SpriteDraw(dXCommon->GetCommandList(), spriteCommon_, dXCommon->GetDevice(), gauge.vbView);

	}
	else if (sceneNum == 3) {
		clear.SpriteDraw(dXCommon->GetCommandList(), spriteCommon_, dXCommon->GetDevice(), clear.vbView);
		spaButton.SpriteDraw(dXCommon->GetCommandList(), spriteCommon_, dXCommon->GetDevice(), spaButton.vbView);
	}
	else if (sceneNum == 4) {
		over.SpriteDraw(dXCommon->GetCommandList(), spriteCommon_, dXCommon->GetDevice(), over.vbView);
		spaButton.SpriteDraw(dXCommon->GetCommandList(), spriteCommon_, dXCommon->GetDevice(), spaButton.vbView);
	}
	else if (sceneNum == 5) {
		HPframe.SpriteDraw(dXCommon->GetCommandList(), spriteCommon_, dXCommon->GetDevice(), HPframe.vbView);
		for (int i = 0; i < player->GetHP(); i++) {
			hP[i].SpriteDraw(dXCommon->GetCommandList(), spriteCommon_, dXCommon->GetDevice(), hP[i].vbView);
		}
		gaugeFlame.SpriteDraw(dXCommon->GetCommandList(), spriteCommon_, dXCommon->GetDevice(), gaugeFlame.vbView);
		gauge.SpriteDraw(dXCommon->GetCommandList(), spriteCommon_, dXCommon->GetDevice(), gauge.vbView);

	}
	else if (sceneNum == 6) {
		if (isShowText == false) {
			if (player->GetFever() == true) {
				effectR[player->GetFeverNum()].SpriteDraw(dXCommon->GetCommandList(), spriteCommon_, dXCommon->GetDevice(), effectR[player->GetFeverNum()].vbView);
				effectL[player->GetFeverNum()].SpriteDraw(dXCommon->GetCommandList(), spriteCommon_, dXCommon->GetDevice(), effectL[player->GetFeverNum()].vbView);
			}
			if (isBack == true) {
				back.SpriteDraw(dXCommon->GetCommandList(), spriteCommon_, dXCommon->GetDevice(), back.vbView);
			}
			if (railCamera->GetIsEnd() == false) {
				if (player->GetAttackTime() <= 8 && player->GetIsAttack() == true) {
					attackEffect[player->GetAttackNum()].SpriteDraw(dXCommon->GetCommandList(), spriteCommon_, dXCommon->GetDevice(), attackEffect[player->GetAttackNum()].vbView);
				}
			}
		}
		HPframe.SpriteDraw(dXCommon->GetCommandList(), spriteCommon_, dXCommon->GetDevice(), HPframe.vbView);
		for (int i = 0; i < player->GetHP(); i++) {
			hP[i].SpriteDraw(dXCommon->GetCommandList(), spriteCommon_, dXCommon->GetDevice(), hP[i].vbView);
		}
		if (tutorialStep > 1) {
			gaugeFlame.SpriteDraw(dXCommon->GetCommandList(), spriteCommon_, dXCommon->GetDevice(), gaugeFlame.vbView);
			gauge.SpriteDraw(dXCommon->GetCommandList(), spriteCommon_, dXCommon->GetDevice(), gauge.vbView);
		}
	}

	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion

#pragma region 3Dオブジェクト描画

	// 3Dオブジェクト描画前処理
	Object3d::PreDraw(dXCommon->GetCommandList());
	if (sceneNum == 0 || sceneNum == 1 || sceneNum == 2 || sceneNum == 4 || sceneNum == 5 || sceneNum == 6) {
		////playerを画像より手前に出したい
		player->Draw(railCamera->GetView());
	}
	// 3Dオブジェクト描画後処理
	Object3d::PostDraw();

	// スプライト描画前処理
	Sprite::PreDraw(dXCommon->GetCommandList(), spriteCommon_);

	//ポーズ画面描画
	if (sceneNum == 5) {
		pause.SpriteDraw(dXCommon->GetCommandList(), spriteCommon_, dXCommon->GetDevice(), pause.vbView);
		close.SpriteDraw(dXCommon->GetCommandList(), spriteCommon_, dXCommon->GetDevice(), close.vbView);
		titleBack.SpriteDraw(dXCommon->GetCommandList(), spriteCommon_, dXCommon->GetDevice(), titleBack.vbView);
		stageBack.SpriteDraw(dXCommon->GetCommandList(), spriteCommon_, dXCommon->GetDevice(), stageBack.vbView);
	}
	//チュートリアルテキスト描画
	if (sceneNum == 6) {
		//text
		if (isShowText == true) {
			if (player->GetFever() == true && tutorialStep == 9) {
				effectR[player->GetFeverNum()].SpriteDraw(dXCommon->GetCommandList(), spriteCommon_, dXCommon->GetDevice(), effectR[player->GetFeverNum()].vbView);
				effectL[player->GetFeverNum()].SpriteDraw(dXCommon->GetCommandList(), spriteCommon_, dXCommon->GetDevice(), effectL[player->GetFeverNum()].vbView);
			}
			pause.SpriteDraw(dXCommon->GetCommandList(), spriteCommon_, dXCommon->GetDevice(), pause.vbView);
			textBox.SpriteDraw(dXCommon->GetCommandList(), spriteCommon_, dXCommon->GetDevice(), textBox.vbView);
			//ようこそ
			if (tutorialStep == 1) {
				if (tutoText == 0) {
					welcomeGame.SpriteDraw(dXCommon->GetCommandList(), spriteCommon_, dXCommon->GetDevice(), welcomeGame.vbView);
				}
				else {
					clearMethod.SpriteDraw(dXCommon->GetCommandList(), spriteCommon_, dXCommon->GetDevice(), clearMethod.vbView);
				}
			}
			//敵倒す
			else if (tutorialStep == 2) {
				if (tutoText == 0) {
					attackMethod_First.SpriteDraw(dXCommon->GetCommandList(), spriteCommon_, dXCommon->GetDevice(), attackMethod_First.vbView);
				}
				else {
					attackMethod_Second.SpriteDraw(dXCommon->GetCommandList(), spriteCommon_, dXCommon->GetDevice(), attackMethod_Second.vbView);
				}
			}
			//スピードアップ
			else if (tutorialStep == 3) {
				feverMode_First.SpriteDraw(dXCommon->GetCommandList(), spriteCommon_, dXCommon->GetDevice(), feverMode_First.vbView);
			}
			//倒せない敵
			else if (tutorialStep == 4) {
				attackMethod_Second.SpriteDraw(dXCommon->GetCommandList(), spriteCommon_, dXCommon->GetDevice(), attackMethod_Second.vbView);
			}
			//HP
			else if (tutorialStep == 5) {
				if (tutoTime < 51) {
					HPframe.SpriteDraw(dXCommon->GetCommandList(), spriteCommon_, dXCommon->GetDevice(), HPframe.vbView);
					for (int i = 0; i < player->GetHP(); i++) {
						hP[i].SpriteDraw(dXCommon->GetCommandList(), spriteCommon_, dXCommon->GetDevice(), hP[i].vbView);
					}
				}
				if (tutoText == 0) {
					enemyCaution.SpriteDraw(dXCommon->GetCommandList(), spriteCommon_, dXCommon->GetDevice(), enemyCaution.vbView);
				}
				else if(tutoText == 1) {
					playerDamage_First.SpriteDraw(dXCommon->GetCommandList(), spriteCommon_, dXCommon->GetDevice(), playerDamage_First.vbView);
				}
				else {
					playerDamage_Second.SpriteDraw(dXCommon->GetCommandList(), spriteCommon_, dXCommon->GetDevice(), playerDamage_Second.vbView);
				}
			}
			//移動
			else if (tutorialStep == 6) {
				if (tutoText == 0) {
					playerMove_First.SpriteDraw(dXCommon->GetCommandList(), spriteCommon_, dXCommon->GetDevice(), playerMove_First.vbView);
				}
				else {
					AorD.SpriteDraw(dXCommon->GetCommandList(), spriteCommon_, dXCommon->GetDevice(), AorD.vbView);
					playerMove_Second.SpriteDraw(dXCommon->GetCommandList(), spriteCommon_, dXCommon->GetDevice(), playerMove_Second.vbView);
				}
			}
			//攻撃
			else if (tutorialStep == 7) {
				attackMethod_Second.SpriteDraw(dXCommon->GetCommandList(), spriteCommon_, dXCommon->GetDevice(), attackMethod_Second.vbView);
			}
			else if (tutorialStep == 8) {
				AorD.SpriteDraw(dXCommon->GetCommandList(), spriteCommon_, dXCommon->GetDevice(), AorD.vbView);
				playerMove_Second.SpriteDraw(dXCommon->GetCommandList(), spriteCommon_, dXCommon->GetDevice(), playerMove_Second.vbView);
			}
			//フィーバー
			else if (tutorialStep == 9) {
				if (tutoTime < 51) {
					gaugeFlame.SpriteDraw(dXCommon->GetCommandList(), spriteCommon_, dXCommon->GetDevice(), gaugeFlame.vbView);
					gauge.SpriteDraw(dXCommon->GetCommandList(), spriteCommon_, dXCommon->GetDevice(), gauge.vbView);
				}
				if (tutoText == 0) {
					feverMode_Second.SpriteDraw(dXCommon->GetCommandList(), spriteCommon_, dXCommon->GetDevice(), feverMode_Second.vbView);
				}
				else {
				
				}
			}
			//フィーバー終わり
			else if (tutorialStep == 10) {
				if (tutoTime < 51) {
					gaugeFlame.SpriteDraw(dXCommon->GetCommandList(), spriteCommon_, dXCommon->GetDevice(), gaugeFlame.vbView);
					gauge.SpriteDraw(dXCommon->GetCommandList(), spriteCommon_, dXCommon->GetDevice(), gauge.vbView);
				}
				if (tutoText == 0) {
					feverEnd_Second.SpriteDraw(dXCommon->GetCommandList(), spriteCommon_, dXCommon->GetDevice(), feverEnd_Second.vbView);
				}
				else {
					feverEnd_First.SpriteDraw(dXCommon->GetCommandList(), spriteCommon_, dXCommon->GetDevice(), feverEnd_First.vbView);
				}
			}
		}
	}

	// スプライト描画後処理
	Sprite::PostDraw();
#pragma endregion
}

void GamePlayScene::Finalize() {
	delete floorModel;
	delete skyModel;
	delete builModel01;
	delete builModel02;
	delete builModel03;
	delete builModel04;
	delete player;
	delete enemy;
	delete invEnemy;
	delete buil;
	delete floor;
	delete sky;
	delete viewProjection;
	delete railCamera;
	delete xmViewProjection;
	delete worldTransform;
	delete particle_1;
	delete pm_1;
	delete particle_2;
	delete pm_2;
	delete p_dmg;
	delete pm_dmg;
	for (int i = 0; i < 3; i++) {
		if (line[i] != nullptr) {
			delete line[i];
		}
	}

	// スプライト解放
	delete sprite;
	sprite = nullptr;
}

void GamePlayScene::LoadEffect(SpriteCommon& spriteCommon) {

	// effect
	//左
	for (int i = 0; i < 6; i++) {
		if (i == 0) {
			effectL[i].LoadTexture(spriteCommon_, 4 + i, L"Resources/EfL1.bmp", dXCommon->GetDevice());
		}
		else if (i == 1) {
			effectL[i].LoadTexture(spriteCommon_, 4 + i, L"Resources/EfL2.bmp", dXCommon->GetDevice());
		}
		else if (i == 2) {
			effectL[i].LoadTexture(spriteCommon_, 4 + i, L"Resources/EfL3.bmp", dXCommon->GetDevice());
		}
		else if (i == 3) {
			effectL[i].LoadTexture(spriteCommon_, 4 + i, L"Resources/EfL4.bmp", dXCommon->GetDevice());
		}
		else if (i == 4) {
			effectL[i].LoadTexture(spriteCommon_, 4 + i, L"Resources/EfL5.bmp", dXCommon->GetDevice());
		}
		else {
			effectL[i].LoadTexture(spriteCommon_, 4 + i, L"Resources/EfL6.bmp", dXCommon->GetDevice());
		}
		effectL[i].SpriteCreate(dXCommon->GetDevice(), 1280, 720, 4 + i, spriteCommon, Vector2(0.0f, 0.0f), false, false);
		effectL[i].SetAlpha(effectL[i], 0.7);
		effectL[i].SetScale(Vector2(1280 * 1, 720 * 1));
		effectL[i].SetRotation(0.0f);
		effectL[i].SetPosition(Vector3(-640, 0, 0));
		effectL[i].SpriteTransferVertexBuffer(effectL[i], spriteCommon, 4 + i);
		effectL[i].SpriteUpdate(effectL[i], spriteCommon_);
	}
	//右
	for (int i = 0; i < 6; i++) {
		if (i == 0) {
			effectR[i].LoadTexture(spriteCommon_, 10 + i, L"Resources/EfR1.jpg", dXCommon->GetDevice());
		}
		else if (i == 1) {
			effectR[i].LoadTexture(spriteCommon_, 10 + i, L"Resources/EfR2.jpg", dXCommon->GetDevice());
		}
		else if (i == 2) {
			effectR[i].LoadTexture(spriteCommon_, 10 + i, L"Resources/EfR3.jpg", dXCommon->GetDevice());
		}
		else if (i == 3) {
			effectR[i].LoadTexture(spriteCommon_, 10 + i, L"Resources/EfR4.jpg", dXCommon->GetDevice());
		}
		else if (i == 4) {
			effectR[i].LoadTexture(spriteCommon_, 10 + i, L"Resources/EfR5.jpg", dXCommon->GetDevice());
		}
		else {
			effectR[i].LoadTexture(spriteCommon_, 10 + i, L"Resources/EfR6.jpg", dXCommon->GetDevice());
		}
		effectR[i].SpriteCreate(dXCommon->GetDevice(), 1280, 720, 10 + i, spriteCommon, Vector2(0.0f, 0.0f), false, false);
		effectR[i].SetAlpha(effectR[i], 0.7);
		effectR[i].SetScale(Vector2(640 * 1, 720 * 1));
		effectR[i].SetRotation(0.0f);
		effectR[i].SetPosition(Vector3(640, 0, 0));
		effectR[i].SpriteTransferVertexBuffer(effectR[i], spriteCommon, 10 + i);
		effectR[i].SpriteUpdate(effectR[i], spriteCommon_);
	}
}

void GamePlayScene::LoadAttackEffect(SpriteCommon& spriteCommon) {
	for (int i = 0; i < 8; i++) {
		if (i == 0) {
			attackEffect[i].LoadTexture(spriteCommon_, 25 + i, L"Resources/airRing_01.png", dXCommon->GetDevice());
		}
		else if (i == 1) {
			attackEffect[i].LoadTexture(spriteCommon_, 25 + i, L"Resources/airRing_02.png", dXCommon->GetDevice());
		}
		else if (i == 2) {
			attackEffect[i].LoadTexture(spriteCommon_, 25 + i, L"Resources/airRing_03.png", dXCommon->GetDevice());
		}
		else if (i == 3) {
			attackEffect[i].LoadTexture(spriteCommon_, 25 + i, L"Resources/airRing_04.png", dXCommon->GetDevice());
		}
		else if (i == 4) {
			attackEffect[i].LoadTexture(spriteCommon_, 25 + i, L"Resources/airRing_05.png", dXCommon->GetDevice());
		}
		else if (i == 5) {
			attackEffect[i].LoadTexture(spriteCommon_, 25 + i, L"Resources/airRing_06.png", dXCommon->GetDevice());
		}
		else if (i == 6) {
			attackEffect[i].LoadTexture(spriteCommon_, 25 + i, L"Resources/airRing_07.png", dXCommon->GetDevice());
		}
		else {
			attackEffect[i].LoadTexture(spriteCommon_, 25 + i, L"Resources/airRing_08.png", dXCommon->GetDevice());
		}
		attackEffect[i].SpriteCreate(dXCommon->GetDevice(), 1280, 720, 25 + i, spriteCommon, Vector2(0.0f, 0.0f), false, false);
		attackEffect[i].SetScale(Vector2(1280 * 1, 720 * 1));
		attackEffect[i].SetRotation(0.0f);
		attackEffect[i].SetPosition(Vector3(0, 0, 0));
		attackEffect[i].SpriteTransferVertexBuffer(attackEffect[i], spriteCommon, 4 + i);
		attackEffect[i].SpriteUpdate(attackEffect[i], spriteCommon_);
	}
}

void GamePlayScene::Reset() {
	delete floorModel;
	delete skyModel;
	delete builModel01;
	delete builModel02;
	delete builModel03;
	delete builModel04;
	delete player;
	delete enemy;
	delete invEnemy;
	delete buil;
	delete floor;
	delete sky;
	delete viewProjection;
	delete railCamera;
	delete xmViewProjection;
	delete worldTransform;
	delete particle_1;
	delete pm_1;
	delete particle_2;
	delete pm_2;
	delete p_dmg;
	delete pm_dmg;

	// OBJからモデルデータを読み込む
	floorModel = Model::LoadFromOBJ("floor");
	skyModel = Model::LoadFromOBJ("skydome");

	builModel01 = Model::LoadFromOBJ("building_01");
	builModel02 = Model::LoadFromOBJ("building_02");
	builModel03 = Model::LoadFromOBJ("building_03");
	builModel04 = Model::LoadFromOBJ("ring");

	if (stageNum != 0) {
		LoadStage(stageNum);
	}
	railCamera = new RailCamera;
	xmViewProjection = new XMViewProjection();
	// 3Dオブジェクト生成
	//床
	floor = Object3d::Create();
	// オブジェクトにモデルをひも付ける
	floor->SetModel(floorModel);
	floor->SetPosition(Vector3(0, -80, 0));
	floor->SetScale(Vector3({ 1000, 1, 1000 }));
	//天球
	sky = Object3d::Create();
	// オブジェクトにモデルをひも付ける
	sky->SetModel(skyModel);
	sky->SetScale(Vector3({ 1000, 1000, 1000 }));

	//player初期化
	player = new Player;
	player->PlayerInitialize();

	//半径分だけ足元から浮いた座標を球の中心にする
	player->SetCollider(new SphereCollider);

	//パーティクル初期化
	particle_1 = Particle::LoadParticleTexture("effect1.png");
	pm_1 = ParticleManager::Create();
	particle_2 = Particle::LoadParticleTexture("effect2.png");
	pm_2 = ParticleManager::Create();
	p_dmg = Particle::LoadParticleTexture("dmg.png");
	pm_dmg = ParticleManager::Create();
	pBomb = Particle::LoadParticleTexture("dmg.png");
	pBombM = ParticleManager::Create();
	pFire = Particle::LoadParticleTexture("dmg.png");
	pFireM = ParticleManager::Create();
	//オブジェクトにモデルを紐付ける
	pm_1->SetParticleModel(particle_1);
	pm_2->SetParticleModel(particle_2);
	pm_dmg->SetParticleModel(p_dmg);
	pBombM->SetParticleModel(pBomb);
	pFireM->SetParticleModel(pFire);
	//カメラをセット
	pm_1->SetXMViewProjection(xmViewProjection);
	pm_2->SetXMViewProjection(xmViewProjection);
	pm_dmg->SetXMViewProjection(xmViewProjection);
	pBombM->SetXMViewProjection(xmViewProjection);
	pFireM->SetXMViewProjection(xmViewProjection);

	railCamera->Initialize();

	titleBack.SetColor(titleBack, Vector4(0.5, 0.5, 0.5, 0.9));
	stageBack.SetColor(stageBack, Vector4(0.5, 0.5, 0.5, 0.9));
	close.SetColor(close, Vector4(1, 1, 0, 1));

	//変数

	gaugeScale = { 3,20 };

	gaugePosition = { 50,167.5f,0 };

	airScale = { 0,0 };

	airPosition = { 0,0,0 };

	isFadeOut = false;
	fadeOut = 0.0f;
	pColor = { 0,0,0,1 }; // ポストエフェクトカラー
	postEffect_->SetColor(pColor);
	titleT = 0.0f;
	isTitleT = false;
	isClearStaging = false;
	cStagingT = 0.0f;
	tutorialStep = 0;
	tutoTime = 0;
	isShowText = false;
	tutoText = 0;
	selectTime = 0.0f;
	isMoveSel = 0;
}

void GamePlayScene::CreatThreeLine(std::vector<Vector3>& points) {

	lineModel = Model::CreateLine(points);

	for (int i = 0; i < 3; i++) {
		line[i] = Line::Create();
		// オブジェクトにモデルをひも付ける
		line[i]->SetModel(lineModel);
	}

	for (int i = 0; i < 2; i++) {
		line[i]->worldTransform_.SetParent3d(&line[0]->worldTransform_);
	}
	line[1]->SetPosition(Vector3(10, 0, 0));
	line[2]->SetPosition(Vector3(-10, 0, 0));

	for (int i = 0; i < 3; i++) {
		line[i]->Update();
	}
}

void GamePlayScene::FadeOut(float pColor_, float fadeOutTimer_) {
	fadeOut++;
	if (0 < fadeOut && fadeOut < fadeOutTimer_) {
		isFadeOut = true;
		if (pColor.x <= 1) {
			pColor += Vector4(pColor_, pColor_, pColor_, 1);
		}
		postEffect_->SetColor(pColor);
	}
	if (fadeOut > 100) {
		isFadeOut = false;
		pColor = { 1,1,1,1 };
		postEffect_->SetColor(pColor);
	}
}

//ステージ選択
void GamePlayScene::StageSelect() {
	static const int STAGE_MAX = 10;
	//演出
	if (input->TriggerKey(DIK_A) || input->TriggerKey(DIK_LEFT)) {
		if (stageNum > 0 && isMoveSel == 0) {
			isMoveSel = 1;
			stageNum--;
		}
	}
	if (input->TriggerKey(DIK_D) || input->TriggerKey(DIK_RIGHT)) {
		if (stageNum < STAGE_MAX && isMoveSel == 0) {
			isMoveSel = 2;
			stageNum++;
		}
	}

	//移動
	if (isMoveSel == 0) {
		if (player->worldTransform_.rotation_.y > 0) {
			player->SetRotation(player->GetRotation() + Vector3(0, -5, 0));
		}
		else if (player->worldTransform_.rotation_.y < 0) {
			player->SetRotation(player->GetRotation() + Vector3(0, 5, 0));
		}
		else{}
	}
	if (isMoveSel > 0) {
		if (isMoveSel == 1) {
			if (player->worldTransform_.rotation_.y > -90) {
				player->SetRotation(player->GetRotation() + Vector3(0, -5, 0));
			}
			if ((stageNum + 1) % 3 == 0) {
				player->worldTransform_.position_.x -= MathFunc::easeInSine(selectTime / 50) * 2.65;
				if (selectTime >= 25) {
					railCamera->GetView()->eye.x -= MathFunc::easeInOutSine(selectTime / 50) * 50;
					railCamera->GetView()->target.x -= MathFunc::easeInOutSine(selectTime / 50) * 50;
				}
			}
			else {
				player->worldTransform_.position_.x -= MathFunc::easeInSine(selectTime / 50) * 2;
			}
		}
		else if (isMoveSel == 2) {
			if (player->worldTransform_.rotation_.y < 90) {
				player->SetRotation(player->GetRotation() + Vector3(0, 5, 0));
			}
			if (stageNum % 3 == 0) {
				player->worldTransform_.position_.x += MathFunc::easeInSine(selectTime / 50) * 2.65;
				if (selectTime >= 25) {
					railCamera->GetView()->eye.x += MathFunc::easeInOutSine(selectTime / 50) * 50;
					railCamera->GetView()->target.x += MathFunc::easeInOutSine(selectTime / 50) * 50;
				}
			}
			else {
				player->worldTransform_.position_.x += MathFunc::easeInSine(selectTime / 50) * 2;
			}
		}

		if (selectTime == 50) {
			selectTime = 0;
			isMoveSel = 0;
		}
		selectTime++;
	}
	railCamera->ViewUpdate();
	player->Update(points);
	//決定
	if (input->TriggerKey(DIK_SPACE) && isMoveSel == 0) {
		selPlayerTmp = player->GetPosition();
		selEyeTmp = railCamera->GetView()->eye;
		selTargetTmp = railCamera->GetView()->target;
		FadeOut(0.01, 100);
		if (stageNum == 0) {
			Reset();
			sceneNum = 0;
		}
		else {
			sceneNum = 2;
			//ステージ
			LoadStage(stageNum);
			//建物
			LoadBuil(stageNum);
			//敵
			LoadEnemy(stageNum);
			//親子構造のセット
			railCamera->SetEye({ 0,5,-800 });
			railCamera->SetTarget({ 0,-5,-750 });
			railCamera->SetPlayer(player);
			player->SetScale(Vector3(0.2, 0.2, 0.2));
		}
	}
}

void GamePlayScene::LoadEnemy(int stageNum) {

	Spline spline;
	spline.Initialize();

	pointsL = points;
	pointsR = points;

	for (int i = 0; i < points.size(); i++)
	{
		pointsL[i] += Vector3(-10, 0, 0);
		pointsR[i] += Vector3(10, 0, 0);
	}

	enemys_.clear();
	invEnemys_.clear();

	//ファイルを開く
	std::ifstream file;
	file.open("Resources/csv/EnemyPop.csv");
	assert(file.is_open());

	HRESULT result = S_FALSE;

	std::string num;
	num = stageNum + 48;

	// １行ずつ読み込む
	string line;
	while (getline(file, line)) {

		// １行分の文字列をストリームに変換して解析しやすくする
		std::istringstream line_stream(line);

		// 半角スパース区切りで行の先頭文字列を取得
		string key;
		getline(line_stream, key, ' ');

		string word;
		getline(line_stream, word, ' ');

		// 先頭文字列がｖなら頂点座標
		if (key == "ea" + num) {
			//敵の生成
			std::unique_ptr<Enemy> newEnemy = std::make_unique<Enemy>();
			//敵の初期化
			newEnemy->EnemyInitialize();
			//コライダーの追加
			newEnemy->SetCollider(new SphereCollider(Vector3(0, 0, 0), 2.0f));
			// X,Y,Z座標読み込み
			Vector3 position{};
			float t;
		
			if (word.find("L") == 0)
			{
				line_stream >> t;
				position = spline.EnemyPosition(pointsL, t);
			}
			else if (word.find("M") == 0) 
			{
				line_stream >> t;
				position = spline.EnemyPosition(points, t);
			}
			else if (word.find("R") == 0) 
			{
				line_stream >> t;
				position = spline.EnemyPosition(pointsR, t);
			}

			// 座標データに追加
			newEnemy->SetPosition(position);
			//登録
			enemys_.push_back(std::move(newEnemy));
		}
		// 先頭文字列がｖなら頂点座標
		if (key == "eb" + num) {
			//敵の生成
			std::unique_ptr<InvisibleEnemy> newInvEnemy = std::make_unique<InvisibleEnemy>();
			//敵の初期化
			newInvEnemy->InvEnemyInitialize();
			//コライダーの追加
			newInvEnemy->SetCollider(new SphereCollider(Vector3(0, 0, 0), 2.0f));
			// X,Y,Z座標読み込み
			Vector3 position{};
			float t;
			if (word.find("L") == 0)
			{
				line_stream >> t;
				position = spline.EnemyPosition(pointsL, t);
			}
			else if (word.find("M") == 0)
			{
				line_stream >> t;
				position = spline.EnemyPosition(points, t);
			}
			else if (word.find("R") == 0)
			{
				line_stream >> t;
				position = spline.EnemyPosition(pointsR, t);
			}
			// 座標データに追加
			newInvEnemy->SetPosition(position);
			//登録
			invEnemys_.push_back(std::move(newInvEnemy));
		}
	}
	// ファイルと閉じる
	file.close();
}

void GamePlayScene::LoadStage(int stageNum) {
	points.clear();

	//ファイルを開く
	std::ifstream file;
	file.open("Resources/csv/stagePop.csv");
	assert(file.is_open());

	HRESULT result = S_FALSE;

	std::string num;
	num = stageNum + 48;

	// １行ずつ読み込む
	string line;
	while (getline(file, line)) {

		// １行分の文字列をストリームに変換して解析しやすくする
		std::istringstream line_stream(line);

		// 半角スパース区切りで行の先頭文字列を取得
		string key;
		getline(line_stream, key, ' ');


		// 先頭文字列がｖなら頂点座標
		if (key == "st" + num) {
			// X,Y,Z座標読み込み
			Vector3 position{};
			line_stream >> position.x;
			line_stream >> position.y;
			line_stream >> position.z;
			// 座標データに追加
			points.emplace_back(position);
		}
		if (stageNum == 10) {
			if (key == "st10") {
				// X,Y,Z座標読み込み
				Vector3 position{};
				line_stream >> position.x;
				line_stream >> position.y;
				line_stream >> position.z;
				// 座標データに追加
				points.emplace_back(position);
			}
		}
		else if (stageNum > 10) {
			if (key == "st1" + stageNum - 10) {
				// X,Y,Z座標読み込み
				Vector3 position{};
				line_stream >> position.x;
				line_stream >> position.y;
				line_stream >> position.z;
				// 座標データに追加
				points.emplace_back(position);
			}
		}
	}
	// ファイルと閉じる
	file.close();

	CreatThreeLine(points);
}

void GamePlayScene::LoadBuil(int stageNum)
{
	buils_.clear();

	//ファイルを開く
	std::ifstream file;
	file.open("Resources/csv/builPop.csv");
	assert(file.is_open());

	HRESULT result = S_FALSE;

	std::string num;
	num = stageNum + 48;

	// １行ずつ読み込む
	string line;
	while (getline(file, line)) {

		// １行分の文字列をストリームに変換して解析しやすくする
		std::istringstream line_stream(line);

		// 半角スパース区切りで行の先頭文字列を取得
		string key;
		getline(line_stream, key, ' ');

		// 先頭文字列がbなら頂点座標
		if (key == "ba" + num) {
			//初期化
			std::unique_ptr<Object3d> newBuil = std::make_unique<Object3d>();
			newBuil->Initialize();
			newBuil->SetModel(builModel01);
			newBuil->SetScale(Vector3{ 10,10,10 });
			// X,Y,Z座標読み込み
			Vector3 position{};
			line_stream >> position.x;
			line_stream >> position.y;
			line_stream >> position.z;
			// 座標データに追加
			newBuil->SetPosition(position);
			//登録
			buils_.push_back(std::move(newBuil));
		}
		if (key == "bb" + num) {
			//初期化
			std::unique_ptr<Object3d> newBuil = std::make_unique<Object3d>();
			newBuil->Initialize();
			newBuil->SetModel(builModel02);
			newBuil->SetScale(Vector3{ 12,12,12 });
			// X,Y,Z座標読み込み
			Vector3 position{};
			line_stream >> position.x;
			line_stream >> position.y;
			line_stream >> position.z;
			// 座標データに追加
			newBuil->SetPosition(position);
			//登録
			buils_.push_back(std::move(newBuil));
		}
		if (key == "bc" + num) {
			//初期化
			std::unique_ptr<Object3d> newBuil = std::make_unique<Object3d>();
			newBuil->Initialize();
			newBuil->SetModel(builModel03);
			newBuil->SetScale(Vector3{ 10,10,10 });
			// X,Y,Z座標読み込み
			Vector3 position{};
			line_stream >> position.x;
			line_stream >> position.y;
			line_stream >> position.z;
			// 座標データに追加
			newBuil->SetPosition(position);
			//登録
			buils_.push_back(std::move(newBuil));
		}
		if (key == "bd" + num) {
			//初期化
			std::unique_ptr<Object3d> newBuil = std::make_unique<Object3d>();
			newBuil->Initialize();
			newBuil->SetModel(builModel04);
			newBuil->SetScale(Vector3{ 3,10,10 });
			// X,Y,Z座標読み込み
			Vector3 position{};
			Vector3 rotation{};
			line_stream >> position.x;
			line_stream >> position.y;
			line_stream >> position.z;
			line_stream >> rotation.y;
			// 座標データに追加
			newBuil->SetPosition(position);
			newBuil->SetRotation(rotation);
			//登録
			buils_.push_back(std::move(newBuil));
		}
	}
	// ファイルと閉じる
	file.close();

}

void GamePlayScene::TutorialUpdate() {
	if (stageNum == 1) {
		//ステップ1
		if (tutorialStep == 0) {
			if (railCamera->GetCamera()->GetPosition().z >= -790) {
				isShowText = true;
				tutorialStep = 1;
			}
		}
		else if (tutorialStep == 1) {
			if (railCamera->GetCamera()->GetPosition().z >= -760) {
				isShowText = true;
				tutorialStep = 2;
			}
		}
		else if (tutorialStep == 2) {
			if (railCamera->GetCamera()->GetPosition().z >= -740) {
				isShowText = true;
				tutorialStep = 3;
			}
		}
		else if (tutorialStep == 3) {
			if (railCamera->GetCamera()->GetPosition().z >= -610) {
				isShowText = true;
				tutorialStep = 4;
			}
		}
		else if (tutorialStep == 4) {
			if (railCamera->GetCamera()->GetPosition().z >= -580) {
				isShowText = true;
				tutorialStep = 5;
			}
		}
		else if (tutorialStep == 5) {
			if (railCamera->GetCamera()->GetPosition().z >= -550) {
				isShowText = true;
				tutorialStep = 6;
			}
		}
		else if (tutorialStep == 6) {
			if (railCamera->GetCamera()->GetPosition().z >= -510) {
				isShowText = true;
				tutorialStep = 7;
			}
		}
		else if (tutorialStep == 7) {
			if (railCamera->GetCamera()->GetPosition().z >= -430) {
				isShowText = true;
				tutorialStep = 8;
			}
		}
		else if (tutorialStep == 8) {
			if (player->GetFever() == true) {
				isShowText = true;
				tutorialStep = 9;
			}
		}
		else if (tutorialStep == 9) {
			if (player->GetFever() == false) {
				isShowText = true;
				tutorialStep = 10;
			}
		}


	}
}