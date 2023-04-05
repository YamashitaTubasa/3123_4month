#pragma once

#include "Vector3.h"
#include <Vector>

class Spline 
{
public:
	//������
	void Initialize();

	//�X�V
	Vector3 Update(std::vector<Vector3>& points,float t,float val);

	//�`��
	void Draw();

	//����_�̏W��(vector�R���e�i)�A��Ԃ����Ԃ̓Y���A���Ԍo�ߗ�
	Vector3 SplinePosition(const std::vector<Vector3>& point, size_t startIndex, float t);

private:
	//���Ԍv�Z�ɕK�v�ȃf�[�^
	long long startCount;
	long long nowCount;
	double elapsedCount = 0;

	float maxTime = 5.0f;				//�S�̎���[s]

	//P1����X�^�[�g����
	size_t startIndex = 1;

	//���̈ʒu
	Vector3 position;
};