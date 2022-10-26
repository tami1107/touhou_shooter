#include "DxLib.h"
#include "SceneMain.h"
#include "SceneTitle.h"
#include "SceneGameOver.h"

namespace
{
	// タイトルの個数
	constexpr int kTitle = 2;
}

// メニュー項目の表示に必要な構造体を用意する
typedef struct {
	int x, y;       // 座標格納用変数
	char name[128]; // 項目名格納用変数
	int Cr;			// カラー用変数
} MenuElement;

// メニュー項目要素を5つ作る
MenuElement MenuElement_o[kTitle] = {
	// タグの中身の順番で格納される。
	// (例) { x , y , "neme" , GetColor(255, 255, 255)}
	{ 480, 100, "リトライ" , GetColor(255, 0, 0)},
	{ 470, 170, "タイトルに戻る", GetColor(255, 255, 255)},
};


void SceneGameOver::init()
{
	m_SelectNum = 0; // 現在の選択番号
	m_Interval = kTInterval;



	m_font = CreateFontToHandle("ＭＳ ゴシック", 30, 9, DX_FONTTYPE_NORMAL);


	m_isEnd = false;
}


SceneBase* SceneGameOver::update()
{


	m_EffectsHandle1 = LoadSoundMem("soundEffect/選択音.wav");
	m_EffectsHandle2 = LoadSoundMem("soundEffect/決定音.wav");
	

	int padState = GetJoypadInputState(DX_INPUT_KEY_PAD1);


	// 計算フェーズ 
	m_Interval--;
	if (m_Interval < 0) m_Interval = 0;

	if (m_Interval <= 0)
	{
		if ((padState & PAD_INPUT_DOWN) && (m_Interval <= 0))
		{
			m_SelectNum = (m_SelectNum + 1) % kTitle; // 現在の選択項目を一つ下にずらす(ループする)
			PlaySoundMem(m_EffectsHandle1, DX_PLAYTYPE_BACK);

			m_Interval = kTInterval;
		}
		if ((padState & PAD_INPUT_UP) && (m_Interval <= 0))
		{
			m_SelectNum = (m_SelectNum + (kTitle - 1)) % kTitle; // 現在の選択項目を一つ上にずらす(逆ループする)
			PlaySoundMem(m_EffectsHandle1, DX_PLAYTYPE_BACK);

			m_Interval = kTInterval;
		}
		if ((padState & PAD_INPUT_3) && (m_Interval <= 0))
		{
			PlaySoundMem(m_EffectsHandle2, DX_PLAYTYPE_BACK);
			// m_SelectNum = 0のとき、3ボタンが押されたらSceneMainにシーンを移行する
			if (m_SelectNum == 0)
			{
				StopSoundMem(m_BgmHandle1);
				// SelectCharaに切り替え
				return(new SceneMain);
			}
			// m_SelectNum = 1のとき、3ボタンが押されたらSceneTitleにシーンを移行する
			if (m_SelectNum == 1)
			{
				StopSoundMem(m_BgmHandle1);
				// Titleに切り替え
				return(new SceneTitle);
			}

			m_Interval = kTInterval;
		}
	
	}


	if ((padState & PAD_INPUT_DOWN) || (padState & PAD_INPUT_UP) )
	{
		for (int i = 0; i < kTitle; i++)
		{
			// メニュー項目数である5個ループ処理
			m_slide = i * 10;

			if (i == m_SelectNum) {          // 今処理しているのが、選択番号と同じ要素なら
				MenuElement_o[i].x = (460 - m_slide); // 座標を80にする
				MenuElement_o[i].Cr = GetColor(255, 0, 0);
			}
			else {                       // 今処理しているのが、選択番号以外なら
				MenuElement_o[i].x = 480 - m_slide;// 座標を100にする
				MenuElement_o[i].Cr = GetColor(255, 255, 255);
			}
		}
	}

	return this;
}

void SceneGameOver::draw()
{


	for (int i = 0; i < 5; i++)
	{
		DrawFormatStringToHandle(MenuElement_o[i].x, MenuElement_o[i].y, MenuElement_o[i].Cr, m_font, MenuElement_o[i].name);
		// デバッグ用
		//DrawFormatString(0, 0, GetColor(255, 255, 255), "%d", m_SelectNum);
	}
	
}