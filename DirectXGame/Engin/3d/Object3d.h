#pragma once

#include <Windows.h>
#include <wrl.h>
#include <d3d12.h>
#include <DirectXMath.h>
#include <d3dx12.h>
#include <string>
#include "ViewProjection.h"
#include "Model.h"
#include "CollisionInfo.h"

class BaseCollider;

/// <summary>
/// 3Dオブジェクト
/// </summary>
class Object3d
{
private: // エイリアス
	// Microsoft::WRL::を省略
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	// DirectX::を省略
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;

public: // サブクラス
	
	// 定数バッファ用データ構造体B0
	struct ConstBufferDataB0
	{
		//XMFLOAT4 color;	// 色 (RGBA)
		XMMATRIX mat;	// ３Ｄ変換行列
	};

public: // 静的メンバ関数
	/// <summary>
	/// 静的初期化
	/// </summary>
	/// <param name="device">デバイス</param>
	/// <param name="window_width">画面幅</param>
	/// <param name="window_height">画面高さ</param>
	static void StaticInitialize(ID3D12Device* device, int window_width, int window_height);

	/// <summary>
	/// 描画前処理
	/// </summary>
	/// <param name="cmdList">描画コマンドリスト</param>
	static void PreDraw(ID3D12GraphicsCommandList* cmdList);

	/// <summary>
	/// 描画後処理
	/// </summary>
	static void PostDraw();

	/// <summary>
	/// 3Dオブジェクト生成
	/// </summary>
	/// <returns></returns>
	static Object3d* Create();

private: // 静的メンバ変数
	// デバイス
	static ID3D12Device* device;
	// コマンドリスト
	static ID3D12GraphicsCommandList* cmdList;
	// ルートシグネチャ
	static ComPtr<ID3D12RootSignature> rootsignature;
	// パイプラインステートオブジェクト
	static ComPtr<ID3D12PipelineState> pipelinestate;

private:// 静的メンバ関数

	/// <summary>
	/// グラフィックパイプライン生成
	/// </summary>
	/// <returns>成否</returns>
	static void InitializeGraphicsPipeline();

public: // メンバ関数

	//コンストラクタ
	Object3d() = default;

	//デストラクタ
	virtual ~Object3d();

	//初期化
	virtual bool Initialize();

	/// 毎フレーム処理
	virtual void Update();

	/// 描画
	virtual void Draw();
	virtual void Draw(float alpha_);

	//ワールド行列の取得
	const XMMATRIX& GetMatWorld() { return matWorld; }

	//コライダーのセット
	void SetCollider(BaseCollider* collider);

	//衝突時コールバック関数
	virtual void OnCollision(const CollisionInfo& info){}

	// モデルの設定
	void SetModel(Model* model) { this->model = model; }

	// オブジェクトの座標
	const XMFLOAT3& GetPosition() const { return position; }
	void SetPosition(const XMFLOAT3& position) { this->position = position; }
	// オブジェクトの大きさ
	void SetScale(const XMFLOAT3& scale) { this->scale = scale; }
	const XMFLOAT3& GetScale() const { return scale; }
	// オブジェクトの回転
	void SetRotation(const XMFLOAT3& rotation) { this->rotation = rotation; }
	const XMFLOAT3& GetRotation() const { return rotation; }

protected: // メンバ変数
	//クラス名
	const char* name = nullptr;
	//コライダー
	BaseCollider* collider = nullptr;

	// モデル
	Model* model = nullptr;
	// 定数バッファ
	ComPtr<ID3D12Resource> constBuffB0; 
	// 色
	XMFLOAT4 color = { 1,1,1,1 };
	// ローカルスケール
	XMFLOAT3 scale = { 1,1,1 };
	// X,Y,Z軸回りのローカル回転角
	XMFLOAT3 rotation = { 0,0,0 };
	// ローカル座標
	XMFLOAT3 position = { 0,0,0 };
	// ローカルワールド変換行列
	XMMATRIX matWorld;
	// 親オブジェクト
	Object3d* parent = nullptr;
};

