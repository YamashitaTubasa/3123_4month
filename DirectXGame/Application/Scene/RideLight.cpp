#include "RideLight.h"

void RideLight::Initialize()
{
	// ���N���X�̏�����
	RLFramework::Initialize();

}

void RideLight::Update()
{
	// ���N���X�̍X�V����
	RLFramework::Update();

	// ImGui��t�J�n
	imGuiManager->Begin();

	// �Q�[���V�[���̍X�V
	gameScene->Update();

	// ImGui��t�I��
	imGuiManager->End();
}

void RideLight::Draw()
{
	// �`��O����
	dXCommon->PreDraw();

	// �Q�[���V�[���̕`��
	gameScene->Draw(dXCommon);

	// ImGui�`��
	imGuiManager->Draw(dXCommon);

	// �`��㏈��
	dXCommon->PostDraw();
}

void RideLight::Finalize()
{

	// ���N���X�̏I������
	RLFramework::Finalize();
}
