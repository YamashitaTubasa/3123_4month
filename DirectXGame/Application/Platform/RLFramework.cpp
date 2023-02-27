#include "RLFramework.h"

void RLFramework::Run()
{
	// ゲームの初期化
	Initialize();

	while (true) // ゲームループ 
	{
		// 毎フレーム更新
		Update();

		// 終了リクエストが来たらループを抜ける
		if (IsEndRequest()) {
			// ゲームループを抜ける
			break;
		}

		// 描画
		Draw();
	}

	// ゲームの終了
	Finalize();
}

void RLFramework::Initialize()
{
	// WindowsAPIの初期化
	winApp = new WinApp();
	winApp->Initialize();

	// DirectXの初期化
	dXCommon = new DirectXCommon();
	dXCommon->Initialize(winApp);

	// 入力の初期化
	input = new Input();
	input->Initialize(winApp);

	// ImGuiの初期化
	imGuiManager = new ImGuiManager();
	imGuiManager->Initialize(dXCommon, winApp);

	// 3Dオブジェクト静的初期化
	Object3d::StaticInitialize(dXCommon->GetDevice(), WinApp::window_width, WinApp::window_height);

	// ゲームシーンの初期化
	gameScene = new GameScene();
	gameScene->Initialize(dXCommon, winApp, spriteCommon, input);
}

void RLFramework::Update()
{
	// Windowsのメッセージ処理
	if (winApp->ProcessMessage()) {
		// ゲームループを抜ける
		endRequest_ = true;
	}

	// 入力の更新
	input->Update();
}

void RLFramework::Finalize()
{
	// ゲームシーンの解放
	gameScene->Finalize();

	// imguiの終了処理
	imGuiManager->Finalize();
	// imguiの解放
	delete imGuiManager;
	imGuiManager = nullptr;

	// 入力開放
	delete input;
	input = nullptr;

	// WindowsAPIの終了処理
	winApp->Finalize();
	// WindowsAPI解放
	delete winApp;
	winApp = nullptr;

	// DirectX解放
	dXCommon->fpsFixedFinalize();
	delete dXCommon;
	dXCommon = nullptr;
}
