#pragma once
#include "ViewProjection.h"
#include "Object3d.h"
#include "WinApp.h"
#include "Vector3.h"
#include "input.h"
#include "Spline.h"


class RailCamera {
public:
	//インスタンス
	RailCamera();
	~RailCamera();
	//初期化
	void Initialize(Object3d* player_);
	//更新
	void Update(Object3d* player_, std::vector<Vector3>& point);

	//正面ベクトルを取得
	void GetVec(Vector3 a, Vector3 b);

	ViewProjection* GetView() { return viewProjection; }

	//feverタイム
	void GoesFever(Object3d* player_);

	bool GetFever() { return isFever; }

	float val;
private:
	Input* input_ = nullptr;
	ViewProjection* viewProjection = nullptr;
	Object3d* camera = nullptr;
	Input* input = nullptr;
	//fever
	int feverTime;
	bool isFever = false;

	//スプライン
	Spline spline_;

	Vector3 rightVec = { 0, 0, 0 };
	Vector3 leftVec = { 0, 0, 0 };
	Vector3 frontVec = { 0, 0, 0 };

	float timeRate;
};

