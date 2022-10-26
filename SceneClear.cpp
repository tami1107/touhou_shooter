#include "DxLib.h"
#include "SceneMain.h"
#include "SceneClear.h"
#include "SceneTitle.h"
#include "game.h"

namespace
{

}


void SceneClear::init()
{

	m_font = CreateFontToHandle("ÇlÇr ÉSÉVÉbÉN", 30, 9, DX_FONTTYPE_NORMAL);
	m_MInterval = kTInterval;
	m_isEnd = false;
}

SceneBase* SceneClear::update()
{

	

	int padState = 0;

	padState = GetJoypadInputState(DX_INPUT_KEY_PAD1);

	m_MInterval--;
	if (m_MInterval < 0) m_MInterval = 0;

	if (m_MInterval <= 0)
	{

		if ((padState & PAD_INPUT_3) && (m_MInterval <= 0))
		{
			// TitleÇ…êÿÇËë÷Ç¶
			return(new SceneTitle);
			m_MInterval = kTInterval;
		}

	}

	
	
	return this;
}

void SceneClear::draw()
{

	DrawStringToHandle(Game::kScreenWidth / 2, Game::kScreenHeight / 2, "GameClear!!",
		GetColor(255, 0, 0), m_font);
}