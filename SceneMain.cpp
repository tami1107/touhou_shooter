
#include "DxLib.h"
#include "SceneMain.h"

#include "SceneTitle.h"
#include <cassert>
#include "ShotNormal.h"
#include "ShotPlayerNormal.h"
#include "Player.h"


namespace
{
	//�V���b�g�̔��ˊԊu
	constexpr int kShotInterval = 16;
	// �O���t�B�b�N�t�@�C����
	//const char* const kPlayerGraphicFilename = "image/player.png";
	const char* const kEnemyGraphicFilename = "image/�t�����h�[��.png";
	const char* const kPlayerGraphicFilename = "image/������.png";
	const char* const kPlayerPoint = "image/�ᑬ���̒��S�_.png";
	const char* const kCirclePoint = "image/�ᑬ���̃T�[�N���G�t�F�N�g.png";

	// �����蔻��̑傫��
	static constexpr int kPlayerHitBoxSize = 4;
	static constexpr int kEnemyHitBoxSize = 40;
	static constexpr int kPlayerShotSize = 5;
	
	
	// �v���C���[�O���t�B�b�N�T�C�Y
	static constexpr int kPlayerGraphicSizeX = Player::kPlayerGraphicSizeX;
	static constexpr int kPlayerGraphicSizeY = Player::kPlayerGraphicSizeX;

	// �G�O���t�B�b�N�T�C�Y
	static constexpr int kEnemyGraphicSizeX = Enemy::kEnemyGraphicSizeX;
	static constexpr int kEnemyGraphicSizeY = Enemy::kEnemyGraphicSizeY;

	// �e�O���t�B�b�N�T�C�Y
	static constexpr int kShotGraphicSizeX = 16;
	static constexpr int kShotGraphicSizeY = 36;
}

SceneMain::SceneMain()
{
	//	m_hPlayerGraphic = -1;
	for (auto& handle : m_hPlayerGraphic)
	{
		handle = -1;
	}
	m_hEnemyGraphic = -1;
	m_hShotGraphic = -1;
	m_hPointGraphic = -1;
	m_hCircleGraphic = -1;

	m_EffectsHandle1 = -1;

	m_hPlayerShotNumber = 0;
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
	m_hEnemyGraphic = LoadGraph(kEnemyGraphicFilename);
	m_hPointGraphic = LoadGraph(kPlayerPoint);
	m_hCircleGraphic = LoadGraph(kCirclePoint);


	m_hShotGraphic = LoadGraph("image/shot.bmp");
	m_hPlayerShot1 = LoadGraph("image/PlayerShot1.png");


	

	// �T�E���h�̃��[�h
	m_hTestSound = LoadSoundMem("sound/cursor0.mp3");
	m_hSoundEffectHandle1 = LoadSoundMem("soundEffect/�I����.wav");
	m_hPlayerSoundEffectHandle = LoadSoundMem("soundEffect/�V���b�g���̌��ʉ�.mp3");
	

	for (int i = 0; i < Player::kPlayerGraphicDivNum; i++)
	{
		m_player.setHandle(i, m_hPlayerGraphic[i]);
	}
	m_player.init();
	m_player.setMain(this);
	m_player.setPointHandle(m_hPointGraphic);
	m_player.setCircleHandle(m_hCircleGraphic);
	m_player.setPlayerSoundEffectHandle(m_hPlayerSoundEffectHandle);
	
	

	m_enemy.setHandle(m_hEnemyGraphic);
	m_enemy.init();
	m_enemy.setMain(this);

	m_SceneTitle.setSoundEffectHandle1(m_hSoundEffectHandle1);
}

// �I������
void SceneMain::end()
{
	// �O���t�B�b�N�A�����[�h
	for (auto& handle : m_hPlayerGraphic)
	{
		DeleteGraph(handle);
	}
	DeleteGraph(m_hEnemyGraphic);
	DeleteGraph(m_hShotGraphic);

	DeleteGraph(m_hPointGraphic);
	DeleteGraph(m_hCircleGraphic);
	// �T�E���h�A�����[�h
	DeleteSoundMem(m_hTestSound);

	for (auto& pShot : m_pShotVt)
	{
		assert(pShot);
		delete pShot;
		pShot = nullptr;
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
	
	// �G�l�~�[�ɓ��������ꍇ�ATitle�ɖ߂�
	if (CheckPlayerHit() == true)
	{
		// Title�ɐ؂�ւ�
		return(new SceneTitle);
	}



	return this;
#if false
	for (auto& pShot : m_pShotVt)
	{
		if (!pShot) continue;		//null�̏ꍇ�������Ȃ�
		pShot->update();
		if (!pShot->isExist())
		{
			delete pShot;
			pShot = nullptr;

			//vector�̗v�f�폜

		}
	}
#endif
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
	
	// �����蔻��̕\��
	DrawCircle(m_playerPosX, m_playerPosY, kPlayerHitBoxSize,GetColor(255, 255, 255), FALSE);
	DrawCircle(m_enemyPosX, m_enemyPosY, kEnemyHitBoxSize, GetColor(255, 255, 255), FALSE);

	//���ݑ��݂��Ă���e�̐���\��
	DrawFormatString(0, 0, GetColor(255, 255, 255), "�e�̐�:%d", m_pShotVt.size());
}

//bool SceneMain::createShotPlayer(Vec2 pos)
//{
//	ShotPlayer* pShot = new ShotPlayer;
//	pShot->setHandle(m_hShotGraphic);
//	pShot->start(pos);
//	m_pShotVt.push_back(pShot);
//
//	return true;
//}

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
	m_pShotVt.push_back(pShot);

	m_hPlayerShotNumber = 1;
	return true;
}

//bool SceneMain::CheckHit()
//{
//	
//
//	float dx = t_circleA.x - t_circleB.x;
//	float dy = t_circleA.y - t_circleB.y;
//	float dr = dx * dx + dy * dy;
//
//	float ar = t_circleA.r + t_circleB.r;
//	float dl = ar * ar;
//	if (dr < dl)
//	{
//		return true;
//	}
//
//	return false;
//}

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


bool SceneMain::CheckPlayerHit()
{
	std::vector<ShotBase*>::iterator it = m_pShotVt.begin();
	while (it != m_pShotVt.end())
	{
		auto& pShot = (*it);
		pShot->getPos();
		//�G�l�~�[�̒��S���W���擾
		m_enemyPosX = m_enemy.getPos().x + (kPlayerGraphicSizeX / 2);
		m_enemyPosY = m_enemy.getPos().y + (kPlayerGraphicSizeY / 2);
		//�v���C���[�̃V���b�g�̒��S���W���擾
		m_myShotPosX = pShot->getPos().x;

		//�����蔻��
		float dx2 = m_enemyPosX - pShot->getPos().x;
		float dy2 = m_enemyPosY - pShot->getPos().y;
		float dr2 = dx2 * dx2 + dy2 * dy2;

		float ar2 = kPlayerShotSize + kEnemyHitBoxSize;
		float dl2 = ar2 * ar2;

		DrawCircle(pShot->getPos().x, pShot->getPos().y, kPlayerShotSize, GetColor(255, 0, 0), FALSE);
		if (dr2 < dl2)
		{
			return true;
		}
		else
		{
			it++;

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