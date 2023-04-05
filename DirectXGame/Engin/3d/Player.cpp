#include "Player.h"

//�f�X�g���N�^
Player::~Player() {
	delete playerModel;
	delete obj;
}

//������
void Player::Initialize() {
	input_ = Input::GetInstance();
	// OBJ���烂�f���f�[�^��ǂݍ���
	playerModel = Model::LoadFromOBJ("fighter");
	// 3D�I�u�W�F�N�g����
	obj = Object3d::Create();
	// �I�u�W�F�N�g�Ƀ��f�����Ђ��t����
	obj->SetModel(playerModel);
	obj->SetRotation(Vector3({ 0, 90, 0 }));
	obj->SetScale(Vector3(1.5, 1, 1));
	//�ϐ�
	val = 1000.0f;
	feverTime = 0;
	isFever = false;
}

//�X�V
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
	//�X�V
	obj->Update();
}

//�`��
void Player::Draw(ViewProjection* viewProjection) {
	obj->Draw(viewProjection);
}

//fever�^�C��
void Player::GoesFever() {
	//fever�łȂ��Ȃ�fever��
	if (isFever == false) {
		isFever = true;
	}
	//fever!!
	if (isFever == true) {
		feverTime++;

		obj->SetScale(Vector3(3, 3, 3));
		//��莞�Ԃ�����ʏ탂�[�h��
		if (feverTime == 300) {
			val = 1000.0f;
			feverTime = 0;
			obj->SetScale(Vector3(0.4, 0.4, 0.4));
			isFever = false;
		}
	}
}

////////////////////////////////////////////////////////////////////////

//�����x�N�g�����擾
void Player::GetVec(Vector3 a, Vector3 b) {
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