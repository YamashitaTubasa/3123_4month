#include "RideLight.h"

void RideLight::Initialize()
{
	// ���N���X�̏�����
	RLFramework::Initialize();

	// �Q�[���V�[���̐����Ə�����
	scene_ = new GameTitleScene();
	scene_->Initialize();
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
	// �`��O����
	dXCommon->PreDraw();

	// �Q�[���V�[���̕`��
	scene_->Draw();

	// ImGui�`��
	imGuiManager->Draw(dXCommon);

	// �`��㏈��
	dXCommon->PostDraw();
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
