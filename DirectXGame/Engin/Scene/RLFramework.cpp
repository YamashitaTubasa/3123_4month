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
	winApp = WinApp::GetInstance();
	winApp->Initialize();

	// DirectX�̏�����
	dXCommon = DirectXCommon::GetInstance();
	dXCommon->Initialize(winApp);

	// ���͂̏�����
	input = Input::GetInstance();
	input->Initialize(winApp);

	// ImGui�̏�����
	imGuiManager = new ImGuiManager();
	imGuiManager->Initialize(dXCommon, winApp);

	// �X�v���C�g���ʕ��̏�����
	//spriteCommon = SpriteCommon::GetInstance();
	//spriteCommon->Initialize();

	// 3D�I�u�W�F�N�g�ÓI������
	Object3d::StaticInitialize(dXCommon->GetDevice(), WinApp::window_width, WinApp::window_height);

	// �p�[�e�B�N���ÓI������
	ParticleManager::StaticInitialize(dXCommon->GetDevice(), WinApp::window_width, WinApp::window_height);
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
	// imgui�̏I������
	imGuiManager->Finalize();
	// imgui�̉��
	delete imGuiManager;
	imGuiManager = nullptr;

	// WindowsAPI�̏I������
	winApp->Finalize();
	
	// DirectX���
	dXCommon->fpsFixedFinalize();
}
