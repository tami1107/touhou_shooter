#pragma once
#include "SceneBase.h"

class SceneClear : public SceneBase
{
public:
	SceneClear()
	{

		
		m_isEnd = false;
	}
	virtual ~SceneClear() {}

	virtual void init() override;
	virtual void end() override {}

	virtual SceneBase* update() override;
	virtual void draw() override;

	virtual bool isEnd() { return m_isEnd; }
private:


	
	int m_MInterval;
	int m_GHandle1;
	int m_GHandle2;

	int m_font;

	bool m_isEnd;
};
