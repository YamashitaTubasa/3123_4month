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




class Line {
private: // �G�C���A�X
	// Microsoft::WRL::���ȗ�
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;

public:
	//// �萔�o�b�t�@�p�f�[�^�\����(�}�e���A��)
	//struct ConstBufferDataMaterial {
	//	Vector4 color_; // �F(RGBA)
	//};

	////�萔�o�b�t�@�p�f�[�^�\����(3D�ϊ��s��)
	//struct ConstBufferDataTransform {
	//	Matrix4 mat;
	//};

public: // �T�u�N���X
	// ���_�f�[�^�\����
	struct VertexPosNormalUv
	{
		Vector3 pos; // xyz���W
		Vector3 normal; // �@���x�N�g��
		Vector2 uv;  // uv���W
	};

	// �萔�o�b�t�@�p�f�[�^�\����B0
	struct ConstBufferDataB0
	{
		//XMFLOAT4 color;	// �F (RGBA)
		Matrix4 mat;	// �R�c�ϊ��s��
	};

	// �萔�o�b�t�@�p�f�[�^�\����B1
	struct ConstBufferDataB1
	{
		Vector3 ambient; // �A���r�G���g�W��
		float pad1;       // �p�f�B���O
		Vector3 diffuse; // �f�B�t���[�Y�W��
		float pad2;       // �p�f�B���O
		Vector3 specular; // �X�y�L�����[�W��
		float alpha;       // �A���t�@
	};

	// �}�e���A��
	struct Material
	{
		std::string name; // �}�e���A����
		Vector3 ambient; // �A���r�G���g�e���x
		Vector3 diffuse; // �f�B�t�F�[�Y�e���x
		Vector3 specular;// �X�y�L�����[�e���x
		float alpha;      // �A���t�@
		std::string textureFilename; // �e�N�X�`���t�@�C����
		// �R���X�g���N�^
		Material() {
			ambient = { 0.3f,0.3f,0.3f };
			diffuse = { 0.0f,0.0f,0.0f };
			specular = { 0.0f,0.0f,0.0f };
			alpha = 1.0f;
		}
	};

public:
	// ������
	/// �ÓI������
	static void StaticInitialize(ID3D12Device* device, int window_width, int window_height);
	void Initialize();
	void InitializeDescriptorHeap();
	void CreateBuffers();

	// �X�V
	void Update();

	// �`��
	void Draw();

	void PreDraw(ID3D12GraphicsCommandList* cmdList);
	void PostDraw();

public:
	Line() = default;
	~Line() = default;

private:
	//struct VertexPosUv {
	//	Vector3 pos;
	//	Vector2 uv;
	//};

	//// ���_�f�[�^
	//std::vector<VertexPosUv> vertices = {
	//	{{ -50.0f, -50.0f, 0.0f },{0.0f,1.0f}}, // ����
	//	{{ -50.0f,  50.0f, 0.0f },{0.0f,0.0f}}, // ����
	//	{{  50.0f, -50.0f, 0.0f },{1.0f,1.0f}}, // �E��
	//	{{  50.0f,  50.0f, 0.0f },{1.0f,0.0f}}, // �E��
	//};

	////std::vector = �ϒ��z��
	//std::vector<uint16_t> indices = {
	//	0,1,2,
	//	1,2,3,
	//};

	////�������s�N�Z����
	//const size_t textureWidth = 256;
	////�c�����s�N�Z����
	//const size_t textureHeight = 256;
	////�z��̗v�f��
	//const size_t imageDataCount = textureWidth * textureHeight;
	////�摜�C���[�W�f�[�^�z��
	//Vector4* imageData = new Vector4[imageDataCount];

	//ComPtr<ID3D12RootSignature> rootSignature;
	//ComPtr<ID3D12PipelineState> pipelineState;
	//ComPtr<ID3D12Resource> vertBuff;
	//ComPtr<ID3D12Resource> indexBuff;

	////�e�N�X�`���o�b�t�@�̐���
	//ID3D12Resource *texBuff = nullptr;

	////�萔�o�b�t�@�̐���(����)
	//ComPtr<ID3D12Resource> constBuffTransform;
	//ConstBufferDataTransform *constMapTransform = nullptr;

	//ComPtr<ID3D12Resource> constBuffMaterial;
	////ComPtr<ConstBufferDataMaterial> constMapMaterial;
	//ConstBufferDataMaterial* constMapMaterial = nullptr;

	////�f�X�N���v�^�q�[�v�𐶐�
	//ID3D12DescriptorHeap *srvHeap = nullptr;

	//// ���_�o�b�t�@�r���[�̍쐬
	//D3D12_VERTEX_BUFFER_VIEW vbView{};

	////�C���f�b�N�X�o�b�t�@�r���[�̍쐬
	//D3D12_INDEX_BUFFER_VIEW ibView{};

	////�e�N�X�`���T���v���[�̐ݒ�
	//D3D12_STATIC_SAMPLER_DESC samplerDesc{};

private: // �ÓI�����o�ϐ�
	// �f�o�C�X
	static ID3D12Device* device;
	// ���_�f�[�^�z��
	std::vector<VertexPosNormalUv> vertices;
	// ���_�C���f�b�N�X�z��
	std::vector<unsigned short> indices;
	// �}�e���A��
	Material material;
	// �e�N�X�`���o�b�t�@
	ComPtr<ID3D12Resource> texbuff;
	// �f�X�N���v�^�q�[�v
	ComPtr<ID3D12DescriptorHeap> descHeap;
	// �V�F�[�_���\�[�X�r���[�̃n���h��(CPU)
	CD3DX12_CPU_DESCRIPTOR_HANDLE cpuDescHandleSRV;
	// �V�F�[�_���\�[�X�r���[�̃n���h��(CPU)
	CD3DX12_GPU_DESCRIPTOR_HANDLE gpuDescHandleSRV;
	// �f�X�N���v�^�T�C�Y
	UINT descriptorHandleIncrementSize;
	// ���_�o�b�t�@
	ComPtr<ID3D12Resource> vertBuff;
	// �C���f�b�N�X�o�b�t�@
	ComPtr<ID3D12Resource> indexBuff;
	// ���_�o�b�t�@�r���[
	D3D12_VERTEX_BUFFER_VIEW vbView;
	// �C���f�b�N�X�o�b�t�@�r���[
	D3D12_INDEX_BUFFER_VIEW ibView;
	// �萔�o�b�t�@�i�}�e���A���j
	ComPtr<ID3D12Resource> constBuffB1; // �萔�o�b�t�@

	// �R�}���h���X�g
	static ID3D12GraphicsCommandList* cmdList;
	// ���[�g�V�O�l�`��
	static ComPtr<ID3D12RootSignature> rootsignature;
	// �p�C�v���C���X�e�[�g�I�u�W�F�N�g
	static ComPtr<ID3D12PipelineState> pipelinestate;
};


