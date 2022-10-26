#pragma once
#include "SceneBase.h"

class SceneGameOver : public SceneBase
{
public:
	SceneGameOver()
	{
		m_SelectNum = 0;

		m_isEnd = false;
	}
	virtual ~SceneGameOver() {}




	virtual void init() override;
	virtual void end() override {}

	virtual SceneBase* update() override;

	virtual void draw() override;

	virtual bool isEnd() { return m_isEnd; }
private:
	// テキスト表示位置変更
	int m_SelectNum;
	int m_Interval;
	int m_slide;

	int m_TitleframeHandle;

	int m_BgmHandle1;

	int m_font;

	bool m_isEnd;
};