#include "Player.h"
#include "SphereCollider.h"
#include "string.h"

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
	// 3D�I�u�W�F�N�g����
	Create();
	// �I�u�W�F�N�g�Ƀ��f�����Ђ��t����
	SetModel(playerModel);
	SetPosition(Vector3(0, 0, -790));

	//�t���O
	isHit = false;
	coolTime = 0;
	isOnRail = false;
	//�����蔻��
	isHit = false;

	//hp
	hp = 3;

	return true;
}

void Player::Update()
{
	input = Input::GetInstance();
	//���[���O�ړ�
	if (isOnRail == false) {
		if (input->PushKey(DIK_W)) {
			SetRotation(Vector3({ 0, 0, 0 }));
			SetPosition(GetPosition() + Vector3(0, 0, 0.2));
		}
		if (input->PushKey(DIK_D)) {
			SetRotation(Vector3({ 0, 90, 0 }));
			SetPosition(GetPosition() + Vector3(0.2, 0, 0));
		}
		if (input->PushKey(DIK_A)) {
			SetRotation(Vector3({ 0, -90, 0 }));
			SetPosition(GetPosition() + Vector3(-0.2, 0, 0));
		}
		if (input->PushKey(DIK_S)) {
			SetRotation(Vector3({ 0, 180, 0 }));
			SetPosition(GetPosition() + Vector3(0, 0, -0.2));
		}
	}

	if (isHit == true) {
		coolTime++;
		if (coolTime == 50) {
			coolTime = 0;
			isHit = false;
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
	const char* str = "class Enemy";
	if (strcmp(toCollisionName, str) == 0) {
		if (isHit == false)
		{
			isHit = true;
			hp--;
		}
	}
}

void Player::OffCollision(const CollisionInfo& info)
{

}