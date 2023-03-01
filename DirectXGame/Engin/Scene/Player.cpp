#include "Player.h"

Player::Player()
{
}

Player::~Player()
{
	delete player;
	delete playerModel;
}

void Player::Initialize(WinApp* winApp)
{
	// OBJからモデルデータを読み込む
	playerModel = Model::LoadFromOBJ("fighter");
	// 3Dオブジェクト生成
	player = Object3d::Create();
	// オブジェクトにモデルをひも付ける
	player->SetModel(playerModel);
	player->SetRotation(XMFLOAT3(0, 270, 0));
	player->SetScale(XMFLOAT3(1, 1, 1));

	player->SetEye(XMFLOAT3(0, 5, 10));
}

void Player::Update()
{

	// 入力の更新
	input->Update();
	static char buf[256]{};
	static float f = 0.0f;
	
	//移動
	if (input->PushKey(DIK_W)) {
		Vector3 playerTmp = ConversionVec(player->GetPosition());
		Vector3 eye = ConversionVec(player->GetEye());
		Vector3 target = ConversionVec(player->GetTarget());
		XMFLOAT3 playerFront = ConversionVec(Vector3(playerTmp.x, playerTmp.y, playerTmp.z + (target.z - eye.z)));
		XMFLOAT3 frontTmp = GetFront(player->GetPosition(), playerFront);
		Vector3 frontTmp_ = ConversionVec(frontTmp);
		XMFLOAT3 resultVec = ConversionVec(playerTmp + frontTmp_ * 0.5);
		player->SetPosition(resultVec);
	}
	else if (input->PushKey(DIK_S)) {
		Vector3 playerTmp = ConversionVec(player->GetPosition());
		Vector3 eye = ConversionVec(player->GetEye());
		Vector3 target = ConversionVec(player->GetTarget());
		XMFLOAT3 playerFront = ConversionVec(Vector3(playerTmp.x, playerTmp.y, playerTmp.z + (target.z - eye.z)));
		XMFLOAT3 frontTmp = GetFront(player->GetPosition(), playerFront);
		Vector3 frontTmp_ = ConversionVec(frontTmp);
		Vector3 behindVec = frontTmp_ * -1;
		XMFLOAT3 resultVec = ConversionVec(playerTmp + behindVec * 0.5);
		player->SetPosition(resultVec);
	}
	else if (input->PushKey(DIK_D)) {
		Vector3 playerTmp = ConversionVec(player->GetPosition());
		Vector3 eye = ConversionVec(player->GetEye());
		Vector3 target = ConversionVec(player->GetTarget());
		XMFLOAT3 playerFront = ConversionVec(Vector3(playerTmp.x, playerTmp.y, playerTmp.z + (target.z - eye.z)));
		XMFLOAT3 rightTmp = GetRight(player->GetPosition(), playerFront);
		Vector3  rightTmp_ = ConversionVec(rightTmp);
		XMFLOAT3 resultVec = ConversionVec(playerTmp + rightTmp_ * 0.5);
		player->SetPosition(resultVec);
	}
	else if (input->PushKey(DIK_A)) {
		Vector3 playerTmp = ConversionVec(player->GetPosition());
		Vector3 eye = ConversionVec(player->GetEye());
		Vector3 target = ConversionVec(player->GetTarget());
		XMFLOAT3 playerFront = ConversionVec(Vector3(playerTmp.x, playerTmp.y, playerTmp.z + (target.z - eye.z)));
		XMFLOAT3 leftTmp = GetLeft(player->GetPosition(), playerFront);
		Vector3  leftTmp_ = ConversionVec(leftTmp);
		XMFLOAT3 resultVec = ConversionVec(playerTmp + leftTmp_ * 0.5);
		player->SetPosition(resultVec);
	}


	player->Update();
}

void Player::Draw()
{
		player->Draw();
}

XMFLOAT3 Player::ConversionVec(Vector3 vec) {
	XMFLOAT3 tmp(0, 0, 0);
	tmp.x = vec.x;
	tmp.y = vec.y;
	tmp.z = vec.z;
	return tmp;
}

Vector3 Player::ConversionVec(XMFLOAT3 vec) {
	Vector3 tmp(0, 0, 0);
	tmp.x = vec.x;
	tmp.y = vec.y;
	tmp.z = vec.z;
	return tmp;
}


XMFLOAT3 Player::GetFront(XMFLOAT3 a, XMFLOAT3 b) {
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

XMFLOAT3 Player::GetRight(XMFLOAT3 a, XMFLOAT3 b) {
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

XMFLOAT3 Player::GetLeft(XMFLOAT3 a, XMFLOAT3 b) {
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