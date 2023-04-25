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


/// 3D�I�u�W�F�N�g
class Line
{
public:
	//���_�o�b�t�@
	struct LineVertex
	{
		Vector3 pos = { 0, 0, 0 };
	};
private: // �G�C���A�X
	// Microsoft::WRL::���ȗ�
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;

public: // �ÓI�����o�֐�
	/// �ÓI������
	static void StaticInitialize(ID3D12Device* device);

	/// �`��O����
	static void PreDraw(ID3D12GraphicsCommandList* cmdList);

	/// �`��㏈��
	static void PostDraw();

	/// 3D�I�u�W�F�N�g����
	static Line* Create();

private: // �ÓI�����o�ϐ�
	// �f�o�C�X
	static ID3D12Device* device;
	// �R�}���h���X�g
	static ID3D12GraphicsCommandList* cmdList;
	// ���[�g�V�O�l�`��
	static ComPtr<ID3D12RootSignature> rootsignature;
	// �p�C�v���C���X�e�[�g�I�u�W�F�N�g
	static ComPtr<ID3D12PipelineState> pipelinestate;

private:// �ÓI�����o�֐�

	/// �O���t�B�b�N�p�C�v���C������
	static void InitializeGraphicsPipeline();

public: // �����o�֐�
	//������
	bool Initialize();

	/// ���t���[������
	void Update();

	/// �`��
	void Draw(ViewProjection* viewProjection);

	// ���f���̐ݒ�
	void SetModel(Model* model) { this->model = model; }

	const Vector3& GetPosition() const { return worldTransform_.position_; }
	void SetPosition(const Vector3& position) { this->worldTransform_.position_ = position; }
	// �I�u�W�F�N�g�̑傫��
	void SetScale(const Vector3& scale) { this->worldTransform_.scale_ = scale; }
public:
	// ���[���h�ϊ��f�[�^
	WorldTransform worldTransform_;

protected: // �����o�ϐ�
	// ���f��
	Model* model = nullptr;

};