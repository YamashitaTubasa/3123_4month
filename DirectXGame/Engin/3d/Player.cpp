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
	obj->SetPosition(Vector3(0, 0, -790));
	//変数
	val = 1000.0f;
	feverTime = 0;
	isFever = false;
}

//更新
void Player::Update() {
	//レール前移動
	if (isOnRail == false) {
		if (input_->PushKey(DIK_W)) {
			obj->SetPosition(obj->GetPosition() + Vector3(0, 0, 0.2));
		}
		if (input_->PushKey(DIK_D)) {
			obj->SetPosition(obj->GetPosition() + Vector3(0.2, 0, 0));
		}
		if (input_->PushKey(DIK_A)) {
			obj->SetPosition(obj->GetPosition() + Vector3(-0.2, 0, 0));
		}
		if (input_->PushKey(DIK_S)) {
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