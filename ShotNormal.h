#pragma once

#include "ShotBase.h"

class ShotNormal : public ShotBase
{
public:
	ShotNormal()
	{
	}
	virtual ~ShotNormal()
	{
	}

	void setHandle(int handle) { m_handle = handle; }

	//ショット開始
	virtual void start(Vec2 pos);
	// 更新
	virtual void update();
	// 
	void draw();
	// 情報の取得
	Vec2 getPos() const { return m_pos; }
};