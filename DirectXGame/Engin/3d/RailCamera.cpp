#include "RailCamera.h"

RailCamera::RailCamera() {
}

RailCamera::~RailCamera() {
	delete viewProjection;
	delete camera;
}

//初期化
void RailCamera::Initialize(Object3d* player_) {
	viewProjection = new ViewProjection;
	input = Input::GetInstance();
	viewProjection->Initialize();
	camera = Object3d::Create();
	viewProjection->eye = { 0, 0, 0 };
	camera->SetPosition(viewProjection->eye);
	camera->SetRotation(viewProjection->target);
	//拡大回転座標変換
	player_->SetScale(Vector3(0.4, 0.4, 0.4));
	player_->SetPosition(Vector3(0, 0, 2.5));
	//変数初期化
	val = 1000.0f;
	feverTime = 0;
	//親子構造のセット
	player_->worldTransform_.SetParent3d(&camera->worldTransform_);
}

//更新
void RailCamera::Update(Object3d* player_, std::vector<Vector3>& point) {
	Vector3 target_ = spline_.Update(point, timeRate,val);
	Vector3 frontTmp = GetFront(viewProjection->eye, target_);
	Vector3 move;
	//一定速度の達したらFever!
	if (val == 600) {
		GoesFever(player_);
	}

	//曲線補完
	move = spline_.Update(point, timeRate,val);
	//親(カメラオブジェクト)の移動
	camera->SetPosition(move + frontTmp * 0.5);
	//カメラ方向に合わせてY軸の回転
	float radY = std::atan2(frontTmp.x, frontTmp.z);
	camera->SetRotationY(radY * 180.0f / 3.1415f);
	//カメラ方向に合わせてX軸の回転
	Vector3 rotaVec = { frontTmp.x,0,frontTmp.z };
	float length = rotaVec.length();
	float radX = std::atan2(-frontTmp.y, length);
	camera->SetRotationX(radX * 180.0f / 3.1415f);

	//更新
	camera->Update();
	viewProjection->target = (move + frontTmp * 0.5);
	viewProjection->eye = ( move - frontTmp );
	viewProjection->UpdateMatrix();
}

void RailCamera::GoesFever(Object3d* player_) {
	if (isFever == false) {
		isFever = true;
	}
	//fever!!
	if (isFever == true) {
		feverTime++;

		player_->SetScale(Vector3(3, 3, 3));

		if (feverTime == 300) {
			val = 1000.0f;
			feverTime = 0;
			player_->SetScale(Vector3(0.4, 0.4, 0.4));
			isFever = false;
		}
	}
}

////////////////////--------クラス内便利関数--------///////////////////////

//方向ベクトルを取得
Vector3 RailCamera::GetFront(Vector3 a, Vector3 b) {
	Vector3 yTmpVec = { 0, 1, 0 };
	Vector3 frontTmp = { 0, 0, 0 };
	Vector3 rightVec = { 0, 0, 0 };
	Vector3 leftVec = { 0, 0, 0 };
	Vector3 frontVec = { 0, 0, 0 };
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
	//正面ベクトル
	frontVec = rightVec.cross(yTmpVec);
	frontVec.normalize();

	return frontVec;
}