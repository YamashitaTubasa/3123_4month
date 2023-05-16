#include "Spline.h"
#include <windows.h>
#include <sysinfoapi.h>

void Spline::Initialize() {
	startCount = GetTickCount64();
	isEnd = false;
	t = 0.0f;
}

Vector3 Spline::Update(std::vector<Vector3>& points, float val) {

	//�o�ߎ��Ԃ̌v�Z
	/*float elapsedTime = static_cast<float> (elapsedCount) / val;*/

	t = t + val;

	//timeRate��1.0f�ȏ�ɂȂ�����A���̋�Ԃɐi��
	if (t >= 1.0f) {
		if (startIndex < points.size() - 3) {

			startIndex++;

			t -= 1.0f;
		}
		else {
			isEnd = true;
			t = 1.0f;
		}
	}

	Vector3 pos = SplinePosition(points, startIndex, t);

	t += 0.002;
	
	return pos;
}

Vector3 Spline::pointCal(std::vector<Vector3>& points) {

	const int INDEXMAX = points.size() - 1;

	float nowPoint = startIndex / INDEXMAX;

	Vector3 pos = SplinePosition(points, startIndex, t);

	if (t >= 1) {
		startIndex++;
		t = 0;
	}
	else {
		t += 0.01f;
	}

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