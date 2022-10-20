#include "DxLib.h"

#include "SceneTitle.h"
#include "SelectChara.h"
#include "SceneMusic.h"
#include "SceneMain.h"
#include "SceneManager.h"
#include "SceneConfig.h"

namespace
{
	// タイトルの個数
	constexpr int kTitle = 5;
}

// メニュー項目の表示に必要な構造体を用意する
typedef struct {
	int x, y;       // 座標格納用変数
	char name[128]; // 項目名格納用変数
	int Cr;			// カラー用変数
} MenuElement_t;

// メニュー項目要素を5つ作る
MenuElement_t MenuElement[kTitle] = {
	// タグの中身の順番で格納される。
	// (例) { x , y , "neme" , GetColor(255, 255, 255)}
	{ 480, 100, "ゲームスタート" , GetColor(255, 0, 0)},
	{ 470, 170, "MusicRoom", GetColor(255, 255, 255)},
	{ 460, 240, "ヘルプ", GetColor(255, 255, 255)},
	{ 450, 310, "Config", GetColor(255, 255, 255)},
	{ 440, 380, "ゲーム終了", GetColor(255, 255, 255)},
};


void SceneTitle::init()
{
	m_SelectNum = 0; // 現在の選択番号
	m_Interval = kTInterval;

	m_BgmHandle1= LoadSoundMem("soundBgm/赤より紅い夢.wav");
	
	m_TitleframeHandle = LoadGraph("image/タイトル魔理沙.jpeg");

	PlaySoundMem(m_BgmHandle1, DX_PLAYTYPE_BACK);

	m_font = CreateFontToHandle("ＭＳ ゴシック", 30, 9, DX_FONTTYPE_NORMAL);
	

	m_isEnd = false;
}


SceneBase* SceneTitle::update()
{
	

	m_EffectsHandle1 = LoadSoundMem("soundEffect/選択音.wav");
	m_EffectsHandle2 = LoadSoundMem("soundEffect/決定音.wav");
	m_EffectsHandle3 = LoadSoundMem("soundEffect/キャンセル音.wav");

	int padState = GetJoypadInputState( DX_INPUT_KEY_PAD1 ) ;


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
			 m_SelectNum = (m_SelectNum + (kTitle-1)) % kTitle; // 現在の選択項目を一つ上にずらす(逆ループする)
			 PlaySoundMem(m_EffectsHandle1, DX_PLAYTYPE_BACK);
			
			 m_Interval = kTInterval;
		 }
		 if ((padState & PAD_INPUT_3) && (m_Interval <= 0))
		 {
			 PlaySoundMem(m_EffectsHandle2, DX_PLAYTYPE_BACK);
			 // m_SelectNum = 0のとき、3ボタンが押されたらSelectCharaにシーンを移行する
			 if (m_SelectNum == 0)
			 {
				 StopSoundMem(m_BgmHandle1);
			  // SelectCharaに切り替え
				 return(new SelectChara);
			 }
			 // m_SelectNum = 1のとき、3ボタンが押されたらSceneMusicにシーンを移行する
			 if (m_SelectNum == 1)
			 {
				StopSoundMem(m_BgmHandle1);
				// Musicに切り替え
				return(new SceneMusic);
			 }
			 // m_SelectNum = 3のとき、3ボタンが押されたらSceneConfigにシーンを移行する
			 if (m_SelectNum == 3)
			 {
				 StopSoundMem(m_BgmHandle1);
				 // SceneConfigに切り替え
				 return(new SceneConfig);
			 }
			 // m_SelectNum = 4のとき、3ボタンが押されたらゲームを終了する
			 if (m_SelectNum == 4)
			 {
				// ゲーム終了
				 DxLib_End();
			 }

			 m_Interval = kTInterval;
		 }
		 // 2ボタンを押したとき、m_SelectNumを強制的に4にする
		 if ((padState & PAD_INPUT_2) && (m_Interval <= 0))
		 {
			 m_SelectNum = 4;

			 PlaySoundMem(m_EffectsHandle3, DX_PLAYTYPE_BACK);
			 m_Interval = kTInterval;
		 }
	 }


	 if ((padState & PAD_INPUT_DOWN) || (padState & PAD_INPUT_UP) || (padState & PAD_INPUT_2))
	 {
		 for (int i = 0; i < kTitle; i++)
		 {   
			 // メニュー項目数である5個ループ処理
			 m_slide = i * 10;
			
			 if (i == m_SelectNum) {          // 今処理しているのが、選択番号と同じ要素なら
				 MenuElement[i].x = (460 - m_slide); // 座標を80にする
				 MenuElement[i].Cr = GetColor(255, 0, 0);
			 }
			 else {                       // 今処理しているのが、選択番号以外なら
				 MenuElement[i].x = 480- m_slide;// 座標を100にする
				 MenuElement[i].Cr = GetColor(255, 255, 255);
			 }
		 }
	 }

	return this;
}

void SceneTitle::draw()
{
	// フレーム(枠)描画
	DrawGraph(0, 0, m_TitleframeHandle, TRUE);

	for (int i = 0; i < 5; i++) 
	{   
		DrawFormatStringToHandle(MenuElement[i].x, MenuElement[i].y, MenuElement[i].Cr, m_font, MenuElement[i].name);
		// デバッグ用
		//DrawFormatString(0, 0, GetColor(255, 255, 255), "%d", m_SelectNum);
	}
	DrawString(0, 0, "↑↓で選択、Bボタンで決定、Aボタンでキャンセル", GetColor(255, 255, 255));
}