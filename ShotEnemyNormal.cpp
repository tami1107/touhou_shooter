#include "ShotEnemyNormal.h"
#include "game.h"
#include "Enemy.h"
#include "DxLib.h"

namespace
{
	// エネミーの弾速
	constexpr float kShotSpeed = 5.0f;

	// 敵グラフィックサイズ
	static constexpr int kEnemyGraphicSizeX = Enemy::kEnemyGraphicSizeX;
	static constexpr int kEnemyGraphicSizeY = Enemy::kEnemyGraphicSizeY;
}




void ShotEnemyNormal::start(Vec2 pos)
{
	ShotBase::start(pos);

	// ショットを画像の中心位置にもっていく
	m_pos.x = pos.x + (kEnemyGraphicSizeX / 2) - (kEnemyShot1GraphicSizeX / 2);
	m_pos.y = pos.y + (kEnemyGraphicSizeY / 2) - (kEnemyShot1GraphicSizeY / 2);

	angle = 0;
	time = 0;

	angle = GetRand(DX_PI * 2);        //0～PI*2の乱数を生成
	//speed = 0.5f + GetRand(10000) / 10000.f * 2;      //0.5～2.5の乱数を生成
	
}

void ShotEnemyNormal::update()
{
	if (!m_isExist)return;

	

	


	

	m_pos.x -= cos(angle);      // x座標を更新
	m_pos.y -= sin(angle);      // y座標を更新
	


	if (m_pos.y > Game::kScreenHeight)
	{
		m_isExist = false;
	}
}

void ShotEnemyNormal::draw()
{
	DrawGraphF(m_pos.x, m_pos.y, m_handle, TRUE);//弾を描画
	
	//DrawGraphF(m_pos.x, m_pos.y, m_handle, true);

}