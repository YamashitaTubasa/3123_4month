#include "Collision.h"
using namespace DirectX;


bool Collision::CheckSphere2Sphere(const Sphere& sphereA, const Sphere& sphereB, Vector3* inter, Vector3* reject)
{
	float x = (sphereB.center.x - sphereA.center.x) * (sphereB.center.x - sphereA.center.x);
	float y = (sphereB.center.y - sphereA.center.y) * (sphereB.center.y - sphereA.center.y);
	float z = (sphereB.center.z - sphereA.center.z) * (sphereB.center.z - sphereA.center.z);

	float dist = x + y + z;
	float radius = (sphereA.radius + sphereB.radius) * (sphereA.radius + sphereB.radius);

	if (dist <= radius) {
		if (inter) {
			// A�̔��a��0�̎����W��B�̒��S  B�̔��a��0�̎����W��A�̒��S  �ƂȂ�悤�ɕ��
			float t = sphereB.radius / (sphereA.radius + sphereB.radius);
			*inter = Vector3::lerp(sphereA.center, sphereB.center, t);
		}
		if (reject) {
			float rejectLen = sphereA.radius + sphereB.radius - sqrtf(dist);
			Vector3 center = sphereA.center - sphereB.center;
			*reject = center.normalize();
			*reject *= rejectLen;

		}
		return true;
	}
	return false;
}

bool Collision::CheckSphere2Plane(const Sphere& sphere, const Plane& plane, Vector3* inter)
{
	// ���W�n�̌��_���狅�̒��S���W�ւ̋���
	Vector3 V;
	float distV = V.dot(sphere.center, plane.normal);
	// ���ʂ̌��_���������Z���邱�ƂŁA���ʂƋ��̒��S�Ƃ̋������o��
	float dist = distV - plane.distance;
	// �����̐�Βl�����a���傫����Γ������Ă��Ȃ�
	if (fabsf(dist) > sphere.radius) return false;

	// �^����_���v�Z
	if (inter) {
		// ���ʏ�̍ŋߐړ_���A�^����_�Ƃ���
		*inter = -dist * plane.normal + sphere.center;
	}

	return true;
}

void Collision::ClosestPtPoint2Triangle(const Vector3& point, const Triangle& triangle, Vector3* closest)
{
	// point��p0�̊O���̒��_�̈�̒��ɂ��邩�ǂ����`�F�b�N
	Vector3 p0_p1 = triangle.p1 - triangle.p0;
	Vector3 p0_p2 = triangle.p2 - triangle.p0;
	Vector3 p0_pt = point - triangle.p0;

	Vector3 V;
	float d1 = V.dot(p0_p1, p0_pt);
	float d2 = V.dot(p0_p2, p0_pt);

	if (d1 <= 0.0f && d2 <= 0.0f)
	{
		// p0���ŋߖT
		*closest = triangle.p0;
		return;
	}

	// point��p1�̊O���̒��_�̈�̒��ɂ��邩�ǂ����`�F�b�N
	Vector3 p1_pt = point - triangle.p1;

	float d3 = V.dot(p0_p1, p1_pt);
	float d4 = V.dot(p0_p2, p1_pt);

	if (d3 >= 0.0f && d4 <= d3)
	{
		// p1���ŋߖT
		*closest = triangle.p1;
		return;
	}

	// point��p0_p1�̕ӗ̈�̒��ɂ��邩�ǂ����`�F�b�N���A�����point��p0_p1��ɑ΂���ˉe��Ԃ�
	float vc = d1 * d4 - d3 * d2;
	if (vc <= 0.0f && d1 >= 0.0f && d3 <= 0.0f)
	{
		float v = d1 / (d1 - d3);
		*closest = triangle.p0 + v * p0_p1;
		return;
	}

	// point��p2�̊O���̒��_�̈�̒��ɂ��邩�ǂ����`�F�b�N
	Vector3 p2_pt = point - triangle.p2;

	float d5 = V.dot(p0_p1, p2_pt);
	float d6 = V.dot(p0_p2, p2_pt);
	if (d6 >= 0.0f && d5 <= d6)
	{
		*closest = triangle.p2;
		return;
	}

	// point��p0_p2�̕ӗ̈�̒��ɂ��邩�ǂ����`�F�b�N���A�����point��p0_p2��ɑ΂���ˉe��Ԃ�
	float vb = d5 * d2 - d1 * d6;
	if (vb <= 0.0f && d2 >= 0.0f && d6 <= 0.0f)
	{
		float w = d2 / (d2 - d6);
		*closest = triangle.p0 + w * p0_p2;
		return;
	}

	// point��p1_p2�̕ӗ̈�̒��ɂ��邩�ǂ����`�F�b�N���A�����point��p1_p2��ɑ΂���ˉe��Ԃ�
	float va = d3 * d6 - d5 * d4;
	if (va <= 0.0f && (d4 - d3) >= 0.0f && (d5 - d6) >= 0.0f)
	{
		float w = (d4 - d3) / ((d4 - d3) + (d5 - d6));
		*closest = triangle.p1 + w * (triangle.p2 - triangle.p1);
		return;
	}

	float denom = 1.0f / (va + vb + vc);
	float v = vb * denom;
	float w = vc * denom;
	*closest = triangle.p0 + p0_p1 * v + p0_p2 * w;
}

