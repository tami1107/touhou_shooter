#pragma once

#include <vector>
#include "player.h"
#include "ShotBase.h"
#include "SceneBase.h"
#include "enemy.h"
#include "SceneTitle.h"
#include "ShotPlayerNormal.h"
#include "ShotEnemyNormal.h"
#include "ShotNormal.h"

class SceneMain : public SceneBase
{
public:
	SceneMain();
	virtual ~SceneMain();

	// ������
	virtual void init();

	// �I������
	virtual void end();

	// ���t���[���̏���
	virtual SceneBase* update();
	// ���t���[���̕`��
	virtual void draw();

	//virtual bool CheckHit();
	//virtual bool CheckHitEnemy();

	//�e�̐���
	//virtual bool createShotPlayer(Vec2 pos);
	virtual bool createShotNormal(Vec2 pos);

	virtual bool createShotPlayerNormal(Vec2 pos);

	virtual bool createShotEnemyNormal(Vec2 pos);

	//�����蔻��
	virtual bool CheckHit();
	virtual bool CheckPlayerShotHit();
	virtual bool CheckEnemyShotHit();
	virtual bool CheckGraze();
	//virtual bool CheckMyShotHit();
	//virtual bool createShotFall(Vec2 pos);
	//virtual bool createShotBound(Vec2 pos);

	

private:

	// �v���C���[�̃O���t�B�b�N�n���h��
	int m_hPlayerGraphic[Player::kPlayerGraphicDivNum];
	int m_hEnemyGraphic[Enemy::kEnemyGraphicDivNum];
	int m_hShotGraphic;
	int m_hPointGraphic;
	int m_hCircleGraphic;
	
	// �v���C���[�̍U����
	int m_hEnemyHP;
	// �G�l�~�[���q�b�g������摜������
	int m_hEnemyHit;

	// �O���C�Y�̉�
	int m_GrazePoint;

	// �v���C���[�̃V���b�g�n���h��
	int m_hPlayerShot1;
	int m_hPlayerShotNumber;
	int m_hPlayerSoundEffectHandle;
	// �G�l�~�[�̃V���b�g�n���h��
	int m_hEnemyShot1;
	int m_hEnemyShotNumber;

	// �ʒu��� 
	//(�v���C���[�ƃG�l�~�[�̈ʒu)
	int m_playerPosX;
	int m_playerPosY;
	int m_enemyPosX;
	int m_enemyPosY;
	//(�v���C���[�ƃG�l�~�[�̃V���b�g�̈ʒu)
	int m_myShotPosX;
	int m_myShotPosY;
	int m_enemyShotPosX;
	int m_enemyShotPosY;

	// �T�E���h�n���h��
	int m_hTestSound;
	int m_hSoundEffectHandle1;
	int m_EffectsHandle1;
	int m_EffectsHandle2;
	int m_EffectsHandle3;

	//�����蔻��p�@�v���C���[�Ɖ~
	float m_PlayerPosX;
	float m_PlayerPosY;

	//�t���[��(�g)
	int m_frameHandle;
	int m_TitleframeHandle;

	//HP
	int m_maxHP;
	
	// ����
	int m_frameTime;
	int m_Time;
	int m_MaxTime;
	int m_CountTime;
	

public:
	// �v���C���[
	Player m_player;
	// �G
	Enemy m_enemy;
	// �v���C���[�V���b�g
	ShotPlayerNormal m_ShotPlayerNormal;

	SceneBase m_SceneBase;

	SceneTitle m_SceneTitle;

	// �V���b�g
	std::vector<ShotBase*> m_pShotVt;

	std::vector<ShotPlayerNormal*> m_pShotPlayer1Vt;

	std::vector<ShotEnemyNormal*> m_pShotEnemy1Vt;

	std::vector<ShotNormal*> m_pShotEnemy2Vt;

	/*ShotBound* m_pShotBound[kShotMax];
	ShotNormal* m_pShotNormal[kShotMax];
	ShotFall* m_pShotFall[kShotMax];*/

	
};


