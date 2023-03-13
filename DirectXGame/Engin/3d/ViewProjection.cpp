#include "ViewProjection.h"
#include <d3dcompiler.h>
#include <DirectXTex.h>
#include <fstream>
#include <sstream>
#include <vector>

Matrix4 ViewProjection::matView{};
Matrix4 ViewProjection::matProjection{};
Vector3 ViewProjection::eye = { 0, 5, 10.0f };
Vector3 ViewProjection::target = { 0, 0, 0 };
Vector3 ViewProjection::up = { 0, 1, 0 };

Microsoft::WRL::ComPtr<ID3D12Device> ViewProjection::device_ = nullptr;

void ViewProjection::StaticInitialize(ID3D12Device* device)
{
	assert(device);
	device_ = device;
}

void ViewProjection::Initialize() {
	CreateConstBuffer();
	Map();
	UpdateMatrix();
}

void ViewProjection::CreateConstBuffer()
{
	HRESULT result;

	// ヒーププロパティ
	CD3DX12_HEAP_PROPERTIES heapProps = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD);
	// リソース設定
	CD3DX12_RESOURCE_DESC resourceDesc =
		CD3DX12_RESOURCE_DESC::Buffer((sizeof(ConstBufferDataViewProjection) + 0xff) & ~0xff);

	// 定数バッファの生成
	result = device_->CreateCommittedResource(
		&heapProps, // アップロード可能
		D3D12_HEAP_FLAG_NONE, &resourceDesc, D3D12_RESOURCE_STATE_GENERIC_READ, nullptr,
		IID_PPV_ARGS(&constBuff));
	assert(SUCCEEDED(result));
}

void ViewProjection::Map()
{
	// 定数バッファとのデータリンク
	HRESULT result = constBuff->Map(0, nullptr, (void**)&constMap);
	assert(SUCCEEDED(result));
}

void ViewProjection::UpdateMatrix()
{
	// ビュー行列の作成
	matView.ViewMat(eye, target, up);
	// 射影行列の作成
	matProjection.ProjectionMat(fovAngleY, aspectRatio, nearZ, farZ);

	//定数バッファに転送
	constMap->view = matView;
	constMap->projection = matProjection;
	constMap->cameraPos = eye;
}

void ViewProjection::Update() {
	// ビュー行列の更新
	matView.ViewMat(eye, target, up);

	//定数バッファに転送
	constMap->view = matView;
	constMap->projection = matProjection;
	constMap->cameraPos = eye;
}

void ViewProjection::SetEye(Vector3 eye)
{
	ViewProjection::eye = eye;
}

void ViewProjection::SetTarget(Vector3 target)
{
	ViewProjection::target = target;
}