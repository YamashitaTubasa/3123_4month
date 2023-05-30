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
	isAttack = false;
	//�ϐ�
	attackTime = 0;
	val = 0.0f;
	len = 6.0f;
	feverTime = 0;
	isFever = false;
	isPush = false;
	pushTime = 0;
	feverNum = 0;
	attackNum = 0;
	speedUpCount = 3;
	res = 0.0f;
	isBurst = false;
	isGauge_ = false;

	moveE = 0.822f;
	moveS = 0.0f;
	moveTime = 0.0f;
	isMove = 0;

	//hp
	hp = 3;

	//���@�̈ʒu
	railPos = MIDDLE;

	attackS = 0.0;
	attackE = 360.0;

	return true;
}

void Player::Update(std::vector <Vector3>& point)
{
	input = Input::GetInstance();

	if (GamePlayScene::GetScene() == 2)
	{
		//�U�����ړ������ĂȂ���
		if (isPush == false && isMove == false)
		{
			//SPACE�L�[����������
			if (input->TriggerKey(DIK_SPACE))
			{
				//�U������
				isPush = true;
				isAttack = true;
			}
			if (isAttack == false)
			{
				//���ȊO�̎��ɍ��L�[����������
				if (input->TriggerKey(DIK_A) || input->TriggerKey(DIK_LEFT))
				{
					if (isMove == 0 && railPos != LEFT)
					{
						isMove = 1;
					}
				}
				//�E�ȊO�̎��ɉE�L�[����������
				if (input->TriggerKey(DIK_D) || input->TriggerKey(DIK_RIGHT))
				{
					if (isMove == 0 && railPos != RIGHT)
					{
						isMove = 2;
					}
				}
			}
		}
		Move(point);
		//�U�����Ȃ�X�V����
		if (isPush == true) {

			// ���[���h�g�����X�t�H�[���̍s��X�V�Ɠ]��
			worldTransform_.UpdateMatrix();

			if (isFever == false)
			{
				pushTime++;
				if (pushTime == 20)
				{
					pushTime = 0;
					isPush = false;

				}
			}
		}
		if (isAttack == true)
		{
			attackTime++;
			worldTransform_.rotation_.z = attackS + (attackE - attackS) * -MathFunc::easeOutSine(attackTime / 30);
			if (attackNum <= 6)
			{
				attackNum++;
			}
			if (attackTime == 30)
			{
				attackTime = 0;
				attackNum = 0;
				worldTransform_.rotation_.z = 0;
				isAttack = false;
			}
		}

		//�J�����������o
		if (len > 6) {
			len -= 0.125f;
		}

		if (isHit == true)
		{
			coolTime++;
			if (coolTime == 50)
			{
				coolTime = 0;
				isHit = false;
			}
		}
	}
	//�`���[�g���A��
	if (GamePlayScene::GetScene() == 6)
	{
		//�U�����ړ������ĂȂ���
		if (isPush == false && isMove == false)
		{
			//SPACE�L�[����������
			if (input->TriggerKey(DIK_SPACE) && GamePlayScene::GetTutorialStep() > 1)
			{
				//�U������
				isPush = true;
				isAttack = true;
			}
			if (isAttack == false && GamePlayScene::GetTutorialStep() > 3)
			{
				//���ȊO�̎��ɍ��L�[����������
				if (input->TriggerKey(DIK_A) || input->TriggerKey(DIK_LEFT))
				{
					if (isMove == 0 && railPos != LEFT)
					{
						isMove = 1;
					}
				}
				//�E�ȊO�̎��ɉE�L�[����������
				if (input->TriggerKey(DIK_D) || input->TriggerKey(DIK_RIGHT))
				{
					if (isMove == 0 && railPos != RIGHT)
					{
						isMove = 2;
					}
				}
			}
		}
		Move(point);
		//�U�����Ȃ�X�V����
		if (isPush == true) {

			// ���[���h�g�����X�t�H�[���̍s��X�V�Ɠ]��
			worldTransform_.UpdateMatrix();

			if (isFever == false)
			{
				pushTime++;
				if (pushTime == 20)
				{
					pushTime = 0;
					isPush = false;

				}
			}
		}
		if (isAttack == true)
		{
			attackTime++;
			worldTransform_.rotation_.z = attackS + (attackE - attackS) * -MathFunc::easeOutSine(attackTime / 30);
			if (attackNum <= 6)
			{
				attackNum++;
			}
			if (attackTime == 30)
			{
				attackTime = 0;
				attackNum = 0;
				worldTransform_.rotation_.z = 0;
				isAttack = false;
			}
		}

		//�J�����������o
		if (len > 6) {
			len -= 0.125f;
		}

		if (isHit == true)
		{
			coolTime++;
			if (coolTime == 50)
			{
				coolTime = 0;
				isHit = false;
			}
		}
	}

	if (val >= 0.0061)
	{
		GoesFever();
	}

	// ���[���h�g�����X�t�H�[���̍s��X�V�Ɠ]��
	worldTransform_.UpdateMatrix();

	//�����蔻��X�V
	if (collider)
	{
		collider->Update();
	}
}

