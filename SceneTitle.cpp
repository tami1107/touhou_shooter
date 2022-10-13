#include "DxLib.h"

#include "SceneTitle.h"
#include "SelectChara.h"
#include "SceneMusic.h"
#include "SceneMain.h"
#include "SceneManager.h"

namespace
{
	// 停止したショットを再度打ち出すまでの時間
	constexpr int kTInterval = 15;
	// タイトルの個数
	constexpr int kTitle = 5;

	
}



// メニュー項目の表示に必要な構造体を用意する
typedef struct {
	int x, y;       // 座標格納用変数
	char name[128]; // 項目名格納用変数
	int Cr;
} MenuElement_t;

// メニュー項目要素を5つ作る
MenuElement_t MenuElement[kTitle] = {
		{ 380, 100, "ゲームスタート" , GetColor(255, 0, 0)}, // タグの中身の順番で格納される。xに80が、yに100が、nameに"ゲームスタート"が
		{ 370, 170, "MusicRoom", GetColor(255, 255, 255)},
		{ 360, 240, "ヘルプ", GetColor(255, 255, 255)},
		{ 350, 310, "コンフィグ", GetColor(255, 255, 255)},
		{ 340, 380, "ゲーム終了", GetColor(255, 255, 255)},
};


void SceneTitle::init()
{
	m_SelectNum = 0; // 現在の選択番号
	m_Interval = kTInterval;

	PlaySoundFile("soundBgm/赤より紅い夢.wav",DX_PLAYTYPE_LOOP);
	
	m_isEnd = false;
}


SceneBase* SceneTitle::update()
{
	

	TEffectsHandle1 = LoadSoundMem("soundEffect/選択音.wav");
	TEffectsHandle2 = LoadSoundMem("soundEffect/決定音.wav");
	TEffectsHandle3 = LoadSoundMem("soundEffect/キャンセル音.wav");

	

	int padState = 0;

	int slide;

	padState = GetJoypadInputState( DX_INPUT_KEY_PAD1 ) ;


	// 計算フェーズ 
	 m_Interval--;
	 if (m_Interval < 0) m_Interval = 0;

	 if (m_Interval <= 0)
	 {
		 if ((padState & PAD_INPUT_DOWN) && (m_Interval <= 0))
		 {
			 m_SelectNum = (m_SelectNum + 1) % kTitle; // 現在の選択項目を一つ下にずらす(ループする)
			 PlaySoundMem(TEffectsHandle1, DX_PLAYTYPE_BACK);
			 m_Interval = kTInterval;
		 }
		 if ((padState & PAD_INPUT_UP) && (m_Interval <= 0))
		 {
			 m_SelectNum = (m_SelectNum + (kTitle-1)) % kTitle; // 現在の選択項目を一つ上にずらす(逆ループする)
			 PlaySoundMem(TEffectsHandle1, DX_PLAYTYPE_BACK);
			 m_Interval = kTInterval;
		 }
		 if ((padState & PAD_INPUT_4) && (m_Interval <= 0))
		 {
			 PlaySoundMem(TEffectsHandle2, DX_PLAYTYPE_BACK);

			 if (m_SelectNum == 0)
			 {// 4ボタンが押された瞬間だけ処理
				// Mainに切り替え
				 return(new SelectChara);
				 
			 }

			 if (m_SelectNum == 1)
			 {// 4ボタンが押された瞬間だけ処理
				StopSoundFile();
				// Musicに切り替え
				return(new SceneMusic);
			 }
			 if (m_SelectNum == 4)
			 {// 4ボタンが押された瞬間だけ処理
				
				 DxLib_End();
				 
			 }

			 m_Interval = kTInterval;
		 }
		 if ((padState & PAD_INPUT_3) && (m_Interval <= 0))
		 {
			
			 m_SelectNum = 4;
			 
			 PlaySoundMem(TEffectsHandle3, DX_PLAYTYPE_BACK);
			 m_Interval = kTInterval;
		 }
	 }


	 if ((padState & PAD_INPUT_DOWN) || (padState & PAD_INPUT_UP) || (padState & PAD_INPUT_3))
	 {
		 for (int i = 0; i < kTitle; i++)
		 {   
			 
			 // メニュー項目数である5個ループ処理
			 slide = i * 10;
			
			 if (i == m_SelectNum) {          // 今処理しているのが、選択番号と同じ要素なら
				 MenuElement[i].x = (360 - slide); // 座標を80にする
				 MenuElement[i].Cr = GetColor(255, 0, 0);
			 }
			 else {                       // 今処理しているのが、選択番号以外なら
				 MenuElement[i].x = 380- slide;// 座標を100にする
				 MenuElement[i].Cr = GetColor(255, 255, 255);
			 }
		 }
	 }

	return this;
}

void SceneTitle::draw()
{

	if (CheckSoundFile() == 1)
	{
		DrawFormatString(0, 40, GetColor(255, 255, 255), "再生中");
	}


	for (int i = 0; i < 5; i++) 
	{   
		// メニュー項目を描画
		DrawFormatString(MenuElement[i].x, MenuElement[i].y, MenuElement[i].Cr, MenuElement[i].name);
		// 文字列の描画
		//DrawString(0, 0, "↑↓で選択、Enterで決定", GetColor(255, 255, 255));
		// デバッグ用
		DrawFormatString(0, 0, GetColor(255, 255, 255), "%d", m_SelectNum);
	}

}