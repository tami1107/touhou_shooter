#pragma once

#include "ShotBase.h"

class ShotEnemyNormal : public ShotBase
{
public:
	// 弾(エネミー)グラフィックサイズ
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

	//ショット開始
	virtual void start(Vec2 pos);
	// 更新
	virtual void update();

	void draw();
	// 情報の取得
	Vec2 getPos() const { return m_pos; }

	int angle;
	int speed;
	int time;

};

