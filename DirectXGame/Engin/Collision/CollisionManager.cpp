#include "CollisionManager.h"
#include "BaseCollider.h"
#include "Collision.h"

using namespace DirectX;

CollisionManager* CollisionManager::GetInstance()
{
	static CollisionManager instance;
	return &instance;
}

void CollisionManager::CheckAllCollisions()
{
	std::forward_list<BaseCollider*>::iterator itA;
	std::forward_list<BaseCollider*>::iterator itB;

	//�S�Ă̑g�ݍ��킹�ɂ��đ�������`�F�b�N
	itA = colliders.begin();
	for (; itA != colliders.end(); ++itA)
	{
		itB = itA;
		++itB;
		for (; itB != colliders.end(); ++itB)
		{
			BaseCollider* colA = *itA;
    		BaseCollider* colB = *itB;
			//�Փˑ�����L��
			colA->GetObject3d()->toCollisionName = colB->GetName();
			colB->GetObject3d()->toCollisionName = colA->GetName();
			

			// �Ƃ��ɋ�
			if (colA->GetShapeType() == COLLISIONSHAPE_SPHERE &&
				colB->GetShapeType() == COLLISIONSHAPE_SPHERE) {
				Sphere* SphereA = dynamic_cast<Sphere*>(colA);
				Sphere* SphereB = dynamic_cast<Sphere*>(colB);
				Vector3 inter;
				Vector3 reject;
				if (Collision::CheckSphere2Sphere(*SphereA, *SphereB, &inter,&reject)) {
					colA->OnCollision(CollisionInfo(colB->GetObject3d(), colB, inter));
					colB->OnCollision(CollisionInfo(colA->GetObject3d(), colA, inter));
				}
				/*else
				{
					colA->OffCollision(CollisionInfo(colB->GetObject3d(), colB, inter));
					colB->OffCollision(CollisionInfo(colA->GetObject3d(), colA, inter));
				}*/
			}
		}
	}
}

bool CollisionManager::Raycast(const Ray& ray, RaycastHit* hitInfo, float maxDistance)
{
	bool result = false;
	//�����p�̃C�e���[�^
	std::forward_list<BaseCollider*>::iterator it;
	//���܂łōł��߂��R���C�_�[���L�^���邽�߂̃C�e���[�^
	std::forward_list<BaseCollider*>::iterator it_hit;
	//���܂łōł��߂��R���C�_�[�̋������L�^����ϐ�
	float distance = maxDistance;
	//���܂łōł��߂��R���C�_�[�Ƃ̌�_���L�^����ϐ�
	Vector3 inter;

	//�S�ẴR���C�_�[�Ƒ�������`�F�b�N
	it = colliders.begin();
	for (; it != colliders.end(); ++it)
	{
		BaseCollider* colA = *it;
		//���̏ꍇ
		if (colA->GetShapeType() == COLLISIONSHAPE_SPHERE)
		{
			Sphere* sphere = dynamic_cast<Sphere*>(colA);
			float tempDistance;
			Vector3 tempInter;
			//������Ȃ���Ώ��O
			if (!Collision::CheckRay2Sphere(ray, *sphere, &tempDistance, &tempInter))continue;
			//�������ŏ��o�Ȃ���Ώ��O
			if (tempDistance >= distance)continue;
			//���܂łōł��߂��̂ŋL�^���Ƃ�
			result = true;
			distance = tempDistance;
			inter = tempInter;
			it_hit = it;
			//�ŏI�I�ɉ����ɓ������Ă����猋�ʂ���������
			if (result && hitInfo)
			{
				hitInfo->distance = distance;
				hitInfo->inter = inter;
				hitInfo->collider = *it_hit;
				hitInfo->object = hitInfo->collider->GetObject3d();
			}
			return result;
		}
	}

}