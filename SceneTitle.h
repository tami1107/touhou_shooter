#pragma once
#include "SceneBase.h"

class SceneTitle : public SceneBase
{
public:
	SceneTitle()
	{
		m_SelectNum = 0;
		
		m_isEnd = false;
	}
	virtual ~SceneTitle() {}
	
	


	virtual void init() override;
	virtual void end() override {}

	virtual SceneBase* update() override;

	virtual void draw() override;

	virtual bool isEnd() { return m_isEnd; }
private:
	// �e�L�X�g�\���ʒu�ύX
	int m_SelectNum;
	int m_Interval;
	int m_slide;
	

	int m_BgmHandle1;

	bool m_isEnd;
};