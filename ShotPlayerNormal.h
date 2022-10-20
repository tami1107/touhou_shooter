#pragma once

#include "ShotBase.h"

class SceneMain;

class ShotPlayerNormal : public ShotBase
{
public:

	// �e�O���t�B�b�N�T�C�Y
	static constexpr int kPlayerShot1GraphicSizeX = 16;
	static constexpr int kPlayerShot1GraphicSizeY = 36;

public:
	ShotPlayerNormal()
	{
	}
	virtual ~ShotPlayerNormal()
	{
	}

	void setHandle(int handle) { m_handle = handle; }
	void setEnemyHit(int EnemyHit) { m_EnemyHit = EnemyHit; }

	

	//�V���b�g�J�n
	virtual void start(Vec2 pos);
	// �X�V
	virtual void update();

	void draw();
	// ���̎擾
	Vec2 getPos() const { return m_pos; }

	int m_EnemyHit;
	
	
};
