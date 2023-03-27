#include "GameTitleScene.h"

GameTitleScene::GameTitleScene()
{
}

GameTitleScene::~GameTitleScene()
{
}

void GameTitleScene::Initialize(DirectXCommon* dXCommon, WinApp* winApp, SpriteCommon& spriteCommon)
{
	// �X�v���C�g
	sprite = new Sprite();
	spriteCommon_ = sprite->SpriteCommonCreate(dXCommon->GetDevice(), 1280, 720);
	// �X�v���C�g�p�p�C�v���C�������Ăяo��
	PipelineSet spritePipelineSet = sprite->SpriteCreateGraphicsPipeline(dXCommon->GetDevice());

	// HP
	Title.LoadTexture(spriteCommon_, 0, L"Resources/title.png", dXCommon->GetDevice());
	Title.SetColor(Vector4(1, 1, 1, 1));
	Title.SpriteCreate(dXCommon->GetDevice(), 1280, 720, 0, spriteCommon, Vector2(0.0f, 0.0f), false, false);
	Title.SetPosition(Vector3(0, 0, 0));
	Title.SetScale(Vector2(1280 * 1, 720 * 1));
	Title.SetRotation(0.0f);
	Title.SpriteTransferVertexBuffer(Title, spriteCommon, 0);
	Title.SpriteUpdate(Title, spriteCommon_);
}

void GameTitleScene::Update()
{
}

void GameTitleScene::Draw(DirectXCommon* dXCommon)
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
	Sprite::PreDraw(dXCommon->GetCommandList(), spriteCommon_);

	///=== �X�v���C�g�`�� ===///
	Title.SpriteDraw(dXCommon->GetCommandList(), spriteCommon_, dXCommon->GetDevice(), Title.vbView);

	// �X�v���C�g�`��㏈��
	Sprite::PostDraw();

#pragma endregion
}

void GameTitleScene::Finalize()
{
	// �X�v���C�g���
	delete sprite;
	sprite = nullptr;
}
