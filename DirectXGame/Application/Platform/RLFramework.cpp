#include "RLFramework.h"

void RLFramework::Run()
{
	// �Q�[���̏�����
	Initialize();

	while (true) // �Q�[�����[�v 
	{
		// ���t���[���X�V
		Update();

		// �I�����N�G�X�g�������烋�[�v�𔲂���
		if (IsEndRequest()) {
			// �Q�[�����[�v�𔲂���
			break;
		}

		// �`��
		Draw();
	}

	// �Q�[���̏I��
	Finalize();
}

void RLFramework::Initialize()
{
	// WindowsAPI�̏�����
	winApp = new WinApp();
	winApp->Initialize();

	// DirectX�̏�����
	dXCommon = new DirectXCommon();
	dXCommon->Initialize(winApp);

	// ���͂̏�����
	input = new Input();
	input->Initialize(winApp);

	// ImGui�̏�����
	imGuiManager = new ImGuiManager();
	imGuiManager->Initialize(dXCommon, winApp);

	// 3D�I�u�W�F�N�g�ÓI������
	Object3d::StaticInitialize(dXCommon->GetDevice(), WinApp::window_width, WinApp::window_height);

	// �Q�[���V�[���̏�����
	gameScene = new GameScene();
	gameScene->Initialize(dXCommon, winApp, spriteCommon, input);
}

void RLFramework::Update()
{
	// Windows�̃��b�Z�[�W����
	if (winApp->ProcessMessage()) {
		// �Q�[�����[�v�𔲂���
		endRequest_ = true;
	}

	// ���͂̍X�V
	input->Update();
}

void RLFramework::Finalize()
{
	// �Q�[���V�[���̉��
	gameScene->Finalize();

	// imgui�̏I������
	imGuiManager->Finalize();
	// imgui�̉��
	delete imGuiManager;
	imGuiManager = nullptr;

	// ���͊J��
	delete input;
	input = nullptr;

	// WindowsAPI�̏I������
	winApp->Finalize();
	// WindowsAPI���
	delete winApp;
	winApp = nullptr;

	// DirectX���
	dXCommon->fpsFixedFinalize();
	delete dXCommon;
	dXCommon = nullptr;
}
