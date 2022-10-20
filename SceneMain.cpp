
#include "DxLib.h"
#include "SceneMain.h"

#include "SceneTitle.h"
#include <cassert>
#include "ShotNormal.h"
#include "ShotPlayerNormal.h"
#include "ShotEnemyNormal.h"
#include "Player.h"


namespace
{
	//�V���b�g�̔��ˊԊu
	constexpr int kShotInterval = 16;
	// �O���t�B�b�N�t�@�C����
	const char* const kEnemyGraphicFilename = "image/�t�����A�j���[�V���� - �R�s�[.png";
	const char* const kPlayerGraphicFilename = "image/������.png";
	const char* const kPlayerPoint = "image/�ᑬ���̒��S�_.png";
	const char* const kCirclePoint = "image/�ᑬ���̃T�[�N���G�t�F�N�g.png";

	// �����蔻��̑傫��
	static constexpr int kPlayerHitBoxSize = 4;
	static constexpr int kEnemyHitBoxSize = 40;
	static constexpr int kPlayerShot1Size = 5;
	static constexpr int kEnemyShot1Size = 5;
	static constexpr int kGrazeSize = 20;
	
	
	// �v���C���[�O���t�B�b�N�T�C�Y
	static constexpr int kPlayerGraphicSizeX = Player::kPlayerGraphicSizeX;
	static constexpr int kPlayerGraphicSizeY = Player::kPlayerGraphicSizeX;

	// �G�O���t�B�b�N�T�C�Y
	static constexpr int kEnemyGraphicSizeX = Enemy::kEnemyGraphicSizeX;
	static constexpr int kEnemyGraphicSizeY = Enemy::kEnemyGraphicSizeY;

	// �e(�v���C���[)�O���t�B�b�N�T�C�Y
	static constexpr int kPlayerShot1GraphicSizeX = ShotPlayerNormal::kPlayerShot1GraphicSizeX;
	static constexpr int kPlayerShot1GraphicSizeY = ShotPlayerNormal::kPlayerShot1GraphicSizeY;
	// �e(�G�l�~�[)�O���t�B�b�N�T�C�Y
	static constexpr int kEnemyShot1GraphicSizeX = ShotEnemyNormal::kEnemyShot1GraphicSizeX;
	static constexpr int kEnemyShot1GraphicSizeY = ShotEnemyNormal::kEnemyShot1GraphicSizeY;
	
}

SceneMain::SceneMain()
{
	//	m_hPlayerGraphic = -1;
	for (auto& handle : m_hPlayerGraphic)
	{
		handle = -1;
	}

	for (auto& handle : m_hEnemyGraphic)
	{
		handle = -1;
	}

	//m_hEnemyGraphic = -1;
	m_hShotGraphic = -1;
	m_hPointGraphic = -1;
	m_hCircleGraphic = -1;

	m_EffectsHandle1 = -1;

	m_hPlayerShotNumber = 0;
	m_hEnemyHP = 0;
}
SceneMain::~SceneMain()
{

}

// ������
void SceneMain::init()
{
	// �O���t�B�b�N�̃��[�h
	LoadDivGraph(kPlayerGraphicFilename, Player::kPlayerGraphicDivNum,
		Player::kPlayerGraphicDivX, Player::kPlayerGraphicDivY,
		Player::kPlayerGraphicSizeX, Player::kPlayerGraphicSizeY, m_hPlayerGraphic);

	LoadDivGraph(kEnemyGraphicFilename, Enemy::kEnemyGraphicDivNum,
		Enemy::kEnemyGraphicDivX, Enemy::kEnemyGraphicDivY,
		Enemy::kEnemyGraphicSizeX, Enemy::kEnemyGraphicSizeY, m_hEnemyGraphic);



	//m_hEnemyGraphic = LoadGraph(kEnemyGraphicFilename);
	m_hPointGraphic = LoadGraph(kPlayerPoint);
	m_hCircleGraphic = LoadGraph(kCirclePoint);

	// �V���b�g�̃��[�h
	m_hShotGraphic = LoadGraph("image/shot.bmp");
	m_hPlayerShot1 = LoadGraph("image/PlayerShot1.png");
	m_hEnemyShot1 = LoadGraph("image/EnemyShot1.png");

	

	// �T�E���h�̃��[�h
	m_hTestSound = LoadSoundMem("sound/cursor0.mp3");
	m_hSoundEffectHandle1 = LoadSoundMem("soundEffect/�I����.wav");
	m_hPlayerSoundEffectHandle = LoadSoundMem("soundEffect/�V���b�g���̌��ʉ�.mp3");
	
	// �t���[���̃��[�h
	m_frameHandle = LoadGraph("image/�t���[��.png");
	


	for (int i = 0; i < Player::kPlayerGraphicDivNum; i++)
	{
		m_player.setHandle(i, m_hPlayerGraphic[i]);
	}
	m_player.init();
	m_player.setMain(this);
	m_player.setPointHandle(m_hPointGraphic);
	m_player.setCircleHandle(m_hCircleGraphic);
	m_player.setPlayerSoundEffectHandle(m_hPlayerSoundEffectHandle);
	
	
	for (int i = 0; i < Enemy::kEnemyGraphicDivNum; i++)
	{
		m_enemy.setHandle(i, m_hEnemyGraphic[i]);
	}
	m_enemy.init();
	m_enemy.setMain(this);

	m_SceneBase.setSoundEffectHandle1(m_hSoundEffectHandle1);

	

	// �G�l�~�[��HP
	m_hEnemyHP = 100;
	// �O���C�Y������
	m_GrazePoint = 0;
}

