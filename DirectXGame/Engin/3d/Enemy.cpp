#include "Enemy.h"

//�f�X�g���N�^
Enemy::~Enemy() {
	delete enemyModel;
	delete obj;
}

//������
void Enemy::Initialize() {
	// OBJ���烂�f���f�[�^��ǂݍ���
	enemyModel = Model::LoadFromOBJ("sphere");
	// 3D�I�u�W�F�N�g����
	obj = Object3d::Create();
	// �I�u�W�F�N�g�Ƀ��f�����Ђ��t����
	obj->SetModel(enemyModel);
	obj->SetRotation(Vector3({ 0, 90, 0 }));
	obj->SetPosition(Vector3(0, 0, -790));

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