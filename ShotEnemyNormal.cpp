#include "ShotEnemyNormal.h"
#include "game.h"
#include "Enemy.h"
#include "DxLib.h"

namespace
{
	// �G�l�~�[�̒e��
	constexpr float kShotSpeed = 10.0f;

	// �G�O���t�B�b�N�T�C�Y
	static constexpr int kEnemyGraphicSizeX = Enemy::kEnemyGraphicSizeX;
	static constexpr int kEnemyGraphicSizeY = Enemy::kEnemyGraphicSizeY;
}




void ShotEnemyNormal::start(Vec2 pos)
{
	ShotBase::start(pos);

	// �V���b�g���摜�̒��S�ʒu�ɂ����Ă���
	m_pos.x = pos.x + (kEnemyGraphicSizeX / 2) - (kEnemyShot1GraphicSizeX / 2);
	m_pos.y = pos.y + (kEnemyGraphicSizeY / 2) - (kEnemyShot1GraphicSizeY / 2);

	angle = 0;
	time = 0;

	
	//m_vec.x = kShotSpeed;
	//m_vec.y = kShotSpeed;
}

void ShotEnemyNormal::update()
{
	if (!m_isExist)return;

	

	

	time++;
	if (time == 10)
	{
		angle = GetRand(360) / 360.f * (DX_PI * 2);        //0�`PI*2�̗����𐶐�
		//speed = 0.5f + GetRand(10000) / 10000.f * 2;      //0.5�`2.5�̗����𐶐�
		time = 0;
	}
	
	m_pos.x += cos(angle);      // x���W���X�V
	m_pos.y -= sin(angle) * kShotSpeed;      // y���W���X�V
	

	if (m_pos.y > Game::kScreenHeight)
	{
		m_isExist = false;
	}
}

void ShotEnemyNormal::draw()
{
	DrawGraphF(m_pos.x, m_pos.y, m_handle, TRUE);//�e��`��
	
	//DrawGraphF(m_pos.x, m_pos.y, m_handle, true);

}