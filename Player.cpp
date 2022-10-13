#include "DxLib.h"

#include "game.h"
#include"Player.h"


void Player::init()
{
	m_handle = -1;

	m_isEnd = false;
}


SceneBase* Player::update()
{


	return this;
}

void Player::draw()
{
	DrawFormatString(0, 0, GetColor(255, 255, 255), "player");

}