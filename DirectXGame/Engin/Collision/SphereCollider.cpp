#include "SphereCollider.h"

void SphereCollider::Update()
{
	// ���[���h�s�񂩂���W�𒊏o
	const Matrix4& matWorld = object3d->worldTransform_.matWorld_;

	const Vector3& position = { matWorld.m[3][0],matWorld.m[3][1] ,matWorld.m[3][2] };

	//Vector4 matVec;
	//matVec.x = matWorld.m[3][0];
	//matVec.y = matWorld.m[3][1];
	//matVec.z = matWorld.m[3][2];
	//matVec.w = matWorld.m[3][3];

	// ���̃����o�ϐ����X�V
	Sphere::center = position + offset;
	Sphere::radius = radius;
}