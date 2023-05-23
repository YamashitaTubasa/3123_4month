#pragma once
#include "Object3d.h"
#include "WinApp.h"
#include "Vector3.h"
#include "Model.h"
#include <list>

//GameScene�̑O���錾
class GamePlayScene;


class InvisibleEnemy : public Object3d
{
public:
	//�f�X�g���N�^
	~InvisibleEnemy();
	//������
	void InvEnemyInitialize();

	//�G���X�g
	const std::list<std::unique_ptr<InvisibleEnemy>>& GetInvEnemys() { return invEnemys_; }

	//gameScene��setter
	void SetGameScene(GamePlayScene* gameScene) { gameScene_ = gameScene; }
private:
	//�Q�[���V�[��
	GamePlayScene* gameScene_ = nullptr;
	//�G
	std::list<std::unique_ptr<InvisibleEnemy>> invEnemys_;

	// ���f��
	Model* invEnemyModel = nullptr;

	//���a
	float radius = 1.0f;
};

