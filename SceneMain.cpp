
#include "DxLib.h"
#include "SceneMain.h"

#include "SceneTitle.h"
#include <cassert>
#include "ShotNormal.h"
#include "ShotPlayerNormal.h"
#include "ShotEnemyNormal.h"
#include "Player.h"


namespace
{
	//ショットの発射間隔
	constexpr int kShotInterval = 16;
	// グラフィックファイル名
	//const char* const kPlayerGraphicFilename = "image/player.png";
	//const char* const kEnemyGraphicFilename = "image/フランドール.png";

	const char* const kEnemyGraphicFilename = "image/フランアニメーション.png";
	const char* const kPlayerGraphicFilename = "image/魔理沙.png";
	const char* const kPlayerPoint = "image/低速時の中心点.png";
	const char* const kCirclePoint = "image/低速時のサークルエフェクト.png";

	// 当たり判定の大きさ
	static constexpr int kPlayerHitBoxSize = 4;
	static constexpr int kEnemyHitBoxSize = 40;
	static constexpr int kPlayerShot1Size = 5;
	static constexpr int kEnemyShot1Size = 5;
	
	
	// プレイヤーグラフィックサイズ
	static constexpr int kPlayerGraphicSizeX = Player::kPlayerGraphicSizeX;
	static constexpr int kPlayerGraphicSizeY = Player::kPlayerGraphicSizeX;

	// 敵グラフィックサイズ
	static constexpr int kEnemyGraphicSizeX = Enemy::kEnemyGraphicSizeX;
	static constexpr int kEnemyGraphicSizeY = Enemy::kEnemyGraphicSizeY;

	// 弾(プレイヤー)グラフィックサイズ
	static constexpr int kPlayerShot1GraphicSizeX = ShotPlayerNormal::kPlayerShot1GraphicSizeX;
	static constexpr int kPlayerShot1GraphicSizeY = ShotPlayerNormal::kPlayerShot1GraphicSizeY;
	// 弾(エネミー)グラフィックサイズ
	static constexpr int kEnemyShot1GraphicSizeX = ShotEnemyNormal::kEnemyShot1GraphicSizeX;
	static constexpr int kEnemyShot1GraphicSizeY = ShotEnemyNormal::kEnemyShot1GraphicSizeY;

}

SceneMain::SceneMain()
{
	//	m_hPlayerGraphic = -1;
	for (auto& handle : m_hPlayerGraphic)
	{
		handle = -1;
	}

	for (auto& handle : m_hEnemyGraphic)
	{
		handle = -1;
	}

	//m_hEnemyGraphic = -1;
	m_hShotGraphic = -1;
	m_hPointGraphic = -1;
	m_hCircleGraphic = -1;

	m_EffectsHandle1 = -1;

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

	LoadDivGraph(kEnemyGraphicFilename, Enemy::kEnemyGraphicDivNum,
		Enemy::kEnemyGraphicDivX, Enemy::kEnemyGraphicDivY,
		Enemy::kEnemyGraphicSizeX, Enemy::kEnemyGraphicSizeY, m_hEnemyGraphic);



	//m_hEnemyGraphic = LoadGraph(kEnemyGraphicFilename);
	m_hPointGraphic = LoadGraph(kPlayerPoint);
	m_hCircleGraphic = LoadGraph(kCirclePoint);

	// ショットのロード
	m_hShotGraphic = LoadGraph("image/shot.bmp");
	m_hPlayerShot1 = LoadGraph("image/PlayerShot1.png");
	m_hEnemyShot1 = LoadGraph("image/EnemyShot1.png");

	

	// サウンドのロード
	m_hTestSound = LoadSoundMem("sound/cursor0.mp3");
	m_hSoundEffectHandle1 = LoadSoundMem("soundEffect/選択音.wav");
	m_hPlayerSoundEffectHandle = LoadSoundMem("soundEffect/ショット時の効果音.mp3");
	

	for (int i = 0; i < Player::kPlayerGraphicDivNum; i++)
	{
		m_player.setHandle(i, m_hPlayerGraphic[i]);
	}
	m_player.init();
	m_player.setMain(this);
	m_player.setPointHandle(m_hPointGraphic);
	m_player.setCircleHandle(m_hCircleGraphic);
	m_player.setPlayerSoundEffectHandle(m_hPlayerSoundEffectHandle);
	
	
	for (int i = 0; i < Enemy::kEnemyGraphicDivNum; i++)
	{
		m_enemy.setHandle(i, m_hEnemyGraphic[i]);
	}
	m_enemy.init();
	m_enemy.setMain(this);

	m_SceneBase.setSoundEffectHandle1(m_hSoundEffectHandle1);
}

