cbuffer cbuff0 : register(b0)
{
	matrix matWorld; // ３Ｄ変換行列
};

cbuffer cbuff1 : register(b1)
{
	matrix view;       // ワールド → ビュー変換行列
	matrix projection; // ビュー → プロジェクション変換行列
	vector cameraPos;  // カメラ座標（ワールド座標）
};

// 頂点シェーダーからピクセルシェーダーへのやり取りに使用する構造体
struct VSOutput
{
	float4 svpos : SV_POSITION; // システム用頂点座標
};
