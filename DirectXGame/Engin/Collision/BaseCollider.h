#pragma once

#include "CollisionTypes.h"
#include "Object3d.h"
#include "CollisionInfo.h"

//�R���C�_�[���N���X
class BaseCollider
{
public:
	BaseCollider() = default;
	//���z�f�X�g���N�^
	virtual ~BaseCollider() = default;

	inline void SetObject(Object3d* object)
	{
		this->object3d = object;
		collname = object->GetName();
	}
	inline Object3d* GetObject3d()
	{
		return object3d;
	}
	void SetName(const char* name_) {
		this->collname = name_;
	}
	const char* GetName() {
		return collname;
	}

	//�X�V
	virtual void Update() = 0;

	//�`��^�C�v�擾
	inline CollisionShapeType GetShapeType()
	{
		return shapeType;
	}

	//�Փˎ��R�[���o�b�N�֐�
	inline void OnCollision(const CollisionInfo& info)
	{
		object3d->OnCollision(info);
	}

	//�Փˎ��R�[���o�b�N�֐�
	inline void OffCollision(const CollisionInfo& info)
	{
		object3d->OffCollision(info);
	}

protected:
	Object3d* object3d = nullptr;
	//�`��^�C�v
	CollisionShapeType shapeType = SHAPE_UNKNOWN;
	//�Փː�N���X��
	const char* collname = nullptr;
};