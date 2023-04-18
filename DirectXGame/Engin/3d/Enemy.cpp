#include "Enemy.h"
#include "GamePlayScene.h"

//�f�X�g���N�^
Enemy::~Enemy() {
	delete enemyModel;
}

//������
void Enemy::EnemyInitialize(const Vector3& v)
{
	Initialize();
	// OBJ���烂�f���f�[�^��ǂݍ���
	enemyModel = Model::LoadFromOBJ("ironSphere");
	// 3D�I�u�W�F�N�g����
	Create();
	// �I�u�W�F�N�g�Ƀ��f�����Ђ��t����
	SetModel(enemyModel);
	SetPosition(Vector3(v.x, v.y, v.z));
}

void Enemy::OnCollision(const CollisionInfo& info)
{
	if (isDead_ == false)
	{
		isDead_ = true;
	}
}
