#include "DxLib.h"

#include "game.h"
#include"SceneMain.h"


void SceneMain::init()
{
	

	m_isEnd = false;
}


SceneBase* SceneMain::update()
{
	

	return this;
}

void SceneMain::draw()
{
	m_player.draw();

}