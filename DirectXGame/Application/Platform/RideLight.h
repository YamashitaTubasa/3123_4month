#pragma once

#include "RLFramework.h"

// �Q�[���S��
class RideLight : public RLFramework
{
public:
	// ������
	void Initialize() override;

	// �X�V
	void Update() override;

	// �`��
	void Draw() override;

	// �I��
	void Finalize() override;

};
