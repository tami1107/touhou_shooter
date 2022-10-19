#include "ShotNormal.h"
#include "game.h"
#include "DxLib.h"


namespace
{
	constexpr float kShotSpeed = 8.0f;
}

void ShotNormal::start(Vec2 pos)
{
	ShotBase::start(pos);

	m_vec.x = 0;
	m_vec.y = kShotSpeed;
}

void ShotNormal::update()
{
	if (!m_isExist)return;
	m_pos += m_vec;

	if (m_pos.y > Game::kScreenHeight)
	{
		m_isExist = false;
	}
}

// •\Ž¦
void ShotNormal::draw()
{
	
	DrawGraphF(m_pos.x, m_pos.y, m_handle, true);


}