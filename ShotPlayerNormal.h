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

	//�V���b�g�J�n
	virtual void start(Vec2 pos);
	// �X�V
	virtual void update();


};
