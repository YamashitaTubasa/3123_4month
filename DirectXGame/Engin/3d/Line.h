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
#include "ViewProjection.h"
#include "Model.h"
#include "WorldTransform.h"


/// 3Dオブジェクト
class Line
{
public:
	//頂点バッファ
	struct LineVertex
	{
		Vector3 pos = { 0, 0, 0 };
	};
private: // エイリアス
	// Microsoft::WRL::を省略
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;

public: // 静的メンバ関数
	/// 静的初期化
	static void StaticInitialize(ID3D12Device* device);

	/// 描画前処理
	static void PreDraw(ID3D12GraphicsCommandList* cmdList);

	/// 描画後処理
	static void PostDraw();

	/// 3Dオブジェクト生成
	static Line* Create();

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
	//初期化
	bool Initialize();

	/// 毎フレーム処理
	void Update();

	/// 描画
	void Draw(ViewProjection* viewProjection);

	// モデルの設定
	void SetModel(Model* model) { this->model = model; }

	const Vector3& GetPosition() const { return worldTransform_.position_; }
	void SetPosition(const Vector3& position) { this->worldTransform_.position_ = position; }
	// オブジェクトの大きさ
	void SetScale(const Vector3& scale) { this->worldTransform_.scale_ = scale; }
public:
	// ワールド変換データ
	WorldTransform worldTransform_;

protected: // メンバ変数
	// モデル
	Model* model = nullptr;

};