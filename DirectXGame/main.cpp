#include "Input.h"
#include "WinApp.h"
#include "DirectXCommon.h"
#include "Sprite.h"
#include "Model.h"
#include "Object3d.h"
#include "GameScene.h"

// windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// コンソールへの文字出力
	OutputDebugStringA("Hellow,DirectX!!\n");

#pragma region 基盤システムの初期化

	// WindowsAPIの初期化
	WinApp* winApp = nullptr;
	winApp = new WinApp();
	winApp->Initialize();

	// DirectXの初期化
	DirectXCommon* dXCommon = nullptr;
	dXCommon = new DirectXCommon();
	dXCommon->Initialize(winApp);

	// スプライト
	SpriteCommon spriteCommon;

	// 3Dオブジェクト静的初期化
	Object3d::StaticInitialize(dXCommon->GetDevice(), WinApp::window_width, WinApp::window_height);
	// パーティクル静的初期化
	ParticleManager::StaticInitialize(dXCommon->GetDevice(), WinApp::window_width, WinApp::window_height);

	// ゲームシーンの初期化
	GameScene* gameScene = new GameScene();

#pragma endregion 基盤システムの初期化

#pragma region シーンの初期化

	gameScene->Initialize(dXCommon, winApp, spriteCommon);
	
#pragma endregion シーンの初期化

	while (true) {

	#pragma region 基盤システムの更新

		// Windowsのメッセージ処理
		if (winApp->ProcessMessage()) {
			// ゲームループを抜ける
			break;
		}

	#pragma endregion 基盤システムの更新

	#pragma region シーンの更新

		// ゲームシーンの更新
		gameScene->Update();
		
	#pragma endregion シーンの更新

	#pragma region シーンの描画

		// ゲームシーンの描画
		gameScene->Draw(dXCommon);

	#pragma endregion シーンの描画

	}
#pragma region シーンの終了

	// ゲームシーンの解放
	gameScene->Finalize();
	
#pragma endregion シーンの終了

#pragma region 基盤システムの終了

	// WindowsAPIの終了処理
	winApp->Finalize();
	// WindowsAPI解放
	delete winApp;
	winApp = nullptr;

	// DirectX解放
	dXCommon->fpsFixedFinalize();
	delete dXCommon;
	dXCommon = nullptr;

#pragma endregion 基盤システムの終了

	return 0;
}