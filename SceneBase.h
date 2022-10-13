#pragma once

// ゲームシーン基底クラス
class SceneBase
{
public:
	SceneBase() {}
	virtual ~SceneBase() {}


	virtual void init() {}
	virtual void end() {}

	virtual SceneBase* update() { return this; }
	virtual void draw() {}

	// シーン終了
	virtual bool isEnd() { return false; }

	int TEffectsHandle1;// 選択音のハンドル
	int TEffectsHandle2;// 決定音のハンドル
	int TEffectsHandle3;// キャンセル音のハンドル



};