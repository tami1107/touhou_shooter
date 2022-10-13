#pragma once
#include "SceneBase.h"
#include"Player.h"

class SceneMain : public SceneBase
{
public:
	SceneMain()
	{
		m_SelectNum = 0;

		m_isEnd = false;
	}
	virtual ~SceneMain() {}


	virtual void init() override;
	virtual void end() override {}

	virtual SceneBase* update() override;

	virtual void draw() override;

	virtual bool isEnd() { return m_isEnd; }
private:
	// �e�L�X�g�\���ʒu�ύX
	int m_SelectNum;
	int m_Interval;

	// �v���C���[
	Player m_player;

	bool m_isEnd;
};