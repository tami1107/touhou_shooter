#include "DxLib.h"
#include <cassert>
#include "game.h"
#include "Player.h"

#include "SceneMain.h"



namespace
{
	// キャラクターアニメーションの速度
	int kAnimeChangeFrame = 8;
	// X方向、Y方向の速度
	constexpr float kSpeed = 4;
	// X方向、Y方向の速度
	constexpr float kSlow = -2;
	//ショットの発射間隔
	constexpr float kShotInterval = 8.0f;
	// 低速時のサークルの回転速度
	constexpr int kRevolutionSpeed = 10;
	// 画面端まで行動可能
	constexpr int kSceneEnd = 7;
	// 画面端
	constexpr int kLeft = 15;
	constexpr int kRight = 490;
}

Player::Player()
{
	for (auto& handle : m_handle)
	{
		handle = -1;
	}
	m_pointHandle = -1;
	m_circleHandle = -1;

	m_pMain = nullptr;
	m_shotInterval = 0;
	
	
	m_push = 0;

	m_revolution = 0.0;

	m_animeNo = 0;
	m_animeFrame = 0;
	m_dirNo = 0;
}

Player::~Player()
{

}

void Player::init()
{
	m_pos.x = Game::kScreenWidth / 2 - kPlayerGraphicSizeX / 2;
	m_pos.y = Game::kScreenHeight - kPlayerGraphicSizeY - 100;
	m_vec.x = kSpeed;
	m_vec.y = kSpeed;
	m_shotInterval = 0;
	m_animeNo = 0;
	m_animeFrame = 0;

	m_push = 0;
	m_revolution = 0.0;

	m_dirNo = 0;
}

void Player::update()
{
	m_revolution--;

	// パッド(もしくはキーボード)からの入力を取得する
	int padState = GetJoypadInputState(DX_INPUT_KEY_PAD1);

	//ショットを撃つ処理
	m_shotInterval--;
	if (m_shotInterval < 0)m_shotInterval = 0;

	if (m_shotInterval <= 0)
	{
		if (padState & PAD_INPUT_1)
		{
			if (m_pMain->createShotPlayerNormal(getPos()))
			{
				// 弾を打った時に効果音を出す
				PlaySoundMem(m_PlayerSoundEffectHandle, DX_PLAYTYPE_BACK);
				m_shotInterval = kShotInterval;
			}
		}
	}


	if (padState & PAD_INPUT_UP)
	{
		if (padState & PAD_INPUT_4) m_pos.y -= (m_vec.y + kSlow);
		else m_pos.y -= m_vec.y;
			
	
		if (m_pos.y < 0) m_pos.y = 0;
	}
	if (padState & PAD_INPUT_DOWN)
	{
		if (padState & PAD_INPUT_4) m_pos.y += (m_vec.y + kSlow);
		else m_pos.y += m_vec.y;
	

		if (m_pos.y > (Game::kScreenHeight)-(kPlayerGraphicSizeY)) m_pos.y = (Game::kScreenHeight)-(kPlayerGraphicSizeY);
	}
	if (padState & PAD_INPUT_LEFT)
	{
		m_dirNo = 8;
		if (padState & PAD_INPUT_4) m_pos.x -= (m_vec.x + kSlow);
		else m_pos.x -= m_vec.x;
		
		
		
		if (m_pos.x < kLeft) m_pos.x = kLeft;
		
	}
	if (padState & PAD_INPUT_RIGHT)
	{
		m_dirNo = 4;
		if (padState & PAD_INPUT_4) m_pos.x += (m_vec.x + kSlow);
		else m_pos.x += m_vec.x;
		
		if (m_pos.x > (kRight)) m_pos.x = (kRight);
	}
	if (padState & PAD_INPUT_4)
	{
		m_push = 1;
	}
	else m_push = 0;


	m_animeFrame++;
	if (m_animeFrame >= kPlayerGraphicDivX * kAnimeChangeFrame)
	{
		m_animeFrame = 0;
	}



	int tempAnimeNo = m_animeFrame / kAnimeChangeFrame;
	m_animeNo = m_dirNo + tempAnimeNo;

	m_dirNo = 0;
}

void Player::draw()
{
	DrawGraph(static_cast<int>(m_pos.x), static_cast<int>(m_pos.y), m_handle[m_animeNo], true);
	if (m_push == 1)
	{
		// playerの中心点
		DrawGraph(m_pos.x + (kPlayerGraphicSizeX / 2) - (kPointHandleSizeX / 2), m_pos.y + (kPlayerGraphicSizeY / 2) - (kPointHandleSizeY / 2), m_pointHandle, TRUE);

		// 読みこんだグラフィックを回転描画
		DrawRotaGraph2(m_pos.x + (kPlayerGraphicSizeX / 2), m_pos.y + (kPlayerGraphicSizeY / 2), (kCircleHandleSizeX / 2), (kCircleHandleSizeY / 2), 0.8, m_revolution / kRevolutionSpeed / DX_PI, m_circleHandle, TRUE);
	
	}
}
