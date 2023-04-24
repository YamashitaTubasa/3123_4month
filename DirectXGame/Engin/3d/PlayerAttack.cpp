#include "PlayerAttack.h"
#include "SphereCollider.h"
#include "string.h"

PlayerAttack::~PlayerAttack() {
	delete attackModel;
}

bool PlayerAttack::AttackInitialize(Player* player_) {
	if (!Object3d::Initialize())
	{
		return false;
	}

	Initialize();

	// OBJからモデルデータを読み込む
	attackModel = Model::LoadFromOBJ("triangle_mat");
	attackModel->LoadTexture("Resources/red.png");
	// 3Dオブジェクト生成
	Create();
	// オブジェクトにモデルをひも付ける
	SetModel(attackModel);
	//変数
	val = 1000.0f;
	feverTime = 0;
	isFever = false;
	isPush = false;
	pushTime = 0;
	isHit = false;
	coolTime = 0;
	feverNum = 0;
	isOnRail = false;
	//playerの子供にする
	worldTransform_.SetParent3d(&player_->worldTransform_);
	SetRotation(Vector3(0, -90, 0));
	/*SetPosition(Vector3(-3, 1, 0));*/
	SetScale(Vector3(2, 2, 2));
	return true;
}

void PlayerAttack::Update() {
	input = Input::GetInstance();

	if (input->TriggerKey(DIK_SPACE)) {
		if (isPush == false) {
			isPush = true;
		}
	}

	//攻撃が当たった時の処理
	if (isHit == true) {
		coolTime++;
		if (coolTime == 10) {
			coolTime = 0;
			isHit = false;
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
			if (pushTime == 20) {
				pushTime = 0;
				isPush = false;
			}
		}
	}
	//当たり判定更新
	if (collider)
	{
		collider->Update();
	}
}

//feverタイム
void PlayerAttack::GoesFever() {
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
			val = 1000.0f;
			feverTime = 0;
			isFever = false;
			SetScale(Vector3(2, 2, 2));
		}
	}
}

void PlayerAttack::OnCollision(const CollisionInfo& info)
{
	const char* str = "class Player";
	if (strcmp(toCollisionName, str) != 0) {
		if (isHit == false) {
			isHit = true;
			if (isFever == false) {
				val -= 500.0f;
			}
			if (isHit == true) {
				isDead = true;
			}
		}
	}
}

void PlayerAttack::OffCollision(const CollisionInfo& info)
{

}