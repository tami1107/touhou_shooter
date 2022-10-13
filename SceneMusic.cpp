#include "DxLib.h"
#include "SceneMain.h"
#include "SceneMusic.h"
#include "SceneTitle.h"


namespace
{
	
	constexpr int kMInterval = 15;

	int GHandle1;
	int GHandle2;

	constexpr int kTitle = 2;
}


// ���j���[���ڂ̕\���ɕK�v�ȍ\���̂�p�ӂ���
typedef struct {
	int x, y;       // ���W�i�[�p�ϐ�
	char name[128]; // ���ږ��i�[�p�ϐ�
	int Cr;
} MenuElement_m;

// ���j���[���ڗv�f��3���
MenuElement_m MenuElement[kTitle] = {
		{  80, 100, "�S�������ׂ̈̃Z�v�e�b�g" ,GetColor(255, 0, 0) }, // �^�O�̒��g�̏��ԂŊi�[�����Bx��80���Ay��100���Aname��"�Q�[���X�^�[�g"��
		{ 100, 150, "UN.�I�[�G���͔ޏ��Ȃ̂�" ,GetColor(255, 255, 255)},
	
};


void SceneMusic::init()
{

	m_SoundSelect = 0;
	m_MInterval = kMInterval;
	m_isEnd = false;
}

SceneBase* SceneMusic::update()
{

	int TMffectsHandle1;// �I�����̃n���h��
	int TMffectsHandle2;// ���艹�̃n���h��
	int TMffectsHandle3;// �L�����Z�����̃n���h��

	TMffectsHandle1 = LoadSoundMem("soundEffect/�I����.wav");
	TMffectsHandle2 = LoadSoundMem("soundEffect/���艹.wav");
	TMffectsHandle3 = LoadSoundMem("soundEffect/�L�����Z����.wav");

	int padState = 0;

	padState = GetJoypadInputState(DX_INPUT_KEY_PAD1);

	m_MInterval--;
	if (m_MInterval < 0) m_MInterval = 0;

	if (m_MInterval <= 0)
	{

		if ((padState & PAD_INPUT_DOWN) && (m_MInterval <= 0))
		{
			m_SoundSelect = (m_SoundSelect + 1) % kTitle; // ���݂̑I�����ڂ�����ɂ��炷(���[�v����)
			PlaySoundMem(TMffectsHandle1, DX_PLAYTYPE_BACK);
			m_MInterval = kMInterval;
		}
		if ((padState & PAD_INPUT_UP) && (m_MInterval <= 0))
		{
			m_SoundSelect = (m_SoundSelect + (kTitle - 1)) % kTitle; // ���݂̑I�����ڂ����ɂ��炷(�t���[�v����)
			PlaySoundMem(TMffectsHandle1, DX_PLAYTYPE_BACK);
			m_MInterval = kMInterval;
		}
		if ((padState & PAD_INPUT_4) && (m_MInterval <= 0))
		{
			PlaySoundMem(TMffectsHandle2, DX_PLAYTYPE_BACK);
			if (m_SoundSelect == 0)
			{// 4�{�^���������ꂽ�u�Ԃ�������
				if (CheckSoundFile() == 0)
				{
					PlaySoundFile("soundBgm/�S�������ׂ̈̃Z�v�e�b�g.wav", DX_PLAYTYPE_LOOP);
				}
				else if (!CheckSoundFile == 0)
				{
					StopSoundFile();
				}
			}

			if (m_SoundSelect == 1)
			{// 4�{�^���������ꂽ�u�Ԃ�������
				
				if (CheckSoundFile() == 0)
				{
					PlaySoundFile("soundBgm/UN.�I�[�G���͔ޏ��Ȃ̂�.wav", DX_PLAYTYPE_LOOP);
				}
				else if (!CheckSoundFile == 0)
				{
					StopSoundFile();
				}
					
			
			}

			m_MInterval = kMInterval;
		}
		if ((padState & PAD_INPUT_3) && (m_MInterval <= 0))
		{
			PlaySoundMem(TMffectsHandle3, DX_PLAYTYPE_BACK);
			// Title�ɐ؂�ւ�
			return(new SceneTitle);
			m_MInterval = kMInterval;
		}

		

		


	}

	if ((padState & PAD_INPUT_DOWN) || (padState & PAD_INPUT_UP) || (padState & PAD_INPUT_3))
	{

		for (int i = 0; i < kTitle; i++)
		{   // ���j���[���ڐ��ł���3���[�v����
			if (i == m_SoundSelect) {          // ���������Ă���̂��A�I��ԍ��Ɠ����v�f�Ȃ�
				MenuElement[i].x = 80; // ���W��80�ɂ���
				MenuElement[i].Cr = GetColor(255, 0, 0);
			}
			else {                       // ���������Ă���̂��A�I��ԍ��ȊO�Ȃ�
				MenuElement[i].x = 100;// ���W��100�ɂ���
				MenuElement[i].Cr = GetColor(255, 255, 255);
			}
		}
	}
	return this;
}

void SceneMusic::draw()
{
	GHandle1 = LoadGraph("image/���~���A_�ʏ�.png");
	GHandle2 = LoadGraph("image/�t����_�ʏ�.png");

	if (m_SoundSelect == 0)
	{
		DrawExtendGraph(300, 0, 640, 480, GHandle1, TRUE);
	}
	if (m_SoundSelect == 1)
	{
		DrawExtendGraph(300, 0, 640, 480, GHandle2, TRUE);
	}


	if (CheckSoundFile() == 1)
	{
		DrawFormatString(0, 40, GetColor(255, 255, 255), "�Đ���");
	}

	for (int i = 0; i < kTitle; i++)
	{
		// ���j���[���ڂ�`��
		DrawFormatString(MenuElement[i].x, MenuElement[i].y, MenuElement[i].Cr, MenuElement[i].name);
		// ������̕`��
		//DrawString(0, 0, "�����őI���AEnter�Ō���ABackspace�ŃL�����Z��", GetColor(255, 255, 255));
		// �f�o�b�O�p
		DrawFormatString(0, 0, GetColor(255, 255, 255), "%d", m_SoundSelect);
	}
}