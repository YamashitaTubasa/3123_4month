#include "InvisibleEnemy.h"
#include "GamePlayScene.h"

InvisibleEnemy::~InvisibleEnemy()
{
	delete invEnemyModel;
}

void InvisibleEnemy::InvEnemyInitialize()
{
	Initialize();
	// OBJ���烂�f���f�[�^��ǂݍ���
	invEnemyModel = Model::LoadFromOBJ("ironSphere_02");
	// 3D�I�u�W�F�N�g����
	Create();
	// �I�u�W�F�N�g�Ƀ��f�����Ђ��t����
	SetModel(invEnemyModel);
}
