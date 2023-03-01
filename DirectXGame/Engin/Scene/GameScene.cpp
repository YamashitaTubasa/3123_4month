#include "GameScene.h"

GameScene::GameScene()
{
}

GameScene::~GameScene()
{
	delete particleMan;
}

void GameScene::Initialize(DirectXCommon* dXCommon, WinApp* winApp, SpriteCommon& spriteCommon)
{
	// 3D�I�u�W�F�N�g����
	particleMan = ParticleManager::Create();
	particleMan->Update();

	// ���͂̏�����
	input = new Input();
	input->Initialize(winApp);

	// ImGui�̏�����
	imGuiManager = new ImGuiManager();
	imGuiManager->Initialize(dXCommon, winApp);
	
	// �I�u�W�F�N�g�̏�����
	ObjectInitialize(dXCommon);
	// �X�v���C�g�̏�����
	SpriteInitialize(dXCommon, spriteCommon);
	// �p�[�e�B�N���̏�����
	ParticleInitialize();
}

void GameScene::Update()
{
	// ImGui��t�J�n
	imGuiManager->Begin();

	// ���͂̍X�V
	input->Update();
	static char buf[256]{};
	static float f = 0.0f;
	switch (scene) {
		case Title:
			if (input->TriggerKey(DIK_SPACE)) {
				scene = Scene_1;
			}
			break;
		case Scene_1:
			time++;
			if (time >= 1000) {
				scene = GameClear;
			}
			ImGui::Text("Hello%d", 123);
			if (ImGui::Button("Save")) {
				imGuiManager->MySaveFunction();

				ImGui::InputText("string", buf, IM_ARRAYSIZE(buf));
				ImGui::SliderFloat("float", &f, 0.0f, 1.0f);
			}
			// �I�u�W�F�N�g�̍X�V
			ObjectUpdate();
			// �X�v���C�g�̍X�V
			SpriteUpdate();
			// �p�[�e�B�N���̍X�V
			ParticleUpdate();
			break;
		case GameClear:
			if (input->TriggerKey(DIK_SPACE)) {
				GameReset();
				scene = Title;
			}
			break;
		case GameOver:
			if (input->TriggerKey(DIK_SPACE)) {
				GameReset();
				scene = Title;
			}
			break;
	}

	// ImGui��t�I��
	imGuiManager->End();
}

void GameScene::Draw(DirectXCommon* dXCommon)
{
	// �`��O����
	dXCommon->PreDraw();

	switch (scene) {
		case Title:
			// �^�C�g���̕`��
			//TitleDraw(dXCommon);
			break;
		case Scene_1:
			// 3D�I�u�W�F�N�g�̕`��
			//ObjectDraw(dXCommon);
			// �p�[�e�B�N���̕`��
			//ParticleDraw(dXCommon);
			// HP�`��
			//GameDraw(dXCommon);
			break;
		case GameClear:
			// �Q�[���N���A�̕`��
			//GameClearDraw(dXCommon);
			break;
		case GameOver:
			//�Q�[���I�[�o�[�̕`��
			//GameOverDraw(dXCommon);
			break;
	}

	// ImGui�`��
	imGuiManager->Draw(dXCommon);
	
	// �`��㏈��
	dXCommon->PostDraw();
}

void GameScene::Finalize()
{

	// ���͊J��
	delete input;
	input = nullptr;

	// imgui�̏I������
	imGuiManager->Finalize();
	// imgui�̉��
	delete imGuiManager;
	imGuiManager = nullptr;

	// �I�u�W�F�N�g�̉��
	ObjectFinalize();

	// �X�v���C�g�̉��
	SpriteFinalize();
}

void GameScene::ObjectInitialize(DirectXCommon* dXCommon) 
{
	// OBJ���烂�f���f�[�^��ǂݍ���
	Model[0] = Model::LoadFromOBJ("fighter", "effect1.png");
	//Model[0]->LoadTexture("effect1.png");
	Model[1] = Model::LoadFromOBJ("ironSphere", "ironShpere/ironSphere.png");
	//Model[2] = Model::LoadFromOBJ("skydome", "skydome/skydome.jpg");
	// 3D�I�u�W�F�N�g����
	for (int i = 0; i < 5; i++) {
		object3d[i] = Object3d::Create();
	}
	// �I�u�W�F�N�g�Ƀ��f�����Ђ��t����
	object3d[0]->SetModel(Model[0]);
	object3d[1]->SetModel(Model[1]);
	object3d[2]->SetModel(Model[2]);
	// 3D�I�u�W�F�N�g�̈ʒu���w��
	position[0] = { -20,-5,0 };
	rotation[0] = { 0,90,0 };
	object3d[0]->SetPosition(position[0]);
	object3d[0]->SetScale({ 5, 5, 5 });
	object3d[0]->SetRotation(rotation[0]);

	position[1] = { 0,0,50 };
	object3d[1]->SetPosition(position[1]);
	object3d[1]->SetScale({ 5,5,5 });
	object3d[1]->SetRotation({ 0, 90, 0 });

	object3d[2]->SetPosition({ 0,-40,0 });
	object3d[2]->SetScale({ 100, 100, 100 });
	object3d[2]->SetRotation({0,100,20});
}

