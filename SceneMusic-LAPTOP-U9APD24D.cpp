#include "DxLib.h"
#include "SceneMain.h"
#include "SceneMusic.h"
#include "SceneTitle.h"


namespace
{
	
	constexpr int kMInterval = 15;

	int GHandle1;
	int GHandle2;

	constexpr int kTitle = 2;
}


// メニュー項目の表示に必要な構造体を用意する
typedef struct {
	int x, y;       // 座標格納用変数
	char name[128]; // 項目名格納用変数
	int Cr;
} MenuElement_m;

// メニュー項目要素を3つ作る
MenuElement_m MenuElement[kTitle] = {
		{  80, 100, "亡き王女の為のセプテット" ,GetColor(255, 0, 0) }, // タグの中身の順番で格納される。xに80が、yに100が、nameに"ゲームスタート"が
		{ 100, 150, "UN.オーエンは彼女なのか" ,GetColor(255, 255, 255)},
		

};


void SceneMusic::init()
{

	m_SoundSelect = 0;
	m_MInterval = kMInterval;
	m_isEnd = false;
}

SceneBase* SceneMusic::update()
{

	int TMffectsHandle1;// 選択音のハンドル
	int TMffectsHandle2;// 決定音のハンドル
	int TMffectsHandle3;// キャンセル音のハンドル

	TMffectsHandle1 = LoadSoundMem("sound/選択音.wav");
	TMffectsHandle2 = LoadSoundMem("sound/決定音.wav");
	TMffectsHandle3 = LoadSoundMem("sound/キャンセル音.wav");

	int padState = 0;

	padState = GetJoypadInputState(DX_INPUT_KEY_PAD1);

	m_MInterval--;
	if (m_MInterval < 0) m_MInterval = 0;

	if (m_MInterval <= 0)
	{

		if ((padState & PAD_INPUT_DOWN) && (m_MInterval <= 0))
		{
			m_SoundSelect = (m_SoundSelect + 1) % kTitle; // 現在の選択項目を一つ下にずらす(ループする)
			PlaySoundMem(TMffectsHandle1, DX_PLAYTYPE_BACK);
			m_MInterval = kMInterval;
		}
		if ((padState & PAD_INPUT_UP) && (m_MInterval <= 0))
		{
			m_SoundSelect = (m_SoundSelect + (kTitle - 1)) % kTitle; // 現在の選択項目を一つ上にずらす(逆ループする)
			PlaySoundMem(TMffectsHandle1, DX_PLAYTYPE_BACK);
			m_MInterval = kMInterval;
		}
		if ((padState & PAD_INPUT_4) && (m_MInterval <= 0))
		{
			PlaySoundMem(TMffectsHandle2, DX_PLAYTYPE_BACK);
			m_MInterval = kMInterval;
		}
		if ((padState & PAD_INPUT_3) && (m_MInterval <= 0))
		{
			PlaySoundMem(TMffectsHandle3, DX_PLAYTYPE_BACK);
			m_MInterval = kMInterval;
		}

		if (m_SoundSelect == 0)
		{// 4ボタンが押された瞬間だけ処理
			if (padState & PAD_INPUT_4)
			{
				if (CheckSoundFile() == 0)
				{
					PlaySoundFile("sound/亡き王女の為のセプテット.wav", DX_PLAYTYPE_LOOP);
				}
				else if(!CheckSoundFile == 0)
				{
					StopSoundFile();
				}
				m_MInterval = kMInterval;
			}
		
		}

		if (m_SoundSelect == 1)
		{// 4ボタンが押された瞬間だけ処理
			if (padState & PAD_INPUT_4)
			{
				if (CheckSoundFile() == 0)
				{
					PlaySoundFile("sound/UN.オーエンは彼女なのか.wav", DX_PLAYTYPE_LOOP);
				}
				else if (!CheckSoundFile == 0)
				{
					StopSoundFile();
				}
				m_MInterval = kMInterval;
			}

		}


	}

	if ((padState & PAD_INPUT_DOWN) || (padState & PAD_INPUT_UP) || (padState & PAD_INPUT_3))
	{

		for (int i = 0; i < kTitle; i++)
		{   // メニュー項目数である3個ループ処理
			if (i == m_SoundSelect) {          // 今処理しているのが、選択番号と同じ要素なら
				MenuElement[i].x = 80; // 座標を80にする
				MenuElement[i].Cr = GetColor(255, 0, 0);
			}
			else {                       // 今処理しているのが、選択番号以外なら
				MenuElement[i].x = 100;// 座標を100にする
				MenuElement[i].Cr = GetColor(255, 255, 255);
			}
		}
	}

	
	
	if (padState & PAD_INPUT_3)
	{

		// Titleに切り替え
		return(new SceneTitle);
	}
	
		

	return this;
}

void SceneMusic::draw()
{
	GHandle1 = LoadGraph("image/レミリア_通常.png");
	GHandle2 = LoadGraph("image/フラン_通常.png");

	if (m_SoundSelect == 0)
	{
		DrawExtendGraph(300, 0, 640, 480, GHandle1, TRUE);
	}
	if (m_SoundSelect == 1)
	{
		DrawExtendGraph(300, 0, 640, 480, GHandle2, TRUE);
	}


	if (CheckSoundFile() == 1)
	{
		DrawFormatString(0, 40, GetColor(255, 255, 255), "再生中");
	}

	for (int i = 0; i < 5; i++)
	{
		// メニュー項目を描画
		DrawFormatString(MenuElement[i].x, MenuElement[i].y, MenuElement[i].Cr, MenuElement[i].name);
		// 文字列の描画
		//DrawString(0, 0, "↑↓で選択、Enterで決定、Backspaceでキャンセル", GetColor(255, 255, 255));
		// デバッグ用
		DrawFormatString(0, 0, GetColor(255, 255, 255), "%d", m_SoundSelect);
	}
}