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
	//�ϐ�
	val = 2000.0f;
	feverTime = 0;
	isFever = false;
	isPush = false;
	pushTime = 0;
	feverNum = 0;
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

	if (input->TriggerKey(DIK_SPACE)) {
		if (isPush == false) {
			isPush = true;
		}
	}

	if (val <= 500) {
		GoesFever();
	}

	//�U�����Ȃ�X�V����
	if (isPush == true) {

		// ���[���h�g�����X�t�H�[���̍s��X�V�Ɠ]��
		worldTransform_.UpdateMatrix();

		if (isFever == false) {
			pushTime++;
			worldTransform_.rotation_.z -= 18;
			if (pushTime == 20) {
				pushTime = 0;
				worldTransform_.rotation_.z = 0;
				if (isHit == true)
				{
					isHit = false;
				}
				isPush = false;
				
			}
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

//fever�^�C��
void Player::GoesFever() {
	//fever�łȂ��Ȃ�fever��
	if (isFever == false) {
		isFever = true;
		isPush = true;
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
		if (feverTime == 250) {
			val = 2000.0f;
			feverTime = 0;
			isFever = false;
		}
	}
}

void Player::OnCollision(const CollisionInfo& info)
{
	const char* str = "class Enemy";
	if (strcmp(toCollisionName, str) == 0) {
		if (isHit == false)
		{
			if (isGauge_ == false) {
				isGauge_ = true;
			}
			if (isPush == true)
			{
				if (isFever == false) {
					val -= 500.0f;
				}
				isBurst = true;
			}
			else
			{
				hp--;
			}
			isHit = true;
		}
	}
}

void Player::OffCollision(const CollisionInfo& info)
{

}