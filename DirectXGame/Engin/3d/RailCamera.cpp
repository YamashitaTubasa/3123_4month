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
	camera->SetRotation(Vector3(0,0,0));
	isEnd = false;
}

//�X�V
void RailCamera::Update(Player* player_, std::vector<Vector3>& point) {


	if (player_->GetPositionZ() >= -778) {
		if (player_->GetOnRail() == false) {
			player_->SetOnRail(true);
			//�g���]���W�ϊ�
			player_->SetScale(Vector3(0.2, 0.2, 0.2));
			player_->SetPosition(Vector3(0, 0, 0));
			//�e�q�\���̃Z�b�g
			player_->worldTransform_.SetParent3d(&camera->worldTransform_);
		}
	}

	if (player_->GetOnRail() == true) {
		Vector3 target_ = spline_.Update(point, timeRate, player_->GetVal());
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
		viewProjection->eye = (target_ - frontVec*3);
		viewProjection->eye.y = (target_.y + 0.5);

		if (spline_.GetIsEnd() == true) {
			isEnd = true;
		}
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