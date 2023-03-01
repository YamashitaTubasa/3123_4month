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
	// 3Dオブジェクト生成
	particleMan = ParticleManager::Create();
	particleMan->Update();

	// 入力の初期化
	input = new Input();
	input->Initialize(winApp);

	// ImGuiの初期化
	imGuiManager = new ImGuiManager();
	imGuiManager->Initialize(dXCommon, winApp);

	// オブジェクトの初期化
	/*ObjectInitialize();*/

	// OBJからモデルデータを読み込む
	skyModel = Model::LoadFromOBJ("skydome");
	// 3Dオブジェクト生成
	sky = Object3d::Create();
	// オブジェクトにモデルをひも付ける
	sky->SetModel(skyModel);
	sky->SetScale(XMFLOAT3(80, 80, 80));

	// OBJからモデルデータを読み込む
	playerModel = Model::LoadFromOBJ("fighter");
	// 3Dオブジェクト生成
	player = Object3d::Create();
	// オブジェクトにモデルをひも付ける
	player->SetModel(playerModel);
	player->SetRotation(XMFLOAT3(0, 270, 0));
	player->SetScale(XMFLOAT3(1, 1, 1));
	playerRote = { player->GetPositionX(),player->GetPositionY(),player->GetPositionZ(),1 };

	tester = Object3d::Create();
	// オブジェクトにモデルをひも付ける
	tester->SetModel(playerModel);
	tester->SetPosition(XMFLOAT3(-1, 0, -12));
	tester->SetRotation(XMFLOAT3(0, 270, 0));
	tester->SetScale(XMFLOAT3(2, 2, 2));

	player->SetEye(XMFLOAT3(0, 5, 10));

	// スプライトの初期化
	SpriteInitialize(dXCommon, spriteCommon);
	// パーティクルの初期化
	ParticleInitialize();
}

void GameScene::Update()
{
	// ImGui受付開始
	imGuiManager->Begin();

	// 入力の更新
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
		/*time++;
		if (time >= 1000) {
			scene = GameClear;
		}*/
		ImGui::Text("Hello%d", 123);
		if (ImGui::Button("Save")) {
			imGuiManager->MySaveFunction();

			ImGui::InputText("string", buf, IM_ARRAYSIZE(buf));
			ImGui::SliderFloat("float", &f, 0.0f, 1.0f);
		}
		// オブジェクトの更新
		ObjectUpdate();
		/*pl->Update();*/
		// スプライトの更新
		SpriteUpdate();
		// パーティクルの更新
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

	// ImGui受付終了
	imGuiManager->End();
}

void GameScene::Draw(DirectXCommon* dXCommon)
{
	// 描画前処理
	dXCommon->PreDraw();
	// 3Dオブジェクト描画前処理
	Object3d::PreDraw(dXCommon->GetCommandList());

	switch (scene) {
	case Title:
		// タイトルの描画
		//TitleDraw(dXCommon);
		break;
	case Scene_1:
		/*pl->Draw();*/
		sky->Draw();
		player-> Draw();
		tester->Draw();
		// パーティクルの描画
		//ParticleDraw(dXCommon);
		// HP描画
		//GameDraw(dXCommon);
		break;
	case GameClear:
		// ゲームクリアの描画
		//GameClearDraw(dXCommon);
		break;
	case GameOver:
		//ゲームオーバーの描画
		//GameOverDraw(dXCommon);
		break;
	}

	// ImGui描画
	imGuiManager->Draw(dXCommon);

	// 3Dオブジェクト描画後処理
	Object3d::PostDraw();
	// 描画後処理
	dXCommon->PostDraw();
}

void GameScene::Finalize()
{

	// 入力開放
	delete input;
	input = nullptr;

	// imguiの終了処理
	imGuiManager->Finalize();
	// imguiの解放
	delete imGuiManager;
	imGuiManager = nullptr;

	// オブジェクトの解放
	ObjectFinalize();

	// スプライトの解放
	SpriteFinalize();
}

void GameScene::ObjectInitialize()
{
	
}

