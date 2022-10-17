#pragma once

#include "Vec2.h"

class ShotBase
{
public:
	ShotBase();
	virtual ~ShotBase();

	void setHandle(int handle) { m_handle = handle; }
	


	//�V���b�g�J�n
	virtual void start(Vec2 pos);
	// �X�V
	virtual void update();
	// �\��
	virtual void draw();

	//���݂邷�邩
	bool isExist() const { return m_isExist; }
	// ���̎擾
	Vec2 getPos() const { return m_pos; }

	//�p���悩����g����悤�ɂȂ�
protected:
	// �O���t�B�b�N�n���h��
	int m_handle;
	
	//int m_shotNumber;
	// �\���ʒu
	Vec2	m_pos;
	// �ړ�
	Vec2	m_vec;
	//���݂��邩
	bool    m_isExist;
};