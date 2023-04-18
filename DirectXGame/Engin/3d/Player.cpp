#include "Player.h"
#include "SphereCollider.h"

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
	attackModel = Model::LoadFromOBJ("triangle_mat");
	// 3Dオブジェクト生成
	Create();
	// オブジェクトにモデルをひも付ける
	SetModel(playerModel);
	SetRotation(Vector3({ 0, 90, 0 }));
	SetPosition(Vector3(0, 0, -790));
	//変数
	val = 1000.0f;
	feverTime = 0;
	isFever = false;
	//フラグ
	isHit = false;

	return true;
}

void Player::Update()
{
	input = Input::GetInstance();
	//レール前移動
	if (isOnRail == false) {
		if (input->PushKey(DIK_W)) {
			SetPosition(GetPosition() + Vector3(0, 0, 0.2));
		}
		if (input->PushKey(DIK_D)) {
			SetPosition(GetPosition() + Vector3(0.2, 0, 0));
		}
		if (input->PushKey(DIK_A)) {
			SetPosition(GetPosition() + Vector3(-0.2, 0, 0));
		}
		if (input->PushKey(DIK_S)) {
			SetPosition(GetPosition() + Vector3(0, 0, -0.2));
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
	if (isHit == false)
	{
		isHit = true;
	}
}

void Player::OffCollision(const CollisionInfo& info)
{
	if (isHit == true)
	{
		isHit = false;
	}
}

//feverタイム
void Player::GoesFever() {
	//feverでないならfeverに
	if (isFever == false) {
		isFever = true;
	}
	//fever!!
	if (isFever == true) {
		feverTime++;

		if (feverTime % 2 == 0) {
			if (feverNum < 5) {
				feverNum++;
			}
			else {
				feverNum = 0;
			}
		}

		//一定時間したら通常モードへ
		if (feverTime == 300) {
			val = 1000.0f;
			feverTime = 0;
			isFever = false;
		}
	}
}