void GameScene::ObjectUpdate()
{

	////移動
	//if (input->PushKey(DIK_W)) {
	//	Vector3 playerTmp = ConversionVec(player->GetPosition());
	//	Vector3 eye = ConversionVec(player->GetEye());
	//	Vector3 target = ConversionVec(player->GetTarget());
	//	XMFLOAT3 playerFront = ConversionVec(Vector3(playerTmp.x, playerTmp.y, playerTmp.z + (target.z - eye.z)));
	//	XMFLOAT3 frontTmp = GetFront(player->GetPosition(), playerFront);
	//	Vector3 frontTmp_ = ConversionVec(frontTmp);
	//	XMFLOAT3 resultVec = ConversionVec(playerTmp + frontTmp_ * 0.5);
	//	player->SetPosition(resultVec);
	//}
	//if (input->PushKey(DIK_S)) {
	//	Vector3 playerTmp = ConversionVec(player->GetPosition());
	//	Vector3 eye = ConversionVec(player->GetEye());
	//	Vector3 target = ConversionVec(player->GetTarget());
	//	XMFLOAT3 playerFront = ConversionVec(Vector3(playerTmp.x, playerTmp.y, playerTmp.z + (target.z - eye.z)));
	//	XMFLOAT3 frontTmp = GetFront(player->GetPosition(), playerFront);
	//	Vector3 frontTmp_ = ConversionVec(frontTmp);
	//	Vector3 behindVec = frontTmp_ * -1;
	//	XMFLOAT3 resultVec = ConversionVec(playerTmp + behindVec * 0.5);
	//	player->SetPosition(resultVec);
	//}
	//if (input->PushKey(DIK_D)) {
	//	Vector3 playerTmp = ConversionVec(player->GetPosition());
	//	Vector3 eye = ConversionVec(player->GetEye());
	//	Vector3 target = ConversionVec(player->GetTarget());
	//	XMFLOAT3 playerFront = ConversionVec(Vector3(playerTmp.x, playerTmp.y, playerTmp.z + (target.z - eye.z)));
	//	XMFLOAT3 rightTmp = GetRight(player->GetPosition(), playerFront);
	//	Vector3  rightTmp_ = ConversionVec(rightTmp);
	//	XMFLOAT3 resultVec = ConversionVec(playerTmp + rightTmp_ * 0.5);
	//	player->SetPosition(resultVec);
	//}
	//if (input->PushKey(DIK_A)) {
	//	Vector3 playerTmp = ConversionVec(player->GetPosition());
	//	Vector3 eye = ConversionVec(player->GetEye());
	//	Vector3 target = ConversionVec(player->GetTarget());
	//	XMFLOAT3 playerFront = ConversionVec(Vector3(playerTmp.x, playerTmp.y, playerTmp.z + (target.z - eye.z)));
	//	XMFLOAT3 leftTmp = GetLeft(player->GetPosition(), playerFront);
	//	Vector3  leftTmp_ = ConversionVec(leftTmp);
	//	XMFLOAT3 resultVec = ConversionVec(playerTmp + leftTmp_ * 0.5);
	//	player->SetPosition(resultVec);
	//}

	Vector3 playerTmp = ConversionVec(player->GetPosition());
	Vector3 eye = ConversionVec(player->GetEye());
	Vector3 target = ConversionVec(player->GetTarget());
	playerRote = { player->GetPositionX(),player->GetPositionY(),player->GetPositionZ(),1 };


	Vector3 dist = eye - playerTmp;
	dist.normalize();
	if (dist.z < 0.8) {

	}

	if (input->PushKey(DIK_A)) {
		player->SetTarget(XMFLOAT3(ConversionVec(Vector3(target.x,target.y * atan(180 * PI / 2), target.z))));
		playerTmp.x += 0.7;
	}
	if (input->PushKey(DIK_D)) {
		player->SetTarget(XMFLOAT3(ConversionVec(Vector3(target.x , target.y * -atan(180 * PI / 2), target.z))));
		playerTmp.x -= 0.7;
	}

	target = ConversionVec(player->GetTarget());
	

	XMFLOAT3 cameraFronttmp = GetFront(ConversionVec(eye),ConversionVec(Vector3(target.x,eye.y,target.z)));
	Vector3 cameraFronttmp_ = ConversionVec(cameraFronttmp);

	player->SetTarget(ConversionVec(target + cameraFronttmp_ * 0.2));
	player->SetEye(ConversionVec(eye + cameraFronttmp_ * 0.2));
	player->SetPosition(ConversionVec((playerTmp * sinf(PI / 2)) + cameraFronttmp_ * 0.2));

	sky->Update();
	player->Update();
	tester->Update();
}

