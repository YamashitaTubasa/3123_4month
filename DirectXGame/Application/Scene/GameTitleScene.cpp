#include "GameTitleScene.h"

GameTitleScene::GameTitleScene()
{
}

GameTitleScene::~GameTitleScene()
{
}

void GameTitleScene::Initialize(DirectXCommon* dXCommon, WinApp* winApp, SpriteCommon& spriteCommon)
{
	// スプライト
	sprite = new Sprite();
	spriteCommon_ = sprite->SpriteCommonCreate(dXCommon->GetDevice(), 1280, 720);
	// スプライト用パイプライン生成呼び出し
	PipelineSet spritePipelineSet = sprite->SpriteCreateGraphicsPipeline(dXCommon->GetDevice());

	// HP
	Title.LoadTexture(spriteCommon_, 0, L"Resources/title.png", dXCommon->GetDevice());
	Title.SetColor(Vector4(1, 1, 1, 1));
	Title.SpriteCreate(dXCommon->GetDevice(), 1280, 720, 0, spriteCommon, Vector2(0.0f, 0.0f), false, false);
	Title.SetPosition(Vector3(0, 0, 0));
	Title.SetScale(Vector2(1280 * 1, 720 * 1));
	Title.SetRotation(0.0f);
	Title.SpriteTransferVertexBuffer(Title, spriteCommon, 0);
	Title.SpriteUpdate(Title, spriteCommon_);
}

void GameTitleScene::Update()
{
}

void GameTitleScene::Draw(DirectXCommon* dXCommon)
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
	Sprite::PreDraw(dXCommon->GetCommandList(), spriteCommon_);

	///=== スプライト描画 ===///
	Title.SpriteDraw(dXCommon->GetCommandList(), spriteCommon_, dXCommon->GetDevice(), Title.vbView);

	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}

void GameTitleScene::Finalize()
{
	// スプライト解放
	delete sprite;
	sprite = nullptr;
}
