#pragma once

#include <d3dx12.h>
#include <d3d12.h>
#include <wrl.h>
#include "Matrix4.h"
#include "Vector3.h"
#include <DirectXMath.h>
#include <Windows.h>
#include <string>

using namespace DirectX;

/// <summary>
/// ビュープロジェクション変換データ
/// </summary>
class ViewProjection {

private:
	// Microsoft::WRL::を省略
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;

public:// サブクラス
// 定数バッファ用データ構造体
	struct ConstBufferDataViewProjection {
		Matrix4 view;       // ワールド → ビュー変換行列
		Matrix4 projection; // ビュー → プロジェクション変換行列
		Vector3 cameraPos;  // カメラ座標（ワールド座標）
	};
public:

	// 静的初期化
	static void StaticInitialize(ID3D12Device* device);

	/// 初期化
	void Initialize();

	/// 視点座標の取得
	static const Vector3& GetEye() { return eye; }

	// 定数バッファの取得
	ID3D12Resource* GetBuff() { return constBuff.Get(); }

	/// 視点座標の設定
	static void SetEye(Vector3 eye);

	/// 注視点座標の取得
	static const Vector3& GetTarget() { return target; }

	/// 注視点座標の設定
	static void SetTarget(Vector3 target);

	static const Matrix4& GetMatView() { return matView; }

	static const Matrix4& GetMatProjection() { return matProjection; }

	//定数バッファ生成
	void CreateConstBuffer();

	//マッピング
	void Map();

	/// 行列を更新する
	void UpdateMatrix();
	//座標更新
	void Update();

	//静的メンバ変数
private:
	static Matrix4 matView;
	// 射影行列
	static Matrix4 matProjection;
	// 視点座標
	static Vector3 eye;
	// 注視点座標
	static Vector3 target;
	// 上方向ベクトル
	static Vector3 up;

private:
#pragma region 射影行列の設定
	float PI = 3.141592;
	// 垂直方向視野角
	float fovAngleY = 45.0f * PI / 180.0f;
	// ビューポートのアスペクト比
	float aspectRatio = (float)16 / 9;
	// 深度限界（手前側）
	float nearZ = 0.1f;
	// 深度限界（奥側）
	float farZ = 1000.0f;
#pragma endregion

	// デバイス（借りてくる）
	static Microsoft::WRL::ComPtr<ID3D12Device> device_;

	// 定数バッファ
	ComPtr<ID3D12Resource> constBuff;

	// マッピング済みアドレス
	ConstBufferDataViewProjection* constMap = nullptr;

};
