#include "Enemy.h"
#include "GamePlayScene.h"

//�f�X�g���N�^
Enemy::~Enemy() {
	delete enemyModel;
	delete obj;
}

//������
void Enemy::Initialize(const Vector3& v)
{
	// OBJ���烂�f���f�[�^��ǂݍ���
	enemyModel = Model::LoadFromOBJ("ironSphere");
	// 3D�I�u�W�F�N�g����
	obj = Object3d::Create();
	// �I�u�W�F�N�g�Ƀ��f�����Ђ��t����
	obj->SetModel(enemyModel);
	obj->SetPosition(Vector3(v.x, v.y, v.z));
}

//�X�V
void Enemy::Update() {
	//�X�V
	obj->Update();
}

//�`��
void Enemy::Draw(ViewProjection* viewProjection) {
	obj->Draw(viewProjection);
}