#include "GameTitleScene.h"

GameTitleScene::GameTitleScene()
{
}

GameTitleScene::~GameTitleScene()
{
}

void GameTitleScene::Initialize()
{
	dXCommon = DirectXCommon::GetInstance();

	// スプライト
	sprite = new Sprite();

	sprite->Initialize();
}

void GameTitleScene::Update()
{
}

void GameTitleScene::Draw()
{
#pragma region 3Dオブジェクト描画

	// 3Dオブジェクト描画前処理
	Object3d::PreDraw(dXCommon->GetCommandList());

	///=== 3Dオブジェクト描画 ===///
	
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

	///=== スプライト描画 ===///
	sprite->Draw();
	
	// スプライト描画後処理
	
#pragma endregion
}

void GameTitleScene::Finalize()
{
	delete sprite;
}
