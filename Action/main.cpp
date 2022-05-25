#include <DxLib.h>

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
	// メインループ、ＥＳＣキーで終了
	while (!ProcessMessage() && !(CheckHitKey(KEY_INPUT_ESCAPE)))
	{
		// 画面を初期化
		ClearDrawScreen();

		// 裏画面の内容を表画面に反映させます
		ScreenFlip();

	}

	// ＤＸライブラリ使用の終了処理
	DxLib_End();

	// ソフトの終了
	return 0;
}