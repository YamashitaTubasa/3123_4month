#include "Player.h"
#include "SphereCollider.h"
#include "string.h"
#include "GamePlayScene.h"

//�f�X�g���N�^
Player::~Player() {
	delete playerModel;
}

//������
bool Player::PlayerInitialize() {
	if (!Object3d::Initialize()) {
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
	isAttack = false;
	attackTime = 0;
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

void Player::Update() {
	input = Input::GetInstance();
	////���[���O�ړ�
	//if (isOnRail == false) {
	//	if (input->PushKey(DIK_W)) {
	//		SetRotation(Vector3({ 0, 0, 0 }));
	//		SetPosition(GetPosition() + Vector3(0, 0, 0.2));
	//	}
	//	if (input->PushKey(DIK_D)) {
	//		SetRotation(Vector3({ 0, 90, 0 }));
	//		SetPosition(GetPosition() + Vector3(0.2, 0, 0));
	//	}
	//	if (input->PushKey(DIK_A)) {
	//		SetRotation(Vector3({ 0, -90, 0 }));
	//		SetPosition(GetPosition() + Vector3(-0.2, 0, 0));
	//	}
	//	if (input->PushKey(DIK_S)) {
	//		SetRotation(Vector3({ 0, 180, 0 }));
	//		SetPosition(GetPosition() + Vector3(0, 0, -0.2));
	//	}
	//}

	if (GamePlayScene::GetScene() == 1) {
		if (input->TriggerKey(DIK_SPACE)) {
			if (isPush == false) {
				isPush = true;
				isAttack = true;
			}
		}

		//�U�����Ȃ�X�V����
		if (isPush == true) {

			// ���[���h�g�����X�t�H�[���̍s��X�V�Ɠ]��
			worldTransform_.UpdateMatrix();

			if (isFever == false) {
				pushTime++;
				if (pushTime == 20) {
					pushTime = 0;
					/*worldTransform_.rotation_.z = 0;*/
					if (isHit == true) {
						isHit = false;
					}
					isPush = false;

				}
			}
		}
		if (isAttack == true) {
			attackTime++;
 			worldTransform_.rotation_.z = start + (end - start) * -easeOutSine(attackTime / 30);
			if (attackTime == 30)
			{
				attackTime = 0;
				worldTransform_.rotation_.z = 0;
				isAttack = false;
			}
		}

		if (isHit == true) {
			coolTime++;
			if (coolTime == 50) {
				coolTime = 0;
				isHit = false;
			}
		}
	}

	if (val <= 500) {
		GoesFever();
	}

	// ���[���h�g�����X�t�H�[���̍s��X�V�Ɠ]��
	worldTransform_.UpdateMatrix();

	//�����蔻��X�V
	if (collider) {
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

		worldTransform_.rotation_.z -= 36;
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
			worldTransform_.rotation_.z = 0;
			feverTime = 0;
			isFever = false;
		}
	}
}

float Player::easeInSine(float a)
{
	const double PI = 3.141592;
	return 1 - cos((a * PI) / 2);
}

float Player::easeOutSine(float a)
{
	const double PI = 3.141592;
	return sin((a * PI) / 2);
}

void Player::OnCollision(const CollisionInfo& info) {
	const char* str = "class Enemy";
	if (strcmp(toCollisionName, str) == 0) {
		if (isHit == false) {
			if (isPush == true) {
				if (isFever == false) {
					if (isGauge_ == false) {
						isGauge_ = true;
					}
					res = val / speedUpCount;
					val -= res;
				}
				isBurst = true;
			}
			else {
				hp--;
			}
			isHit = true;
		}
	}
}

void Player::OffCollision(const CollisionInfo& info) {

}