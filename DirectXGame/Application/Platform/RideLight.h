#pragma once

#include "RLFramework.h"

// ゲーム全体
class RideLight : public RLFramework
{
public:
	// 初期化
	void Initialize() override;

	// 更新
	void Update() override;

	// 描画
	void Draw() override;

	// 終了
	void Finalize() override;

};
