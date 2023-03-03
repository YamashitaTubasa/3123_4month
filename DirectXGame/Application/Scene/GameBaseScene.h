#pragma once

//========================//
// ゲームシーン基底クラス
//========================//
class GameBaseScene
{
public:
	virtual ~GameBaseScene() = default;

public:
	// 初期化
	virtual void Initialize() = 0;

	// 更新
	virtual void Update() = 0;

	// 描画
	virtual void Draw() = 0;

	// 解放
	virtual void Finalize() = 0;
};
