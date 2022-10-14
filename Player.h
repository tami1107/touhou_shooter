#pragma once

#include "Vec2.h"

class SceneMain;

class Player
{
public:
	// 定数定義

	// プレイヤーグラフィック分割数
	static constexpr int kPlayerGraphicDivX = 4;
	static constexpr int kPlayerGraphicDivY = 3;
	static constexpr int kPlayerGraphicDivNum = kPlayerGraphicDivX * kPlayerGraphicDivY;

	// プレイヤーグラフィックサイズ
	static constexpr int kPlayerGraphicSizeX = 50;
	static constexpr int kPlayerGraphicSizeY = 50;

public:
	Player();
	virtual ~Player();

	// グラフィックデータ設定
	void setHandle(int index, int handle) { m_handle[index] = handle; }

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
	int m_handle[kPlayerGraphicDivNum];

	//SceneMainのポインタ
	SceneMain* m_pMain;

	// 表示位置
	Vec2 m_pos;
	// 移動
	Vec2 m_vec;

	int m_shotInterval;

	int m_point;
	int m_pointSizeX, m_pointSizeY;

	int m_circle;
	int m_circleSizeX, m_circleSizeY;
	double m_revolution;

	int m_push;
	// キャラクターのアニメーション
	int m_animeNo;	// 表示する番号
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
//	// テキスト表示位置変更
//	int m_SelectNum;
//	int m_Interval;
//	// グラフィックハンドル
//	int m_handle;
//
//	bool m_isEnd;
//};