void GameScene::ObjectDraw(DirectXCommon* dXCommon)
{
	player->Draw();
}

void GameScene::ObjectFinalize()
{
	delete player;
	delete playerModel;
}

void GameScene::SpriteInitialize(DirectXCommon* dXCommon, SpriteCommon& spriteCommon)
{
	// スプライト
	sprite = new Sprite();
	spriteCommon_ = sprite->SpriteCommonCreate(dXCommon->GetDevice(), 1280, 720);

	// タイトルの設定
	title.LoadTexture(spriteCommon_, 0, L"Resources/gametitle.png", dXCommon->GetDevice());
	title.SetColor(XMFLOAT4(1, 1, 1, 1));
	title.SpriteCreate(dXCommon->GetDevice(), 1280, 720, 0, spriteCommon, XMFLOAT2(0.0f, 0.0f), false, false);
	title.SetPosition(XMFLOAT3(0, 0, 0));
	title.SetScale(XMFLOAT2(1280 * 1, 720 * 1));
	title.SetRotation(0.0f);
	title.SpriteTransferVertexBuffer(title, spriteCommon, 0);
	title.SpriteUpdate(title, spriteCommon_);

	// ゲームクリアの設定
	gameClear.LoadTexture(spriteCommon_, 1, L"Resources/gameclear.png", dXCommon->GetDevice());
	gameClear.SpriteCreate(dXCommon->GetDevice(), 1280, 720, 1, spriteCommon, XMFLOAT2(0.0f, 0.0f), false, false);
	gameClear.SetPosition(XMFLOAT3(0, 0, 0));
	gameClear.SetScale(XMFLOAT2(1280 * 1, 720 * 1));
	gameClear.SpriteTransferVertexBuffer(gameClear, spriteCommon, 1);
	gameClear.SpriteUpdate(gameClear, spriteCommon_);

	// ゲームオーバーの設定
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

	// スプライト用パイプライン生成呼び出し
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
	// スプライト解放
	delete sprite;
	sprite = nullptr;
}

void GameScene::ParticleInitialize()
{
	for (int i = 0; i < 100; i++) {
		// X,Y,Zすべて[-5.0f,+5.0f]でランダムに分布
		const float md_pos = 10.0f;
		XMFLOAT3 pos{};
		pos.x = (float)rand() / RAND_MAX * md_pos - md_pos / 2.0f;
		pos.y = (float)rand() / RAND_MAX * md_pos - md_pos / 2.0f;
		pos.z = (float)rand() / RAND_MAX * md_pos - md_pos / 2.0f;
		// X,Y,Z全て[-0.05f,+0.05f]でランダム分布
		const float md_vel = 0.1f;
		XMFLOAT3 vel{};
		vel.x = (float)rand() / RAND_MAX * md_vel - md_vel / 2.0f;
		vel.y = (float)rand() / RAND_MAX * md_vel - md_vel / 2.0f;
		vel.z = (float)rand() / RAND_MAX * md_vel - md_vel / 2.0f;
		// 重力に見立ててYのみ[-0.001f,0]でランダム分布
		XMFLOAT3 acc{};
		const float md_acc = 0.001f;
		acc.y = (float)rand() / RAND_MAX * md_acc;

		// 追加
		particleMan->Add(60, pos, vel, acc, 1.0f, 0.0);
	}
}

void GameScene::ParticleUpdate()
{
	// カメラ移動
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
	// コマンドリストの取得
	//ID3D12GraphicsCommandList* cmdList = dXCommon->GetCommandList();

	// 3Dオブジェクト描画前処理
	ParticleManager::PreDraw(dXCommon->GetCommandList());

	// 3Dオブクジェクトの描画
	particleMan->Draw();

	/// <summary>
	/// ここに3Dオブジェクトの描画処理を追加できる
	/// </summary>

	// 3Dオブジェクト描画後処理
	ParticleManager::PostDraw();
}

void GameScene::GameReset()
{
	time = 0;
}

