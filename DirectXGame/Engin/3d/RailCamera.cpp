#include "RailCamera.h"

RailCamera::RailCamera() {
}

RailCamera::~RailCamera() {
	delete viewProjection;
	delete camera;
}

//������
void RailCamera::Initialize(Player* player_) {
	viewProjection = new ViewProjection;
	input = Input::GetInstance();
	viewProjection->Initialize();
	camera = Object3d::Create();
	viewProjection->eye = { 0, 0, 0 };
	camera->SetPosition(viewProjection->eye);
	camera->SetRotation(viewProjection->target);
	//�g���]���W�ϊ�
	player_->obj->SetScale(Vector3(0.4, 0.4, 0.4));
	player_->obj->SetPosition(Vector3(0, -0.5, 1.5));
	//�e�q�\���̃Z�b�g
	player_->obj->worldTransform_.SetParent3d(&camera->worldTransform_);
}

//�X�V
void RailCamera::Update(Player* player_, std::vector<Vector3>& point) {
	Vector3 target_ = spline_.Update(point, timeRate,player_->GetVal());
	//�����x�N�g���̎擾
	GetVec(viewProjection->eye, target_);

	//�e(�J�����I�u�W�F�N�g)�̈ړ�
	camera->SetPosition(target_ + frontVec * 0.5);
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
	viewProjection->target = (target_ + frontVec * 0.5);
	viewProjection->eye = (target_ - frontVec );
	viewProjection->UpdateMatrix();
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