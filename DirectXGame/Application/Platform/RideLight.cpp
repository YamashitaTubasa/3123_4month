#include "RideLight.h"

void RideLight::Initialize()
{
	// ���N���X�̏�����
	RLFramework::Initialize();

	// �Q�[���V�[���̐���
	gamePlayScene = new GamePlayScene();
	// �Q�[���V�[���̏�����
	gamePlayScene->Initialize(dXCommon, winApp, spriteCommon, input);
}

void RideLight::Update()
{
	// ���N���X�̍X�V����
	RLFramework::Update();

	// ImGui��t�J�n
	imGuiManager->Begin();

	// �Q�[���V�[���̍X�V
	gamePlayScene->Update();

	// ImGui��t�I��
	imGuiManager->End();
}

void RideLight::Draw()
{
	// �`��O����
	dXCommon->PreDraw();

	// �Q�[���V�[���̕`��
	gamePlayScene->Draw(dXCommon);

	// ImGui�`��
	imGuiManager->Draw(dXCommon);

	// �`��㏈��
	dXCommon->PostDraw();
}

void RideLight::Finalize()
{
	// �Q�[���V�[���̏I������
	gamePlayScene->Finalize();
	// �Q�[���V�[���̉��
	delete gamePlayScene;

	// ���N���X�̏I������
	RLFramework::Finalize();
}
