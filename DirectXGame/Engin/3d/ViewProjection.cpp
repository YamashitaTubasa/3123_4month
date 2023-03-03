#include "ViewProjection.h"
#include <d3dcompiler.h>
#include <DirectXTex.h>
#include <fstream>
#include <sstream>
#include <vector>

XMMATRIX ViewProjection::matView{};
XMMATRIX ViewProjection::matProjection{};
XMFLOAT3 ViewProjection::eye = { 0, 5, 10.0f };
XMFLOAT3 ViewProjection::target = { 0, 0, 0 };
XMFLOAT3 ViewProjection::up = { 0, 1, 0 };

void ViewProjection::Initialize(int window_width, int window_height) {
	// ビュー行列の生成
	matView = XMMatrixLookAtLH(
		XMLoadFloat3(&eye),
		XMLoadFloat3(&target),
		XMLoadFloat3(&up));

	// 平行投影による射影行列の生成
	//constMap->mat = XMMatrixOrthographicOffCenterLH(
	//	0, window_width,
	//	window_height, 0,
	//	0, 1);
	// 透視投影による射影行列の生成
	matProjection = XMMatrixPerspectiveFovLH(
		XMConvertToRadians(60.0f),
		(float)window_width / window_height,
		0.1f, 1000.0f
	);
}

void ViewProjection::Update() {
	// ビュー行列の更新
	matView = XMMatrixLookAtLH(XMLoadFloat3(&eye), XMLoadFloat3(&target), XMLoadFloat3(&up));
}

void ViewProjection::SetEye(XMFLOAT3 eye)
{
	ViewProjection::eye = eye;

	Update();
}

void ViewProjection::SetTarget(XMFLOAT3 target)
{
	ViewProjection::target = target;

	Update();
}