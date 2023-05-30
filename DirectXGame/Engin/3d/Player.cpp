#include "Player.h"
#include "SphereCollider.h"
#include "string.h"
#include "GamePlayScene.h"

//デストラクタ
Player::~Player() {
	delete playerModel;
}

//初期化
bool Player::PlayerInitialize() {
	if (!Object3d::Initialize()) {
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
	isAttack = false;
	//変数
	attackTime = 0;
	val = 0.0f;
	len = 6.0f;
	feverTime = 0;
	isFever = false;
	isPush = false;
	pushTime = 0;
	feverNum = 0;
	attackNum = 0;
	speedUpCount = 3;
	res = 0.0f;
	isBurst = false;
	isGauge_ = false;

	moveE = 0.822f;
	moveS = 0.0f;
	moveTime = 0.0f;
	isMove = 0;

	//hp
	hp = 3;

	//自機の位置
	railPos = MIDDLE;

	attackS = 0.0;
	attackE = 360.0;

	return true;
}

void Player::Update(std::vector <Vector3>& point)
{
	input = Input::GetInstance();

	if (GamePlayScene::GetScene() == 2)
	{
		//攻撃も移動もしてない時
		if (isPush == false && isMove == false)
		{
			//SPACEキーを押したら
			if (input->TriggerKey(DIK_SPACE))
			{
				//攻撃する
				isPush = true;
				isAttack = true;
			}
			if (isAttack == false)
			{
				//左以外の時に左キーを押したら
				if (input->TriggerKey(DIK_A) || input->TriggerKey(DIK_LEFT))
				{
					if (isMove == 0 && railPos != LEFT)
					{
						isMove = 1;
					}
				}
				//右以外の時に右キーを押したら
				if (input->TriggerKey(DIK_D) || input->TriggerKey(DIK_RIGHT))
				{
					if (isMove == 0 && railPos != RIGHT)
					{
						isMove = 2;
					}
				}
			}
		}
		Move(point);
		//攻撃中なら更新する
		if (isPush == true) {

			// ワールドトランスフォームの行列更新と転送
			worldTransform_.UpdateMatrix();

			if (isFever == false)
			{
				pushTime++;
				if (pushTime == 20)
				{
					pushTime = 0;
					isPush = false;

				}
			}
		}
		if (isAttack == true)
		{
			attackTime++;
			worldTransform_.rotation_.z = attackS + (attackE - attackS) * -MathFunc::easeOutSine(attackTime / 30);
			if (attackNum <= 6)
			{
				attackNum++;
			}
			if (attackTime == 30)
			{
				attackTime = 0;
				attackNum = 0;
				worldTransform_.rotation_.z = 0;
				isAttack = false;
			}
		}

		//カメラ距離演出
		if (len > 6) {
			len -= 0.125f;
		}

		if (isHit == true)
		{
			coolTime++;
			if (coolTime == 50)
			{
				coolTime = 0;
				isHit = false;
			}
		}
	}
	//チュートリアル
	if (GamePlayScene::GetScene() == 6)
	{
		//攻撃も移動もしてない時
		if (isPush == false && isMove == false)
		{
			//SPACEキーを押したら
			if (input->TriggerKey(DIK_SPACE) && GamePlayScene::GetTutorialStep() > 1)
			{
				//攻撃する
				isPush = true;
				isAttack = true;
			}
			if (isAttack == false && GamePlayScene::GetTutorialStep() > 3)
			{
				//左以外の時に左キーを押したら
				if (input->TriggerKey(DIK_A) || input->TriggerKey(DIK_LEFT))
				{
					if (isMove == 0 && railPos != LEFT)
					{
						isMove = 1;
					}
				}
				//右以外の時に右キーを押したら
				if (input->TriggerKey(DIK_D) || input->TriggerKey(DIK_RIGHT))
				{
					if (isMove == 0 && railPos != RIGHT)
					{
						isMove = 2;
					}
				}
			}
		}
		Move(point);
		//攻撃中なら更新する
		if (isPush == true) {

			// ワールドトランスフォームの行列更新と転送
			worldTransform_.UpdateMatrix();

			if (isFever == false)
			{
				pushTime++;
				if (pushTime == 20)
				{
					pushTime = 0;
					isPush = false;

				}
			}
		}
		if (isAttack == true)
		{
			attackTime++;
			worldTransform_.rotation_.z = attackS + (attackE - attackS) * -MathFunc::easeOutSine(attackTime / 30);
			if (attackNum <= 6)
			{
				attackNum++;
			}
			if (attackTime == 30)
			{
				attackTime = 0;
				attackNum = 0;
				worldTransform_.rotation_.z = 0;
				isAttack = false;
			}
		}

		//カメラ距離演出
		if (len > 6) {
			len -= 0.125f;
		}

		if (isHit == true)
		{
			coolTime++;
			if (coolTime == 50)
			{
				coolTime = 0;
				isHit = false;
			}
		}
	}

	if (val >= 0.0061)
	{
		GoesFever();
	}

	// ワールドトランスフォームの行列更新と転送
	worldTransform_.UpdateMatrix();

	//当たり判定更新
	if (collider)
	{
		collider->Update();
	}
}

void Player::Move(std::vector <Vector3>& point)
{
	if (isMove == 1)
	{
		//左隣のレールに移動する
		for (float i = 0; i < point.size(); i++)
		{
			point[i].x -= moveS + (moveE - moveS) * MathFunc::easeOutSine(moveTime / 20);
		}
		if (moveTime <= 10)
		{
			worldTransform_.rotation_.z += 3 * MathFunc::easeOutSine(moveTime / 10);
		}
		else
		{
			worldTransform_.rotation_.z -= 3 * MathFunc::easeOutSine(moveTime / 20);
		}
		moveTime++;
		//フラグ切り替え
		if (moveTime == 20)
		{
			worldTransform_.rotation_.z = 0;
			isMove = 0;
			moveTime = 0;
			//場所のenum切り替え
			if (railPos == MIDDLE)
			{
				railPos = LEFT;
			}
			else if (railPos == RIGHT)
			{
				railPos = MIDDLE;
			}
		}
	}

	if (isMove == 2)
	{
		//右隣のレールに移動する
		for (float i = 0; i < point.size(); i++)
		{
			point[i].x += moveS + (moveE - moveS) * MathFunc::easeOutSine(moveTime / 20);
		}
		if (moveTime <= 10)
		{
			worldTransform_.rotation_.z -= 3 * MathFunc::easeOutSine(moveTime / 10);
		}
		else
		{
			worldTransform_.rotation_.z += 3 * MathFunc::easeOutSine(moveTime / 20);
		}
		moveTime++;
		//フラグ切り替え
		if (moveTime == 20)
		{
			worldTransform_.rotation_.z = 0;
			isMove = 0;
			moveTime = 0;
			//場所のenum切り替え
			if (railPos == MIDDLE)
			{
				railPos = RIGHT;
			}
			else if (railPos == LEFT)
			{
				railPos = MIDDLE;
			}
		}
	}
}

//feverタイム
void Player::GoesFever()
{
	//feverでないならfeverに
	if (isFever == false) {
		isFever = true;
		isPush = true;
	}
	//fever!!
	if (isFever == true) {
		feverTime++;

		worldTransform_.rotation_.z -= 36;
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
			EndFever();
		}
	}
}

void Player::OnCollision(const CollisionInfo& info) {
	const char* str = "class Enemy";
	const char* str2 = "class InvisibleEnemy";
	if (strcmp(toCollisionName, str) == 0) {
		if (isPush == true) {
			if (isFever == false) {
				if (isGauge_ == false) {
					isGauge_ = true;
				}
				val += 0.002f;
				len = 15;
			}
			isBurst = true;
		}
		else {
			if (isHit == false) {
				hp--;
				GamePlayScene::SetIsBack(true);
				isHit = true;
			}
		}
	}
	if (strcmp(toCollisionName, str2) == 0) {
		if (isHit == false) {
			if (isFever == false) {
				hp--;
				isHit = true;
				GamePlayScene::SetIsBack(true);
			}
		}
	}
}

void Player::OffCollision(const CollisionInfo& info) {

}

void Player::EndFever() {
	val = 0.0f;
	worldTransform_.rotation_.z = 0;
	feverTime = 0;
	isFever = false;
}