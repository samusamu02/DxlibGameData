#include <DxLib.h>

int cPosX = 300;
int cPosY = 100;

int bg;
int circle;

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	SetGraphMode(640, 480, 16);
	ChangeWindowMode(true);

	// ＤＸライブラリ初期化処理
	if (DxLib_Init() == -1)
	{
		// エラーが起きたら直ちに終了
		return -1;
	}

	SetDrawScreen(DX_SCREEN_BACK);


	bg = LoadGraph("images/syounyudou.png");

	// メインループ、ＥＳＣキーで終了
	while (!ProcessMessage() && !(CheckHitKey(KEY_INPUT_ESCAPE)))
	{
		// 画面を初期化
		ClearDrawScreen();

		if (CheckHitKey(KEY_INPUT_UP) == 0)
		{
			cPosY++;
		}
		if (CheckHitKey(KEY_INPUT_DOWN) == 0)
		{
			cPosY--;
		}
		if (CheckHitKey(KEY_INPUT_LEFT) == 0)
		{
			cPosX++;
		}
		if (CheckHitKey(KEY_INPUT_RIGHT) == 0)
		{
			cPosX--;
		}
		DrawGraph(0, 0, bg, true);
		CreateMaskScreen();
		DrawMask(cPosX, cPosY, circle, DX_MASKTRANS_BLACK);

		DeleteMaskScreen();
		// 裏画面の内容を表画面に反映させます
		ScreenFlip();

	}

	// ＤＸライブラリ使用の終了処理
	DxLib_End();

	// ソフトの終了
	return 0;
}