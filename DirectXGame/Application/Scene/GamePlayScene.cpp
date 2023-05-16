#include "GamePlayScene.h"
#include "spline.h"
#include <fstream>
#include "SphereCollider.h"
#include "CollisionManager.h"
#include "Player.h"
#include "WorldTransform.h"

int GamePlayScene::sceneNum = 0;

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

	// 3Dオブジェクト生成
	//床
	floor = Object3d::Create();
	// オブジェクトにモデルをひも付ける
	floor->SetModel(floorModel);
	floor->SetPosition(Vector3(0, -500, 0));
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

	//敵の情報の初期化
	LoadEnemyPopData();

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
		hP[i].LoadTexture(spriteCommon_, 3, L"Resources/hitPoint.png", dXCommon->GetDevice());
		hP[i].SetColor(Vector4(1, 1, 1, 1));
		hP[i].SpriteCreate(dXCommon->GetDevice(), 50, 50, 3, spriteCommon, Vector2(0.0f, 0.0f), false, false);
		hP[i].SetPosition(Vector3(40 + (i * 60), 30, 0));
		hP[i].SetScale(Vector2(40 * 1, 40 * 1));
		hP[i].SetRotation(0.0f);
		hP[i].SpriteTransferVertexBuffer(hP[i], spriteCommon, 3);
		hP[i].SpriteUpdate(hP[i], spriteCommon_);
	}

	//gaugeFlame
	gaugeFlame.LoadTexture(spriteCommon_, 20, L"Resources/gaugeFlame_01.png", dXCommon->GetDevice());
	gaugeFlame.SetColor(Vector4(1, 1, 1, 1));
	gaugeFlame.SpriteCreate(dXCommon->GetDevice(), 128, 64, 20, spriteCommon, Vector2(0.0f, 0.0f), false, false);
	gaugeFlame.SetPosition(Vector3(45, 120, 0));
	gaugeFlame.SetScale(Vector2(150, 35));
	gaugeFlame.SetRotation(0.0f);
	gaugeFlame.SpriteTransferVertexBuffer(gaugeFlame, spriteCommon, 20);
	gaugeFlame.SpriteUpdate(gaugeFlame, spriteCommon_);

	//gauge
	gauge.LoadTexture(spriteCommon_, 21, L"Resources/gaugeOne.png", dXCommon->GetDevice());
	gauge.SetColor(Vector4(1, 1, 1, 1));
	gauge.SpriteCreate(dXCommon->GetDevice(), 110, 26, 21, spriteCommon, Vector2(0.0f, 0.5f), false, false);
	gauge.SetPosition(Vector3(gaugePosition.x, gaugePosition.y, gaugePosition.z));
	gauge.SetScale(Vector2(gaugeScale.x, gaugeScale.y));
	gauge.SetRotation(0.0f);
	gauge.SpriteTransferVertexBuffer(gauge, spriteCommon, 21);
	gauge.SpriteUpdate(gauge, spriteCommon_);

	//UIboard
	//board.LoadTexture(spriteCommon_, 22, L"Resources/UIboard.png", dXCommon->GetDevice());
	//board.SetColor(Vector4(1, 1, 1, 0.9));
	//board.SpriteCreate(dXCommon->GetDevice(), 128, 128, 22, spriteCommon, Vector2(0.0f, 0.0f), false, false);
	//board.SetPosition(Vector3(0, 0, 0));
	//board.SetScale(Vector2(240, 225));
	//board.SetRotation(0.0f);
	//board.SpriteTransferVertexBuffer(board, spriteCommon, 22);
	//board.SpriteUpdate(board, spriteCommon_);

	//SpaceButton
	spaButton.LoadTexture(spriteCommon_, 23, L"Resources/space.png", dXCommon->GetDevice());
	spaButton.SetColor(Vector4(1, 1, 1, 1));
	spaButton.SpriteCreate(dXCommon->GetDevice(), 412, 95, 23, spriteCommon, Vector2(0.0f, 0.0f), false, false);
	spaButton.SetPosition(Vector3(440, 610, 0));
	spaButton.SetScale(Vector2(412, 95));
	spaButton.SetRotation(0.0f);
	spaButton.SpriteTransferVertexBuffer(spaButton, spriteCommon, 23);
	spaButton.SpriteUpdate(spaButton, spriteCommon_);

	LoadEffect(spriteCommon);
	LoadAttackEffect(spriteCommon);

	//title
	title.LoadTexture(spriteCommon_, 17, L"Resources/RideLight.png", dXCommon->GetDevice());
	title.SetColor(Vector4(1, 1, 1, 1));
	title.SpriteCreate(dXCommon->GetDevice(), 1280, 720, 17, spriteCommon, Vector2(0.0f, 0.0f), false, false);
	title.SetPosition(Vector3(730, 10, 0));
	title.SetScale(Vector2(640 * 1, 360 * 1));
	title.SetRotation(0.0f);
	title.SpriteTransferVertexBuffer(title, spriteCommon, 17);
	title.SpriteUpdate(title, spriteCommon_);
	//clear
	clear.LoadTexture(spriteCommon_, 18, L"Resources/GameClear.png", dXCommon->GetDevice());
	clear.SetColor(Vector4(1, 1, 1, 1));
	clear.SpriteCreate(dXCommon->GetDevice(), 1280, 720, 18, spriteCommon, Vector2(0.0f, 0.0f), false, false);
	clear.SetPosition(Vector3(0, 0, 0));
	clear.SetScale(Vector2(1280 * 1, 720 * 1));
	clear.SetRotation(0.0f);
	clear.SpriteTransferVertexBuffer(clear, spriteCommon, 18);
	clear.SpriteUpdate(clear, spriteCommon_);
	//over
	over.LoadTexture(spriteCommon_, 19, L"Resources/GameOver_01.png", dXCommon->GetDevice());
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

	sceneNum = 0;
	selectPause = 1;
	stageNum = 49;

	////制御点
	//start = { 0.0f, 0.0f, -800.0f };		//スタート地点
	//p2 = { 100.0f, 0.0f, -750.0f };			//制御点その1
	//p3 = { -200.0f, 0.0f, -600.0f };			//制御点その2
	//p4 = { -400.0f, -50.0f, -400.0 };
	//p5 = { -200.0f, 50.0f, -100.0 };
	//p6 = { -100.0f, 0.0f, 0.0 };
	//p7 = { 100.0f, 0.0f, 200.0 };
	//p8 = { 100.0f, 50.0f, 400.0 };
	//p9 = { -100.0f, 100.0f, 600.0 };
	//end = { -300.0f, 100.0f, 800.0f };

	//points = { start,start,p2,p3,p4,p5,p6,p7,p8,p9,end,end };

	LoadStage(stageNum);

	CreatThreeLine(points);

}

