#include "RailCamera.h"

RailCamera::RailCamera() {
}

RailCamera::~RailCamera() {
	delete viewProjection;
	delete camera;
}

//������
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

//�X�V
void RailCamera::Update(Player* player_, std::vector<Vector3>& point) {


	Vector3 target_ = spline_.Update(point, 0.00001 + player_->GetVal());
	camera->SetPosition(splineCam.Update(point, player_->GetVal()));
	//�����x�N�g���̎擾
	GetVec(camera->GetPosition(), target_);

	//�J���������ɍ��킹��Y���̉�]
	float radY = std::atan2(frontVec.x, frontVec.z);
	camera->SetRotationY(radY * 180.0f / 3.1415f);
	//�J���������ɍ��킹��X���̉�]
	Vector3 rotaVec = { frontVec.x,0,frontVec.z };
	float length = rotaVec.length();
	float radX = std::atan2(-frontVec.y, length);
	camera->SetRotationX(radX * 180.0f / 3.1415f);
	//�X�V
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

////////////////////--------�N���X���֗��֐�--------///////////////////////

//�����x�N�g�����擾
void RailCamera::GetVec(Vector3 a, Vector3 b) {
	Vector3 yTmpVec = { 0, 1, 0 };
	Vector3 frontTmp = { 0, 0, 0 };
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
	//���ʃx�N�g��(Y���W��0�ɂ���)
	frontVec = rightVec.cross(yTmpVec);
	frontVec.normalize();
}

void RailCamera::SetPlayer(Player* player_) {
	//�g���]���W�ϊ�
	player_->SetScale(Vector3(0.2, 0.2, 0.2));
	player_->SetPosition(Vector3(0, 0, 0));
	//�e�q�\���̃Z�b�g
	player_->worldTransform_.SetParent3d(&camera->worldTransform_);
}

void RailCamera::SetEye(Vector3 view) {
	this->viewProjection->eye = view;
	viewProjection->UpdateMatrix();
}