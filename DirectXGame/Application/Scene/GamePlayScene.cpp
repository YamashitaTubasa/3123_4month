#include "GamePlayScene.h"
#include "spline.h"
#include <fstream>
#include "SphereCollider.h"
#include "CollisionManager.h"
#include"Player.h"

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

	// OBJからモデルデータを読み込む
	skyModel = Model::LoadFromOBJ("skydome");

	// 3Dオブジェクト生成
	sky = Object3d::Create();
	// オブジェクトにモデルをひも付ける
	sky->SetModel(skyModel);
	sky->SetScale(Vector3({ 1000, 1000, 1000 }));

	//player初期化
	player = new Player;
	player->PlayerInitialize();

	//半径分だけ足元から浮いた座標を球の中心にする
	player->SetCollider(new SphereCollider);

	//攻撃初期化
	playerAttack = new PlayerAttack;
	playerAttack->AttackInitialize(player);

	//半径分だけ足元から浮いた座標を球の中心にする
	playerAttack->SetCollider(new SphereCollider(Vector3(0,0,0),3.0f));

	//敵の情報の初期化
	LoadEnemyPopData();

	//ステージ
	// OBJからモデルデータを読み込む
	stageModel = Model::LoadFromOBJ("triangle_mat");

	// 3Dオブジェクト生成
	stage = Object3d::Create();
	// オブジェクトにモデルをひも付ける
	stage->SetModel(stageModel);
	stage->SetScale(Vector3({ 80, 20, 20 }));
	stage->SetPosition(Vector3(0, -26, -775));

	//パーティクル初期化
	particle_1 = Particle::LoadParticleTexture("effect1.png");
	pm_1 = ParticleManager::Create();
	particle_2 = Particle::LoadParticleTexture("effect2.png");
	pm_2 = ParticleManager::Create();
	p_dmg = Particle::LoadParticleTexture("dmg.png");
	pm_dmg = ParticleManager::Create();
	//オブジェクトにモデルを紐付ける
	pm_1->SetParticleModel(particle_1);
	pm_2->SetParticleModel(particle_2);
	pm_dmg->SetParticleModel(p_dmg);
	//カメラをセット
	pm_1->SetXMViewProjection(xmViewProjection);
	pm_2->SetXMViewProjection(xmViewProjection);
	pm_dmg->SetXMViewProjection(xmViewProjection);

	// スプライトの初期化
	// スプライト
	sprite = new Sprite();
	spriteCommon_ = sprite->SpriteCommonCreate(dXCommon->GetDevice(), 1280, 720);
	// スプライト用パイプライン生成呼び出し
	PipelineSet spritePipelineSet = sprite->SpriteCreateGraphicsPipeline(dXCommon->GetDevice());

	// HP
	for (int i = 0; i < 3; i++) {
		hP[i].LoadTexture(spriteCommon_, 3, L"Resources/hp.png", dXCommon->GetDevice());
		hP[i].SetColor(Vector4(1, 1, 1, 1));
		hP[i].SpriteCreate(dXCommon->GetDevice(), 50, 50, 3, spriteCommon, Vector2(0.0f, 0.0f), false, false);
		hP[i].SetPosition(Vector3(0 + (i * 64), 0, 0));
		hP[i].SetScale(Vector2(50 * 1, 50 * 1));
		hP[i].SetRotation(0.0f);
		hP[i].SpriteTransferVertexBuffer(hP[i], spriteCommon, 3);
		hP[i].SpriteUpdate(hP[i], spriteCommon_);
	}

	LoadEffect(spriteCommon);

	//title
	title.LoadTexture(spriteCommon_, 17, L"Resources/title.png", dXCommon->GetDevice());
	title.SetColor(Vector4(1, 1, 1, 1));
	title.SpriteCreate(dXCommon->GetDevice(), 1280, 720, 17, spriteCommon, Vector2(0.0f, 0.0f), false, false);
	title.SetPosition(Vector3(0, 0, 0));
	title.SetScale(Vector2(1280 * 1, 720 * 1));
	title.SetRotation(0.0f);
	title.SpriteTransferVertexBuffer(title, spriteCommon, 17);
	title.SpriteUpdate(title, spriteCommon_);
	//clear
	clear.LoadTexture(spriteCommon_, 18, L"Resources/clear.png", dXCommon->GetDevice());
	clear.SetColor(Vector4(1, 1, 1, 1));
	clear.SpriteCreate(dXCommon->GetDevice(), 1280, 720, 18, spriteCommon, Vector2(0.0f, 0.0f), false, false);
	clear.SetPosition(Vector3(0, 0, 0));
	clear.SetScale(Vector2(1280 * 1, 720 * 1));
	clear.SetRotation(0.0f);
	clear.SpriteTransferVertexBuffer(clear, spriteCommon, 18);
	clear.SpriteUpdate(clear, spriteCommon_);
	//over
	over.LoadTexture(spriteCommon_, 19, L"Resources/gameover.png", dXCommon->GetDevice());
	over.SetColor(Vector4(1, 1, 1, 1));
	over.SpriteCreate(dXCommon->GetDevice(), 1280, 720, 19, spriteCommon, Vector2(0.0f, 0.0f), false, false);
	over.SetPosition(Vector3(0, 0, 0));
	over.SetScale(Vector2(1280 * 1, 720 * 1));
	over.SetRotation(0.0f);
	over.SpriteTransferVertexBuffer(over, spriteCommon, 19);
	over.SpriteUpdate(over, spriteCommon_);
	//back
	back.LoadTexture(spriteCommon_, 7, L"Resources/back.png", dXCommon->GetDevice());
	back.SetColor(Vector4(1, 1, 1, 1));
	back.SpriteCreate(dXCommon->GetDevice(), 1280, 720, 7, spriteCommon, Vector2(0.0f, 0.0f), false, false);
	back.SetPosition(Vector3(0, 0, 0));
	back.SetScale(Vector2(1280 * 1, 720 * 1));
	back.SetRotation(0.0f);
	back.SpriteTransferVertexBuffer(back, spriteCommon, 7);
	back.SpriteUpdate(back, spriteCommon_);

	//レールカメラ初期化
	railCamera->Initialize();

	//レーン
	start = { 0.0f, 0.0f, -800.0f };		//スタート地点
	p2 = { 100.0f, 0.0f, -750.0f };		//制御点その1
	p3 = { -200.0f, 0.0f, 0.0f };			//制御点その2
	p4 = { 500.0f, -300.0f, -400.0 };
	end = { -300.0f, 300.0f, 800.0f };		//ゴール地点

	points = { start,start,p2,p3,p4,end,end };

	lineModel = Model::CreateLine(points);

	// 3Dオブジェクト生成
	line = Line::Create();
	// オブジェクトにモデルをひも付ける
	line->SetModel(lineModel);
	line->SetPosition(Vector3(0, -5, 0));
}

