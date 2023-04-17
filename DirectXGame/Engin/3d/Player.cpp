#include "Player.h"
#include "SphereCollider.h"

//デストラクタ
Player::~Player() {
	delete playerModel;
	delete obj;
}

//初期化
bool Player::Initialize() {
	if (!Object3d::Initialize())
	{
		return false;
	}
	//コライダーの追加
	float radius = 0.6f;
	//半径分だけ足元から浮いた座標を球の中心にする
	SetCollider(new SphereCollider(Vector3({ 0,radius,0 }), radius));

	// OBJからモデルデータを読み込む
	playerModel = Model::LoadFromOBJ("fighter");
	attackModel = Model::LoadFromOBJ("triangle_mat");
	// 3Dオブジェクト生成
	obj = Object3d::Create();
	// オブジェクトにモデルをひも付ける
	obj->SetModel(playerModel);
	obj->SetRotation(Vector3({ 0, 90, 0 }));
	obj->SetPosition(Vector3(0, 0, -790));
	// 3Dオブジェクト生成
	attack = Object3d::Create();
	// オブジェクトにモデルをひも付ける
	attack->SetModel(attackModel);
	attack->SetRotation(Vector3({ 0, 90, 0 }));
	attack->SetPosition(Vector3(0, 0, -780));
	//変数
	val = 1000.0f;
	feverTime = 0;
	isFever = false;
	//フラグ
	isHit = false;

	return true;
}

//更新
void Player::Update() {
	input = Input::GetInstance();
	//レール前移動
	if (isOnRail == false) {
		if (input->PushKey(DIK_W)) {
			obj->SetPosition(obj->GetPosition() + Vector3(0, 0, 0.2));
		}
		if (input->PushKey(DIK_D)) {
			obj->SetPosition(obj->GetPosition() + Vector3(0.2, 0, 0));
		}
		if (input->PushKey(DIK_A)) {
			obj->SetPosition(obj->GetPosition() + Vector3(-0.2, 0, 0));
		}
		if (input->PushKey(DIK_S)) {
			obj->SetPosition(obj->GetPosition() + Vector3(0, 0, -0.2));
		}
	}
	//レール後処理
	if (isOnRail == true) {
		//feverTaime
		if (val == 600) {
			GoesFever();
		}
	}
	//更新
	obj->Update();
	attack->Update();
}

void Player::OnCollision(const CollisionInfo& info)
{
	if (isHit == false)
	{
		isHit = true;
	}
}

//描画
void Player::Draw(ViewProjection* viewProjection) {
	obj->Draw(viewProjection);
	/*attack->Draw(viewProjection);*/
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