// �I������
void SceneMain::end()
{
	// �O���t�B�b�N�A�����[�h
	for (auto& handle : m_hPlayerGraphic)
	{
		DeleteGraph(handle);
	}
	
	for (auto& handle : m_hEnemyGraphic)
	{
		DeleteGraph(handle);
	}
	
	DeleteGraph(m_hShotGraphic);

	DeleteGraph(m_hPointGraphic);
	DeleteGraph(m_hCircleGraphic);
	// �T�E���h�A�����[�h
	DeleteSoundMem(m_hTestSound);

	// �t���[���A�����[�h
	DeleteGraph(m_frameHandle);
	DeleteGraph(m_TitleframeHandle);


	for (auto& pShot : m_pShotVt)
	{
		assert(pShot);
		delete pShot;
		pShot = nullptr;
	}
	// �v���C���[�̃V���b�g
	for (auto& pShotPlayer1 : m_pShotPlayer1Vt)
	{
		assert(pShotPlayer1);
		delete pShotPlayer1;
		pShotPlayer1 = nullptr;
	}
	// �G�l�~�[�̃V���b�g
	for (auto& pShotEnemy1 : m_pShotEnemy1Vt)
	{
		assert(pShotEnemy1);
		delete pShotEnemy1;
		pShotEnemy1 = nullptr;
	}


	for (auto& pShotEnemy2 : m_pShotEnemy2Vt)
	{
		assert(pShotEnemy2);
		delete pShotEnemy2;
		pShotEnemy2 = nullptr;
	}
}

// ���t���[���̏���
SceneBase* SceneMain::update()
{
	int padState = GetJoypadInputState(DX_INPUT_KEY_PAD1);
	if (padState & PAD_INPUT_1)
	{
		PlaySoundMem(m_hTestSound, DX_PLAYTYPE_BACK, true);
	}
	m_player.update();
	m_enemy.update();

	std::vector<ShotBase*>::iterator it = m_pShotVt.begin();
	while (it != m_pShotVt.end())
	{
		auto& pShot = (*it);
		assert(pShot);
		pShot->update();
		if (!pShot->isExist())
		{
			delete pShot;
			pShot = nullptr;

			//vector�̗v�f�폜
			it = m_pShotVt.erase(it);
			continue;
		}
		it++;
	}

	std::vector<ShotPlayerNormal*>::iterator itShotPlayer1 = m_pShotPlayer1Vt.begin();
	while (itShotPlayer1 != m_pShotPlayer1Vt.end())
	{
		auto& pShotPlayer1 = (*itShotPlayer1);
		assert(pShotPlayer1);
		pShotPlayer1->update();
		if (!pShotPlayer1->isExist())
		{
			delete pShotPlayer1;
			pShotPlayer1 = nullptr;

			//vector�̗v�f�폜
			itShotPlayer1 = m_pShotPlayer1Vt.erase(itShotPlayer1);
			continue;
		}
		itShotPlayer1++;
	}

	std::vector<ShotEnemyNormal*>::iterator itShotEnemy1 = m_pShotEnemy1Vt.begin();
	while (itShotEnemy1 != m_pShotEnemy1Vt.end())
	{
		auto& pShotEnemy1 = (*itShotEnemy1);
		assert(pShotEnemy1);
		pShotEnemy1->update();
		if (!pShotEnemy1->isExist())
		{
			delete pShotEnemy1;
			pShotEnemy1 = nullptr;

			//vector�̗v�f�폜
			itShotEnemy1 = m_pShotEnemy1Vt.erase(itShotEnemy1);
			continue;
		}
		itShotEnemy1++;
	}



	if (padState & PAD_INPUT_3)
	{
		// Title�ɐ؂�ւ�
		return(new SceneTitle);
	}

	// �G�l�~�[�ɓ��������ꍇ�ATitle�ɖ߂�
	if (CheckHit() == true)
	{
		// Title�ɐ؂�ւ�
		return(new SceneTitle);
	}
	
	// �v���C���[�̒e���G�l�~�[�ɓ��������ꍇ�AHP�����炷
	if (CheckPlayerShotHit() == true)
	{
		m_hEnemyHP--;
	}

	// �G�l�~�[�̒e���v���C���[�ɓ��������ꍇ�ATitle�ɖ߂�
	if (CheckEnemyShotHit() == true)
	{
		// Title�ɐ؂�ւ�
		//return(new SceneTitle);
	}

	if (CheckGraze() == true)
	{
		m_GrazePoint++;
	}

	m_enemy.setEnemyHP(m_hEnemyHP);

	return this;

}

