#pragma once

#include <Windows.h>
#include <wrl.h>
#include <d3d12.h>
#include <DirectXMath.h>
#include <d3dx12.h>
#include <string>
#include "WorldTransform.h"
#include "ViewProjection.h"
#include "Model.h"
#include "CollisionInfo.h"

class BaseCollider;

/// 3Dオブジェクト
class Object3d
{
private: // エイリアス
	// Microsoft::WRL::を省略
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;


public: // サブクラス
	
	// 定数バッファ用データ構造体B0
	struct ConstBufferDataB0
	{
		Vector4 color;	// 色 (RGBA)
		Matrix4 mat;	// ３Ｄ変換行列
	};

public: // 静的メンバ関数
	/// 静的初期化
	static void StaticInitialize(ID3D12Device* device, int window_width, int window_height);

	/// 描画前処理
	static void PreDraw(ID3D12GraphicsCommandList* cmdList);

	/// 描画後処理
	static void PostDraw();

	/// 3Dオブジェクト生成
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

	/// グラフィックパイプライン生成
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
	virtual void Draw(ViewProjection* viewProjection);
	virtual void Draw(ViewProjection* viewProjection, float alpha_);

	//ワールド行列の取得
	const Matrix4& GetMatWorld() { return matWorld; }

	//コライダーのセット
	void SetCollider(BaseCollider* collider);

	//衝突時コールバック関数
	virtual void OnCollision(const CollisionInfo& info){}

	// モデルの設定
	void SetModel(Model* model) { this->model = model; }

	// オブジェクトの座標
	const Vector3& GetPosition() const { return position; }
	void SetPosition(const Vector3& position) { this->position = position; }
	// オブジェクトの大きさ
	void SetScale(const Vector3& scale) { this->scale = scale; }
	const Vector3& GetScale() const { return scale; }
	// オブジェクトの回転
	void SetRotation(const Vector3& rotation) { this->rotation = rotation; }
	const Vector3& GetRotation() const { return rotation; }

public:
	// ワールド変換データ
	WorldTransform worldTransform_;

protected: // メンバ変数
	//クラス名
	const char* name = nullptr;
	//コライダー
	BaseCollider* collider = nullptr;

	// モデル
	Model* model = nullptr;
	// 定数バッファ
	ComPtr<ID3D12Resource> constBuff; 
	// 定数バッファのマップ
	ConstBufferDataB0* constMap = nullptr;
	// ローカルスケール
	Vector3 scale = { 1,1,1 };
	// X,Y,Z軸回りのローカル回転角
	Vector3 rotation = { 0,0,0 };
	// ローカル座標
	Vector3 position = { 0,0,0 };
	// ローカルワールド変換行列
	Matrix4 matWorld;
	// 親オブジェクト
	Object3d* parent = nullptr;
};

