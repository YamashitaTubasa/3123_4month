#pragma once

//========================//
// �Q�[���V�[�����N���X
//========================//
class GameBaseScene
{
public:
	virtual ~GameBaseScene() = default;

public:
	// ������
	virtual void Initialize() = 0;

	// �X�V
	virtual void Update() = 0;

	// �`��
	virtual void Draw() = 0;

	// ���
	virtual void Finalize() = 0;
};
