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

	// �q�[�v�v���p�e�B
	CD3DX12_HEAP_PROPERTIES heapProps = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD);
	// ���\�[�X�ݒ�
	CD3DX12_RESOURCE_DESC resourceDesc =
		CD3DX12_RESOURCE_DESC::Buffer((sizeof(ConstBufferDataViewProjection) + 0xff) & ~0xff);

	// �萔�o�b�t�@�̐���
	result = device_->CreateCommittedResource(
		&heapProps, // �A�b�v���[�h�\
		D3D12_HEAP_FLAG_NONE, &resourceDesc, D3D12_RESOURCE_STATE_GENERIC_READ, nullptr,
		IID_PPV_ARGS(&constBuff));
	assert(SUCCEEDED(result));
}

void ViewProjection::Map()
{
	// �萔�o�b�t�@�Ƃ̃f�[�^�����N
	HRESULT result = constBuff->Map(0, nullptr, (void**)&constMap);
	assert(SUCCEEDED(result));
}

void ViewProjection::UpdateMatrix()
{
	// �r���[�s��̍쐬
	matView.ViewMat(eye, target, up);
	// �ˉe�s��̍쐬
	matProjection.ProjectionMat(fovAngleY, aspectRatio, nearZ, farZ);

	//�萔�o�b�t�@�ɓ]��
	constMap->view = matView;
	constMap->projection = matProjection;
	constMap->cameraPos = eye;
}

void ViewProjection::Update() {
	// �r���[�s��̍X�V
	matView.ViewMat(eye, target, up);

	//�萔�o�b�t�@�ɓ]��
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