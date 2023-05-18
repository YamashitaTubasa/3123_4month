#include "RailCamera.h"

RailCamera::RailCamera() {
}

RailCamera::~RailCamera() {
	delete viewProjection;
	delete camera;
}

//初期化
void RailCamera::Initialize() {
	viewProjection = new ViewProjection;
	input = Input::GetInstance();
	viewProjection->Initialize();
	camera = Object3d::Create();
	viewProjection->eye = { 0, 5, -800 };
	viewProjection->target = { 0,-5,-750 };
	camera->SetPosition(viewProjection->eye);
	camera->SetRotation(Vector3(0, 0, 0));
	isEnd = false;
}

void RailCamera::ViewUpdate() {
	viewProjection->UpdateMatrix();
}

//更新
void RailCamera::Update(Player* player_, std::vector<Vector3>& point) {


	Vector3 target_ = spline_.Update(point, 0.00001 + player_->GetVal());
	camera->SetPosition(splineCam.Update(point, player_->GetVal()));
	//方向ベクトルの取得
	GetVec(camera->GetPosition(), target_);

	//カメラ方向に合わせてY軸の回転
	float radY = std::atan2(frontVec.x, frontVec.z);
	camera->SetRotationY(radY * 180.0f / 3.1415f);
	//カメラ方向に合わせてX軸の回転
	Vector3 rotaVec = { frontVec.x,0,frontVec.z };
	float length = rotaVec.length();
	float radX = std::atan2(-frontVec.y, length);
	camera->SetRotationX(radX * 180.0f / 3.1415f);
	//更新
	camera->Update();
	viewProjection->target = (target_ + frontVec * 5);
	viewProjection->eye = (camera->GetPosition() - frontVec * player_->GetLen());
	viewProjection->eye.y = (camera->GetPosition().y + 1);

	if (spline_.GetIsEnd() == true) {
		isEnd = true;
		player_->EndFever();
	}

	viewProjection->UpdateMatrix();
}

void RailCamera::TitleR(Player* player_)
{
	//player_->worldTransform_.ResetParent();
	//camera->worldTransform_.SetParent3d(&player_->worldTransform_);
	viewProjection->eye.z -= 1.5;
}

////////////////////--------クラス内便利関数--------///////////////////////

//方向ベクトルを取得
void RailCamera::GetVec(Vector3 a, Vector3 b) {
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

void RailCamera::SetPlayer(Player* player_) {
	//拡大回転座標変換
	player_->SetScale(Vector3(0.2, 0.2, 0.2));
	player_->SetPosition(Vector3(0, 0, 0));
	//親子構造のセット
	player_->worldTransform_.SetParent3d(&camera->worldTransform_);
}

void RailCamera::SetEye(Vector3 view) {
	this->viewProjection->eye = view;
	viewProjection->UpdateMatrix();
}