#include "GameScene.h"

GameScene::GameScene()
{
}

GameScene::~GameScene()
{
}

void GameScene::Initialize(DirectXCommon* dXCommon, WinApp* winApp, SpriteCommon& spriteCommon,Input* input_)
{
	this->input = input_;

	// オブジェクトの初期化
	ObjectInitialize(dXCommon);
	// スプライトの初期化
	SpriteInitialize(dXCommon, spriteCommon);
}

void GameScene::Update()
{
	// オブジェクトの更新
	ObjectUpdate();
}

void GameScene::Draw(DirectXCommon* dXCommon)
{
	// 3Dオブジェクトの描画
	ObjectDraw(dXCommon);
	
	// HP描画
	GameDraw(dXCommon);
}

void GameScene::Finalize()
{
	// オブジェクトの解放
	ObjectFinalize();

	// スプライトの解放
	SpriteFinalize();
}

void GameScene::ObjectInitialize(DirectXCommon* dXCommon) 
{
	// OBJからモデルデータを読み込む
	Model[0] = Model::LoadFromOBJ("fighter", "effect1.png");
	//Model[0]->LoadTexture("effect1.png");
	Model[1] = Model::LoadFromOBJ("ironSphere", "ironShpere/ironSphere.png");
	//Model[2] = Model::LoadFromOBJ("skydome", "skydome/skydome.jpg");
	// 3Dオブジェクト生成
	for (int i = 0; i < 5; i++) {
		object3d[i] = Object3d::Create();
	}
	// オブジェクトにモデルをひも付ける
	object3d[0]->SetModel(Model[0]);
	object3d[1]->SetModel(Model[1]);
	object3d[2]->SetModel(Model[2]);
	// 3Dオブジェクトの位置を指定
	position[0] = { -20,-5,0 };
	rotation[0] = { 0,90,0 };
	object3d[0]->SetPosition(position[0]);
	object3d[0]->SetScale({ 5, 5, 5 });
	object3d[0]->SetRotation(rotation[0]);

	position[1] = { 0,0,50 };
	object3d[1]->SetPosition(position[1]);
	object3d[1]->SetScale({ 5,5,5 });
	object3d[1]->SetRotation({ 0, 90, 0 });

	object3d[2]->SetPosition({ 0,-40,0 });
	object3d[2]->SetScale({ 100, 100, 100 });
	object3d[2]->SetRotation({0,100,20});
}

void GameScene::ObjectUpdate()
{
	// 3Dオブジェクト更新
	for (int i = 0; i < 5; i++) {
		object3d[i]->Update();
	}

	object3d[0]->SetPosition(position[0]);
	object3d[0]->SetRotation(rotation[0]);
	object3d[1]->SetPosition(position[1]);

	if (input->PushKey(DIK_W)) {
		position[0].y += 0.4;
	}

	if (input->PushKey(DIK_A)) {
		position[0].x -= 0.4;
		isPush_A = true;
	}
	else {
		isPush_A = false;
	}
	if (isPush_D == false) {
		if (isPush_A == true) {
			if (rotation[0].x >= -20) {
				rotation[0].x -= 1;
			}
			if (rotation[0].x <= -20) {
				rotation[0].x = -20;
			}
		}
		else {
			if (rotation[0].x >= -20) {
				rotation[0].x += 1;
			}
			if (rotation[0].x >= 0) {
				rotation[0].x = 0;
			}
		}
	}

	if (input->PushKey(DIK_S)) {
		position[0].y -= 0.4;
	}

	if (input->PushKey(DIK_D)) {
		position[0].x += 0.4;
		isPush_D = true;
	}else {
		isPush_D = false;
	}
	if (isPush_A == false) {
		if (isPush_D == true) {
			if (rotation[0].x <= 20) {
				rotation[0].x += 1;
			}
			if (rotation[0].x >= 20) {
				rotation[0].x = 20;
			}
		}
		else {
			if (rotation[0].x <= 20) {
				rotation[0].x -= 1;
			}
			if (rotation[0].x <= 0) {
				rotation[0].x = 0;
			}
		}
	}

	position[1].z -= 1;
	if (position[1].z < -100) {
		position[1].z = 50;
	}

}

void GameScene::ObjectDraw(DirectXCommon* dXCommon)
{
	// 3Dオブジェクト描画前処理
	Object3d::PreDraw(dXCommon->GetCommandList());

	// 3Dオブジェクトの描画
	for (int i = 0; i < 5; i++) {
		object3d[i]->Draw();
	}

	// 3Dオブジェクト描画後処理
	Object3d::PostDraw();
}

void GameScene::ObjectFinalize()
{
	// 3Dオブジェクト解放
	for (int i = 0; i < 5; i++) {
		delete object3d[i];
	}
	// 3Dモデル解放
	for (int i = 0; i < 5; i++) {
		delete Model[i];
	}
}

void GameScene::SpriteInitialize(DirectXCommon* dXCommon, SpriteCommon& spriteCommon)
{
	// スプライト
	sprite = new Sprite();
	spriteCommon_ = sprite->SpriteCommonCreate(dXCommon->GetDevice(), 1280, 720);

	// HP
	hP.LoadTexture(spriteCommon_, 3, L"Resources/hp.png", dXCommon->GetDevice());
	hP.SetColor(XMFLOAT4(1, 1, 1, 1));
	hP.SpriteCreate(dXCommon->GetDevice(), 50, 50, 3, spriteCommon, XMFLOAT2(0.0f, 0.0f), false, false);
	hP.SetPosition(XMFLOAT3(0, 0, 0));
	hP.SetScale(XMFLOAT2(50 * 1, 50 * 1));
	hP.SetRotation(0.0f);
	hP.SpriteTransferVertexBuffer(hP, spriteCommon, 3);
	hP.SpriteUpdate(hP, spriteCommon_);

	// スプライト用パイプライン生成呼び出し
	PipelineSet spritePipelineSet = sprite->SpriteCreateGraphicsPipeline(dXCommon->GetDevice());
}

void GameScene::GameDraw(DirectXCommon* dXCommon)
{
	sprite->PreDraw(dXCommon->GetCommandList(), spriteCommon_);

	hP.SpriteDraw(dXCommon->GetCommandList(), spriteCommon_, dXCommon->GetDevice(), hP.vbView);
	
	sprite->PostDraw();
}

void GameScene::SpriteFinalize()
{
	// スプライト解放
	delete sprite;
	sprite = nullptr;
}
