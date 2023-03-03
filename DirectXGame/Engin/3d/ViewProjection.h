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

#pragma endregion
private:
#pragma region 射影行列の設定
	float PI = 3.141592;
	// 垂直方向視野角
	float fovAngleY = 45.0f *  PI / 180.0f;
	// ビューポートのアスペクト比
	float aspectRatio = (float)16 / 9;
	// 深度限界（手前側）
	float nearZ = 0.1f;
	// 深度限界（奥側）
	float farZ = 1000.0f;
	// 定数バッファ
	ComPtr<ID3D12Resource> constBuffB0;
#pragma endregion
	//静的メンバ変数
private:
	static XMMATRIX matView;
	// 射影行列
	static XMMATRIX matProjection;
	// 視点座標
	static XMFLOAT3 eye;
	// 注視点座標
	static XMFLOAT3 target;
	// 上方向ベクトル
	static XMFLOAT3 up;

	static void Update();

public:
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(int window_width, int window_height);
	/// <summary>
	/// 行列を更新する
	/// </summary>
	


	/// <summary>
	/// 視点座標の取得
	/// </summary>
	/// <returns>座標</returns>
	static const XMFLOAT3& GetEye() { return eye; }

	/// <summary>
	/// 視点座標の設定
	/// </summary>
	/// <param name="position">座標</param>
	static void SetEye(XMFLOAT3 eye);

	/// <summary>
	/// 注視点座標の取得
	/// </summary>
	/// <returns>座標</returns>
	static const XMFLOAT3& GetTarget() { return target; }

	/// <summary>
	/// 注視点座標の設定
	/// </summary>
	/// <param name="position">座標</param>
	static void SetTarget(XMFLOAT3 target);

	static const XMMATRIX& GetMatView() { return matView; }

	static const XMMATRIX& GetMatProjection() { return matProjection; }
};
