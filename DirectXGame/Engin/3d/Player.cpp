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
	obj->SetPosition(Vector3(0, 0, -790));
	//�ϐ�
	val = 1000.0f;
	feverTime = 0;
	isFever = false;
}

//�X�V
void Player::Update() {
	//���[���O�ړ�
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

	//���[���㏈��
	if (isOnRail == true) {
		//feverTaime
		if (val == 600) {
			GoesFever();
		}
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