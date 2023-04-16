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
	struct VertexPosUv {
		Vector3 pos;
		Vector2 uv;
	};

	// 頂点データ
	std::vector<VertexPosUv> vertices = {
		{{ -0.4f, -0.7f, 0.0f },{0.0f,1.0f}}, // 左下
		{{ -0.4f, +0.7f, 0.0f },{0.0f,0.0f}}, // 左上
		{{ +0.4f, -0.7f, 0.0f },{1.0f,1.0f}}, // 右下
		{{ +0.4f, +0.7f, 0.0f },{1.0f,0.0f}}, // 右上
	};

	//std::vector = 可変長配列
	std::vector<uint16_t> indices = {
		0,1,2,
		1,2,3,
	};

	ComPtr<ID3D12RootSignature> rootSignature;
	ComPtr<ID3D12PipelineState> pipelineState;
	ComPtr<ID3D12Resource> vertBuff;
	ComPtr<ID3D12Resource> indexBuff;

	//定数バッファの生成(準備)
	ComPtr<ID3D12Resource> constBuffTransform;
	//ComPtr<ConstBufferDataTransform> constMapTransform;

	ComPtr<ID3D12Resource> constBuffMaterial;
	//ComPtr<ConstBufferDataMaterial> constMapMaterial;
	ConstBufferDataMaterial* constMapMaterial = nullptr;

	// 頂点バッファビューの作成
	D3D12_VERTEX_BUFFER_VIEW vbView{};

	//インデックスバッファビューの作成
	D3D12_INDEX_BUFFER_VIEW ibView{};

public:
	DirectXCommon* GetDXCommon() const { return dXCommon_; }

private:
	DirectXCommon* dXCommon_ = nullptr;
};


