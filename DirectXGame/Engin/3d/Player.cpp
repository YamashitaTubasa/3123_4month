#include "Player.h"

//デストラクタ
Player::~Player() {
	delete playerModel;
	delete obj;
}

//初期化
void Player::Initialize() {
	input_ = Input::GetInstance();
	// OBJからモデルデータを読み込む
	playerModel = Model::LoadFromOBJ("fighter");
	// 3Dオブジェクト生成
	obj = Object3d::Create();
	// オブジェクトにモデルをひも付ける
	obj->SetModel(playerModel);
	obj->SetRotation(Vector3({ 0, 90, 0 }));
	obj->SetScale(Vector3(1.5, 1, 1));
	//変数
	val = 1000.0f;
	feverTime = 0;
	isFever = false;
}

//更新
void Player::Update() {
	if (input_->TriggerKey(DIK_D)) {
		obj->SetPosition(obj->GetPosition() + Vector3(1, 0, 0));
	}
	if (input_->TriggerKey(DIK_A)) {
		obj->SetPosition(obj->GetPosition() + Vector3(-1, 0, 0));
	}
	//feverTaime
	if (val == 600) {
		GoesFever();
	}
	//更新
	obj->Update();
}

//描画
void Player::Draw(ViewProjection* viewProjection) {
	obj->Draw(viewProjection);
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

		obj->SetScale(Vector3(3, 3, 3));
		//一定時間したら通常モードへ
		if (feverTime == 300) {
			val = 1000.0f;
			feverTime = 0;
			obj->SetScale(Vector3(0.4, 0.4, 0.4));
			isFever = false;
		}
	}
}

////////////////////////////////////////////////////////////////////////

//方向ベクトルを取得
void Player::GetVec(Vector3 a, Vector3 b) {
	Vector3 yTmpVec = { 0, 1, 0 };
	Vector3 frontTmp = { 0, 0, 0 };
	Vector3 a_ = { a.x,a.y,a.z };
	Vector3 b_ = { b.x,b.y,b.z };

	//Y軸仮ベクトル
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
	//正面ベクトル(Y座標を0にした)
	frontVec = rightVec.cross(yTmpVec);
	frontVec.normalize();
}