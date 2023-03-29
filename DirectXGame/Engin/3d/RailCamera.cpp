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
	player_->SetParent3d(camera);
	player_->SetScale(Vector3(0.4, 0.4, 0.4));
	player_->SetRotation(Vector3(0, 90, 0));
	player_->SetPosition(Vector3(0, -2, 2.5));
	velo = 0.8f;
}

//更新
void RailCamera::Update(Object3d* player_, std::vector<Vector3>& point) {
	Vector3 target_ = spline_.Update(point, timeRate);
	Vector3 eye_ = viewProjection->eye;
	Vector3 frontTmp = GetFront(Vector3(eye_.x, 0, eye_.z), target_);
	Vector3 camera_ = camera->GetPosition();
	Vector3 yTmpVec = { 0,1,0 };


	//曲線補完
	camera_ = spline_.Update(point, timeRate);

	camera->SetPosition(camera_ + frontTmp * 0.5);
	player_->SetPosition(camera->GetPosition()+ frontTmp);
	player_->SetRotationY(std::atan2(frontTmp.z, frontTmp.x) + frontTmp.x * 70 + 90);
	Vector3 rotaVec = { frontTmp.x,0,frontTmp.z };
	rotaVec.length();
	player_->SetRotationX(std::atan2(-frontTmp.y, rotaVec.z) + frontTmp.y * 70);
	Vector3 answer = camera->GetRotation();

	//更新
	camera->Update();
	viewProjection->target = (camera_ + frontTmp * 0.5);
	viewProjection->eye = ( camera_ - frontTmp );
	viewProjection->UpdateMatrix();


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