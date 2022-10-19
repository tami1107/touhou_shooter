#include "DxLib.h"
#include <cassert>
#include "game.h"
#include "Enemy.h"

#include "SceneMain.h"

namespace
{
	// キャラクターアニメーションの速度
	int kAnimeChangeFrame = 6;
	// X方向、Y方向の速度
	constexpr float kSpeed = 4;
	//ショットの発射間隔
	constexpr float kShotInterval = 8.0f;

}

Enemy::Enemy()
{
	for (auto& handle : m_handle)
	{
		 handle = -1;
	}
	//m_handle = 1;
	m_pMain = nullptr;
	m_shotInterval = 0;
}

Enemy::~Enemy()
{

}

void Enemy::init()
{
	m_pos.x = Game::kScreenWidth / 2 - kEnemyGraphicSizeX / 2;
	m_pos.y = 0;
	m_vec.x = kSpeed;
	m_vec.y = kSpeed;
	m_shotInterval = 0;
	


}

void Enemy::update()
{
	
	//ショットを撃つ処理
	m_shotInterval--;
	if (m_shotInterval < 0)m_shotInterval = 0;

	if (m_shotInterval <= 0)
	{
		
		if (m_pMain->createShotEnemyNormal(getPos()))
		{
			m_shotInterval = kShotInterval;
		}
		
	
	}

	if (m_EnemyHP > 0)
	{
		if (m_pos.x < 0)
		{
			m_vec.x *= -1;
		
		}
		if (m_pos.x > Game::kScreenWidth - kEnemyGraphicSizeX)
		{
			m_vec.x *= -1;
		}
	}
	else if(m_EnemyHP < 0)
	{
		m_vec.x = 0;
	}
	
	

	
	

	m_pos.x += m_vec.x;

	m_animeFrame++;
	if (m_animeFrame >= kEnemyGraphicDivX * kAnimeChangeFrame)
	{
		m_animeFrame = 0;
	}

	int tempAnimeNo = m_animeFrame / kAnimeChangeFrame;
	m_animeNo = m_dirNo + tempAnimeNo;

	

	m_dirNo = 0;
}

void Enemy::draw()
{
	DrawGraph(static_cast<int>(m_pos.x), static_cast<int>(m_pos.y), m_handle[m_animeNo], true);
	//敵のHPを表示
	DrawFormatString(0, 0, GetColor(255, 255, 255), "HP:%d", m_EnemyHP);
}