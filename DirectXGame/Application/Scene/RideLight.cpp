#include "RideLight.h"

void RideLight::Initialize()
{
	// 基底クラスの初期化
	RLFramework::Initialize();

}

void RideLight::Update()
{
	// 基底クラスの更新処理
	RLFramework::Update();

	// ImGui受付開始
	imGuiManager->Begin();

	// ゲームシーンの更新
	gameScene->Update();

	// ImGui受付終了
	imGuiManager->End();
}

void RideLight::Draw()
{
	// 描画前処理
	dXCommon->PreDraw();

	// ゲームシーンの描画
	gameScene->Draw(dXCommon);

	// ImGui描画
	imGuiManager->Draw(dXCommon);

	// 描画後処理
	dXCommon->PostDraw();
}

void RideLight::Finalize()
{

	// 基底クラスの終了処理
	RLFramework::Finalize();
}
