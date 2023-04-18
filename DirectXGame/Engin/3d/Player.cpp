#include "Player.h"
#include "SphereCollider.h"

//�f�X�g���N�^
Player::~Player() {
	delete playerModel;
}

//������
bool Player::PlayerInitialize() {
	if (!Object3d::Initialize())
	{
		return false;
	}

	Initialize();

	// OBJ���烂�f���f�[�^��ǂݍ���
	playerModel = Model::LoadFromOBJ("fighter");
	attackModel = Model::LoadFromOBJ("triangle_mat");
	// 3D�I�u�W�F�N�g����
	Create();
	// �I�u�W�F�N�g�Ƀ��f�����Ђ��t����
	SetModel(playerModel);
	SetRotation(Vector3({ 0, 90, 0 }));
	SetPosition(Vector3(0, 0, -790));
	//�ϐ�
	val = 1000.0f;
	feverTime = 0;
	isFever = false;
	//�t���O
	isHit = false;

	return true;
}

void Player::Update()
{
	input = Input::GetInstance();
	//���[���O�ړ�
	if (isOnRail == false) {
		if (input->PushKey(DIK_W)) {
			SetPosition(GetPosition() + Vector3(0, 0, 0.2));
		}
		if (input->PushKey(DIK_D)) {
			SetPosition(GetPosition() + Vector3(0.2, 0, 0));
		}
		if (input->PushKey(DIK_A)) {
			SetPosition(GetPosition() + Vector3(-0.2, 0, 0));
		}
		if (input->PushKey(DIK_S)) {
			SetPosition(GetPosition() + Vector3(0, 0, -0.2));
		}
	}
	// ���[���h�g�����X�t�H�[���̍s��X�V�Ɠ]��
	worldTransform_.UpdateMatrix();

	//�����蔻��X�V
	if (collider)
	{
		collider->Update();
	}
}

void Player::OnCollision(const CollisionInfo& info)
{
	if (isHit == false)
	{
		isHit = true;
	}
}

void Player::OffCollision(const CollisionInfo& info)
{
	if (isHit == true)
	{
		isHit = false;
	}
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