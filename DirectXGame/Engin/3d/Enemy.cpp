#include "Enemy.h"
#include "GamePlayScene.h"
#include "string.h"

//�f�X�g���N�^
Enemy::~Enemy() {
	delete enemyModel;
}

//������
void Enemy::EnemyInitialize()
{
	Initialize();
	// OBJ���烂�f���f�[�^��ǂݍ���
	enemyModel = Model::LoadFromOBJ("ironSphere_01");
	// 3D�I�u�W�F�N�g����
	Create();
	// �I�u�W�F�N�g�Ƀ��f�����Ђ��t����
	SetModel(enemyModel);
	isDead_ = false;
}

void Enemy::OnCollision(const CollisionInfo& info)
{
	const char* str1 = "class Player";
	const char* str2 = "class PlayerAttack";

	//���肪player
	if (strcmp(toCollisionName, str1) == 0) {

	}

	//���肪player�̍U��
	if (strcmp(toCollisionName, str2) == 0) {
		if (isDead_ == false)
		{
			isDead_ = true;
		}
	}
}

void Enemy::OffCollision(const CollisionInfo& info)
{

}