void GameScene::ObjectUpdate()
{
	// 3D�I�u�W�F�N�g�X�V
	for (int i = 0; i < 5; i++) {
		object3d[i]->Update();
	}

	object3d[0]->SetPosition(position[0]);
	object3d[0]->SetRotation(rotation[0]);
	object3d[1]->SetPosition(position[1]);

	if (input->PushKey(DIK_W)) {
		position[0].y += 0.4;
	}

	if (input->PushKey(DIK_A)) {
		position[0].x -= 0.4;
		isPush_A = true;
	}
	else {
		isPush_A = false;
	}
	if (isPush_D == false) {
		if (isPush_A == true) {
			if (rotation[0].x >= -20) {
				rotation[0].x -= 1;
			}
			if (rotation[0].x <= -20) {
				rotation[0].x = -20;
			}
		}
		else {
			if (rotation[0].x >= -20) {
				rotation[0].x += 1;
			}
			if (rotation[0].x >= 0) {
				rotation[0].x = 0;
			}
		}
	}

	if (input->PushKey(DIK_S)) {
		position[0].y -= 0.4;
	}

	if (input->PushKey(DIK_D)) {
		position[0].x += 0.4;
		isPush_D = true;
	}else {
		isPush_D = false;
	}
	if (isPush_A == false) {
		if (isPush_D == true) {
			if (rotation[0].x <= 20) {
				rotation[0].x += 1;
			}
			if (rotation[0].x >= 20) {
				rotation[0].x = 20;
			}
		}
		else {
			if (rotation[0].x <= 20) {
				rotation[0].x -= 1;
			}
			if (rotation[0].x <= 0) {
				rotation[0].x = 0;
			}
		}
	}

	position[1].z -= 1;
	if (position[1].z < -100) {
		position[1].z = 50;
	}

	// �v���C���[�ƓS���̓����蔻��
	if (CheckCollision(object3d[1]->GetPosition(), object3d[1]->GetScale()) == true) {
		playerHp -= 1;
	}
	if (playerHp == 0) {
		scene = GameOver;
	}
}

void GameScene::ObjectDraw(DirectXCommon* dXCommon)
{
	// 3D�I�u�W�F�N�g�`��O����
	Object3d::PreDraw(dXCommon->GetCommandList());

	// 3D�I�u�W�F�N�g�̕`��
	for (int i = 0; i < 5; i++) {
		object3d[i]->Draw();
	}

	// 3D�I�u�W�F�N�g�`��㏈��
	Object3d::PostDraw();
}

void GameScene::ObjectFinalize()
{
	// 3D�I�u�W�F�N�g���
	for (int i = 0; i < 5; i++) {
		delete object3d[i];
	}
	// 3D���f�����
	for (int i = 0; i < 5; i++) {
		delete Model[i];
	}
}

