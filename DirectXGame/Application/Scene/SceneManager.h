#pragma once

#include "GameBaseScene.h"

class SceneManager 
{
public:
	~SceneManager();

public:
	/// <summary>
	/// �X�V
	/// </summary>
	void Update();

	/// <summary>
	/// �`��
	/// </summary>
	void Draw();

public:
	// ���V�[���\��
	void SetNextScene(GameBaseScene* nextScene) { nextScene_ = nextScene; }

private:
	// ���̃V�[��(���s���V�[��)
	GameBaseScene* scene_ = nullptr;
	// ���̃V�[��
	GameBaseScene* nextScene_ = nullptr;
};