void Player::Move(std::vector <Vector3>& point)
{
	if (isMove == 1)
	{
		//���ׂ̃��[���Ɉړ�����
		for (float i = 0; i < point.size(); i++)
		{
			point[i].x -= moveS + (moveE - moveS) * MathFunc::easeOutSine(moveTime / 20);
		}
		if (moveTime <= 10)
		{
			worldTransform_.rotation_.z += 3 * MathFunc::easeOutSine(moveTime / 10);
		}
		else
		{
			worldTransform_.rotation_.z -= 3 * MathFunc::easeOutSine(moveTime / 20);
		}
		moveTime++;
		//�t���O�؂�ւ�
		if (moveTime == 20)
		{
			worldTransform_.rotation_.z = 0;
			isMove = 0;
			moveTime = 0;
			//�ꏊ��enum�؂�ւ�
			if (railPos == MIDDLE)
			{
				railPos = LEFT;
			}
			else if (railPos == RIGHT)
			{
				railPos = MIDDLE;
			}
		}
	}

	if (isMove == 2)
	{
		//�E�ׂ̃��[���Ɉړ�����
		for (float i = 0; i < point.size(); i++)
		{
			point[i].x += moveS + (moveE - moveS) * MathFunc::easeOutSine(moveTime / 20);
		}
		if (moveTime <= 10)
		{
			worldTransform_.rotation_.z -= 3 * MathFunc::easeOutSine(moveTime / 10);
		}
		else
		{
			worldTransform_.rotation_.z += 3 * MathFunc::easeOutSine(moveTime / 20);
		}
		moveTime++;
		//�t���O�؂�ւ�
		if (moveTime == 20)
		{
			worldTransform_.rotation_.z = 0;
			isMove = 0;
			moveTime = 0;
			//�ꏊ��enum�؂�ւ�
			if (railPos == MIDDLE)
			{
				railPos = RIGHT;
			}
			else if (railPos == LEFT)
			{
				railPos = MIDDLE;
			}
		}
	}
}

//fever�^�C��
void Player::GoesFever()
{
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
			EndFever();
		}
	}
}

void Player::OnCollision(const CollisionInfo& info) {
	const char* str = "class Enemy";
	const char* str2 = "class InvisibleEnemy";
	if (strcmp(toCollisionName, str) == 0) {
		if (isPush == true) {
			if (isFever == false) {
				if (isGauge_ == false) {
					isGauge_ = true;
				}
				val += 0.002f;
				len = 15;
			}
			isBurst = true;
		}
		else {
			if (isHit == false) {
				hp--;
				GamePlayScene::SetIsBack(true);
				isHit = true;
			}
		}
	}
	if (strcmp(toCollisionName, str2) == 0) {
		if (isHit == false) {
			if (isFever == false) {
				hp--;
				isHit = true;
				GamePlayScene::SetIsBack(true);
			}
		}
	}
}

void Player::OffCollision(const CollisionInfo& info) {

}

void Player::EndFever() {
	val = 0.0f;
	worldTransform_.rotation_.z = 0;
	feverTime = 0;
	isFever = false;
}