bool Collision::CheckSphere2Triangle(const Sphere& sphere, const Triangle& triangle, Vector3* inter, Vector3* reject)
{
	Vector3 p;
	// ���̒��S�ɑ΂���ŋߐړ_�ł���O�p�`��ɂ���_p��������
	ClosestPtPoint2Triangle(sphere.center, triangle, &p);

	// �_p�Ƌ��̒��S�̍����x�N�g��
	Vector3 v = p - sphere.center;
	Vector3 VV;
	// �����̓������߂�
	// �i�����x�N�g�����m�̓��ς͎O�����̒藝�̃��[�g�����̎��ƈ�v����j
	float vvv = VV.dot(v, v);

	// ���ƎO�p�`�̋��������a�ȉ��Ȃ瓖�����Ă��Ȃ�
	if (vvv > sphere.radius * sphere.radius)return false;

	// �^����_���v�Z
	if (inter) {
		// �O�p�`��̍ŋߐړ_p���^����_�Ƃ���
		*inter = p;
	}
	// �����o���x�N�g�����v�Z
	if (reject) {
		float ds = Vector3::dot(sphere.center, triangle.normal);
		float dt = Vector3::dot(triangle.p0, triangle.normal);
		float rejectLen = dt - ds + sphere.radius;
		*reject = triangle.normal * rejectLen;
	}
	return true;
}

bool Collision::CheckRay2Plane(const Ray& ray, const Plane& plane, float* distance, Vector3* inter)
{
	const float epsilon = 1.0e-5f; // �덷�z���p�̔����Ȓl
	// �ʖ@���g���C�̕����x�N�g���̓���
	Vector3 V;
	float d1 = V.dot(plane.normal, ray.dir);
	// ���ʂɂ͓�����Ȃ�
	if (d1 > -epsilon) { return false; }
	// �n�_�ƌ��_�̋����i���ʂ̖@�������j
	// �ʖ@���g���C�̎��_���W�i�ʒu�x�N�g���j�̓���
	float d2 = V.dot(plane.normal, ray.start);
	// �n�_�ƕ��ʂ̋����i���ʂ̖@�������j
	float dist = d2 - plane.distance;
	// �n�_�ƕ��ʂ̋����i���C�����j
	float t = dist / -d1;
	// ��_���n�_�����ɂ���̂ŁA������Ȃ�
	if (t < 0)return false;
	// ��������������
	if (distance) { *distance = t; }

	// ��_���v�Z
	if (inter) { *inter = ray.start + t * ray.dir; }

	return true;
}

bool Collision::CheckRay2Triangle(const Ray& ray, const Triangle& triangle, float* distance, Vector3* inter)
{
	// �O�p�`������Ă��镽�ʂ��Z�o
	Plane plane;
	Vector3 interPlane;
	Vector3 V;
	plane.normal = triangle.normal;
	plane.distance = V.dot(triangle.normal, triangle.p0);

	// ���C�ƕ��ʂ��������Ă��Ȃ���΁A�������Ă��Ȃ�
	if (!CheckRay2Plane(ray, plane, distance, &interPlane)) { return false; }

	// ���C�ƕ��ʂ��������Ă����̂ŁA�����ƌ�_���������܂ꂽ
	// ���C�ƕ��ʂ̌�_���O�p�`�̓����ɂ��邩����
	const float epsilon = 1.0e-5f;// �덷�z���p�̔����Ȓl
	Vector3 m;

	// ��p0_p1�ɂ���
	Vector3 pt_p0 = triangle.p0 - interPlane;
	Vector3 p0_p1 = triangle.p1 - triangle.p0;
	m = pt_p0.cross(p0_p1);

	// �ӂ̊O���ł���Γ������Ă��Ȃ��̂Ŕ����ł��؂�
	if (V.dot(m, triangle.normal) < -epsilon) { return false; }

	// ��p1_p2�ɂ���
	Vector3 pt_p1 = triangle.p1 - interPlane;
	Vector3 p1_p2 = triangle.p2 - triangle.p1;
	m = pt_p1.cross(p1_p2);

	// �ӂ̊O���ł���Γ������Ă��Ȃ��̂Ŕ����ł��؂�
	if (V.dot(m, triangle.normal) < -epsilon) { return false; }

	// ��p2_p0�ɂ���
	Vector3 pt_p2 = triangle.p2 - interPlane;
	Vector3 p2_p0 = triangle.p0 - triangle.p2;
	m = pt_p2.cross(p2_p0);

	// �ӂ̊O���ł���Γ������Ă��Ȃ��̂Ŕ����ł��؂�
	if (V.dot(m, triangle.normal) < -epsilon) { return false; }

	// �����Ȃ̂ŁA�������Ă���
	if (inter) {
		*inter = interPlane;
	}

	return true;
}

bool Collision::CheckRay2Sphere(const Ray& ray, const Sphere& sphere, float* distance, Vector3* inter)
{
	Vector3 m = ray.start - sphere.center;
	Vector3 V;
	float b = V.dot(m, ray.dir);
	float c = V.dot(m, m) - sphere.radius * sphere.radius;

	// ray�̎n�_��sphere�̊O���ɂ���(c>0)�Aray��sphere���痣��Ă��������������Ă���ꍇ(b>0)�A������Ȃ�
	if (c > 0.0f && b > 0.0f) { return false; }

	float discr = b * b - c;

	// ���̔��ʎ��͗Ⴊ�����O��Ă��邱�ƂɈ�v
	if (discr < 0.0f) { return false; }

	// ���C�͋��ƌ������Ă���
	// ��������ŏ��̒lt���v�Z
	float t = -b - sqrtf(discr);

	// �������ł���ꍇ�A���C�͋��̓�������J�n���Ă���̂ł����[���ɃN�����v
	if (t < 0)t = 0.0f;
	if (distance) { *distance = t; }

	if (inter) { *inter = ray.start + t * ray.dir; }

	return true;
}
