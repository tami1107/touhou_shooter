#include "DxLib.h"
#include "SceneMain.h"
#include "SceneTitle.h"
#include "SceneGameOver.h"

namespace
{
	// �^�C�g���̌�
	constexpr int kTitle = 2;
}

// ���j���[���ڂ̕\���ɕK�v�ȍ\���̂�p�ӂ���
typedef struct {
	int x, y;       // ���W�i�[�p�ϐ�
	char name[128]; // ���ږ��i�[�p�ϐ�
	int Cr;			// �J���[�p�ϐ�
} MenuElement;

// ���j���[���ڗv�f��5���
MenuElement MenuElement_o[kTitle] = {
	// �^�O�̒��g�̏��ԂŊi�[�����B
	// (��) { x , y , "neme" , GetColor(255, 255, 255)}
	{ 480, 100, "���g���C" , GetColor(255, 0, 0)},
	{ 470, 170, "�^�C�g���ɖ߂�", GetColor(255, 255, 255)},
};


void SceneGameOver::init()
{
	m_SelectNum = 0; // ���݂̑I��ԍ�
	m_Interval = kTInterval;



	m_font = CreateFontToHandle("�l�r �S�V�b�N", 30, 9, DX_FONTTYPE_NORMAL);


	m_isEnd = false;
}


SceneBase* SceneGameOver::update()
{


	m_EffectsHandle1 = LoadSoundMem("soundEffect/�I����.wav");
	m_EffectsHandle2 = LoadSoundMem("soundEffect/���艹.wav");
	

	int padState = GetJoypadInputState(DX_INPUT_KEY_PAD1);


	// �v�Z�t�F�[�Y 
	m_Interval--;
	if (m_Interval < 0) m_Interval = 0;

	if (m_Interval <= 0)
	{
		if ((padState & PAD_INPUT_DOWN) && (m_Interval <= 0))
		{
			m_SelectNum = (m_SelectNum + 1) % kTitle; // ���݂̑I�����ڂ�����ɂ��炷(���[�v����)
			PlaySoundMem(m_EffectsHandle1, DX_PLAYTYPE_BACK);

			m_Interval = kTInterval;
		}
		if ((padState & PAD_INPUT_UP) && (m_Interval <= 0))
		{
			m_SelectNum = (m_SelectNum + (kTitle - 1)) % kTitle; // ���݂̑I�����ڂ����ɂ��炷(�t���[�v����)
			PlaySoundMem(m_EffectsHandle1, DX_PLAYTYPE_BACK);

			m_Interval = kTInterval;
		}
		if ((padState & PAD_INPUT_3) && (m_Interval <= 0))
		{
			PlaySoundMem(m_EffectsHandle2, DX_PLAYTYPE_BACK);
			// m_SelectNum = 0�̂Ƃ��A3�{�^���������ꂽ��SceneMain�ɃV�[�����ڍs����
			if (m_SelectNum == 0)
			{
				StopSoundMem(m_BgmHandle1);
				// SelectChara�ɐ؂�ւ�
				return(new SceneMain);
			}
			// m_SelectNum = 1�̂Ƃ��A3�{�^���������ꂽ��SceneTitle�ɃV�[�����ڍs����
			if (m_SelectNum == 1)
			{
				StopSoundMem(m_BgmHandle1);
				// Title�ɐ؂�ւ�
				return(new SceneTitle);
			}

			m_Interval = kTInterval;
		}
	
	}


	if ((padState & PAD_INPUT_DOWN) || (padState & PAD_INPUT_UP) )
	{
		for (int i = 0; i < kTitle; i++)
		{
			// ���j���[���ڐ��ł���5���[�v����
			m_slide = i * 10;

			if (i == m_SelectNum) {          // ���������Ă���̂��A�I��ԍ��Ɠ����v�f�Ȃ�
				MenuElement_o[i].x = (460 - m_slide); // ���W��80�ɂ���
				MenuElement_o[i].Cr = GetColor(255, 0, 0);
			}
			else {                       // ���������Ă���̂��A�I��ԍ��ȊO�Ȃ�
				MenuElement_o[i].x = 480 - m_slide;// ���W��100�ɂ���
				MenuElement_o[i].Cr = GetColor(255, 255, 255);
			}
		}
	}

	return this;
}

void SceneGameOver::draw()
{


	for (int i = 0; i < 5; i++)
	{
		DrawFormatStringToHandle(MenuElement_o[i].x, MenuElement_o[i].y, MenuElement_o[i].Cr, m_font, MenuElement_o[i].name);
		// �f�o�b�O�p
		//DrawFormatString(0, 0, GetColor(255, 255, 255), "%d", m_SelectNum);
	}
	
}