void GamePlayScene::Update() {
	switch (sceneNum)
	{
	case 0:
		if (input->TriggerKey(DIK_SPACE)) {
			sceneNum = 1;
		}
		break;

	case 1:
		//デスフラグの立った敵を削除
		enemys_.remove_if([](std::unique_ptr < Enemy>& enemy_)
			{
				return enemy_->GetIsDead();
			});

		// スタート画面演出
		startE++;
		if (startE < 50) {
			isStartE = true;
		}
		if (startE > 50) {
			isStartE = false;
		}

		//カメラ更新
		railCamera->Update(player, playerAttack, points);
		//プレイヤー
		player->Update();
		playerAttack->Update();
		//ステージ
		stage->Update();
		line->Update();
		//天球
		sky->Update();

		//パーティクル
		pm_1->Update();
		pm_2->Update();
		pm_dmg->Update();

		// ダメージを受けた時の画面演出
		if (player->GetIsHit() == true) {
			isBack = true;
		}
		if (isBack == true) {
			backT++;
		}
		if (backT >= 50) {
			isBack = false;
			backT = 0.0f;
		}


		// 敵を倒した時の演出
		if (playerAttack->GetIsDead() == true) {
			isDeadT++;
		}
		if (isDeadT >= 20) {
			playerAttack->SetIsDead(false);
			isDeadT = 0.0f;
		}
		if (playerAttack->GetIsDead() == true) {
			pm_dmg->Fire(p_dmg, 30, 0.2f, 0, 3, { 4.0f, 0.0f });
		}

		//更新コマンド
		UpdateEnemyPopCommands();

		//敵キャラの更新
		for (const std::unique_ptr<Enemy>& enemy : enemys_) {
			enemy->SetGameScene(this);
			enemy->Update();
		}

		//全ての衝突をチェック
		collisionManager->CheckAllCollisions();

		//パーティクル発生実験
		/*if (player->GetIsHit() == true)
		{
			pm_1->Fire(particle_1, 30, 0.2f, 0, 20, { 8.0f, 0.0f });
			pm_2->Fire(particle_2, 70, 0.2f, 0, 20, { 4.0f,0.0f });
		}*/

		//ゲームオーバー
		if (player->GetHP() == 0) {
			sceneNum = 3;
		}
		//クリア
		if (railCamera->GetIsEnd() == true) {
			sceneNum = 2;
		}

		break;
	//クリア
	case 2:
		if (input->TriggerKey(DIK_SPACE)) {
			Reset();
			sceneNum = 0;
		}
		break;
	//ゲームオーバー
	case 3:
		if (input->TriggerKey(DIK_SPACE)) {
			Reset();
			sceneNum = 0;
		}
		break;
	}
}

