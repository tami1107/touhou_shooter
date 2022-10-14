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

	// 初期化
	virtual void init();

	// 終了処理
	virtual void end();

	// 毎フレームの処理
	virtual SceneBase* update();
	// 毎フレームの描画
	virtual void draw();

	//弾の生成
	//virtual bool createShotPlayer(Vec2 pos);
	virtual bool createShotNormal(Vec2 pos);

	virtual bool createShotPlayerNormal(Vec2 pos);
	//virtual bool createShotFall(Vec2 pos);
	//virtual bool createShotBound(Vec2 pos);

private:

	// プレイヤーのグラフィックハンドル
	int m_hPlayerGraphic[Player::kPlayerGraphicDivNum];
	int m_hPlayerCenter;

	int m_hEnemyGraphic;
	int m_hShotGraphic;
	// プレイヤーのショットハンドル
	int m_hPlayerShot1;
	int m_hPlayerShotNumber;

	// サウンドハンドル
	int m_hTestSound;
	// プレイヤー
	Player m_player;
	// 敵
	Enemy m_enemy;
	// ショット
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
//	// テキスト表示位置変更
//	int m_SelectNum;
//	int m_Interval;
//
//	// プレイヤー
//	Player m_player;
//
//	bool m_isEnd;
//};