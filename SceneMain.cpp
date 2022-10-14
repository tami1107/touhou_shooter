
#include "DxLib.h"
#include "SceneMain.h"

#include "SceneTitle.h"
#include <cassert>
#include "ShotNormal.h"
#include "ShotPlayerNormal.h"



namespace
{
	//ショットの発射間隔
	constexpr int kShotInterval = 16;
	// グラフィックファイル名
	//const char* const kPlayerGraphicFilename = "image/player.png";
	const char* const kEnemyGraphicFilename = "image/enemy.bmp";
	const char* const kPlayerGraphicFilename = "image/魔理沙.png";

}

SceneMain::SceneMain()
{
	//	m_hPlayerGraphic = -1;
	for (auto& handle : m_hPlayerGraphic)
	{
		handle = -1;
	}
	m_hEnemyGraphic = -1;
	m_hShotGraphic = -1;
	m_hPlayerShotNumber = 0;
}
SceneMain::~SceneMain()
{

}

// 初期化
void SceneMain::init()
{
	// グラフィックのロード
	LoadDivGraph(kPlayerGraphicFilename, Player::kPlayerGraphicDivNum,
		Player::kPlayerGraphicDivX, Player::kPlayerGraphicDivY,
		Player::kPlayerGraphicSizeX, Player::kPlayerGraphicSizeY, m_hPlayerGraphic);
	m_hEnemyGraphic = LoadGraph(kEnemyGraphicFilename);

	m_hShotGraphic = LoadGraph("image/shot.bmp");
	m_hPlayerShot1 = LoadGraph("image/PlayerShot1.png");



	// サウンドのロード
	m_hTestSound = LoadSoundMem("sound/cursor0.mp3");

	for (int i = 0; i < Player::kPlayerGraphicDivNum; i++)
	{
		m_player.setHandle(i, m_hPlayerGraphic[i]);
	}
	m_player.init();
	m_player.setMain(this);
	m_enemy.setHandle(m_hEnemyGraphic);
	m_enemy.init();
	m_enemy.setMain(this);
}

// 終了処理
void SceneMain::end()
{
	// グラフィックアンロード
	for (auto& handle : m_hPlayerGraphic)
	{
		DeleteGraph(handle);
	}
	DeleteGraph(m_hEnemyGraphic);
	DeleteGraph(m_hShotGraphic);
	// サウンドアンロード
	DeleteSoundMem(m_hTestSound);

	for (auto& pShot : m_pShotVt)
	{
		assert(pShot);
		delete pShot;
		pShot = nullptr;
	}
}

// 毎フレームの処理
SceneBase* SceneMain::update()
{
	int padState = GetJoypadInputState(DX_INPUT_KEY_PAD1);
	if (padState & PAD_INPUT_1)
	{
		PlaySoundMem(m_hTestSound, DX_PLAYTYPE_BACK, true);
	}
	m_player.update();
	m_enemy.update();
	std::vector<ShotBase*>::iterator it = m_pShotVt.begin();
	while (it != m_pShotVt.end())
	{
		auto& pShot = (*it);
		assert(pShot);
		pShot->update();
		if (!pShot->isExist())
		{
			delete pShot;
			pShot = nullptr;

			//vectorの要素削除
			it = m_pShotVt.erase(it);
			continue;
		}
		it++;
	}

	if (padState & PAD_INPUT_3)
	{
		// Musicに切り替え
		return(new SceneTitle);
	}

	return this;
#if false
	for (auto& pShot : m_pShotVt)
	{
		if (!pShot) continue;		//nullの場合処理しない
		pShot->update();
		if (!pShot->isExist())
		{
			delete pShot;
			pShot = nullptr;

			//vectorの要素削除

		}
	}
#endif
}

// 毎フレームの描画
void SceneMain::draw()
{
	m_player.draw();
	m_enemy.draw();
	for (auto& pShot : m_pShotVt)
	{
		assert(pShot);
		pShot->draw();
	}

	//現在存在している弾の数を表示
	DrawFormatString(0, 0, GetColor(255, 255, 255), "弾の数:%d", m_pShotVt.size());
}

//bool SceneMain::createShotPlayer(Vec2 pos)
//{
//	ShotPlayer* pShot = new ShotPlayer;
//	pShot->setHandle(m_hShotGraphic);
//	pShot->start(pos);
//	m_pShotVt.push_back(pShot);
//
//	return true;
//}

bool SceneMain::createShotNormal(Vec2 pos)
{
	ShotNormal* pShot = new ShotNormal;
	pShot->setHandle(m_hShotGraphic);
	pShot->start(pos);
	m_pShotVt.push_back(pShot);
	
	return true;
}

bool SceneMain::createShotPlayerNormal(Vec2 pos)
{
	ShotPlayerNormal* pShot = new ShotPlayerNormal;
	pShot->setHandle(m_hPlayerShot1);
	pShot->start(pos);
	m_pShotVt.push_back(pShot);

	m_hPlayerShotNumber = 1;
	return true;
}

//bool SceneMain::createShotFall(Vec2 pos)
//{
//	ShotFall* pShot = new ShotFall;
//	pShot->setHandle(m_hShotGraphic);
//	pShot->start(pos);
//	m_pShotVt.push_back(pShot);
//
//	return true;
//}
//
//bool SceneMain::createShotBound(Vec2 pos)
//{
//	ShotBound* pShot = new ShotBound;
//	pShot->setHandle(m_hShotGraphic);
//	pShot->start(pos);
//	m_pShotVt.push_back(pShot);
//
//	return true;
//}












//#include "DxLib.h"
//
//#include "game.h"
//#include"SceneMain.h"
//
//
//void SceneMain::init()
//{
//	
//
//	m_isEnd = false;
//}
//
//
//SceneBase* SceneMain::update()
//{
//	
//
//	return this;
//}
//
//void SceneMain::draw()
//{
//	m_player.draw();
//
//}