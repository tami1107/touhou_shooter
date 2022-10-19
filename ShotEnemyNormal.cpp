#include "ShotEnemyNormal.h"
#include "game.h"

#include "DxLib.h"

#define BOSS_SHOT_MAX 10

struct BOSS_SHOT {
	double first_x;
	double first_y;
	double x[300];
	double y[300];
	double draw_x[300];
	double draw_y[300];
	double angle[300];
	double angle2[300];
	double var[300];
	int init_flag;
	int move_flag;
	int move_type;
	int max_bullet;
	int gamecount_point[5];
	double range;
	int boss_num;
};

struct BOSS_SHOT boss_shot[BOSS_SHOT_MAX];

namespace
{
	constexpr float kShotSpeed = 10.0f;
}




void ShotEnemyNormal::start(Vec2 pos)
{
	ShotBase::start(pos);

	

	m_vec.x = 0;
	m_vec.y = kShotSpeed;
}

void ShotEnemyNormal::update()
{
	if (!m_isExist)return;



	m_pos += m_vec;

	if (m_pos.y > Game::kScreenHeight)
	{
		m_isExist = false;
	}
}

void ShotEnemyNormal::draw()
{
	DrawGraphF(m_pos.x, m_pos.y, m_handle, true);

}