#pragma once

#include "ShotBase.h"

class ShotEnemyNormal : public ShotBase
{
public:
	// �e(�G�l�~�[)�O���t�B�b�N�T�C�Y
	static constexpr int kEnemyShot1GraphicSizeX = 8;
	static constexpr int kEnemyShot1GraphicSizeY = 14;
public:
	ShotEnemyNormal()
	{
	}
	virtual ~ShotEnemyNormal()
	{
	}

	void setHandle(int handle) { m_handle = handle; }

	//�V���b�g�J�n
	virtual void start(Vec2 pos);
	// �X�V
	virtual void update();

	void draw();
	// ���̎擾
	Vec2 getPos() const { return m_pos; }


};

