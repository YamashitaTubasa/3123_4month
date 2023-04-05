#include "SceneManager.h"

SceneManager::~SceneManager()
{
	// 最後のシーンの終了と解放
	scene_->Finalize();
	delete scene_;
}

void SceneManager::Update()
{
	// TODO:シーン切り替え機構
	if (nextScene_) {
		// 旧シーンの終了
		if (scene_) {
			scene_->Finalize();
			delete scene_;
		}

		// シーン切り替え
		scene_ = nextScene_;
		nextScene_ = nullptr;
		// 次シーンを初期化する
		scene_->Initialize();
	} 

	// 実行中シーンの更新
	scene_->Update();
}

void SceneManager::Draw()
{
	scene_->Draw();
}
