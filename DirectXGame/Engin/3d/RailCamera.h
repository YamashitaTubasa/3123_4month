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
	Vector3 GetFront(Vector3 a, Vector3 b);

	ViewProjection* GetView() { return viewProjection; }

private:
	ViewProjection* viewProjection = nullptr;
	Object3d* camera = nullptr;
	Input* input = nullptr;
	enum rane {
		LEFT,
		MID,
		RIGHT
	};
	rane raneNum = MID;
	float velo;
	Vector3 angle = { 0,0,0 };


	//スプライン
	Spline spline_;

	float timeRate;
};