void GamePlayScene::Draw(SpriteCommon& spriteCommon) {
#pragma region 3Dオブジェクト描画

	// 3Dオブジェクト描画前処理
	Object3d::PreDraw(dXCommon->GetCommandList());

	if (sceneNum == 1) {
		sky->Draw(railCamera->GetView());
		stage->Draw(railCamera->GetView());
		//敵キャラの描画
		for (const std::unique_ptr<Enemy>& enemy : enemys_) {
			enemy->Draw(railCamera->GetView());
		}
	}

	// 3Dオブジェクト描画後処理
	Object3d::PostDraw();

#pragma endregion レール


	// 3Dオブジェクト描画前処理
	Line::PreDraw(dXCommon->GetCommandList());

	line->Draw(railCamera->GetView());

	// 3Dオブジェクト描画後処理
	Line::PostDraw();

#pragma region パーティクル描画

	// パーティクル描画前処理
	ParticleManager::PreDraw(dXCommon->GetCommandList());

	///==== パーティクル描画 ====///
	//パーティクル

	pm_1->Draw();
	pm_2->Draw();
	pm_dmg->Draw();

	// パーティクル描画後処理
	ParticleManager::PostDraw();

#pragma endregion

#pragma region スプライト描画

	// スプライト描画前処理
	Sprite::PreDraw(dXCommon->GetCommandList(), spriteCommon_);

	///=== スプライト描画 ===///
	if (sceneNum == 0) {
		title.SpriteDraw(dXCommon->GetCommandList(), spriteCommon_, dXCommon->GetDevice(), title.vbView);
	}
	else if (sceneNum == 1) {
		for (int i = 0; i < player->GetHP(); i++) {
			hP[i].SpriteDraw(dXCommon->GetCommandList(), spriteCommon_, dXCommon->GetDevice(), hP[i].vbView);
		}
		if (playerAttack->GetFever() == true) {
			effectR[playerAttack->GetFeverNum()].SpriteDraw(dXCommon->GetCommandList(), spriteCommon_, dXCommon->GetDevice(), effectR[playerAttack->GetFeverNum()].vbView);
			effectL[playerAttack->GetFeverNum()].SpriteDraw(dXCommon->GetCommandList(), spriteCommon_, dXCommon->GetDevice(), effectL[playerAttack->GetFeverNum()].vbView);
		}
		if (isBack == true) {
			back.SpriteDraw(dXCommon->GetCommandList(), spriteCommon_, dXCommon->GetDevice(), back.vbView);
		}
	}
	else if(sceneNum == 2) {
		clear.SpriteDraw(dXCommon->GetCommandList(), spriteCommon_, dXCommon->GetDevice(), clear.vbView);
	}
	else if(sceneNum == 3) {
		over.SpriteDraw(dXCommon->GetCommandList(), spriteCommon_, dXCommon->GetDevice(), over.vbView);
	}


	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion

#pragma region 3Dオブジェクト描画

	// 3Dオブジェクト描画前処理
	Object3d::PreDraw(dXCommon->GetCommandList());
	if (sceneNum == 1) {
		////playerを画像より手前に出したい
		player->Draw(railCamera->GetView());
		if (playerAttack->GetIsPush() == true) {
			playerAttack->Draw(railCamera->GetView());
		}
		////敵キャラの描画
		//for (const std::unique_ptr<Enemy>& enemy : enemys_) {
		//	enemy->Draw(railCamera->GetView());
		//}
	}
	// 3Dオブジェクト描画後処理
	Object3d::PostDraw();

#pragma endregion
}

