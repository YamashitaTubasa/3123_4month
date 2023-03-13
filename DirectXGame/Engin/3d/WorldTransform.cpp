#include "WorldTransform.h"
#include<cassert>
#include <d3dx12.h>

Microsoft::WRL::ComPtr<ID3D12Device> WorldTransform::device_ = nullptr;

void WorldTransform::StaticInitialize(ID3D12Device* device)
{
	assert(device);
	device_ = device;
}

void WorldTransform::Initialize()
{
	CreateConstBuffer();
	Map();
	UpdateMatrix();
}

void WorldTransform::CreateConstBuffer()
{
	assert(device_);

	// �q�[�v�v���p�e�B
	CD3DX12_HEAP_PROPERTIES heapProps = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD);
	// ���\�[�X�ݒ�
	CD3DX12_RESOURCE_DESC resourceDesc =
		CD3DX12_RESOURCE_DESC::Buffer((sizeof(ConstBufferDataWorldTransform) + 0xff) & ~0xff);

	HRESULT result;

	// �萔�o�b�t�@�̐���
	result = device_->CreateCommittedResource(
		&heapProps, // �A�b�v���[�h�\
		D3D12_HEAP_FLAG_NONE,
		&resourceDesc,
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS(&constBuff));

	assert(SUCCEEDED(result));
}

void WorldTransform::Map()
{
	//�萔�o�b�t�@�̃}�b�s���O
	HRESULT result = constBuff->Map(0, nullptr, (void**)&constMap);//�}�b�s���O
	assert(SUCCEEDED(result));
}

void WorldTransform::UpdateMatrix()
{
	Matrix4 matScale, matRot, matTrans;
	Matrix4 matRotX, matRotY, matRotZ;
	matScale.identity();

	matTrans.identity();

	//�e�s��v�Z
	matScale.scale(scale_);
	matRot.identity();
	matRotZ.rotateZ(rotation_.z);
	matRotX.rotateX(rotation_.x);
	matRotY.rotateY(rotation_.y);
	matRot = matRotZ * matRotX * matRotY;
	matTrans.translate(position_);

	matWorld_.identity();
	matWorld_ *= matScale;
	matWorld_ *= matRot;
	matWorld_ *= matTrans;

	if (parent_ != nullptr) {
		matWorld_ *= parent_->matWorld_;
	}

	//�萔�o�b�t�@�ɓ]��
	constMap->matWorld = matWorld_;
}
