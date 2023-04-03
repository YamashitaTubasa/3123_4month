#include "RailCamera.h"

RailCamera::RailCamera() {
}

RailCamera::~RailCamera() {
	delete viewProjection;
	delete camera;
}

//������
void RailCamera::Initialize(Object3d* player_) {
	viewProjection = new ViewProjection;
	input = Input::GetInstance();
	viewProjection->Initialize();
	camera = Object3d::Create();
	viewProjection->eye = { 0, 0, 0 };
	camera->SetPosition(viewProjection->eye);
	camera->SetRotation(viewProjection->target);
	//�g���]���W�ϊ�
	player_->SetScale(Vector3(0.4, 0.4, 0.4));
	//player_->SetRotation(Vector3(0, 90, 0));
	player_->SetPosition(Vector3(0, 0, 2.5));
	velo = 0.8f;
	//�e�q�\���̃Z�b�g
	player_->worldTransform_.SetParent3d(&camera->worldTransform_);
}

//�X�V
void RailCamera::Update(Object3d* player_, std::vector<Vector3>& point) {
	Vector3 target_ = spline_.Update(point, timeRate);
	Vector3 eye_ = viewProjection->eye;
	Vector3 frontTmp = GetFront(Vector3(eye_.x, 0, eye_.z), target_);
	Vector3 camera_;// = camera->GetPosition();
	Vector3 yTmpVec = { 0,1,0 };


	//�Ȑ��⊮
	camera_ = spline_.Update(point, timeRate);

	//frontTmp = { 2, 1 ,0 };

	camera->SetPosition(camera_ + frontTmp * 0.5);

	float rad = std::atan2(frontTmp.x, frontTmp.z);
	camera->SetRotationY(rad * 180.0f / 3.1415f);


	Vector3 rotaVec = { frontTmp.x,0,frontTmp.z };
	float length = rotaVec.length();
	float radddd = std::atan2(-frontTmp.y, length);
	camera->SetRotationX(radddd * 180.0f / 3.1415f);
	Vector3 answer = camera->GetRotation();

	//�X�V
	camera->Update();
	viewProjection->target = (camera_ + frontTmp * 0.5);
	viewProjection->eye = ( camera_ - frontTmp );
	viewProjection->UpdateMatrix();
}


////////////////////--------�N���X���֗��֐�--------///////////////////////

//�����x�N�g�����擾
Vector3 RailCamera::GetFront(Vector3 a, Vector3 b) {
	Vector3 yTmpVec = { 0, 1, 0 };
	Vector3 frontTmp = { 0, 0, 0 };
	Vector3 rightVec = { 0, 0, 0 };
	Vector3 leftVec = { 0, 0, 0 };
	Vector3 frontVec = { 0, 0, 0 };
	Vector3 a_ = { a.x,a.y,a.z };
	Vector3 b_ = { b.x,b.y,b.z };

	//Y�����x�N�g��
	yTmpVec.normalize();
	//���ʉ��x�N�g��
	frontTmp = b_ - a_;
	frontTmp.normalize();
	//�E�x�N�g��
	rightVec = yTmpVec.cross(frontTmp);
	rightVec.normalize();
	//���x�N�g��
	leftVec = frontTmp.cross(yTmpVec);
	leftVec.normalize();
	//���ʃx�N�g��
	frontVec = rightVec.cross(yTmpVec);
	frontVec.normalize();

	return frontVec;
}