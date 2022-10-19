#pragma once

// �Q�[���V�[�����N���X
class SceneBase
{
public:
	SceneBase() 
	{
		//int m_SoundEffectHandle1 = 0;

		int m_EffectsHandle1 = 0;// �I�����̃n���h��
		int m_EffectsHandle2 = 0;// ���艹�̃n���h��
		int m_EffectsHandle3 = 0;// �L�����Z�����̃n���h��

		int kTInterval = 15;
	}
	virtual ~SceneBase() {}

	// ���ʉ��̃n���h��
	void setSoundEffectHandle1(int SoundEffectHandle1) { m_SoundEffectHandle1 = SoundEffectHandle1; }


	virtual void init() {}
	virtual void end() {}

	virtual SceneBase* update() { return this; }
	virtual void draw() {}

	// �V�[���I��
	virtual bool isEnd() { return false; }

	
	// �T�E���h�n���h��
	int m_SoundEffectHandle1;

	int m_EffectsHandle1;// �I�����̃n���h��
	int m_EffectsHandle2;// ���艹�̃n���h��
	int m_EffectsHandle3;// �L�����Z�����̃n���h��

	int kTInterval = 15;

	

};