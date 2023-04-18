#include "Player.h"
#include "SphereCollider.h"

//�f�X�g���N�^
Player::~Player() {
	delete playerModel;
	delete obj;
}

//������
bool Player::Initialize() {
	if (!Object3d::Initialize())
	{
		return false;
	}
	//�R���C�_�[�̒ǉ�
	float radius = 0.6f;
	//���a�������������畂�������W�����̒��S�ɂ���
	SetCollider(new SphereCollider(Vector3({ 0,radius,0 }), radius));

	// OBJ���烂�f���f�[�^��ǂݍ���
	playerModel = Model::LoadFromOBJ("fighter");
	attackModel = Model::LoadFromOBJ("triangle_mat");
	// 3D�I�u�W�F�N�g����
	obj = Object3d::Create();
	// �I�u�W�F�N�g�Ƀ��f�����Ђ��t����
	obj->SetModel(playerModel);
	obj->SetRotation(Vector3({ 0, 90, 0 }));
	obj->SetPosition(Vector3(0, 0, -790));
	// 3D�I�u�W�F�N�g����
	attack = Object3d::Create();
	// �I�u�W�F�N�g�Ƀ��f�����Ђ��t����
	attack->SetModel(attackModel);
	attack->SetRotation(Vector3({ 0, 90, 0 }));
	attack->SetPosition(Vector3(0, 0, -780));
	//�ϐ�
	val = 1000.0f;
	feverTime = 0;
	isFever = false;
	//�t���O
	isHit = false;

	return true;
}

//�X�V
void Player::Update() {
	input = Input::GetInstance();
	//���[���O�ړ�
	if (isOnRail == false) {
		if (input->PushKey(DIK_W)) {
			obj->SetPosition(obj->GetPosition() + Vector3(0, 0, 0.2));
		}
		if (input->PushKey(DIK_D)) {
			obj->SetPosition(obj->GetPosition() + Vector3(0.2, 0, 0));
		}
		if (input->PushKey(DIK_A)) {
			obj->SetPosition(obj->GetPosition() + Vector3(-0.2, 0, 0));
		}
		if (input->PushKey(DIK_S)) {
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
	attack->Update();
}

void Player::OnCollision(const CollisionInfo& info)
{
	if (isHit == false)
	{
		isHit = true;
	}
}

//�`��
void Player::Draw(ViewProjection* viewProjection) {
	obj->Draw(viewProjection);
	/*attack->Draw(viewProjection);*/
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

		if (feverTime % 2 == 0) {
			if (feverNum < 5) {
				feverNum++;
			}
			else {
				feverNum = 0;
			}
		}

		//��莞�Ԃ�����ʏ탂�[�h��
		if (feverTime == 300) {
			val = 1000.0f;
			feverTime = 0;
			isFever = false;
		}
	}
}