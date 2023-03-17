#include "GamePlayScene.h"
#include "spline.h"

GamePlayScene::GamePlayScene() {
}

GamePlayScene::~GamePlayScene() {
}

void GamePlayScene::Initialize(SpriteCommon& spriteCommon) {
	dXCommon = DirectXCommon::GetInstance();
	winApp = WinApp::GetInstance();
	input = Input::GetInstance();

	viewProjection->Initialize(WinApp::window_width, WinApp::window_height);

	// OBJからモデルデータを読み込む
	skyModel = Model::LoadFromOBJ("skydome");

	// 3Dオブジェクト生成
	sky = Object3d::Create();
	// オブジェクトにモデルをひも付ける

	sky->SetModel(skyModel);
	sky->SetScale(XMFLOAT3(80, 80, 80));

	//// OBJからモデルデータを読み込む
	//playerModel = Model::LoadFromOBJ("fighter");
	//// 3Dオブジェクト生成
	//player = Object3d::Create();
	//// オブジェクトにモデルをひも付ける
	//player->SetModel(playerModel);
	//player->SetRotation(XMFLOAT3(0, 270, 0));
	//player->SetScale(XMFLOAT3(1, 1, 1));

	tester = Object3d::Create();
	// オブジェクトにモデルをひも付ける
	tester->SetModel(playerModel);
	tester->SetPosition(XMFLOAT3(-1, 0, -12));
	tester->SetRotation(XMFLOAT3(0, 270, 0));
	tester->SetScale(XMFLOAT3(2, 2, 2));

	// スプライトの初期化
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

	start = { -100.0f, 0.0f, 0.0f };		//スタート地点
	p2 = { -20.0f, 50.0f, +50.0f };			//制御点その1
	p3 = { 0.0f, -30.0f, -50.0f };			//制御点その2
	p4 = { 50.0f, 0.0f, 0.0 };
	end = { 100.0f, 0.0f, 0.0f };				//ゴール地点

	points = { start,start,p2,p3,p4,end,end };
}

void GamePlayScene::Update() {
	Vector3 eye_ = spline_.Update(points,timeRate);
	viewProjection->SetEye(ConversionVec(eye_));

	if (input->TriggerKey(DIK_SPACE)) {
		int a = 0;
	}

	sky->Update();
	//player->Update();
	tester->Update();

}

void GamePlayScene::Draw() {
#pragma region 3Dオブジェクト描画

	// 3Dオブジェクト描画前処理
	Object3d::PreDraw(dXCommon->GetCommandList());

	sky->Draw();
	//player->Draw();
	tester->Draw();

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

void GamePlayScene::Finalize() {
	//delete player;
	delete playerModel;
	delete sky;
	delete skyModel;

	// スプライト解放
	delete sprite;
	sprite = nullptr;
}

XMFLOAT3 GamePlayScene::ConversionVec(Vector3 vec) {
	XMFLOAT3 tmp(0, 0, 0);
	tmp.x = vec.x;
	tmp.y = vec.y;
	tmp.z = vec.z;
	return tmp;
}

Vector3 GamePlayScene::ConversionVec(XMFLOAT3 vec) {
	Vector3 tmp(0, 0, 0);
	tmp.x = vec.x;
	tmp.y = vec.y;
	tmp.z = vec.z;
	return tmp;
}


XMFLOAT3 GamePlayScene::GetFront(XMFLOAT3 a, XMFLOAT3 b) {
	Vector3 yTmpVec = { 0, 1, 0 };
	Vector3 frontTmp = { 0, 0, 0 };
	Vector3 rightVec = { 0, 0, 0 };
	Vector3 leftVec = { 0, 0, 0 };
	Vector3 frontVec = { 0, 0, 0 };
	Vector3 a_ = { a.x,a.y,a.z };
	Vector3 b_ = { b.x,b.y,b.z };

	yTmpVec.normalize();
	//正面仮ベクトル
	frontTmp = b_ - a_;
	frontTmp.normalize();
	//右ベクトル
	rightVec = yTmpVec.cross(frontTmp);
	rightVec.normalize();
	//左ベクトル
	leftVec = frontTmp.cross(yTmpVec);
	leftVec.normalize();
	//正面ベクトル
	frontVec = rightVec.cross(yTmpVec);
	frontVec.normalize();

	return ConversionVec(frontVec);
}

XMFLOAT3 GamePlayScene::GetRight(XMFLOAT3 a, XMFLOAT3 b) {
	Vector3 yTmpVec = { 0, 1, 0 };
	Vector3 frontTmp = { 0, 0, 0 };
	Vector3 rightVec = { 0, 0, 0 };
	Vector3 a_ = { a.x,a.y,a.z };
	Vector3 b_ = { b.x,b.y,b.z };

	yTmpVec.normalize();
	//正面仮ベクトル
	frontTmp = b_ - a_;
	frontTmp.normalize();
	//右ベクトル
	rightVec = yTmpVec.cross(frontTmp);
	rightVec.normalize();

	return ConversionVec(rightVec);
}

XMFLOAT3 GamePlayScene::GetLeft(XMFLOAT3 a, XMFLOAT3 b) {
	Vector3 yTmpVec = { 0, 1, 0 };
	Vector3 frontTmp = { 0, 0, 0 };
	Vector3 leftVec = { 0, 0, 0 };
	Vector3 a_ = { a.x,a.y,a.z };
	Vector3 b_ = { b.x,b.y,b.z };

	yTmpVec.normalize();
	//正面仮ベクトル
	frontTmp = b_ - a_;
	frontTmp.normalize();
	//左ベクトル
	leftVec = frontTmp.cross(yTmpVec);
	leftVec.normalize();

	return ConversionVec(leftVec);
}