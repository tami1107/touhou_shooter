#pragma once
#include "SceneBase.h"

class SelectChara : public SceneBase
{
public:
	SelectChara()
	{
		int m_textPosX=0;
		int m_textVecX=0;
		m_isEnd = false;
	}
	virtual ~SelectChara() {}


	virtual void init() override;
	virtual void end() override {}

	virtual SceneBase* update() override;

	virtual void draw() override;

	virtual bool isEnd() { return m_isEnd; }
private:
	// テキスト表示位置変更
	int m_textPosX;
	int m_textVecX;

	int m_SInterval;


	bool m_isEnd;
};