void GameScene::SpriteInitialize(DirectXCommon* dXCommon, SpriteCommon& spriteCommon)
{
	// �X�v���C�g
	sprite = new Sprite();
	spriteCommon_ = sprite->SpriteCommonCreate(dXCommon->GetDevice(), 1280, 720);

	// �^�C�g���̐ݒ�
	title.LoadTexture(spriteCommon_, 0, L"Resources/gametitle.png", dXCommon->GetDevice());
	title.SetColor(XMFLOAT4(1, 1, 1, 1));
	title.SpriteCreate(dXCommon->GetDevice(), 1280, 720, 0 , spriteCommon, XMFLOAT2(0.0f, 0.0f), false, false);
	title.SetPosition(XMFLOAT3(0, 0, 0));
	title.SetScale(XMFLOAT2(1280 * 1, 720 * 1));
	title.SetRotation(0.0f);
	title.SpriteTransferVertexBuffer(title, spriteCommon, 0);
	title.SpriteUpdate(title, spriteCommon_);

	// �Q�[���N���A�̐ݒ�
	gameClear.LoadTexture(spriteCommon_, 1, L"Resources/gameclear.png", dXCommon->GetDevice());
	gameClear.SpriteCreate(dXCommon->GetDevice(), 1280, 720, 1, spriteCommon, XMFLOAT2(0.0f, 0.0f), false, false);
	gameClear.SetPosition(XMFLOAT3(0, 0, 0));
	gameClear.SetScale(XMFLOAT2(1280 * 1, 720 * 1));
	gameClear.SpriteTransferVertexBuffer(gameClear, spriteCommon, 1);
	gameClear.SpriteUpdate(gameClear, spriteCommon_);

	// �Q�[���I�[�o�[�̐ݒ�
	gameOver.LoadTexture(spriteCommon_, 2, L"Resources/gameover.png", dXCommon->GetDevice());
	gameOver.SpriteCreate(dXCommon->GetDevice(), 1280, 720, 2, spriteCommon, XMFLOAT2(0.0f, 0.0f), false, false);
	gameOver.SetPosition(XMFLOAT3(0, 0, 0));
	gameOver.SetScale(XMFLOAT2(1280 * 1, 720 * 1));
	gameOver.SpriteTransferVertexBuffer(gameOver, spriteCommon, 2);
	gameOver.SpriteUpdate(gameOver, spriteCommon_);

	// HP
	hP.LoadTexture(spriteCommon_, 3, L"Resources/hp.png", dXCommon->GetDevice());
	hP.SetColor(XMFLOAT4(1, 1, 1, 1));
	hP.SpriteCreate(dXCommon->GetDevice(), 50, 50, 3, spriteCommon, XMFLOAT2(0.0f, 0.0f), false, false);
	hP.SetPosition(XMFLOAT3(0, 0, 0));
	hP.SetScale(XMFLOAT2(50 * 1, 50 * 1));
	hP.SetRotation(0.0f);
	hP.SpriteTransferVertexBuffer(hP, spriteCommon, 3);
	hP.SpriteUpdate(hP, spriteCommon_);
	hP1.LoadTexture(spriteCommon_, 4, L"Resources/hp.png", dXCommon->GetDevice());
	hP1.SetColor(XMFLOAT4(1, 1, 1, 1));
	hP1.SpriteCreate(dXCommon->GetDevice(), 50, 50, 4, spriteCommon, XMFLOAT2(0.0f, 0.0f), false, false);
	hP1.SetPosition(XMFLOAT3(50, 0, 0));
	hP1.SetScale(XMFLOAT2(50 * 1, 50 * 1));
	hP1.SetRotation(0.0f);
	hP1.SpriteTransferVertexBuffer(hP1, spriteCommon, 4);
	hP1.SpriteUpdate(hP1, spriteCommon_);

	// �X�v���C�g�p�p�C�v���C�������Ăяo��
	PipelineSet spritePipelineSet = sprite->SpriteCreateGraphicsPipeline(dXCommon->GetDevice());
}

void GameScene::SpriteUpdate()
{
}

void GameScene::TitleDraw(DirectXCommon* dXCommon)
{
	sprite->PreDraw(dXCommon->GetCommandList(), spriteCommon_);

	title.SpriteDraw(dXCommon->GetCommandList(), spriteCommon_, dXCommon->GetDevice(), title.vbView);

	sprite->PostDraw();
}

void GameScene::GameDraw(DirectXCommon* dXCommon)
{
	sprite->PreDraw(dXCommon->GetCommandList(), spriteCommon_);

	hP.SpriteDraw(dXCommon->GetCommandList(), spriteCommon_, dXCommon->GetDevice(), hP.vbView);
	hP1.SpriteDraw(dXCommon->GetCommandList(), spriteCommon_, dXCommon->GetDevice(), hP1.vbView);

	sprite->PostDraw();
}

void GameScene::GameClearDraw(DirectXCommon* dXCommon)
{
	sprite->PreDraw(dXCommon->GetCommandList(), spriteCommon_);

	gameClear.SpriteDraw(dXCommon->GetCommandList(), spriteCommon_, dXCommon->GetDevice(), gameClear.vbView);

	sprite->PostDraw();
}

void GameScene::GameOverDraw(DirectXCommon* dXCommon)
{
	sprite->PreDraw(dXCommon->GetCommandList(), spriteCommon_);

	gameOver.SpriteDraw(dXCommon->GetCommandList(), spriteCommon_, dXCommon->GetDevice(), gameOver.vbView);

	sprite->PostDraw();
}


void GameScene::SpriteFinalize()
{
	// �X�v���C�g���
	delete sprite;
	sprite = nullptr;
}

