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
	//変数
	val = 2000.0f;
	feverTime = 0;
	isFever = false;
	isPush = false;
	pushTime = 0;
	feverNum = 0;
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

	if (input->TriggerKey(DIK_SPACE)) {
		if (isPush == false) {
			isPush = true;
		}
	}

	if (val <= 500) {
		GoesFever();
	}

	//攻撃中なら更新する
	if (isPush == true) {

		// ワールドトランスフォームの行列更新と転送
		worldTransform_.UpdateMatrix();

		if (isFever == false) {
			pushTime++;
			worldTransform_.rotation_.z -= 18;
			if (pushTime == 20) {
				pushTime = 0;
				worldTransform_.rotation_.z = 0;
				if (isHit == true)
				{
					isHit = false;
				}
				isPush = false;
				
			}
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

//feverタイム
void Player::GoesFever() {
	//feverでないならfeverに
	if (isFever == false) {
		isFever = true;
		isPush = true;
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
		if (feverTime == 250) {
			val = 2000.0f;
			feverTime = 0;
			isFever = false;
		}
	}
}

void Player::OnCollision(const CollisionInfo& info)
{
	const char* str = "class Enemy";
	if (strcmp(toCollisionName, str) == 0) {
		if (isHit == false)
		{
			if (isGauge_ == false) {
				isGauge_ = true;
			}
			if (isPush == true)
			{
				if (isFever == false) {
					val -= 500.0f;
				}
				isBurst = true;
			}
			else
			{
				hp--;
			}
			isHit = true;
		}
	}
}

void Player::OffCollision(const CollisionInfo& info)
{

}