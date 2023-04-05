#pragma once

#include "GameBaseScene.h"

class SceneManager 
{
public:
	~SceneManager();

public:
	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

public:
	// 次シーン予約
	void SetNextScene(GameBaseScene* nextScene) { nextScene_ = nextScene; }

private:
	// 今のシーン(実行中シーン)
	GameBaseScene* scene_ = nullptr;
	// 次のシーン
	GameBaseScene* nextScene_ = nullptr;
};
