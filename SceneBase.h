#pragma once

// ゲームシーン基底クラス
class SceneBase
{
public:
	SceneBase() 
	{
		int m_SoundEffectHandle1 = 0;

		int m_EffectsHandle1 = 0;// 選択音のハンドル
		int m_EffectsHandle2 = 0;// 決定音のハンドル
		int m_EffectsHandle3 = 0;// キャンセル音のハンドル

		int kTInterval = 15;
	}
	virtual ~SceneBase() {}

	

	virtual void init() {}
	virtual void end() {}

	virtual SceneBase* update() { return this; }
	virtual void draw() {}

	// シーン終了
	virtual bool isEnd() { return false; }

	

	int m_EffectsHandle1;// 選択音のハンドル
	int m_EffectsHandle2;// 決定音のハンドル
	int m_EffectsHandle3;// キャンセル音のハンドル

	int kTInterval = 15;

	

};