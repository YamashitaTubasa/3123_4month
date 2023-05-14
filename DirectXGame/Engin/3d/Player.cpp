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
	isMove = false;
	isHit = false;
	coolTime = 0;
	isOnRail = false;
	isAttack = false;
	//�ϐ�
	attackTime = 0;
	val = 2000.0f;
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

	moveE = 12.0f;
	moveS = 0.0f;

	//hp
	hp = 3;

	//���@�̈ʒu
	railPos = MIDDLE;

	start = 0.0;
	end = 360.0;

	return true;
}

void Player::Update(std::vector <Vector3>& point)
{
	input = Input::GetInstance();

	if (GamePlayScene::GetScene() == 1)
	{
		//�U�����ړ������ĂȂ���
		if (isPush == false /*&& isMove == false*/)
		{
			//SPACE�L�[����������
			if (input->TriggerKey(DIK_SPACE))
			{
				//�U������
				isPush = true;
				isAttack = true;
			}
			//���ȊO�̎��ɍ��L�[����������
			if (input->TriggerKey(DIK_A) || input->TriggerKey(DIK_LEFT))
			{
				if (railPos != LEFT)
				{
					//���ׂ̃��[���Ɉړ�����
					for (float i = 0; i < point.size(); i++)
					{
						point[i].x -= 10;
						/*point[i].x = moveS + (moveE - moveS) * -MathFunc::easeOutSine(i / 12);*/
					}
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
			//�E�ȊO�̎��ɉE�L�[����������
			if (input->TriggerKey(DIK_D) || input->TriggerKey(DIK_RIGHT))
			{
				if (railPos != RIGHT)
				{
					//�E�ׂ̃��[���Ɉړ�����
					for (float i = 0; i < point.size(); i++)
					{
						point[i].x += 10;
						/*point[i].x = moveS + (moveE - moveS) * MathFunc::easeOutSine(i / 12);*/
					}
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
					if (isHit == true)
					{
						isHit = false;
					}
					isPush = false;

				}
			}
		}
		if (isAttack == true)
		{
			attackTime++;
			worldTransform_.rotation_.z = start + (end - start) * -MathFunc::easeOutSine(attackTime / 30);
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

	if (val <= 500)
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
			val = 2000.0f;
			worldTransform_.rotation_.z = 0;
			feverTime = 0;
			isFever = false;
		}
	}
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