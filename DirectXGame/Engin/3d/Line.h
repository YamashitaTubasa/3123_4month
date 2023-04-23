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
private: // エイリアス
	// Microsoft::WRL::を省略
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;

public:
	//// 定数バッファ用データ構造体(マテリアル)
	//struct ConstBufferDataMaterial {
	//	Vector4 color_; // 色(RGBA)
	//};

	////定数バッファ用データ構造体(3D変換行列)
	//struct ConstBufferDataTransform {
	//	Matrix4 mat;
	//};

public: // サブクラス
	// 頂点データ構造体
	struct VertexPosNormalUv
	{
		Vector3 pos; // xyz座標
		Vector3 normal; // 法線ベクトル
		Vector2 uv;  // uv座標
	};

	// 定数バッファ用データ構造体B0
	struct ConstBufferDataB0
	{
		//XMFLOAT4 color;	// 色 (RGBA)
		Matrix4 mat;	// ３Ｄ変換行列
	};

	// 定数バッファ用データ構造体B1
	struct ConstBufferDataB1
	{
		Vector3 ambient; // アンビエント係数
		float pad1;       // パディング
		Vector3 diffuse; // ディフューズ係数
		float pad2;       // パディング
		Vector3 specular; // スペキュラー係数
		float alpha;       // アルファ
	};

	// マテリアル
	struct Material
	{
		std::string name; // マテリアル名
		Vector3 ambient; // アンビエント影響度
		Vector3 diffuse; // ディフェーズ影響度
		Vector3 specular;// スペキュラー影響度
		float alpha;      // アルファ
		std::string textureFilename; // テクスチャファイル名
		// コンストラクタ
		Material() {
			ambient = { 0.3f,0.3f,0.3f };
			diffuse = { 0.0f,0.0f,0.0f };
			specular = { 0.0f,0.0f,0.0f };
			alpha = 1.0f;
		}
	};

public:
	// 初期化
	/// 静的初期化
	static void StaticInitialize(ID3D12Device* device, int window_width, int window_height);
	void Initialize();
	void InitializeDescriptorHeap();
	void CreateBuffers();

	// 更新
	void Update();

	// 描画
	void Draw();

	void PreDraw(ID3D12GraphicsCommandList* cmdList);
	void PostDraw();

public:
	Line() = default;
	~Line() = default;

private:
	//struct VertexPosUv {
	//	Vector3 pos;
	//	Vector2 uv;
	//};

	//// 頂点データ
	//std::vector<VertexPosUv> vertices = {
	//	{{ -50.0f, -50.0f, 0.0f },{0.0f,1.0f}}, // 左下
	//	{{ -50.0f,  50.0f, 0.0f },{0.0f,0.0f}}, // 左上
	//	{{  50.0f, -50.0f, 0.0f },{1.0f,1.0f}}, // 右下
	//	{{  50.0f,  50.0f, 0.0f },{1.0f,0.0f}}, // 右上
	//};

	////std::vector = 可変長配列
	//std::vector<uint16_t> indices = {
	//	0,1,2,
	//	1,2,3,
	//};

	////横方向ピクセル数
	//const size_t textureWidth = 256;
	////縦方向ピクセル数
	//const size_t textureHeight = 256;
	////配列の要素数
	//const size_t imageDataCount = textureWidth * textureHeight;
	////画像イメージデータ配列
	//Vector4* imageData = new Vector4[imageDataCount];

	//ComPtr<ID3D12RootSignature> rootSignature;
	//ComPtr<ID3D12PipelineState> pipelineState;
	//ComPtr<ID3D12Resource> vertBuff;
	//ComPtr<ID3D12Resource> indexBuff;

	////テクスチャバッファの生成
	//ID3D12Resource *texBuff = nullptr;

	////定数バッファの生成(準備)
	//ComPtr<ID3D12Resource> constBuffTransform;
	//ConstBufferDataTransform *constMapTransform = nullptr;

	//ComPtr<ID3D12Resource> constBuffMaterial;
	////ComPtr<ConstBufferDataMaterial> constMapMaterial;
	//ConstBufferDataMaterial* constMapMaterial = nullptr;

	////デスクリプタヒープを生成
	//ID3D12DescriptorHeap *srvHeap = nullptr;

	//// 頂点バッファビューの作成
	//D3D12_VERTEX_BUFFER_VIEW vbView{};

	////インデックスバッファビューの作成
	//D3D12_INDEX_BUFFER_VIEW ibView{};

	////テクスチャサンプラーの設定
	//D3D12_STATIC_SAMPLER_DESC samplerDesc{};

private: // 静的メンバ変数
	// デバイス
	static ID3D12Device* device;
	// 頂点データ配列
	std::vector<VertexPosNormalUv> vertices;
	// 頂点インデックス配列
	std::vector<unsigned short> indices;
	// マテリアル
	Material material;
	// テクスチャバッファ
	ComPtr<ID3D12Resource> texbuff;
	// デスクリプタヒープ
	ComPtr<ID3D12DescriptorHeap> descHeap;
	// シェーダリソースビューのハンドル(CPU)
	CD3DX12_CPU_DESCRIPTOR_HANDLE cpuDescHandleSRV;
	// シェーダリソースビューのハンドル(CPU)
	CD3DX12_GPU_DESCRIPTOR_HANDLE gpuDescHandleSRV;
	// デスクリプタサイズ
	UINT descriptorHandleIncrementSize;
	// 頂点バッファ
	ComPtr<ID3D12Resource> vertBuff;
	// インデックスバッファ
	ComPtr<ID3D12Resource> indexBuff;
	// 頂点バッファビュー
	D3D12_VERTEX_BUFFER_VIEW vbView;
	// インデックスバッファビュー
	D3D12_INDEX_BUFFER_VIEW ibView;
	// 定数バッファ（マテリアル）
	ComPtr<ID3D12Resource> constBuffB1; // 定数バッファ

	// コマンドリスト
	static ID3D12GraphicsCommandList* cmdList;
	// ルートシグネチャ
	static ComPtr<ID3D12RootSignature> rootsignature;
	// パイプラインステートオブジェクト
	static ComPtr<ID3D12PipelineState> pipelinestate;
};


