#pragma once

#include <vector>
#include "player.h"
#include "ShotBase.h"
#include "SceneBase.h"
#include "enemy.h"

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

	//�e�̐���
	//virtual bool createShotPlayer(Vec2 pos);
	virtual bool createShotNormal(Vec2 pos);

	virtual bool createShotPlayerNormal(Vec2 pos);
	//virtual bool createShotFall(Vec2 pos);
	//virtual bool createShotBound(Vec2 pos);

private:

	// �v���C���[�̃O���t�B�b�N�n���h��
	int m_hPlayerGraphic[Player::kPlayerGraphicDivNum];
	int m_hPlayerCenter;

	int m_hEnemyGraphic;
	int m_hShotGraphic;
	// �v���C���[�̃V���b�g�n���h��
	int m_hPlayerShot1;
	int m_hPlayerShotNumber;

	// �T�E���h�n���h��
	int m_hTestSound;
	// �v���C���[
	Player m_player;
	// �G
	Enemy m_enemy;
	// �V���b�g
	//ShotBase* m_pShot[kShotMax];
	std::vector<ShotBase*> m_pShotVt;
	/*ShotBound* m_pShotBound[kShotMax];
	ShotNormal* m_pShotNormal[kShotMax];
	ShotFall* m_pShotFall[kShotMax];*/
};







//#pragma once
//#include "SceneBase.h"
//#include"Player.h"
//
//class SceneMain : public SceneBase
//{
//public:
//	SceneMain()
//	{
//		m_SelectNum = 0;
//
//		m_isEnd = false;
//	}
//	virtual ~SceneMain() {}
//
//
//	virtual void init() override;
//	virtual void end() override {}
//
//	virtual SceneBase* update() override;
//
//	virtual void draw() override;
//
//	virtual bool isEnd() { return m_isEnd; }
//private:
//	// �e�L�X�g�\���ʒu�ύX
//	int m_SelectNum;
//	int m_Interval;
//
//	// �v���C���[
//	Player m_player;
//
//	bool m_isEnd;
//};