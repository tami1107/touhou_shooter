#pragma once

#include "ShotBase.h"

class SceneMain;

class ShotPlayerNormal : public ShotBase
{
public:

	// 弾グラフィックサイズ
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
	void setEnemyHit(int EnemyHIt) { m_EnemyHIt = EnemyHIt; }

	

	//ショット開始
	virtual void start(Vec2 pos);
	// 更新
	virtual void update();

	void draw();
	// 情報の取得
	Vec2 getPos() const { return m_pos; }

	int m_EnemyHIt;
};
