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
	isMove = false;
	isHit = false;
	coolTime = 0;
	isOnRail = false;
	isAttack = false;
	//変数
	attackTime = 0;
	val = 2000.0f;
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

	moveE = 12.0f;
	moveS = 0.0f;

	//hp
	hp = 3;

	//自機の位置
	railPos = MIDDLE;

	start = 0.0;
	end = 360.0;

	return true;
}

void Player::Update(std::vector <Vector3>& point)
{
	input = Input::GetInstance();

	if (GamePlayScene::GetScene() == 1)
	{
		//攻撃も移動もしてない時
		if (isPush == false /*&& isMove == false*/)
		{
			//SPACEキーを押したら
			if (input->TriggerKey(DIK_SPACE))
			{
				//攻撃する
				isPush = true;
				isAttack = true;
			}
			//左以外の時に左キーを押したら
			if (input->TriggerKey(DIK_A) || input->TriggerKey(DIK_LEFT))
			{
				if (railPos != LEFT)
				{
					//左隣のレールに移動する
					for (float i = 0; i < point.size(); i++)
					{
						point[i].x -= 10;
						/*point[i].x = moveS + (moveE - moveS) * -MathFunc::easeOutSine(i / 12);*/
					}
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
			//右以外の時に右キーを押したら
			if (input->TriggerKey(DIK_D) || input->TriggerKey(DIK_RIGHT))
			{
				if (railPos != RIGHT)
				{
					//右隣のレールに移動する
					for (float i = 0; i < point.size(); i++)
					{
						point[i].x += 10;
						/*point[i].x = moveS + (moveE - moveS) * MathFunc::easeOutSine(i / 12);*/
					}
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
					if (isHit == true)
					{
						isHit = false;
					}
					isPush = false;

				}
			}
		}
		if (isAttack == true)
		{
			attackTime++;
			worldTransform_.rotation_.z = start + (end - start) * -MathFunc::easeOutSine(attackTime / 30);
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

	if (val <= 500)
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
			val = 2000.0f;
			worldTransform_.rotation_.z = 0;
			feverTime = 0;
			isFever = false;
		}
	}
}

void Player::OnCollision(const CollisionInfo& info) {
	const char* str = "class Enemy";
	if (strcmp(toCollisionName, str) == 0) {
		if (isHit == false) {
			if (isPush == true) {
				if (isFever == false) {
					if (isGauge_ == false) {
						isGauge_ = true;
					}
					res = val / speedUpCount;
					val -= res;
				}
				isBurst = true;
			}
			else {
				hp--;
			}
			isHit = true;
		}
	}
}

void Player::OffCollision(const CollisionInfo& info) {

}