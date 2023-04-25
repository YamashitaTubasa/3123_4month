#pragma once

#include <Windows.h>
#include <wrl.h>
#include <d3d12.h>
#include <DirectXMath.h>
#include <d3dx12.h>
#include <string>
#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"
#include "Matrix4.h"
#include "Spline.h"

class Model 
{
private: // �G�C���A�X
	// Microsoft::WRL::���ȗ�
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;

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

	// �萔�o�b�t�@�p�f�[�^�\����B2
	struct ConstBufferDataB2
	{
		Vector4 color;	// �F (RGBA)
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

	//���_�o�b�t�@
	struct LineVertex
	{
		Vector3 pos;
	};

private: // �萔
	static const int division = 50; // ������
	static const float radius; // ��ʂ̔��a
	static const float prizmHeight; // ���̍���
	static const int planeCount = division * 2 + division * 2; // �ʂ̐�
	static const int vertexCount = planeCount * 3; // ���_��

public: // �ÓI�����o�֐�
	
	// OBJ�t�@�C������3D���f����ǂݍ���
	static Model* LoadFromOBJ(const std::string& modelname, const std::string& texname = "Resources");
	static Model* CreateLine(std::vector<Vector3>& point);

	// �}�e���A���ǂݍ���
	void LoadMaterial(const std::string& directoryPath, const std::string& filename);

	// �e�N�X�`���ǂݍ���
	void LoadTexture(const std::string& directoryPath, const std::string& filename);
	void LoadTexture(const std::string& filename = "Resources");

	// �`��
	/// <param name="cmdList">�`��R�}���h���X�g</param>
	/// <param name="rootParamIndexMaterial">�}�e���A���p���[�g�p�����[�^�ԍ�</param>
	void Draw(ID3D12GraphicsCommandList* cmdList, UINT rootParamIndexMaterial,float alpha_ = 1);
	void DrawLine(ID3D12GraphicsCommandList* cmdList, UINT rootParamIndexMaterial);

	// setter
	static void SetDevice(ID3D12Device* device) { Model::device = device; }

	void SetAlpha(float alpha_);

	void UpdateLineVertex(std::vector<Vector3>& point);


private: // �ÓI�����o�ϐ�
	// �f�o�C�X
	static ID3D12Device* device;
	// ���_�f�[�^�z��
	std::vector<VertexPosNormalUv> vertices;
	std::vector<LineVertex> lineVertices;
	// ���_�C���f�b�N�X�z��
	std::vector<unsigned short> indices;
	std::vector<unsigned short> lineIndices;
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
	ComPtr<ID3D12Resource> constBuffB2; // �萔�o�b�t�@
private:// �ÓI�����o�֐�
	// OBJ�t�@�C������3D���f����ǂݍ���(����J)
	void LoadFromOBJInternal(const std::string& modelname);

	// �f�X�N���v�^�q�[�v�̏�����
	void InitializeDescriptorHeap();

	// �e��o�b�t�@����
	void CreateBuffers();
	void CreateLineBuffers();

};