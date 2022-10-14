#pragma once

#include "Vec2.h"

class SceneMain;

class Enemy
{
public:
	// �G�O���t�B�b�N�T�C�Y
	static constexpr int kEnemyGraphicSizeX = 64;
	static constexpr int kEnemyGraphicSizeY = 80;
public:
	Enemy();
	virtual ~Enemy();

	// �O���t�B�b�N�f�[�^�ݒ�
	void setHandle(int handle) { m_handle = handle; }

	// �v���C���[�̏�����
	void init();

	//SceneMain�N���X�̃|�C���^�ݒ�
	void setMain(SceneMain* pMain) { m_pMain = pMain; }

	// ����
	void update();
	// �`��
	void draw();

	// ���̎擾
	Vec2 getPos() const { return m_pos; }

private:
	int m_handle;

	//SceneMain�̃|�C���^
	SceneMain* m_pMain;

	// �\���ʒu
	Vec2 m_pos;
	// �ړ�
	Vec2 m_vec;

	int m_shotInterval;
	int m_waitFrame;
};
