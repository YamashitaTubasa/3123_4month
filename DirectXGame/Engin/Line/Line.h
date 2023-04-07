#pragma once
#include "Vector3.h"
#include "Matrix4.h"
#include <DirectXMath.h>
#include <vector>

#include "WinApp.h"
#include "DirectXCommon.h"

class Line {
public:
	//static SpriteCommon* GetInstance();

public:
	// 定数バッファ用データ構造体(マテリアル)
	struct ConstBufferDataMaterial {
		Matrix4 color; // 色(RGBA)
	};

	////定数バッファ用データ構造体(Material)
	//struct ConstBufferDataTransform {
	//	XMMATRIX mat; //3D変換行列
	//};

public:
	// 初期化
	void Initialize();

	// 更新
	void Update();

	// 描画
	void Draw();

public:
	Line() = default;
	~Line() = default;

private:
	// 頂点データ
	Vector3 vertices[4] = {
		{ -0.5f, -0.5f, 0.0f }, // 左下
		{ -0.5f, +0.5f, 0.0f }, // 左上
		{ +0.5f, -0.5f, 0.0f }, // 右下
		{ -0.5f, -0.5f, 0.0f },
	};

	ComPtr<ID3D12RootSignature> rootSignature;
	ComPtr<ID3D12PipelineState> pipelineState;
	ComPtr<ID3D12Resource> vertBuff;

	//定数バッファの生成(準備)
	ComPtr<ID3D12Resource> constBuffTransform;
	//ComPtr<ConstBufferDataTransform> constMapTransform;

	// 頂点バッファビューの作成
	D3D12_VERTEX_BUFFER_VIEW vbView{};

public:
	DirectXCommon* GetDXCommon() const { return dXCommon_; }

private:
	DirectXCommon* dXCommon_ = nullptr;
};


