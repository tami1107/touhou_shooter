#pragma once
#include "SceneBase.h"

class Player : public SceneBase
{
public:
	Player()
	{
		m_SelectNum = 0;

		m_isEnd = false;
	}
	virtual ~Player() {}


	virtual void init() override;
	virtual void end() override {}

	virtual SceneBase* update() override;

	virtual void draw() override;

	virtual bool isEnd() { return m_isEnd; }
private:
	// テキスト表示位置変更
	int m_SelectNum;
	int m_Interval;
	// グラフィックハンドル
	int m_handle;

	bool m_isEnd;
};