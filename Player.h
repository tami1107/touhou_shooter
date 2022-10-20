#pragma once
#include "DxLib.h"
#include "Vec2.h"

class SceneMain;

class Player
{
public:
	// �萔��`
	
	// �v���C���[�O���t�B�b�N������
	static constexpr int kPlayerGraphicDivX = 4;
	static constexpr int kPlayerGraphicDivY = 3;
	static constexpr int kPlayerGraphicDivNum = kPlayerGraphicDivX * kPlayerGraphicDivY;

	// �v���C���[�O���t�B�b�N�T�C�Y
	static constexpr int kPlayerGraphicSizeX = 209 / kPlayerGraphicDivX;
	static constexpr int kPlayerGraphicSizeY = 155 / kPlayerGraphicDivY;

	// ���S�_("�ᑬ���̒��S�_.png")�̃O���t�B�b�N�T�C�Y
	static constexpr int kPointHandleSizeX = 16;
	static constexpr int kPointHandleSizeY = 16;

	// �~("�ᑬ���̃G�t�F�N�g.png")�̃O���t�B�b�N�T�C�Y
	static constexpr int kCircleHandleSizeX = 64;
	static constexpr int kCircleHandleSizeY = 64;

public:
	Player();
	virtual ~Player();

	// �O���t�B�b�N�f�[�^�ݒ�
	void setHandle(int index, int handle) { m_handle[index] = handle; }

	void setPointHandle(int PointHandle) { m_pointHandle = PointHandle; }

	void setCircleHandle(int CircleHandle) { m_circleHandle = CircleHandle; }

	void setPlayerSoundEffectHandle(int PlayerSoundEffectHandle){ m_PlayerSoundEffectHandle = PlayerSoundEffectHandle;}

	// �v���C���[�̏�����
	void init();

	//SceneMain�N���X�̃|�C���^�ݒ�
	void setMain(SceneMain* pMain) { m_pMain = pMain; }

	// ����
	void update();
	// �`��
	void draw();

	// ���̎擾
	Vec2 getPos() const { return m_pos; }

private:
	int m_handle[kPlayerGraphicDivNum];

	int m_pointHandle;
	int m_pointHandleSizeX, m_pointHandleSizeY;
	
	int m_circleHandle;
	int m_circleHandleSizeX, m_circleHandleSizeY;

	int m_PlayerSoundEffectHandle;
	
	//SceneMain�̃|�C���^
	SceneMain* m_pMain;

	// �\���ʒu
	Vec2 m_pos;
	// �ړ�
	Vec2 m_vec;
	// �V���b�g�̊Ԋu
	int m_shotInterval;

	



	double m_revolution;

	int m_push;
	// �L�����N�^�[�̃A�j���[�V����
	int m_animeNo;	// �\������ԍ�
	int m_animeFrame;
	int m_dirNo;
};






//#pragma once
//#include "SceneBase.h"
//
//class Player : public SceneBase
//{
//public:
//	Player()
//	{
//		m_SelectNum = 0;
//
//		m_isEnd = false;
//	}
//	virtual ~Player() {}
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
//	// �O���t�B�b�N�n���h��
//	int m_handle;
//
//	bool m_isEnd;
//};