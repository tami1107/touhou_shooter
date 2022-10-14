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
	{ 380, 100, "�Q�[���X�^�[�g" , GetColor(255, 0, 0)},
	{ 370, 170, "MusicRoom", GetColor(255, 255, 255)},
	{ 360, 240, "�w���v", GetColor(255, 255, 255)},
	{ 350, 310, "Config", GetColor(255, 255, 255)},
	{ 340, 380, "�Q�[���I��", GetColor(255, 255, 255)},
};


void SceneTitle::init()
{
	m_SelectNum = 0; // ���݂̑I��ԍ�
	m_Interval = kTInterval;

	m_BgmHandle1= LoadSoundMem("soundBgm/�Ԃ��g����.wav");
	


	PlaySoundMem(m_BgmHandle1, DX_PLAYTYPE_BACK);
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
		 if ((padState & PAD_INPUT_4) && (m_Interval <= 0))
		 {
			 PlaySoundMem(m_EffectsHandle2, DX_PLAYTYPE_BACK);

			 if (m_SelectNum == 0)
			 {// 4�{�^���������ꂽ�u�Ԃ�������
				 StopSoundMem(m_BgmHandle1);
			  // Main�ɐ؂�ւ�
				 return(new SelectChara);
				 
			 }

			 if (m_SelectNum == 1)
			 {// 4�{�^���������ꂽ�u�Ԃ�������
				StopSoundMem(m_BgmHandle1);
				// Music�ɐ؂�ւ�
				return(new SceneMusic);
			 }


			 if (m_SelectNum == 3)
			 {// 4�{�^���������ꂽ�u�Ԃ�������
				 StopSoundMem(m_BgmHandle1);
				 // Music�ɐ؂�ւ�
				 return(new SceneConfig);
			 }

			 if (m_SelectNum == 4)
			 {// 4�{�^���������ꂽ�u�Ԃ�������
				
				 DxLib_End();
				 
			 }

			 m_Interval = kTInterval;
		 }
		 if ((padState & PAD_INPUT_3) && (m_Interval <= 0))
		 {
			
			 m_SelectNum = 4;
			 
			 PlaySoundMem(m_EffectsHandle3, DX_PLAYTYPE_BACK);
			 m_Interval = kTInterval;
		 }
	 }


	 if ((padState & PAD_INPUT_DOWN) || (padState & PAD_INPUT_UP) || (padState & PAD_INPUT_3))
	 {
		 for (int i = 0; i < kTitle; i++)
		 {   
			 
			 // ���j���[���ڐ��ł���5���[�v����
			 m_slide = i * 10;
			
			 if (i == m_SelectNum) {          // ���������Ă���̂��A�I��ԍ��Ɠ����v�f�Ȃ�
				 MenuElement[i].x = (360 - m_slide); // ���W��80�ɂ���
				 MenuElement[i].Cr = GetColor(255, 0, 0);
			 }
			 else {                       // ���������Ă���̂��A�I��ԍ��ȊO�Ȃ�
				 MenuElement[i].x = 380- m_slide;// ���W��100�ɂ���
				 MenuElement[i].Cr = GetColor(255, 255, 255);
			 }
		 }
	 }

	return this;
}

void SceneTitle::draw()
{

	if (CheckSoundFile() == 1)
	{
		DrawFormatString(0, 40, GetColor(255, 255, 255), "�Đ���");
	}


	for (int i = 0; i < 5; i++) 
	{   
		// ���j���[���ڂ�`��
		DrawFormatString(MenuElement[i].x, MenuElement[i].y, MenuElement[i].Cr, MenuElement[i].name);
		// ������̕`��
		//DrawString(0, 0, "�����őI���AEnter�Ō���", GetColor(255, 255, 255));
		// �f�o�b�O�p
		DrawFormatString(0, 0, GetColor(255, 255, 255), "%d", m_SelectNum);
	}

}