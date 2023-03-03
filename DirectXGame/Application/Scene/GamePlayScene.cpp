#include "GamePlayScene.h"

GamePlayScene::GamePlayScene()
{
}

GamePlayScene::~GamePlayScene()
{
}

void GamePlayScene::Initialize(SpriteCommon& spriteCommon)
{
	dXCommon = DirectXCommon::GetInstance();
	winApp = WinApp::GetInstance();
	input = Input::GetInstance();

	// OBJからモデルデータを読み込む
	Model[0] = Model::LoadFromOBJ("fighter", "effect1.png");
	// 3Dオブジェクト生成
	for (int i = 0; i < 5; i++) {
		object3d[i] = Object3d::Create();
	}
	// オブジェクトにモデルをひも付ける
	object3d[0]->SetModel(Model[0]);
	// 3Dオブジェクトの位置を指定
	position[0] = { -20,-5,0 };
	rotation[0] = { 0,90,0 };
	object3d[0]->SetPosition(position[0]);
	object3d[0]->SetScale({ 5, 5, 5 });
	object3d[0]->SetRotation(rotation[0]);

	// スプライト
	sprite = new Sprite();
	spriteCommon_ = sprite->SpriteCommonCreate(dXCommon->GetDevice(), 1280, 720);
	// スプライト用パイプライン生成呼び出し
	PipelineSet spritePipelineSet = sprite->SpriteCreateGraphicsPipeline(dXCommon->GetDevice());

	// HP
	hP.LoadTexture(spriteCommon_, 3, L"Resources/hp.png", dXCommon->GetDevice());
	hP.SetColor(XMFLOAT4(1, 1, 1, 1));
	hP.SpriteCreate(dXCommon->GetDevice(), 50, 50, 3, spriteCommon, XMFLOAT2(0.0f, 0.0f), false, false);
	hP.SetPosition(XMFLOAT3(0, 0, 0));
	hP.SetScale(XMFLOAT2(50 * 1, 50 * 1));
	hP.SetRotation(0.0f);
	hP.SpriteTransferVertexBuffer(hP, spriteCommon, 3);
	hP.SpriteUpdate(hP, spriteCommon_);
}

void GamePlayScene::Update()
{
	// 3Dオブジェクト更新
	for (int i = 0; i < 5; i++) {
		object3d[i]->Update();
	}

	object3d[0]->SetPosition(position[0]);
	object3d[0]->SetRotation(rotation[0]);

	if (input->PushKey(DIK_W)) { position[0].y += 0.4; }

	if (input->PushKey(DIK_A)) { position[0].x -= 0.4; isPush_A = true; }
	else { isPush_A = false; }
	if (isPush_D == false) {
		if (isPush_A == true) {
			if (rotation[0].x >= -20) {rotation[0].x -= 1;}
			if (rotation[0].x <= -20) {rotation[0].x = -20;}
		}
		else {
			if (rotation[0].x >= -20) {rotation[0].x += 1;}
			if (rotation[0].x >= 0) {rotation[0].x = 0;}
		}
	}

	if (input->PushKey(DIK_S)) {position[0].y -= 0.4;}

	if (input->PushKey(DIK_D)) {position[0].x += 0.4; isPush_D = true;}
	else {isPush_D = false;}
	if (isPush_A == false) {
		if (isPush_D == true) {
			if (rotation[0].x <= 20) {rotation[0].x += 1;}
			if (rotation[0].x >= 20) {rotation[0].x = 20;}
		}
		else {
			if (rotation[0].x <= 20) {rotation[0].x -= 1;}
			if (rotation[0].x <= 0) {rotation[0].x = 0;}
		}
	}
}

void GamePlayScene::Draw()
{
#pragma region 3Dオブジェクト描画

	// 3Dオブジェクト描画前処理
	Object3d::PreDraw(dXCommon->GetCommandList());

	///=== 3Dオブジェクト描画 ===///
	for (int i = 0; i < 5; i++) {
		object3d[i]->Draw();
	}

	// 3Dオブジェクト描画後処理
	Object3d::PostDraw();

#pragma endregion

#pragma region パーティクル描画

	// パーティクル描画前処理
	ParticleManager::PreDraw(dXCommon->GetCommandList());

	///==== パーティクル描画 ====///
	

	// パーティクル描画後処理
	ParticleManager::PostDraw();

#pragma endregion

#pragma region スプライト描画

	// スプライト描画前処理
	Sprite::PreDraw(dXCommon->GetCommandList(), spriteCommon_);

	///=== スプライト描画 ===///
	hP.SpriteDraw(dXCommon->GetCommandList(), spriteCommon_, dXCommon->GetDevice(), hP.vbView);

	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}

void GamePlayScene::Finalize()
{
	// 3Dオブジェクト解放
	for (int i = 0; i < 5; i++) {
		delete object3d[i];
	}
	// 3Dモデル解放
	for (int i = 0; i < 5; i++) {
		delete Model[i];
	}

	// スプライト解放
	delete sprite;
	sprite = nullptr;
}
