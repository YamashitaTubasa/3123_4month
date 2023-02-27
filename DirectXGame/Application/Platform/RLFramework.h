#pragma once

#include "Input.h"
#include "WinApp.h"
#include "DirectXCommon.h"
#include "Sprite.h"
#include "Model.h"
#include "Object3d.h"
#include "GameScene.h"
#include "ImGuiManager.h"

class RLFramework
{
public:
	virtual ~RLFramework() = default;

public:
	// 実行
	void Run();

	// 初期化
	virtual void Initialize();

	// 更新
	virtual void Update();

	// 更新
	virtual void Draw() = 0;

	// 終了
	virtual void Finalize();

public:
	//　終了チェック
	virtual bool IsEndRequest() { return endRequest_; }

protected:
	WinApp* winApp = nullptr;
	DirectXCommon* dXCommon = nullptr;
	Input* input = nullptr;
	ImGuiManager* imGuiManager = nullptr;
	GameScene* gameScene = nullptr;
	SpriteCommon spriteCommon;

private:
	// ゲーム終了フラグ
	bool endRequest_ = false;
};