void GamePlayScene::Update(SpriteCommon& spriteCommon) {
	switch (sceneNum) {
	case 0:
		// スタート画面フェードアウト演出
		FadeOut();
		
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
			railCamera->SetPlayer(player);
			sceneNum = 1;
		}
		break;

	case 1:
		// ゲーム画面フェードアウト演出
		FadeOut();

		//デスフラグの立った敵を削除
		enemys_.remove_if([](std::unique_ptr < Enemy>& enemy_) {
			return enemy_->GetIsDead();
			});

		gauge.GetScale();

		if (isMaxGauge == true) {
			if (gaugeScale.x >= 4) {
				gaugeScale.x -= 0.55;
			}
			else {
				isMaxGauge = false;
			}
		}

		gauge.SetPosition(gauge.GetPosition() + Vector3(1, 0, 0));
		//gauge.SpriteUpdate(gauge, spriteCommon_);

		if (player->GetGaugeAdd() == true) {
			player->SetGaugeAdd(false);
			calRes = static_cast<float>(140) / (player->GetDivide() + 1);
			gaugeScale.x += calRes;

		}
		if (gaugeScale.x >= 140) {
			if (isMaxGauge == false) {
				isMaxGauge = true;
			}
		}

		gauge.SetScale(Vector2(gaugeScale.x, gaugeScale.y));
		gauge.SpriteTransferVertexBuffer(gauge, spriteCommon, 21);

		//カメラ更新
		if (railCamera->GetIsEnd() == false) {
			railCamera->Update(player, points);
		}
		//プレイヤー
		player->Update(points);
		//ステージ
		//天球
		floor->Update();
		sky->Update();

		//パーティクル
		pm_1->Update();
		pm_2->Update();
		pm_dmg->Update();

		// ダメージを受けた時の画面演出
		if (player->GetIsPush() == false) {
			if (player->GetIsHit() == true)
			{
				isBack = true;
			}
		}
		if (isBack == true) {
			backT++;
		}
		if (backT >= 50) {
			isBack = false;
			backT = 0.0f;
		}

		// 敵を倒した時の演出
		if (player->GetIsBurst() == true) {
			isDeadT++;
		}
		if (isDeadT >= 20) {
			player->SetIsBurst(false);
			isDeadT = 0.0f;
		}
		if (player->GetIsBurst() == true) {
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

		//ポーズ画面
		if (input->TriggerKey(DIK_P) || input->TriggerKey(DIK_TAB)) {
			selectPause = 1;
			sceneNum = 4;
		}

		//ゲームオーバー
		if (player->GetHP() == 0) {
			sceneNum = 3;
		}
		//クリア
		if (railCamera->GetIsEnd() == true) {

			cStagingT++;
			isClearStaging = true;
			player->SetPosition(player->GetPosition() + Vector3(0, 0, 0.8));
			Vector3 behindVec = (railCamera->GetView()->target - railCamera->GetView()->eye)* -1;
			behindVec /= 80;
			railCamera->SetEye(railCamera->GetView()->eye + behindVec);

			if (cStagingT >= 100) {
				sceneNum = 2;
				isClearStaging = false;
			}
		}

		break;
		//クリア
	case 2:
		// クリア画面フェードアウト演出
		FadeOut();

		if (input->TriggerKey(DIK_SPACE)) {
			Reset();
			sceneNum = 0;
		}
		break;
		//ゲームオーバー
	case 3:
		// ゲームオーバー画面フェードアウト演出
		FadeOut();

		if (input->TriggerKey(DIK_SPACE)) {
			Reset();
			sceneNum = 0;
		}
		break;
	case 4://ポーズ画面
		postEffect_->SetColor(Vector4(0.3,0.3,0.3,1));
		if (input->TriggerKey(DIK_W) || input->TriggerKey(DIK_UP)) {
			if (selectPause <= 0) {
				selectPause++;
			}
		}
		if (input->TriggerKey(DIK_S) || input->TriggerKey(DIK_DOWN)) {
			if (selectPause > 0) {
				selectPause--;
			}
		}
		//戻る
		if (input->TriggerKey(DIK_SPACE)) {
			if (selectPause == 0) {
				Reset();
			}
			postEffect_->SetColor(Vector4(1, 1, 1, 1));
			sceneNum = selectPause;
		}
		if (input->TriggerKey(DIK_P) || input->TriggerKey(DIK_TAB)) {
			postEffect_->SetColor(Vector4(1, 1, 1, 1));
			sceneNum = 1;
		}
		break;
	}
}

