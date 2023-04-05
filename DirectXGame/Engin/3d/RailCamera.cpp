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
	player_->SetPosition(Vector3(0, 0, 2.5));
	//�ϐ�������
	val = 1000.0f;
	feverTime = 0;
	//�e�q�\���̃Z�b�g
	player_->worldTransform_.SetParent3d(&camera->worldTransform_);
}

//�X�V
void RailCamera::Update(Object3d* player_, std::vector<Vector3>& point) {
	Vector3 target_ = spline_.Update(point, timeRate,val);
	GetVec(viewProjection->eye, target_);
	Vector3 move;
	//��葬�x�̒B������Fever!
	if (val == 600) {
		GoesFever(player_);
	}

	//�Ȑ��⊮
	move = spline_.Update(point, timeRate,val);
	//�e(�J�����I�u�W�F�N�g)�̈ړ�
	camera->SetPosition(move + frontVec * 0.5);
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
	viewProjection->target = (move + frontVec * 0.5);
	viewProjection->eye = ( move - frontVec );
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