#include "SphereCollider.h"

void SphereCollider::Update()
{
	// ���[���h�s�񂩂���W�𒊏o
	const Matrix4& matWorld = object3d->GetMatWorld();

	const Vector3& position = { matWorld.m[3][0],matWorld.m[3][1] ,matWorld.m[3][2] };

	// ���̃����o�ϐ����X�V
	Sphere::center = position + offset;
	Sphere::radius = radius;
}