#pragma once

#include "Input.h"
#include "WinApp.h"
#include "DirectXCommon.h"
#include "Sprite.h"
#include "Model.h"
#include "Object3d.h"
#include "GamePlayScene.h"
#include "GameTitleScene.h"
#include "ImGuiManager.h"
#include "PostEffect.h"
#include "Line.h"

class RLFramework
{
public:
	virtual ~RLFramework() = default;

public:
	// ���s
	void Run();

	// ������
	virtual void Initialize();

	// �X�V
	virtual void Update();

	// �X�V
	virtual void Draw() = 0;

	// �I��
	virtual void Finalize();

public:
	//�@�I���`�F�b�N
	virtual bool IsEndRequest() { return endRequest_; }

protected:
	WinApp* winApp = nullptr;
	DirectXCommon* dXCommon = nullptr;
	Input* input = nullptr;
	ImGuiManager* imGuiManager = nullptr;
	GamePlayScene* scene_ = nullptr;
	SpriteCommon spriteCommon;
	PostEffect* postEffect_ = nullptr;
	Line* line = nullptr;

private:
	// �Q�[���I���t���O
	bool endRequest_ = false;
};