void GameScene::ParticleInitialize()
{
	for (int i = 0; i < 100; i++) {
		// X,Y,Z���ׂ�[-5.0f,+5.0f]�Ń����_���ɕ��z
		const float md_pos = 10.0f;
		XMFLOAT3 pos{};
		pos.x = (float)rand() / RAND_MAX * md_pos - md_pos / 2.0f;
		pos.y = (float)rand() / RAND_MAX * md_pos - md_pos / 2.0f;
		pos.z = (float)rand() / RAND_MAX * md_pos - md_pos / 2.0f;
		// X,Y,Z�S��[-0.05f,+0.05f]�Ń����_�����z
		const float md_vel = 0.1f;
		XMFLOAT3 vel{};
		vel.x = (float)rand() / RAND_MAX * md_vel - md_vel / 2.0f;
		vel.y = (float)rand() / RAND_MAX * md_vel - md_vel / 2.0f;
		vel.z = (float)rand() / RAND_MAX * md_vel - md_vel / 2.0f;
		// �d�͂Ɍ����Ă�Y�̂�[-0.001f,0]�Ń����_�����z
		XMFLOAT3 acc{};
		const float md_acc = 0.001f;
		acc.y = (float)rand() / RAND_MAX * md_acc;

		// �ǉ�
		particleMan->Add(60, pos, vel, acc, 1.0f, 0.0);
	}
}

void GameScene::ParticleUpdate()
{
	// �J�����ړ�
	if (input->PushKey(DIK_W) || input->PushKey(DIK_S) || input->PushKey(DIK_D) || input->PushKey(DIK_A))
	{
		if (input->PushKey(DIK_W)) { ParticleManager::CameraMoveEyeVector({ 0.0f,+1.0f,0.0f }); }
		else if (input->PushKey(DIK_S)) { ParticleManager::CameraMoveEyeVector({ 0.0f,-1.0f,0.0f }); }
		if (input->PushKey(DIK_D)) { ParticleManager::CameraMoveEyeVector({ +1.0f,0.0f,0.0f }); }
		else if (input->PushKey(DIK_A)) { ParticleManager::CameraMoveEyeVector({ -1.0f,0.0f,0.0f }); }
	}

	particleMan->Update();
}

void GameScene::ParticleDraw(DirectXCommon* dXCommon)
{
	// �R�}���h���X�g�̎擾
	//ID3D12GraphicsCommandList* cmdList = dXCommon->GetCommandList();

	// 3D�I�u�W�F�N�g�`��O����
	ParticleManager::PreDraw(dXCommon->GetCommandList());

	// 3D�I�u�N�W�F�N�g�̕`��
	particleMan->Draw();

	/// <summary>
	/// ������3D�I�u�W�F�N�g�̕`�揈����ǉ��ł���
	/// </summary>

	// 3D�I�u�W�F�N�g�`��㏈��
	ParticleManager::PostDraw();
}

void GameScene::GameReset()
{
	// 3D�I�u�W�F�N�g�̈ʒu���w��
	position[0] = { -20,-5,0 };
	rotation[0] = { 0,90,0 };
	object3d[0]->SetPosition(position[0]);
	object3d[0]->SetScale({ 5, 5, 5 });
	object3d[0]->SetRotation(rotation[0]);
	position[1] = { 0,5,50 };
	object3d[1]->SetPosition(position[1]);
	object3d[1]->SetRotation({ 0, 90, 0 });
	object3d[1]->SetScale({ 5,5,5 });

	playerHp = 3;
	time = 0;
}

int GameScene::CheckCollision(XMFLOAT3 position, XMFLOAT3 scale) {
	//�I�u�W�F�N�g�̍��W
	float objLeftX = position.x - scale.x;
	float objRightX = position.x + scale.x;
	float objTopY = position.y + scale.y;
	float objBottomY = position.y - scale.y;
	float objFrontZ = position.z - scale.z;
	float objBZ = position.z + scale.z;
	//�v���C���[�̍��W
	float playerLeftX = object3d[0]->GetPosition().x - object3d[0]->GetScale().x;
	float playerRightX = object3d[0]->GetPosition().x + object3d[0]->GetScale().x;
	float playerTopY = object3d[0]->GetPosition().y + object3d[0]->GetScale().y;
	float playerBottomY = object3d[0]->GetPosition().y - object3d[0]->GetScale().y;
	float playerFrontZ = object3d[0]->GetPosition().z - object3d[0]->GetScale().z;
	float playerBZ = object3d[0]->GetPosition().z + object3d[0]->GetScale().z;

	if (objLeftX < playerRightX && playerLeftX < objRightX) {
		if (objBottomY < playerTopY && playerBottomY < objTopY) {
			if (objFrontZ < playerBZ && playerFrontZ < objBZ) {
				return true;
			}
		}
	}
}