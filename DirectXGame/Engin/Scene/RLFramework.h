#pragma once

#include "Input.h"
#include "WinApp.h"
#include "DirectXCommon.h"
#include "SpriteCommon.h"
#include "Model.h"
#include "Object3d.h"
#include "GamePlayScene.h"
#include "GameTitleScene.h"
#include "ImGuiManager.h"

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
	GameTitleScene* scene_ = nullptr;
	SpriteCommon* spriteCommon = nullptr;


private:
	// �Q�[���I���t���O
	bool endRequest_ = false;
};
