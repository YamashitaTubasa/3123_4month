#pragma once

#include "Input.h"
#include "WinApp.h"
#include "DirectXCommon.h"
#include "Object3d.h"
#include "Model.h"
#include "Sprite.h"
#include "ImGuiManager.h"
#include "Vector3.h"
#include "ParticleManager.h"
#include "GameBaseScene.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "RailCamera.h"
#include "Player.h"

//====================//
// ゲームプレイシーン
//====================//
class GamePlayScene
{
public:
	GamePlayScene();
	~GamePlayScene();

public:
	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="dXCommon"></param>
	void Initialize(SpriteCommon& spriteCommon) ;

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw() ;

	/// <summary>
	/// 解放
	/// </summary>
	void Finalize();

	
	Vector3 start;
	Vector3 p2;
	Vector3 p3;
	Vector3 p4;
	Vector3 end;

	
	std::vector<Vector3> points{ start,start,p2,p3,p4,end,end };

	float timeRate;

private:
	Input* input = nullptr;
	Model* skyModel;
	Model* stageModel;
	Player* player;
	Object3d* sky;
	Object3d* stage;
	ViewProjection* viewProjection = nullptr;
	RailCamera* railCamera = nullptr;
	WorldTransform* worldTransform = nullptr;
	Sprite* sprite = nullptr;
	Sprite hP;
	SpriteCommon spriteCommon_;

	DirectXCommon* dXCommon = nullptr;
	ImGuiManager* imGuiManager = nullptr;
	ParticleManager* ParticleMan = nullptr;
	WinApp* winApp = nullptr;

	XMFLOAT3 position[5]{};
	XMFLOAT3 rotation[5]{};
	XMFLOAT3 scale[5]{};

	bool isPush_D = false;
	bool isPush_A = false;

	int playerHp = 3;
	int time = 0;

	const float PI = 3.141592;
};