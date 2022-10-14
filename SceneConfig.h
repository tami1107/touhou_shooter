#pragma once
#include "SceneBase.h"

class SceneConfig : public SceneBase
{
public:
	SceneConfig()
	{

		m_SoundSelect = 0;
		m_isEnd = false;
	}
	virtual ~SceneConfig() {}

	virtual void init() override;
	virtual void end() override {}

	virtual SceneBase* update() override;
	virtual void draw() override;

	virtual bool isEnd() { return m_isEnd; }
private:


	int m_SoundSelect;
	int m_MInterval;
	int m_GHandle1;
	int m_GHandle2;

	

	bool m_isEnd;
};