// ���t���[���̕`��
void SceneMain::draw()
{
	
	// �ʒu���̎擾
	//(�v���C���[�ʒu)
	m_player.getPos();
	m_playerPosX = m_player.getPos().x + (kPlayerGraphicSizeX / 2);
	m_playerPosY = m_player.getPos().y + (kPlayerGraphicSizeY / 2);
	//(�G�l�~�[�ʒu)
	m_enemy.getPos();
	m_enemyPosX = m_enemy.getPos().x + (kEnemyGraphicSizeX / 2);
	m_enemyPosY = m_enemy.getPos().y + (kEnemyGraphicSizeY / 2);


	m_enemy.draw();
	m_player.draw();	
	for (auto& pShot : m_pShotVt)
	{
		assert(pShot);
		pShot->draw();
	}
	//�v���C���[�̒e�\��
	for (auto& pShot : m_pShotPlayer1Vt)
	{
		assert(pShot);
		
		pShot->draw();
	}
	//�G�l�~�[�̒e�\��
	for (auto& pShot : m_pShotEnemy1Vt)
	{
		assert(pShot);

		pShot->draw();
	}
	// �����蔻��̕\��
	DrawCircle(m_playerPosX, m_playerPosY, kPlayerHitBoxSize,GetColor(255, 255, 255), FALSE);
	DrawCircle(m_enemyPosX, m_enemyPosY, kEnemyHitBoxSize, GetColor(255, 255, 255), FALSE);
	// �t���[��(�g)�`��
	DrawGraph(0, 0, m_frameHandle, TRUE);
	//���݂̃O���C�Y����\��
	DrawFormatString(600, 261, GetColor(255, 255, 255), ":%d", m_GrazePoint);
	//test
	//LoadGraphScreen(0, 0, "image/Ftest.png", TRUE);


}



bool SceneMain::createShotNormal(Vec2 pos)
{
	ShotNormal* pShot = new ShotNormal;
	pShot->setHandle(m_hShotGraphic);
	pShot->start(pos);
	m_pShotVt.push_back(pShot);
	
	return true;
}

bool SceneMain::createShotPlayerNormal(Vec2 pos)
{
	ShotPlayerNormal* pShot = new ShotPlayerNormal;
	pShot->setHandle(m_hPlayerShot1);
	pShot->start(pos);
	m_pShotPlayer1Vt.push_back(pShot);

	m_hPlayerShotNumber = 1;
	return true;
}

bool SceneMain::createShotEnemyNormal(Vec2 pos)
{
	ShotEnemyNormal* pShot = new ShotEnemyNormal;
	pShot->setHandle(m_hEnemyShot1);
	pShot->start(pos);
	m_pShotEnemy1Vt.push_back(pShot);

	m_hPlayerShotNumber = 1;
	return true;
}


bool SceneMain::CheckHit()
{
	//�����蔻��
	float dx = m_playerPosX - m_enemyPosX;
	float dy = m_playerPosY - m_enemyPosY;
	float dr = dx * dx + dy * dy;

	float ar = kPlayerHitBoxSize + kEnemyHitBoxSize;
	float dl = ar * ar;
	if (dr < dl)
	{
		return true;
	}

	return false;
}


