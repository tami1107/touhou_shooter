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

	//ショット開始
	virtual void start(Vec2 pos);
	// 更新
	virtual void update();


};