// 終了処理
void SceneMain::end()
{
	// グラフィックアンロード
	for (auto& handle : m_hPlayerGraphic)
	{
		DeleteGraph(handle);
	}
	
	for (auto& handle : m_hEnemyGraphic)
	{
		DeleteGraph(handle);
	}
	
	//DeleteGraph(m_hEnemyGraphic);
	DeleteGraph(m_hShotGraphic);

	DeleteGraph(m_hPointGraphic);
	DeleteGraph(m_hCircleGraphic);
	// サウンドアンロード
	DeleteSoundMem(m_hTestSound);

	for (auto& pShot : m_pShotVt)
	{
		assert(pShot);
		delete pShot;
		pShot = nullptr;
	}
	// プレイヤーのショット
	for (auto& pShotPlayer1 : m_pShotPlayer1Vt)
	{
		assert(pShotPlayer1);
		delete pShotPlayer1;
		pShotPlayer1 = nullptr;
	}
	// エネミーのショット
	for (auto& pShotEnemy1 : m_pShotEnemy1Vt)
	{
		assert(pShotEnemy1);
		delete pShotEnemy1;
		pShotEnemy1 = nullptr;
	}




	for (auto& pShotEnemy2 : m_pShotEnemy2Vt)
	{
		assert(pShotEnemy2);
		delete pShotEnemy2;
		pShotEnemy2 = nullptr;
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

	std::vector<ShotPlayerNormal*>::iterator itShotPlayer1 = m_pShotPlayer1Vt.begin();
	while (itShotPlayer1 != m_pShotPlayer1Vt.end())
	{
		auto& pShotPlayer1 = (*itShotPlayer1);
		assert(pShotPlayer1);
		pShotPlayer1->update();
		if (!pShotPlayer1->isExist())
		{
			delete pShotPlayer1;
			pShotPlayer1 = nullptr;

			//vectorの要素削除
			itShotPlayer1 = m_pShotPlayer1Vt.erase(itShotPlayer1);
			continue;
		}
		itShotPlayer1++;
	}

	std::vector<ShotEnemyNormal*>::iterator itShotEnemy1 = m_pShotEnemy1Vt.begin();
	while (itShotEnemy1 != m_pShotEnemy1Vt.end())
	{
		auto& pShotEnemy1 = (*itShotEnemy1);
		assert(pShotEnemy1);
		pShotEnemy1->update();
		if (!pShotEnemy1->isExist())
		{
			delete pShotEnemy1;
			pShotEnemy1 = nullptr;

			//vectorの要素削除
			itShotEnemy1 = m_pShotEnemy1Vt.erase(itShotEnemy1);
			continue;
		}
		itShotEnemy1++;
	}



	if (padState & PAD_INPUT_3)
	{
		// Titleに切り替え
		return(new SceneTitle);
	}

	// エネミーに当たった場合、Titleに戻る
	if (CheckHit() == true)
	{
		// Titleに切り替え
		return(new SceneTitle);
	}
	
	// プレイヤーの弾がエネミーに当たった場合、Titleに戻る
	if (CheckPlayerShotHit() == true)
	{
		// Titleに切り替え
		return(new SceneTitle);
	}

	// エネミーの弾がプレイヤーに当たった場合、Titleに戻る
	if (CheckEnemyShotHit() == true)
	{
		// Titleに切り替え
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
	
	// 位置情報の取得
	//(プレイヤー位置)
	m_player.getPos();
	m_playerPosX = m_player.getPos().x + (kPlayerGraphicSizeX / 2);
	m_playerPosY = m_player.getPos().y + (kPlayerGraphicSizeY / 2);
	//(エネミー位置)
	m_enemy.getPos();
	m_enemyPosX = m_enemy.getPos().x + (kEnemyGraphicSizeX / 2);
	m_enemyPosY = m_enemy.getPos().y + (kEnemyGraphicSizeY / 2);


	m_enemy.draw();
	m_player.draw();	
	for (auto& pShot : m_pShotVt)
	{
		assert(pShot);
		pShot->draw();
	}
	//プレイヤーの弾表示
	for (auto& pShot : m_pShotPlayer1Vt)
	{
		assert(pShot);
		
		pShot->draw();
	}
	//エネミーの弾表示
	for (auto& pShot : m_pShotEnemy1Vt)
	{
		assert(pShot);

		pShot->draw();
	}
	// 当たり判定の表示
	DrawCircle(m_playerPosX, m_playerPosY, kPlayerHitBoxSize,GetColor(255, 255, 255), FALSE);
	DrawCircle(m_enemyPosX, m_enemyPosY, kEnemyHitBoxSize, GetColor(255, 255, 255), FALSE);

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
	m_pShotPlayer1Vt.push_back(pShot);

	m_hPlayerShotNumber = 1;
	return true;
}

bool SceneMain::createShotEnemyNormal(Vec2 pos)
{
	ShotEnemyNormal* pShot = new ShotEnemyNormal;
	pShot->setHandle(m_hEnemyShot1);
	pShot->start(pos);
	m_pShotEnemy1Vt.push_back(pShot);

	m_hPlayerShotNumber = 1;
	return true;
}

//bool SceneMain::CheckHit()
//{
//	
//
//	float dx = t_circleA.x - t_circleB.x;
//	float dy = t_circleA.y - t_circleB.y;
//	float dr = dx * dx + dy * dy;
//
//	float ar = t_circleA.r + t_circleB.r;
//	float dl = ar * ar;
//	if (dr < dl)
//	{
//		return true;
//	}
//
//	return false;
//}

bool SceneMain::CheckHit()
{
	//当たり判定
	float dx = m_playerPosX - m_enemyPosX;
	float dy = m_playerPosY - m_enemyPosY;
	float dr = dx * dx + dy * dy;

	float ar = kPlayerHitBoxSize + kEnemyHitBoxSize;
	float dl = ar * ar;
	if (dr < dl)
	{
		return true;
	}

	return false;
}


bool SceneMain::CheckPlayerShotHit()
{
	std::vector<ShotPlayerNormal*>::iterator itShotPlayer1 = m_pShotPlayer1Vt.begin();
	while (itShotPlayer1 != m_pShotPlayer1Vt.end())
	{
		auto& pShot = (*itShotPlayer1);
		pShot->getPos();
		
		//プレイヤーのショットの中心座標を取得
		m_myShotPosX = (pShot->getPos().x) + (kPlayerShot1GraphicSizeX / 2);
		m_myShotPosY = (pShot->getPos().y) + (kPlayerShot1GraphicSizeY / 2);

		//当たり判定
		float dx = m_enemyPosX - m_myShotPosX;
		float dy = m_enemyPosY - m_myShotPosY;
		float dr = dx * dx + dy * dy;

		float ar = kPlayerShot1Size + kEnemyHitBoxSize;
		float dl = ar * ar;

		DrawCircle(m_myShotPosX, m_myShotPosY, kPlayerShot1Size, GetColor(255, 0, 0), FALSE);
		//現在存在している弾の数を表示
		DrawFormatString(0, 10, GetColor(255, 255, 255), "自機弾の数:%d", m_pShotPlayer1Vt.size());
		if (dr < dl)
		{
			return true;
		}
		else
		{
			itShotPlayer1++;

			continue;
		}
		return false;
	}
}


bool SceneMain::CheckEnemyShotHit()
{
	std::vector<ShotEnemyNormal*>::iterator itShotEnemy1 = m_pShotEnemy1Vt.begin();
	while (itShotEnemy1 != m_pShotEnemy1Vt.end())
	{
		auto& pShot = (*itShotEnemy1);
		pShot->getPos();
		//エネミーのショットの中心座標を取得
		m_enemyShotPosX = pShot->getPos().x + (kEnemyShot1GraphicSizeX / 2);
		m_enemyShotPosY = pShot->getPos().y + (kEnemyShot1GraphicSizeY / 2);

		//当たり判定
		float dx2 = m_playerPosX - m_enemyShotPosX;
		float dy2 = m_playerPosY - m_enemyShotPosY;
		float dr2 = dx2 * dx2 + dy2 * dy2;

		float ar2 = kEnemyShot1Size + kPlayerHitBoxSize;
		float dl2 = ar2 * ar2;

		DrawCircle(m_enemyShotPosX, m_enemyShotPosY, kEnemyShot1Size, GetColor(255, 0, 0), FALSE);
		//現在存在している弾の数を表示
		DrawFormatString(0, 25, GetColor(255, 255, 255), "敵弾の数:%d", m_pShotEnemy1Vt.size());
		if (dr2 < dl2)
		{
			return true;
		}
		else
		{
			itShotEnemy1++;

			continue;
		}
		return false;
	}
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