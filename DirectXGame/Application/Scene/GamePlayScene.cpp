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

	viewProjection = new ViewProjection;
	viewProjection->Initialize();
	viewProjection->eye = { 0, 0, -10 };
	viewProjection->target = { 0, 0, 0 };

	// OBJからモデルデータを読み込む
	skyModel = Model::LoadFromOBJ("skydome");

	// 3Dオブジェクト生成
	sky = Object3d::Create();

	// オブジェクトにモデルをひも付ける
	sky->SetModel(skyModel);
	sky->SetScale(Vector3({80, 80, 80}));

	// OBJからモデルデータを読み込む
	playerModel = Model::LoadFromOBJ("fighter");
	// 3Dオブジェクト生成
	player = Object3d::Create();
	// オブジェクトにモデルをひも付ける
	player->SetModel(playerModel);
	player->SetRotation(Vector3({ 0, 90, 0 }));
	player->SetScale(Vector3(1.5, 1, 1));

	//tester = Object3d::Create();
	//// オブジェクトにモデルをひも付ける
	//tester->SetModel(playerModel);
	//tester->SetPosition(Vector3(-1, 0, -12));
	//tester->SetRotation(Vector3(0, 20, 0));
	//tester->SetScale(Vector3(2, 2, 2));

	// スプライトの初期化
	// スプライト
	sprite = new Sprite();
	spriteCommon_ = sprite->SpriteCommonCreate(dXCommon->GetDevice(), 1280, 720);
	// スプライト用パイプライン生成呼び出し
	PipelineSet spritePipelineSet = sprite->SpriteCreateGraphicsPipeline(dXCommon->GetDevice());

	// HP
	hP.LoadTexture(spriteCommon_, 3, L"Resources/hp.png", dXCommon->GetDevice());
	hP.SetColor(Vector4(1, 1, 1, 1));
	hP.SpriteCreate(dXCommon->GetDevice(), 50, 50, 3, spriteCommon, Vector2(0.0f, 0.0f), false, false);
	hP.SetPosition(Vector3(0, 0, 0));
	hP.SetScale(Vector2(50 * 1, 50 * 1));
	hP.SetRotation(0.0f);
	hP.SpriteTransferVertexBuffer(hP, spriteCommon, 3);
	hP.SpriteUpdate(hP, spriteCommon_);
}

void GamePlayScene::Update()
{
	viewProjection->UpdateMatrix();

	sky->Update();
	player->Update();
	/*tester->Update();*/

}

void GamePlayScene::Draw()
{
#pragma region 3Dオブジェクト描画

	// 3Dオブジェクト描画前処理
	Object3d::PreDraw(dXCommon->GetCommandList());

	sky->Draw(viewProjection);
	player->Draw(viewProjection);
	/*tester->Draw(viewProjection);*/

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
	delete player;
	delete playerModel;
	delete sky;
	delete skyModel;

	// スプライト解放
	delete sprite;
	sprite = nullptr;
}

//XMFLOAT3 GamePlayScene::ConversionVec(Vector3 vec) {
//	XMFLOAT3 tmp(0, 0, 0);
//	tmp.x = vec.x;
//	tmp.y = vec.y;
//	tmp.z = vec.z;
//	return tmp;
//}
//
//Vector3 GamePlayScene::ConversionVec(XMFLOAT3 vec) {
//	Vector3 tmp(0, 0, 0);
//	tmp.x = vec.x;
//	tmp.y = vec.y;
//	tmp.z = vec.z;
//	return tmp;
//}


Vector3 GamePlayScene::GetFront(Vector3 a, Vector3 b) {
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

	return frontVec;
}

Vector3 GamePlayScene::GetRight(Vector3 a, Vector3 b) {
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

	return rightVec;
}

Vector3 GamePlayScene::GetLeft(Vector3 a, Vector3 b) {
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

	return leftVec;
}