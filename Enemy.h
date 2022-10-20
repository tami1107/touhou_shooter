#pragma once

#include "Vec2.h"

class SceneMain;

class Enemy
{
public:
	// 敵グラフィック分割数
	static constexpr int kEnemyGraphicDivX = 6;
	static constexpr int kEnemyGraphicDivY = 1;
	static constexpr int kEnemyGraphicDivNum = kEnemyGraphicDivX * kEnemyGraphicDivY;

	// 敵グラフィックサイズ
	static constexpr int kEnemyGraphicSizeX = 504/6;
	static constexpr int kEnemyGraphicSizeY = 126;


public:
	Enemy();
	virtual ~Enemy();

	// グラフィックデータ設定
	void setHandle(int index, int handle) { m_handle[index] = handle; }
	void setEnemyHP(int EnemyHP) { m_EnemyHP = EnemyHP; }

	// プレイヤーの初期化
	void init();

	//SceneMainクラスのポインタ設定
	void setMain(SceneMain* pMain) { m_pMain = pMain; }

	// 処理
	void update();
	// 描画
	void draw();

	// 情報の取得
	Vec2 getPos() const { return m_pos; }

private:
	int m_handle[kEnemyGraphicDivNum];

	int m_EnemyHP;

	

	//SceneMainのポインタ
	SceneMain* m_pMain;

	// 表示位置
	Vec2 m_pos;
	// 移動
	Vec2 m_vec;

	// ショットのインターバル
	int m_shotInterval;
	
	// キャラクターのアニメーション
	int m_animeNo;	// 表示する番号
	int m_animeFrame;
	int m_dirNo;
};
