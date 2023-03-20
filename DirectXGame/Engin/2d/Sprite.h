#pragma once

#include "SpriteCommon.h"

//============//
// スプライト //
//============//
class Sprite
{
private:
	using XMFLOAT3 = DirectX::XMFLOAT3;

public:
	// 初期化
	void Initialize();

	// 更新
	void Update();

	// 描画
	void Draw();

public:
	Sprite() = default;
	~Sprite() = default;

private:
	// 頂点データ
	XMFLOAT3 vertices[4] = {
		{ -0.5f, -0.5f, 0.0f }, // 左下
		{ -0.5f, +0.5f, 0.0f }, // 左上
		{ +0.5f, -0.5f, 0.0f }, // 右下
	};

private:
	SpriteCommon* spriteCommon = nullptr;
};