void GamePlayScene::Finalize() {
	delete player;
	delete enemy;
	delete sky;
	delete skyModel;

	// スプライト解放
	delete sprite;
	sprite = nullptr;
}

void GamePlayScene::EnemyOcurrence(const Vector3& v)
{
	//敵の生成
	std::unique_ptr<Enemy> newEnemy = std::make_unique<Enemy>();
	//敵の初期化
	newEnemy->EnemyInitialize(Vector3(v.x, v.y, v.z));
	//コライダーの追加
	newEnemy->SetCollider(new SphereCollider(Vector3(0,0,0),2.0f));
	//敵の登録
	enemys_.push_back(std::move(newEnemy));
}

void GamePlayScene::LoadEnemyPopData()
{
	//ファイルを開く
	std::ifstream file;
	file.open("Resources/enemyPop.csv");
	assert(file.is_open());

	//ファイルの内容を文字列ストリームにコピー
	enemyPopCommands << file.rdbuf();

	//ファイルを閉じる
	file.close();
}

void GamePlayScene::UpdateEnemyPopCommands()
{
	//待機処理
	if (isWait_)
	{
		waitTimer--;
		if (waitTimer <= 0)
		{
			//待機完了
			isWait_ = false;
		}
		return;
	}

	//1桁分の文字列を入れる変数
	std::string line;

	//コマンド実行ループ
	while (getline(enemyPopCommands, line))
	{
		//1桁分文字列をストリームに変換して解析しやすくする
		std::istringstream line_stream(line);

		std::string word;
		//,区切りで行の先頭文字列を取得
		getline(line_stream, word, ',');

		//"//"から始まる行はコメント
		if (word.find("//") == 0)
		{
			//コメント行を飛ばす
			continue;
		}

		//POPコマンド
		if (word.find("POP") == 0)
		{
			//x座標
			getline(line_stream, word, ',');
			float x = (float)std::atof(word.c_str());

			//y座標
			getline(line_stream, word, ',');
			float y = (float)std::atof(word.c_str());

			//z座標
			getline(line_stream, word, ',');
			float z = (float)std::atof(word.c_str());

			//敵を発生させる
			EnemyOcurrence(Vector3(x, y, z));
		}

		//WAITコマンド
		else if (word.find("WAIT") == 0)
		{
			getline(line_stream, word, ',');

			//待ち時間
			int32_t waitTime = atoi(word.c_str());

			//待機開始
			isWait_ = true;
			waitTimer = waitTime;

			//コマンドループを抜ける
			break;
		}
	}
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
		effectL[i].SetColor(Vector4(1, 1, 1, 0.8));
		effectL[i].SpriteCreate(dXCommon->GetDevice(), 1280, 720, 4 + i, spriteCommon, Vector2(0.0f, 0.0f), false, false);
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
		effectR[i].SetColor(Vector4(1, 1, 1, 0.9));
		effectR[i].SpriteCreate(dXCommon->GetDevice(), 1280, 720, 10 + i, spriteCommon, Vector2(0.0f, 0.0f), false, false);
		effectR[i].SetScale(Vector2(640 * 1, 720 * 1));
		effectR[i].SetRotation(0.0f);
		effectR[i].SetPosition(Vector3(640, 0, 0));
		effectR[i].SpriteTransferVertexBuffer(effectR[i], spriteCommon, 10 + i);
		effectR[i].SpriteUpdate(effectR[i], spriteCommon_);
	}
}

