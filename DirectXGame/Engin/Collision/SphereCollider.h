#pragma once
#include "BaseCollider.h"
#include "CollisionPrimitive.h"

#include "Vector3.h"
#include "Matrix4.h"


class SphereCollider :public BaseCollider, public Sphere
{
private:// �G�C���A�X
public:
	SphereCollider(Vector3 offset = { 0,0,0 }, float radius = 1.0f) :offset(offset), radius(radius) {
		// ���`����Z�b�g
		shapeType = COLLISIONSHAPE_SPHERE;
	}

	// �X�V
	void Update()override;

	inline const Vector3& GetOffset() { return offset; }

	inline void SetOffset(const Vector3& offset) { this->offset = offset; }

	inline float GetRadius() { return radius; }

	inline void SetRadius(float radius) { this->radius = radius; }

private:
	// �I�u�W�F�N�g���S����̃I�t�Z�b�g
	Vector3 offset;
	// ���a
	float radius;
};