int GameScene::CheckCollision(XMFLOAT3 position, XMFLOAT3 scale) {
	///*オブジェクトの座標
	//float objLeftX = position.x - scale.x;
	//float objRightX = position.x + scale.x;
	//float objTopY = position.y + scale.y;
	//float objBottomY = position.y - scale.y;
	//float objFrontZ = position.z - scale.z;
	//float objBZ = position.z + scale.z;
	//プレイヤーの座標
	//float playerLeftX = object3d[0]->GetPosition().x - object3d[0]->GetScale().x;
	//float playerRightX = object3d[0]->GetPosition().x + object3d[0]->GetScale().x;
	//float playerTopY = object3d[0]->GetPosition().y + object3d[0]->GetScale().y;
	//float playerBottomY = object3d[0]->GetPosition().y - object3d[0]->GetScale().y;
	//float playerFrontZ = object3d[0]->GetPosition().z - object3d[0]->GetScale().z;
	//float playerBZ = object3d[0]->GetPosition().z + object3d[0]->GetScale().z;

	//if (objLeftX < playerRightX && playerLeftX < objRightX) {
	//	if (objBottomY < playerTopY && playerBottomY < objTopY) {
	//		if (objFrontZ < playerBZ && playerFrontZ < objBZ) {
	//			return true;
	//		}
	//	}
	//}*/
	return true;
}

XMFLOAT3 GameScene::ConversionVec(Vector3 vec) {
	XMFLOAT3 tmp(0, 0, 0);
	tmp.x = vec.x;
	tmp.y = vec.y;
	tmp.z = vec.z;
	return tmp;
}

Vector3 GameScene::ConversionVec(XMFLOAT3 vec) {
	Vector3 tmp(0, 0, 0);
	tmp.x = vec.x;
	tmp.y = vec.y;
	tmp.z = vec.z;
	return tmp;
}


XMFLOAT3 GameScene::GetFront(XMFLOAT3 a, XMFLOAT3 b) {
	Vector3 yTmpVec = { 0, 1, 0 };
	Vector3 frontTmp = { 0, 0, 0 };
	Vector3 rightVec = { 0, 0, 0 };
	Vector3 leftVec = { 0, 0, 0 };
	Vector3 frontVec = { 0, 0, 0 };
	Vector3 a_ = { a.x,a.y,a.z };
	Vector3 b_ = { b.x,b.y,b.z };

	yTmpVec.normalize();
	//正面仮ベクトル
	frontTmp = b_ - a_;
	frontTmp.normalize();
	//右ベクトル
	rightVec = yTmpVec.cross(frontTmp);
	rightVec.normalize();
	//左ベクトル
	leftVec = frontTmp.cross(yTmpVec);
	leftVec.normalize();
	//正面ベクトル
	frontVec = rightVec.cross(yTmpVec);
	frontVec.normalize();
	
	return ConversionVec(frontVec);
}

XMFLOAT3 GameScene::GetRight(XMFLOAT3 a, XMFLOAT3 b) {
	Vector3 yTmpVec = { 0, 1, 0 };
	Vector3 frontTmp = { 0, 0, 0 };
	Vector3 rightVec = { 0, 0, 0 };
	Vector3 a_ = { a.x,a.y,a.z };
	Vector3 b_ = { b.x,b.y,b.z };

	yTmpVec.normalize();
	//正面仮ベクトル
	frontTmp = b_ - a_;
	frontTmp.normalize();
	//右ベクトル
	rightVec = yTmpVec.cross(frontTmp);
	rightVec.normalize();

	return ConversionVec(rightVec);
}

XMFLOAT3 GameScene::GetLeft(XMFLOAT3 a, XMFLOAT3 b) {
	Vector3 yTmpVec = { 0, 1, 0 };
	Vector3 frontTmp = { 0, 0, 0 };
	Vector3 leftVec = { 0, 0, 0 };
	Vector3 a_ = { a.x,a.y,a.z };
	Vector3 b_ = { b.x,b.y,b.z };

	yTmpVec.normalize();
	//正面仮ベクトル
	frontTmp = b_ - a_;
	frontTmp.normalize();
	//左ベクトル
	leftVec = frontTmp.cross(yTmpVec);
	leftVec.normalize();

	return ConversionVec(leftVec);
}