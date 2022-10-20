#include "DxLib.h"

#include "SceneTitle.h"
#include "SelectChara.h"
#include "SceneMusic.h"
#include "SceneMain.h"
#include "SceneManager.h"
#include "SceneConfig.h"

namespace
{
	// �^�C�g���̌�
	constexpr int kTitle = 5;
}

// ���j���[���ڂ̕\���ɕK�v�ȍ\���̂�p�ӂ���
typedef struct {
	int x, y;       // ���W�i�[�p�ϐ�
	char name[128]; // ���ږ��i�[�p�ϐ�
	int Cr;			// �J���[�p�ϐ�
} MenuElement_t;

// ���j���[���ڗv�f��5���
MenuElement_t MenuElement[kTitle] = {
	// �^�O�̒��g�̏��ԂŊi�[�����B
	// (��) { x , y , "neme" , GetColor(255, 255, 255)}
	{ 480, 100, "�Q�[���X�^�[�g" , GetColor(255, 0, 0)},
	{ 470, 170, "MusicRoom", GetColor(255, 255, 255)},
	{ 460, 240, "�w���v", GetColor(255, 255, 255)},
	{ 450, 310, "Config", GetColor(255, 255, 255)},
	{ 440, 380, "�Q�[���I��", GetColor(255, 255, 255)},
};


void SceneTitle::init()
{
	m_SelectNum = 0; // ���݂̑I��ԍ�
	m_Interval = kTInterval;

	m_BgmHandle1= LoadSoundMem("soundBgm/�Ԃ��g����.wav");
	
	m_TitleframeHandle = LoadGraph("image/�^�C�g��������.jpeg");

	PlaySoundMem(m_BgmHandle1, DX_PLAYTYPE_BACK);

	m_font = CreateFontToHandle("�l�r �S�V�b�N", 30, 9, DX_FONTTYPE_NORMAL);
	

	m_isEnd = false;
}


SceneBase* SceneTitle::update()
{
	

	m_EffectsHandle1 = LoadSoundMem("soundEffect/�I����.wav");
	m_EffectsHandle2 = LoadSoundMem("soundEffect/���艹.wav");
	m_EffectsHandle3 = LoadSoundMem("soundEffect/�L�����Z����.wav");

	int padState = GetJoypadInputState( DX_INPUT_KEY_PAD1 ) ;


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
			 m_SelectNum = (m_SelectNum + (kTitle-1)) % kTitle; // ���݂̑I�����ڂ����ɂ��炷(�t���[�v����)
			 PlaySoundMem(m_EffectsHandle1, DX_PLAYTYPE_BACK);
			
			 m_Interval = kTInterval;
		 }
		 if ((padState & PAD_INPUT_3) && (m_Interval <= 0))
		 {
			 PlaySoundMem(m_EffectsHandle2, DX_PLAYTYPE_BACK);
			 // m_SelectNum = 0�̂Ƃ��A3�{�^���������ꂽ��SelectChara�ɃV�[�����ڍs����
			 if (m_SelectNum == 0)
			 {
				 StopSoundMem(m_BgmHandle1);
			  // SelectChara�ɐ؂�ւ�
				 return(new SelectChara);
			 }
			 // m_SelectNum = 1�̂Ƃ��A3�{�^���������ꂽ��SceneMusic�ɃV�[�����ڍs����
			 if (m_SelectNum == 1)
			 {
				StopSoundMem(m_BgmHandle1);
				// Music�ɐ؂�ւ�
				return(new SceneMusic);
			 }
			 // m_SelectNum = 3�̂Ƃ��A3�{�^���������ꂽ��SceneConfig�ɃV�[�����ڍs����
			 if (m_SelectNum == 3)
			 {
				 StopSoundMem(m_BgmHandle1);
				 // SceneConfig�ɐ؂�ւ�
				 return(new SceneConfig);
			 }
			 // m_SelectNum = 4�̂Ƃ��A3�{�^���������ꂽ��Q�[�����I������
			 if (m_SelectNum == 4)
			 {
				// �Q�[���I��
				 DxLib_End();
			 }

			 m_Interval = kTInterval;
		 }
		 // 2�{�^�����������Ƃ��Am_SelectNum�������I��4�ɂ���
		 if ((padState & PAD_INPUT_2) && (m_Interval <= 0))
		 {
			 m_SelectNum = 4;

			 PlaySoundMem(m_EffectsHandle3, DX_PLAYTYPE_BACK);
			 m_Interval = kTInterval;
		 }
	 }


	 if ((padState & PAD_INPUT_DOWN) || (padState & PAD_INPUT_UP) || (padState & PAD_INPUT_2))
	 {
		 for (int i = 0; i < kTitle; i++)
		 {   
			 // ���j���[���ڐ��ł���5���[�v����
			 m_slide = i * 10;
			
			 if (i == m_SelectNum) {          // ���������Ă���̂��A�I��ԍ��Ɠ����v�f�Ȃ�
				 MenuElement[i].x = (460 - m_slide); // ���W��80�ɂ���
				 MenuElement[i].Cr = GetColor(255, 0, 0);
			 }
			 else {                       // ���������Ă���̂��A�I��ԍ��ȊO�Ȃ�
				 MenuElement[i].x = 480- m_slide;// ���W��100�ɂ���
				 MenuElement[i].Cr = GetColor(255, 255, 255);
			 }
		 }
	 }

	return this;
}

void SceneTitle::draw()
{
	// �t���[��(�g)�`��
	DrawGraph(0, 0, m_TitleframeHandle, TRUE);

	for (int i = 0; i < 5; i++) 
	{   
		DrawFormatStringToHandle(MenuElement[i].x, MenuElement[i].y, MenuElement[i].Cr, m_font, MenuElement[i].name);
		// �f�o�b�O�p
		//DrawFormatString(0, 0, GetColor(255, 255, 255), "%d", m_SelectNum);
	}
	DrawString(0, 0, "�����őI���AB�{�^���Ō���AA�{�^���ŃL�����Z��", GetColor(255, 255, 255));
}