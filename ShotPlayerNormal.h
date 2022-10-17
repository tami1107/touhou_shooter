#pragma once

#include "ShotBase.h"

class ShotPlayerNormal : public ShotBase
{
public:
	ShotPlayerNormal()
	{
	}
	virtual ~ShotPlayerNormal()
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
