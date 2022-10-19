#pragma once

#include "Vec2.h"

class SceneMain;

class Enemy
{
public:
	// �G�O���t�B�b�N������
	static constexpr int kEnemyGraphicDivX = 6;
	static constexpr int kEnemyGraphicDivY = 1;
	static constexpr int kEnemyGraphicDivNum = kEnemyGraphicDivX * kEnemyGraphicDivY;

	// �G�O���t�B�b�N�T�C�Y
	static constexpr int kEnemyGraphicSizeX = 140;
	static constexpr int kEnemyGraphicSizeY = 210;


public:
	Enemy();
	virtual ~Enemy();

	// �O���t�B�b�N�f�[�^�ݒ�
	void setHandle(int index, int handle) { m_handle[index] = handle; }
	void setEnemyHP(int EnemyHP) { m_EnemyHP = EnemyHP; }

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
	int m_handle[kEnemyGraphicDivNum];

	int m_EnemyHP;

	//SceneMain�̃|�C���^
	SceneMain* m_pMain;

	// �\���ʒu
	Vec2 m_pos;
	// �ړ�
	Vec2 m_vec;

	// �V���b�g�̃C���^�[�o��
	int m_shotInterval;
	
	// �L�����N�^�[�̃A�j���[�V����
	int m_animeNo;	// �\������ԍ�
	int m_animeFrame;
	int m_dirNo;
};
