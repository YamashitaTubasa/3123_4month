#pragma once
#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"
#include "Matrix4.h"
#include <DirectXMath.h>
#include <vector>

#include "WinApp.h"
#include "DirectXCommon.h"
#include "stdint.h"




class Line {
public:
	//static SpriteCommon* GetInstance();

public:
	// 定数バッファ用データ構造体(マテリアル)
	struct ConstBufferDataMaterial {
		Vector4 color_; // 色(RGBA)
	};

	//定数バッファ用データ構造体(3D変換行列)
	struct ConstBufferDataTransform {
		Matrix4 mat;
	};

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
	struct VertexPosUv {
		Vector3 pos;
		Vector2 uv;
	};

	// 頂点データ
	std::vector<VertexPosUv> vertices = {
		{{ -50.0f, -50.0f, 0.0f },{0.0f,1.0f}}, // 左下
		{{ -50.0f,  50.0f, 0.0f },{0.0f,0.0f}}, // 左上
		{{  50.0f, -50.0f, 0.0f },{1.0f,1.0f}}, // 右下
		{{  50.0f,  50.0f, 0.0f },{1.0f,0.0f}}, // 右上
	};

	//std::vector = 可変長配列
	std::vector<uint16_t> indices = {
		0,1,2,
		1,2,3,
	};

	//横方向ピクセル数
	const size_t textureWidth = 256;
	//縦方向ピクセル数
	const size_t textureHeight = 256;
	//配列の要素数
	const size_t imageDataCount = textureWidth * textureHeight;
	//画像イメージデータ配列
	Vector4* imageData = new Vector4[imageDataCount];

	ComPtr<ID3D12RootSignature> rootSignature;
	ComPtr<ID3D12PipelineState> pipelineState;
	ComPtr<ID3D12Resource> vertBuff;
	ComPtr<ID3D12Resource> indexBuff;

	//テクスチャバッファの生成
	ID3D12Resource *texBuff = nullptr;

	//定数バッファの生成(準備)
	ComPtr<ID3D12Resource> constBuffTransform;
	ConstBufferDataTransform *constMapTransform = nullptr;

	ComPtr<ID3D12Resource> constBuffMaterial;
	//ComPtr<ConstBufferDataMaterial> constMapMaterial;
	ConstBufferDataMaterial* constMapMaterial = nullptr;

	//デスクリプタヒープを生成
	ID3D12DescriptorHeap *srvHeap = nullptr;

	// 頂点バッファビューの作成
	D3D12_VERTEX_BUFFER_VIEW vbView{};

	//インデックスバッファビューの作成
	D3D12_INDEX_BUFFER_VIEW ibView{};

	//テクスチャサンプラーの設定
	D3D12_STATIC_SAMPLER_DESC samplerDesc{};

public:
	DirectXCommon* GetDXCommon() const { return dXCommon_; }

private:
	DirectXCommon* dXCommon_ = nullptr;
};


