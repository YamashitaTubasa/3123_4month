#pragma once
#include "Object3d.h"
#include "WinApp.h"
#include "Vector3.h"
#include "Model.h"
#include <list>

//GameScene�̑O���錾
class GamePlayScene;

class Enemy {
public:
	//�f�X�g���N�^
	~Enemy();
	//������
	void Initialize(const Vector3& v);
	//�X�V
	void Update();
	//�`��
	void Draw(ViewProjection* viewProjection);

	//�G���X�g
	const std::list<std::unique_ptr<Enemy>>& GetEnemys() { return enemys_; }

	//gameScene��setter
	void SetGameScene(GamePlayScene* gameScene) { gameScene_ = gameScene; }

	bool IsDead() const { return isDead_; }

public:
	// �I�u�W�F�N�g
	Object3d* obj = nullptr;

private:
	//�Q�[���V�[��
	GamePlayScene* gameScene_ = nullptr;

	//�f�X�t���O
	bool isDead_ = false;

	//�G
	std::list<std::unique_ptr<Enemy>> enemys_;

	// ���f��
	Model* enemyModel = nullptr;

	//���a
	float radius = 1.0f;
};
