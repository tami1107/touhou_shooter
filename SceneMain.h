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

	// 初期化
	virtual void init();

	// 終了処理
	virtual void end();

	// 毎フレームの処理
	virtual SceneBase* update();
	// 毎フレームの描画
	virtual void draw();

	//virtual bool CheckHit();
	//virtual bool CheckHitEnemy();

	//弾の生成
	//virtual bool createShotPlayer(Vec2 pos);
	virtual bool createShotNormal(Vec2 pos);

	virtual bool createShotPlayerNormal(Vec2 pos);

	virtual bool createShotEnemyNormal(Vec2 pos);

	//当たり判定
	virtual bool CheckHit();
	virtual bool CheckPlayerShotHit();
	virtual bool CheckEnemyShotHit();
	virtual bool CheckGraze();
	//virtual bool CheckMyShotHit();
	//virtual bool createShotFall(Vec2 pos);
	//virtual bool createShotBound(Vec2 pos);

	

private:

	// プレイヤーのグラフィックハンドル
	int m_hPlayerGraphic[Player::kPlayerGraphicDivNum];
	int m_hEnemyGraphic[Enemy::kEnemyGraphicDivNum];
	int m_hShotGraphic;
	int m_hPointGraphic;
	int m_hCircleGraphic;
	
	// プレイヤーの攻撃力
	int m_hEnemyHP;
	// エネミーがヒットしたら画像を消す
	int m_hEnemyHit;

	// グレイズの回数
	int m_GrazePoint;

	// プレイヤーのショットハンドル
	int m_hPlayerShot1;
	int m_hPlayerShotNumber;
	int m_hPlayerSoundEffectHandle;
	// エネミーのショットハンドル
	int m_hEnemyShot1;
	int m_hEnemyShotNumber;

	// 位置情報 
	//(プレイヤーとエネミーの位置)
	int m_playerPosX;
	int m_playerPosY;
	int m_enemyPosX;
	int m_enemyPosY;
	//(プレイヤーとエネミーのショットの位置)
	int m_myShotPosX;
	int m_myShotPosY;
	int m_enemyShotPosX;
	int m_enemyShotPosY;

	// サウンドハンドル
	int m_hTestSound;
	int m_hSoundEffectHandle1;
	int m_EffectsHandle1;
	int m_EffectsHandle2;
	int m_EffectsHandle3;

	//当たり判定用　プレイヤーと円
	float m_PlayerPosX;
	float m_PlayerPosY;

	//フレーム(枠)
	int m_frameHandle;
	int m_TitleframeHandle;

public:
	// プレイヤー
	Player m_player;
	// 敵
	Enemy m_enemy;
	// プレイヤーショット
	ShotPlayerNormal m_ShotPlayerNormal;

	SceneBase m_SceneBase;

	SceneTitle m_SceneTitle;
	// ショット
	//ShotBase* m_pShot[kShotMax];
	std::vector<ShotBase*> m_pShotVt;

	std::vector<ShotPlayerNormal*> m_pShotPlayer1Vt;

	std::vector<ShotEnemyNormal*> m_pShotEnemy1Vt;

	std::vector<ShotNormal*> m_pShotEnemy2Vt;

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