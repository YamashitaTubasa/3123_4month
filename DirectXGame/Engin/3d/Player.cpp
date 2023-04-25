#include "Player.h"
#include "SphereCollider.h"
#include "string.h"

//デストラクタ
Player::~Player() {
	delete playerModel;
}

//初期化
bool Player::PlayerInitialize() {
	if (!Object3d::Initialize())
	{
		return false;
	}

	Initialize();

	// OBJからモデルデータを読み込む
	playerModel = Model::LoadFromOBJ("fighter");
	// 3Dオブジェクト生成
	Create();
	// オブジェクトにモデルをひも付ける
	SetModel(playerModel);
	SetPosition(Vector3(0, 0, -790));

	//フラグ
	isHit = false;
	coolTime = 0;
	isOnRail = false;
	//当たり判定
	isHit = false;

	//hp
	hp = 3;

	return true;
}

void Player::Update()
{
	input = Input::GetInstance();
	//レール前移動
	if (isOnRail == false) {
		if (input->PushKey(DIK_W)) {
			SetRotation(Vector3({ 0, 0, 0 }));
			SetPosition(GetPosition() + Vector3(0, 0, 0.2));
		}
		if (input->PushKey(DIK_D)) {
			SetRotation(Vector3({ 0, 90, 0 }));
			SetPosition(GetPosition() + Vector3(0.2, 0, 0));
		}
		if (input->PushKey(DIK_A)) {
			SetRotation(Vector3({ 0, -90, 0 }));
			SetPosition(GetPosition() + Vector3(-0.2, 0, 0));
		}
		if (input->PushKey(DIK_S)) {
			SetRotation(Vector3({ 0, 180, 0 }));
			SetPosition(GetPosition() + Vector3(0, 0, -0.2));
		}
	}

	if (isHit == true) {
		coolTime++;
		if (coolTime == 50) {
			coolTime = 0;
			isHit = false;
		}
	}

	// ワールドトランスフォームの行列更新と転送
	worldTransform_.UpdateMatrix();

	//当たり判定更新
	if (collider)
	{
		collider->Update();
	}
}

void Player::OnCollision(const CollisionInfo& info)
{
	const char* str = "class Enemy";
	if (strcmp(toCollisionName, str) == 0) {
		if (isHit == false)
		{
			isHit = true;
			hp--;
		}
	}
}

void Player::OffCollision(const CollisionInfo& info)
{

}