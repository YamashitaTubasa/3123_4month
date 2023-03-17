#include "Spline.h"
#include <windows.h>
#include <sysinfoapi.h>

void Spline::Initialize() {
	startCount = GetTickCount64();
}

Vector3 Spline::Update(std::vector<Vector3>& points,float timeRate) {

	//�o�ߎ��Ԃ̌v�Z
	nowCount = GetTickCount64();
	elapsedCount = nowCount - startCount;
	float elapsedTime = static_cast<float> (elapsedCount) / 1000.0f;

	timeRate = elapsedTime / maxTime;

	//timeRate��1.0f�ȏ�ɂȂ�����A���̋�Ԃɐi��
	if (timeRate >= 1.0f) {
		if (startIndex < points.size() - 3) {

			startIndex++;

			timeRate -= 1.0f;
			startCount = GetTickCount64();
		}
		else {
			timeRate = 1.0f;
		}
	}

	Vector3 pos = SplinePosition(points, startIndex, timeRate);
	
	return pos;
}


void Spline::Draw() {
	
}

Vector3 Spline::SplinePosition(const std::vector<Vector3>& points, size_t startIndex, float t) {
	//��Ԃ��ׂ��_
	size_t n = points.size() - 2;

	if (startIndex > n) return points[n];
	if (startIndex < 1) return points[1];

	//p0~p3�̐���_���擾����
	Vector3 p0_ = points[startIndex - 1];
	Vector3 p1_ = points[startIndex];
	Vector3 p2_ = points[startIndex + 1];
	Vector3 p3_ = points[startIndex + 2];

	//Catmull-Rom �̎��ɂ����
	Vector3 position = 0.5 * (p1_ * 2 + (-p0_ + p2_) *
							  t + (p0_ * 2 - p1_ * 5 + p2_ * 4 - p3_) *
							  (t * t) + (-p0_ + p1_ * 3 - p2_ * 3 + p3_) *
							  (t * t * t));

	return position;
}
