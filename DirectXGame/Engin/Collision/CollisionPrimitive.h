#pragma once
#pragma once
#include<DirectXMath.h>
#include "Vector3.h"

//��
struct Sphere
{
	//���S���W
	Vector3 center = { 0,0,0 };
	//���a
	float radius = 1.0f;
	//���W
	Vector3 position = { 0,0,0 };
};
//����
struct Plane
{
	//�@���x�N�g��
	Vector3 normal = { 0,1,0 };
	//���_(0,0,0)����̋���
	float distance = 0.0f;
};
//���C
struct Ray
{
	//�n�_���W
	Vector3 start = { 0,0,0 };

	//����
	Vector3 dir = { 1,0,0 };
};

//�@���t���O�p�`(���v��肪�\��)
class Triangle
{
public:
	//���_3��
	Vector3 p0;
	Vector3 p1;
	Vector3 p2;
	//�@���x�N�g��
	Vector3 normal;

	//�@���̌v�Z
	void ComputeNormal();
};

class CollisionPrimitive
{
public:
};

