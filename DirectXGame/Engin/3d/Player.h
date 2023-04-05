#pragma once
#include "Object3d.h"
#include "WinApp.h"
#include "Vector3.h"
#include "input.h"
#include "Spline.h"
#include "Model.h"

class Player {
public:
	//デストラクタ
	~Player();
	//初期化
	void Initialize();
	//更新
	void Update();
	//描画
	void Draw(ViewProjection* viewProjection);

	//feverタイム
	void GoesFever();
	bool GetFever() { return isFever; }

	//ベクトルを取得
	void GetVec(Vector3 a, Vector3 b);
	float GetVal() { return val; }
	//フラグ
	bool GetOnRail() { return isOnRail; }
	void SetOnRail(bool isOnRail_) { this->isOnRail = isOnRail_; }

public:
	// オブジェクト
	Object3d* obj = nullptr;
private:
	Input* input_ = nullptr;
	// モデル
	Model* playerModel = nullptr;
	//fever
	int feverTime;
	bool isFever = false;
	float val = 1000.0f;
	//レールに乗っている状態
	bool isOnRail = false;

	//移動用方向ベクトル
	Vector3 rightVec = { 0, 0, 0 };
	Vector3 leftVec = { 0, 0, 0 };
	Vector3 frontVec = { 0, 0, 0 };
};