void GamePlayScene::Draw(SpriteCommon& spriteCommon) {
#pragma endregion レール

	// 3Dオブジェクト描画前処理
	Line::PreDraw(dXCommon->GetCommandList());

	if (sceneNum == 1 || sceneNum == 4)
	{
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

	if (sceneNum == 1 || sceneNum == 4) {
		floor->Draw(railCamera->GetView());
		//敵キャラの描画
		for (const std::unique_ptr<Enemy>& enemy : enemys_) {
			enemy->Draw(railCamera->GetView());
		}
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
	else if (sceneNum == 1 || sceneNum == 4) {
		//board.SpriteDraw(dXCommon->GetCommandList(), spriteCommon_, dXCommon->GetDevice(), board.vbView);
		for (int i = 0; i < player->GetHP(); i++) {
			hP[i].SpriteDraw(dXCommon->GetCommandList(), spriteCommon_, dXCommon->GetDevice(), hP[i].vbView);
		}
		if (player->GetFever() == true) {
			effectR[player->GetFeverNum()].SpriteDraw(dXCommon->GetCommandList(), spriteCommon_, dXCommon->GetDevice(), effectR[player->GetFeverNum()].vbView);
			effectL[player->GetFeverNum()].SpriteDraw(dXCommon->GetCommandList(), spriteCommon_, dXCommon->GetDevice(), effectL[player->GetFeverNum()].vbView);
		}
		if (player->GetAttackTime() <= 8&& player->GetIsAttack() == true)
		{
			attackEffect[player->GetAttackNum()].SpriteDraw(dXCommon->GetCommandList(), spriteCommon_, dXCommon->GetDevice(), attackEffect[player->GetAttackNum()].vbView);
		}
		if (isBack == true) {
			back.SpriteDraw(dXCommon->GetCommandList(), spriteCommon_, dXCommon->GetDevice(), back.vbView);
		}
		gaugeFlame.SpriteDraw(dXCommon->GetCommandList(), spriteCommon_, dXCommon->GetDevice(), gaugeFlame.vbView);
		gauge.SpriteDraw(dXCommon->GetCommandList(), spriteCommon_, dXCommon->GetDevice(), gauge.vbView);
	}
	else if (sceneNum == 2) {
		clear.SpriteDraw(dXCommon->GetCommandList(), spriteCommon_, dXCommon->GetDevice(), clear.vbView);
		spaButton.SpriteDraw(dXCommon->GetCommandList(), spriteCommon_, dXCommon->GetDevice(), spaButton.vbView);
	}
	else if (sceneNum == 3) {
		over.SpriteDraw(dXCommon->GetCommandList(), spriteCommon_, dXCommon->GetDevice(), over.vbView);
		spaButton.SpriteDraw(dXCommon->GetCommandList(), spriteCommon_, dXCommon->GetDevice(), spaButton.vbView);
	}

	//ポーズ画面描画
	if (sceneNum == 4) {

	}

	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion

#pragma region 3Dオブジェクト描画

	// 3Dオブジェクト描画前処理
	Object3d::PreDraw(dXCommon->GetCommandList());
	if (sceneNum == 0 || sceneNum == 1 || sceneNum == 4) {
		////playerを画像より手前に出したい
		player->Draw(railCamera->GetView());
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
	delete floor;
	delete floorModel;
	delete sky;
	delete skyModel;

	// スプライト解放
	delete sprite;
	sprite = nullptr;
}

void GamePlayScene::EnemyOcurrence(const Vector3& v) {
	//敵の生成
	std::unique_ptr<Enemy> newEnemy = std::make_unique<Enemy>();
	//敵の初期化
	newEnemy->EnemyInitialize(Vector3(v.x, v.y, v.z));
	//コライダーの追加
	newEnemy->SetCollider(new SphereCollider(Vector3(0, 0, 0), 2.0f));
	//敵の登録
	enemys_.push_back(std::move(newEnemy));
}

void GamePlayScene::LoadEnemyPopData() {
	//ファイルを開く
	std::ifstream file;
	file.open("Resources/enemyPop.csv");
	assert(file.is_open());

	//ファイルの内容を文字列ストリームにコピー
	enemyPopCommands << file.rdbuf();

	//ファイルを閉じる
	file.close();
}

void GamePlayScene::UpdateEnemyPopCommands() {
	//待機処理
	if (isWait_) {
		waitTimer--;
		if (waitTimer <= 0) {
			//待機完了
			isWait_ = false;
		}
		return;
	}

	//1桁分の文字列を入れる変数
	std::string line;

	//コマンド実行ループ
	while (getline(enemyPopCommands, line)) {
		//1桁分文字列をストリームに変換して解析しやすくする
		std::istringstream line_stream(line);

		std::string word;
		//,区切りで行の先頭文字列を取得
		getline(line_stream, word, ',');

		//"//"から始まる行はコメント
		if (word.find("//") == 0) {
			//コメント行を飛ばす
			continue;
		}

		//POPコマンド
		if (word.find("POP") == 0) {
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
		else if (word.find("WAIT") == 0) {
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
		effectR[i].SetColor(Vector4(1, 1, 1, 0.8));
		effectR[i].SpriteCreate(dXCommon->GetDevice(), 1280, 720, 10 + i, spriteCommon, Vector2(0.0f, 0.0f), false, false);
		effectR[i].SetScale(Vector2(640 * 1, 720 * 1));
		effectR[i].SetRotation(0.0f);
		effectR[i].SetPosition(Vector3(640, 0, 0));
		effectR[i].SpriteTransferVertexBuffer(effectR[i], spriteCommon, 10 + i);
		effectR[i].SpriteUpdate(effectR[i], spriteCommon_);
	}
}

void GamePlayScene::LoadAttackEffect(SpriteCommon& spriteCommon)
{
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
		attackEffect[i].SetColor(Vector4(1, 1, 1, 0.8));
		attackEffect[i].SpriteCreate(dXCommon->GetDevice(), 1280, 720, 25 + i, spriteCommon, Vector2(0.0f, 0.0f), false, false);
		attackEffect[i].SetScale(Vector2(1280 * 1, 720 * 1));
		attackEffect[i].SetRotation(0.0f);
		attackEffect[i].SetPosition(Vector3(0, 0, 0));
		attackEffect[i].SpriteTransferVertexBuffer(attackEffect[i], spriteCommon, 4 + i);
		attackEffect[i].SpriteUpdate(attackEffect[i], spriteCommon_);
	}
}

void GamePlayScene::Reset() 
{
	delete floorModel;
	delete skyModel;
	delete player;
	delete enemy;
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
		delete line[i];
	}

	LoadStage(stageNum);
	railCamera = new RailCamera;
	xmViewProjection = new XMViewProjection();

	// OBJからモデルデータを読み込む
	floorModel = Model::LoadFromOBJ("floor");
	skyModel = Model::LoadFromOBJ("skydome");

	// 3Dオブジェクト生成
	//床
	floor = Object3d::Create();
	// オブジェクトにモデルをひも付ける
	floor->SetModel(floorModel);
	floor->SetPosition(Vector3(0, -500, 0));
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

	//敵の情報の初期化
	LoadEnemyPopData();

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


	CreatThreeLine(points);

	//変数
	//敵の打ち出すまでの時間
	enemyDalayTimer = 0.0f;

	isWait_ = false;

	waitTimer = 300;

	gaugeScale = { 3,25 };

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

void GamePlayScene::FadeOut() 
{
	fadeOut++;
	if (0 < fadeOut && fadeOut < 100) {
		isFadeOut = true;
		if (pColor.x <= 1 && pColor.y <= 1 && pColor.z <= 1) {
			pColor += Vector4(0.01, 0.01, 0.01, 1);
		}
		postEffect_->SetColor(pColor);
	}
	if (fadeOut > 100) {
		isFadeOut = false;
		pColor = { 1,1,1,1 };
		postEffect_->SetColor(pColor);
	}
}

void GamePlayScene::LoadStage(int stageNum) {
	points.clear();

	//ファイルを開く
	std::ifstream file;
	file.open("Resources/stagePop.csv");
	assert(file.is_open());

	HRESULT result = S_FALSE;

	std::string num;
	num = stageNum;

	// １行ずつ読み込む
	string line;
	while (getline(file, line)) {

		// １行分の文字列をストリームに変換して解析しやすくする
		std::istringstream line_stream(line);

		// 半角スパース区切りで行の先頭文字列を取得
		string key;
		getline(line_stream, key, ' ');


		// 先頭文字列がｖなら頂点座標
		if (key == "v" + num) {
			// X,Y,Z座標読み込み
			Vector3 position{};
			line_stream >> position.x;
			line_stream >> position.y;
			line_stream >> position.z;
			// 座標データに追加
			points.emplace_back(position);
		}
	}
	// ファイルと閉じる
	file.close();
}