#include "DxLib.h"
#include <cassert>
#include "game.h"
#include "Enemy.h"

#include "SceneMain.h"

namespace
{
	// �L�����N�^�[�A�j���[�V�����̑��x
	int kAnimeChangeFrame = 6;
	// X�����AY�����̑��x
	constexpr float kSpeed = 4;
	// �V���b�g�̔��ˊԊu
	constexpr float kShotInterval = 8.0f;
	// ��ʒ[
	constexpr int kLeft = 15;
	constexpr int kRight = 450;

}

Enemy::Enemy()
{
	for (auto& handle : m_handle)
	{
		 handle = -1;
	}
	
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
	
	//�V���b�g��������
	m_shotInterval--;
	if (m_shotInterval < 0)m_shotInterval = 0;

	if (m_shotInterval <= 0)
	{
		
		if (m_pMain->createShotEnemyNormal(getPos()))
		{
			m_shotInterval = kShotInterval;
		}
		
	
	}

	
	
		if (m_pos.x < kLeft)
		{
			m_vec.x *= -1;
		
		}
		if (m_pos.x > kRight)
		{
			m_vec.x *= -1;
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
	//�G��HP��\��(�f�o�b�O)
	DrawFormatString(100, 100, GetColor(255, 255, 255), "HP:%d", m_EnemyHP);
	
}