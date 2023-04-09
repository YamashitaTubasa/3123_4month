#include "RideLight.h"

void RideLight::Initialize()
{
	// 基底クラスの初期化
	RLFramework::Initialize();

	// ゲームシーンの生成と初期化
	scene_ = new GamePlayScene();
	scene_->Initialize(spriteCommon);
}

void RideLight::Update()
{
	// 基底クラスの更新処理
	RLFramework::Update();

	// ImGui受付開始
	imGuiManager->Begin();

	// ゲームシーンの更新
	scene_->Update();

	// ImGui受付終了
	imGuiManager->End();
}

void RideLight::Draw()
{
#pragma region ゲームシーン描画
	// レンダーテクスチャの前処理
	postEffect->PreDrawScene(dXCommon->GetCommandList());

	//=== ゲームシーンの描画 ===//
	scene_->Draw();

	// レンダーテクスチャの後処理
	postEffect->PostDrawScene(dXCommon->GetCommandList());
#pragma endregion ゲームシーン描画

#pragma region 描画
	// 描画前処理
	dXCommon->PreDraw();

	//=== ポストエフェクトの描画 ===//
	postEffect->Draw(dXCommon->GetCommandList());

	//=== ImGui描画 ===//
	imGuiManager->Draw(dXCommon);

	// 描画後処理
	dXCommon->PostDraw();
#pragma endregion 描画
}

void RideLight::Finalize()
{
	// ゲームシーンの終了処理
	scene_->Finalize();
	// ゲームシーンの解放
	delete scene_;

	// 基底クラスの終了処理
	RLFramework::Finalize();
}