void GamePlayScene::Reset() {
	delete skyModel;
	delete stageModel;
	delete player;
	delete playerAttack;
	delete enemy;
	delete sky;
	delete stage;
	delete viewProjection;
	delete railCamera;
	delete xmViewProjection;
	delete worldTransform;
	delete particle_1;
	delete pm_1;
	delete particle_2;
	delete pm_2;
	delete line;
	delete p_dmg;
	delete pm_dmg;

	railCamera = new RailCamera;
	xmViewProjection = new XMViewProjection();

	// OBJからモデルデータを読み込む
	skyModel = Model::LoadFromOBJ("skydome");

	// 3Dオブジェクト生成
	sky = Object3d::Create();
	// オブジェクトにモデルをひも付ける
	sky->SetModel(skyModel);
	sky->SetScale(Vector3({ 1000, 1000, 1000 }));

	//player初期化
	player = new Player;
	player->PlayerInitialize();

	//半径分だけ足元から浮いた座標を球の中心にする
	player->SetCollider(new SphereCollider);

	//攻撃初期化
	playerAttack = new PlayerAttack;
	playerAttack->AttackInitialize(player);

	//半径分だけ足元から浮いた座標を球の中心にする
	playerAttack->SetCollider(new SphereCollider(Vector3(0, 0, 0), 3.0f));

	//敵の情報の初期化
	LoadEnemyPopData();

	//ステージ
	// OBJからモデルデータを読み込む
	stageModel = Model::LoadFromOBJ("triangle_mat");

	// 3Dオブジェクト生成
	stage = Object3d::Create();
	// オブジェクトにモデルをひも付ける
	stage->SetModel(stageModel);
	stage->SetScale(Vector3({ 80, 20, 20 }));
	stage->SetPosition(Vector3(0, -26, -775));


	//パーティクル初期化
	particle_1 = Particle::LoadParticleTexture("effect1.png");
	pm_1 = ParticleManager::Create();
	particle_2 = Particle::LoadParticleTexture("effect2.png");
	pm_2 = ParticleManager::Create();
	p_dmg = Particle::LoadParticleTexture("dmg.png");
	pm_dmg = ParticleManager::Create();
	//オブジェクトにモデルを紐付ける
	pm_1->SetParticleModel(particle_1);
	pm_2->SetParticleModel(particle_2);
	pm_dmg->SetParticleModel(p_dmg);
	//カメラをセット
	pm_1->SetXMViewProjection(xmViewProjection);
	pm_2->SetXMViewProjection(xmViewProjection);
	pm_dmg->SetXMViewProjection(xmViewProjection);

	railCamera->Initialize();


	lineModel = Model::CreateLine(points);
	// 3Dオブジェクト生成
	line = Line::Create();
	// オブジェクトにモデルをひも付ける
	line->SetModel(lineModel);
	line->SetPosition(Vector3(0, -5, 0));

	//変数
	//敵の打ち出すまでの時間
	enemyDalayTimer = 0.0f;

	isWait_ = false;

	waitTimer = 300;


}