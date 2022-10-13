#include "DxLib.h"

#include "SceneTitle.h"
#include "SelectChara.h"
#include "SceneMusic.h"
#include "SceneMain.h"
#include "SceneManager.h"

namespace
{
	// ��~�����V���b�g���ēx�ł��o���܂ł̎���
	constexpr int kTInterval = 15;
	// �^�C�g���̌�
	constexpr int kTitle = 5;

	
}



// ���j���[���ڂ̕\���ɕK�v�ȍ\���̂�p�ӂ���
typedef struct {
	int x, y;       // ���W�i�[�p�ϐ�
	char name[128]; // ���ږ��i�[�p�ϐ�
	int Cr;
} MenuElement_t;

// ���j���[���ڗv�f��5���
MenuElement_t MenuElement[kTitle] = {
		{ 380, 100, "�Q�[���X�^�[�g" , GetColor(255, 0, 0)}, // �^�O�̒��g�̏��ԂŊi�[�����Bx��80���Ay��100���Aname��"�Q�[���X�^�[�g"��
		{ 370, 170, "MusicRoom", GetColor(255, 255, 255)},
		{ 360, 240, "�w���v", GetColor(255, 255, 255)},
		{ 350, 310, "�R���t�B�O", GetColor(255, 255, 255)},
		{ 340, 380, "�Q�[���I��", GetColor(255, 255, 255)},
};


void SceneTitle::init()
{
	m_SelectNum = 0; // ���݂̑I��ԍ�
	m_Interval = kTInterval;

	PlaySoundFile("soundBgm/�Ԃ��g����.wav",DX_PLAYTYPE_LOOP);
	
	m_isEnd = false;
}


SceneBase* SceneTitle::update()
{
	int TEffectsHandle1;// �I�����̃n���h��
	int TEffectsHandle2;// ���艹�̃n���h��
	int TEffectsHandle3;// �L�����Z�����̃n���h��

	TEffectsHandle1 = LoadSoundMem("soundEffect/�I����.wav");
	TEffectsHandle2 = LoadSoundMem("soundEffect/���艹.wav");
	TEffectsHandle3 = LoadSoundMem("soundEffect/�L�����Z����.wav");

	

	int padState = 0;

	int slide;

	padState = GetJoypadInputState( DX_INPUT_KEY_PAD1 ) ;


	// �v�Z�t�F�[�Y 
	 m_Interval--;
	 if (m_Interval < 0) m_Interval = 0;

	 if (m_Interval <= 0)
	 {
		 if ((padState & PAD_INPUT_DOWN) && (m_Interval <= 0))
		 {
			 m_SelectNum = (m_SelectNum + 1) % kTitle; // ���݂̑I�����ڂ�����ɂ��炷(���[�v����)
			 PlaySoundMem(TEffectsHandle1, DX_PLAYTYPE_BACK);
			 m_Interval = kTInterval;
		 }
		 if ((padState & PAD_INPUT_UP) && (m_Interval <= 0))
		 {
			 m_SelectNum = (m_SelectNum + (kTitle-1)) % kTitle; // ���݂̑I�����ڂ����ɂ��炷(�t���[�v����)
			 PlaySoundMem(TEffectsHandle1, DX_PLAYTYPE_BACK);
			 m_Interval = kTInterval;
		 }
		 if ((padState & PAD_INPUT_4) && (m_Interval <= 0))
		 {
			 PlaySoundMem(TEffectsHandle2, DX_PLAYTYPE_BACK);

			 if (m_SelectNum == 0)
			 {// 4�{�^���������ꂽ�u�Ԃ�������
				// Main�ɐ؂�ւ�
				 return(new SelectChara);
				 
			 }

			 if (m_SelectNum == 1)
			 {// 4�{�^���������ꂽ�u�Ԃ�������
				StopSoundFile();
				// Music�ɐ؂�ւ�
				return(new SceneMusic);
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
			 
			 PlaySoundMem(TEffectsHandle3, DX_PLAYTYPE_BACK);
			 m_Interval = kTInterval;
		 }
	 }


	 if ((padState & PAD_INPUT_DOWN) || (padState & PAD_INPUT_UP) || (padState & PAD_INPUT_3))
	 {
		 for (int i = 0; i < kTitle; i++)
		 {   
			 
			 // ���j���[���ڐ��ł���5���[�v����
			 slide = i * 10;
			
			 if (i == m_SelectNum) {          // ���������Ă���̂��A�I��ԍ��Ɠ����v�f�Ȃ�
				 MenuElement[i].x = (360 - slide); // ���W��80�ɂ���
				 MenuElement[i].Cr = GetColor(255, 0, 0);
			 }
			 else {                       // ���������Ă���̂��A�I��ԍ��ȊO�Ȃ�
				 MenuElement[i].x = 380- slide;// ���W��100�ɂ���
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