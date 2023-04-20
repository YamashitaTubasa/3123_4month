#include "RideLight.h"

void RideLight::Initialize()
{
	// ���N���X�̏�����
	RLFramework::Initialize();

	dXCommon = DirectXCommon::GetInstance();

	// �Q�[���V�[���̐����Ə�����
	scene_ = new GamePlayScene();
	scene_->Initialize(spriteCommon);
}

void RideLight::Update()
{
	// ���N���X�̍X�V����
	RLFramework::Update();

	// ImGui��t�J�n
	imGuiManager->Begin();

	// �Q�[���V�[���̍X�V
	scene_->Update();

	// ImGui��t�I��
	imGuiManager->End();
}

void RideLight::Draw()
{
#pragma region �Q�[���V�[���`��
	// �����_�[�e�N�X�`���̑O����
	postEffect_->PreDrawScene(dXCommon->GetCommandList());

	//=== �Q�[���V�[���`�� ===//
	scene_->Draw(spriteCommon);

	// �����_�[�e�N�X�`���̌㏈��
	postEffect_->PostDrawScene(dXCommon->GetCommandList());
#pragma endregion

#pragma region �`��
	// �`��O����
	dXCommon->PreDraw();
	
	//=== �|�X�g�G�t�F�N�g�̕`�� ===//
	postEffect_->Draw(dXCommon->GetCommandList());

	//=== ImGui�`�� ===//
	imGuiManager->Draw(dXCommon);

	// �`��㏈��
	dXCommon->PostDraw();
#pragma endregion
}

void RideLight::Finalize()
{
	// �Q�[���V�[���̏I������
	scene_->Finalize();
	// �Q�[���V�[���̉��
	delete scene_;

	// ���N���X�̏I������
	RLFramework::Finalize();
}
