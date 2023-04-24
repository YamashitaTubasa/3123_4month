#include "PlayerAttack.h"
#include "SphereCollider.h"
#include "string.h"

PlayerAttack::~PlayerAttack() {
	delete attackModel;
}

bool PlayerAttack::AttackInitialize(Player* player_) {
	if (!Object3d::Initialize())
	{
		return false;
	}

	Initialize();

	// OBJ���烂�f���f�[�^��ǂݍ���
	attackModel = Model::LoadFromOBJ("triangle_mat");
	attackModel->LoadTexture("Resources/red.png");
	// 3D�I�u�W�F�N�g����
	Create();
	// �I�u�W�F�N�g�Ƀ��f�����Ђ��t����
	SetModel(attackModel);
	//�ϐ�
	val = 1000.0f;
	feverTime = 0;
	isFever = false;
	isPush = false;
	pushTime = 0;
	isHit = false;
	coolTime = 0;
	feverNum = 0;
	isOnRail = false;
	//player�̎q���ɂ���
	worldTransform_.SetParent3d(&player_->worldTransform_);
	SetRotation(Vector3(0, -90, 0));
	/*SetPosition(Vector3(-3, 1, 0));*/
	SetScale(Vector3(2, 2, 2));
	return true;
}

void PlayerAttack::Update() {
	input = Input::GetInstance();

	if (input->TriggerKey(DIK_SPACE)) {
		if (isPush == false) {
			isPush = true;
		}
	}

	//�U���������������̏���
	if (isHit == true) {
		coolTime++;
		if (coolTime == 10) {
			coolTime = 0;
			isHit = false;
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
			if (pushTime == 20) {
				pushTime = 0;
				isPush = false;
			}
		}
	}
	//�����蔻��X�V
	if (collider)
	{
		collider->Update();
	}
}

//fever�^�C��
void PlayerAttack::GoesFever() {
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
			val = 1000.0f;
			feverTime = 0;
			isFever = false;
			SetScale(Vector3(2, 2, 2));
		}
	}
}

void PlayerAttack::OnCollision(const CollisionInfo& info)
{
	const char* str = "class Player";
	if (strcmp(toCollisionName, str) != 0) {
		if (isHit == false) {
			isHit = true;
			if (isFever == false) {
				val -= 500.0f;
			}
			if (isHit == true) {
				isDead = true;
			}
		}
	}
}

void PlayerAttack::OffCollision(const CollisionInfo& info)
{

}