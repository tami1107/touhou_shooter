#include "ShotPlayerNormal.h"
#include "game.h"

#include "DxLib.h"
namespace
{
	constexpr float kShotSpeed = -18.0f;
}

void ShotPlayerNormal::start(Vec2 pos)
{
	ShotBase::start(pos);
	

	m_vec.x = 0;
	m_vec.y = kShotSpeed;
}

void ShotPlayerNormal::update()
{
	int PlayerNormal[2];

	if (!m_isExist)return;
	m_pos += m_vec;

	
	
	
	

	if (m_pos.y < 0)
	{
		m_isExist = false;
	}
}

void ShotPlayerNormal::draw()
{
	DrawGraphF(m_pos.x , m_pos.y, m_handle, true);
	
}