bool SceneMain::CheckPlayerShotHit()
{
	std::vector<ShotPlayerNormal*>::iterator itShotPlayer1 = m_pShotPlayer1Vt.begin();
	while (itShotPlayer1 != m_pShotPlayer1Vt.end())
	{
		auto& pShot = (*itShotPlayer1);
		pShot->getPos();
		
		//�v���C���[�̃V���b�g�̒��S���W���擾
		m_myShotPosX = (pShot->getPos().x) + (kPlayerShot1GraphicSizeX / 2);
		m_myShotPosY = (pShot->getPos().y) + (kPlayerShot1GraphicSizeY / 2);

		//�����蔻��
		float dx = m_enemyPosX - m_myShotPosX;
		float dy = m_enemyPosY - m_myShotPosY;
		float dr = dx * dx + dy * dy;

		float ar = kPlayerShot1Size + kEnemyHitBoxSize;
		float dl = ar * ar;

		DrawCircle(m_myShotPosX, m_myShotPosY, kPlayerShot1Size, GetColor(255, 0, 0), FALSE);
		//���ݑ��݂��Ă���e�̐���\��
		DrawFormatString(0, 10, GetColor(255, 255, 255), "���@�e�̐�:%d", m_pShotPlayer1Vt.size());
		if (dr < dl)
		{
			//vector�̗v�f�폜
			itShotPlayer1 = m_pShotPlayer1Vt.erase(itShotPlayer1);
			return true;
		}
		else
		{
			itShotPlayer1++;

			continue;
		}
		return false;
	}
}


bool SceneMain::CheckEnemyShotHit()
{
	std::vector<ShotEnemyNormal*>::iterator itShotEnemy1 = m_pShotEnemy1Vt.begin();
	while (itShotEnemy1 != m_pShotEnemy1Vt.end())
	{
		auto& pShot = (*itShotEnemy1);
		pShot->getPos();
		//�G�l�~�[�̃V���b�g�̒��S���W���擾
		m_enemyShotPosX = pShot->getPos().x + (kEnemyShot1GraphicSizeX / 2);
		m_enemyShotPosY = pShot->getPos().y + (kEnemyShot1GraphicSizeY / 2);

		//�����蔻��
		float dx2 = m_playerPosX - m_enemyShotPosX;
		float dy2 = m_playerPosY - m_enemyShotPosY;
		float dr2 = dx2 * dx2 + dy2 * dy2;

		float ar2 = kEnemyShot1Size + kPlayerHitBoxSize;
		float dl2 = ar2 * ar2;

		DrawCircle(m_enemyShotPosX, m_enemyShotPosY, kEnemyShot1Size, GetColor(255, 0, 0), FALSE);
		//���ݑ��݂��Ă���e�̐���\��
		DrawFormatString(0, 25, GetColor(255, 255, 255), "�G�e�̐�:%d", m_pShotEnemy1Vt.size());
		if (dr2 < dl2)
		{
			//vector�̗v�f�폜
			itShotEnemy1 = m_pShotEnemy1Vt.erase(itShotEnemy1);
			return true;
		}
		else
		{
			itShotEnemy1++;

			continue;
		}
		return false;
	}
}

bool SceneMain::CheckGraze()
{
	std::vector<ShotEnemyNormal*>::iterator itShotEnemy1 = m_pShotEnemy1Vt.begin();
	while (itShotEnemy1 != m_pShotEnemy1Vt.end())
	{
		auto& pShot = (*itShotEnemy1);
		pShot->getPos();
		//�G�l�~�[�̃V���b�g�̒��S���W���擾
		m_enemyShotPosX = pShot->getPos().x + (kEnemyShot1GraphicSizeX / 2);
		m_enemyShotPosY = pShot->getPos().y + (kEnemyShot1GraphicSizeY / 2);

		//�����蔻��
		float dx2 = m_playerPosX - m_enemyShotPosX;
		float dy2 = m_playerPosY - m_enemyShotPosY;
		float dr2 = dx2 * dx2 + dy2 * dy2;

		float ar2 = kEnemyShot1Size + kGrazeSize;
		float dl2 = ar2 * ar2;
		//�O���C�Y�̔���\��
		DrawCircle(m_playerPosX, m_playerPosY, kGrazeSize, GetColor(0, 255, 0), FALSE);
		
		if (dr2 < dl2)
		{
			return true;
		}
		else
		{
			itShotEnemy1++;

			continue;
		}
		return false;
	}
}





//bool SceneMain::createShotFall(Vec2 pos)
//{
//	ShotFall* pShot = new ShotFall;
//	pShot->setHandle(m_hShotGraphic);
//	pShot->start(pos);
//	m_pShotVt.push_back(pShot);
//
//	return true;
//}
//
//bool SceneMain::createShotBound(Vec2 pos)
//{
//	ShotBound* pShot = new ShotBound;
//	pShot->setHandle(m_hShotGraphic);
//	pShot->start(pos);
//	m_pShotVt.push_back(pShot);
//
//	return true;
//}












//#include "DxLib.h"
//
//#include "game.h"
//#include"SceneMain.h"
//
//
//void SceneMain::init()
//{
//	
//
//	m_isEnd = false;
//}
//
//
//SceneBase* SceneMain::update()
//{
//	
//
//	return this;
//}
//
//void SceneMain::draw()
//{
//	m_player.draw();
//
//}