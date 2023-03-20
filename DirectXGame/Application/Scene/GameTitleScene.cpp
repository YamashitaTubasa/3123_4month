#include "GameTitleScene.h"

GameTitleScene::GameTitleScene()
{
}

GameTitleScene::~GameTitleScene()
{
}

void GameTitleScene::Initialize()
{
	dXCommon = DirectXCommon::GetInstance();

	// �X�v���C�g
	sprite = new Sprite();

	sprite->Initialize();
}

void GameTitleScene::Update()
{
}

void GameTitleScene::Draw()
{
#pragma region 3D�I�u�W�F�N�g�`��

	// 3D�I�u�W�F�N�g�`��O����
	Object3d::PreDraw(dXCommon->GetCommandList());

	///=== 3D�I�u�W�F�N�g�`�� ===///
	
	// 3D�I�u�W�F�N�g�`��㏈��
	Object3d::PostDraw();

#pragma endregion

#pragma region �p�[�e�B�N���`��

	// �p�[�e�B�N���`��O����
	ParticleManager::PreDraw(dXCommon->GetCommandList());

	///==== �p�[�e�B�N���`�� ====///

	// �p�[�e�B�N���`��㏈��
	ParticleManager::PostDraw();

#pragma endregion

#pragma region �X�v���C�g�`��

	// �X�v���C�g�`��O����

	///=== �X�v���C�g�`�� ===///
	sprite->Draw();
	
	// �X�v���C�g�`��㏈��
	
#pragma endregion
}

void GameTitleScene::Finalize()
{
	delete sprite;
}
