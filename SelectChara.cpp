#include "DxLib.h"

#include "SceneTitle.h"
#include "SceneMain.h"
#include "SelectChara.h"


namespace
{
	// 停止したショットを再度打ち出すまでの時間
	constexpr int kSInterval = 15;
	// タイトルの個数
	constexpr int kTitle = 5;


}



void SelectChara::init()
{
	m_textPosX = 0;
	m_textVecX = 4;
}

SceneBase* SelectChara::update()
{
	int padState = GetJoypadInputState(DX_INPUT_KEY_PAD1);
	int TEffectsHandle1;// 選択音のハンドル

	TEffectsHandle1 = LoadSoundMem("soundEffect/選択音.wav");

	m_SInterval--;
	if (m_SInterval < 0) m_SInterval = 0;

	if (m_SInterval <= 0)
	{
		if ((padState & PAD_INPUT_3) && (m_SInterval <= 0))
		{
			PlaySoundMem(TEffectsHandle1, DX_PLAYTYPE_BACK);
			return(new SceneMain);
			m_SInterval = kSInterval;
			
		}
	}

	// 文字の移動
	m_textPosX += m_textVecX;
	if (m_textPosX < 0)
	{
		m_textPosX = 0;
		m_textVecX = 4;
	}
	if (m_textPosX > 300)
	{
		m_textPosX = 300;
		m_textVecX = -4;
	}

	
	if (padState & PAD_INPUT_2)
	{
		PlaySoundFile("sound/cursor1.mp3", DX_PLAYTYPE_BACK);
	}
	
	

	return this;
}

void SelectChara::draw()
{
	DrawString(m_textPosX, 0, "キャラ選択画面", GetColor(255, 255, 255));
}