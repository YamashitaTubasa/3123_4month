#pragma once

#include "DirectXCommon.h"
#include "WinApp.h"
#include <DirectXMath.h>
#include <d3dcompiler.h>
#include <string>

#pragma comment(lib, "d3dcompiler.lib")

//==================//
// スプライト共通部 //
//==================//
class SpriteCommon final
{
private:
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;

public:
	static SpriteCommon* GetInstance();

public:
	// 定数バッファ用データ構造体(マテリアル)
	struct ConstBufferDataMaterial {
		XMFLOAT4 color; // 色(RGBA)
	};

public:
	// 初期化
	void Initialize();

	// 更新
	void Update();

	// 描画
	void Draw();

private:
	SpriteCommon() = default;
	~SpriteCommon() = default;
	SpriteCommon(const SpriteCommon&) = delete;
	SpriteCommon& operator=(const SpriteCommon&) = delete;

private:
	//// 頂点データ
	//XMFLOAT3 vertices[4] = {
	//	{ -0.5f, -0.5f, 0.0f }, // 左下
	//	{ -0.5f, +0.5f, 0.0f }, // 左上
	//	{ +0.5f, -0.5f, 0.0f }, // 右下
	//};

	ComPtr<ID3D12RootSignature> rootSignature;
	ComPtr<ID3D12PipelineState> pipelineState;

public:
	DirectXCommon* GetDXCommon() const { return dXCommon_; }

private:
	DirectXCommon* dXCommon_ = nullptr;
};