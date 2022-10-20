#include "DxLib.h"

#include "SceneTitle.h"
#include "SceneMain.h"
#include "SelectChara.h"


namespace
{
	// ��~�����V���b�g���ēx�ł��o���܂ł̎���
	constexpr int kSInterval = 15;
	// �^�C�g���̌�
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
	int TEffectsHandle1;// �I�����̃n���h��

	TEffectsHandle1 = LoadSoundMem("soundEffect/�I����.wav");

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

	// �����̈ړ�
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
	DrawString(m_textPosX, 0, "�L�����I�����", GetColor(255, 255, 255));
}