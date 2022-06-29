#include <DxLib.h>
#include <math.h>

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	int Handle;
	int MaskScreen;
	float Angle;
	int i;

	// ウインドウモードで起動
	ChangeWindowMode(TRUE);

	// ＤＸライブラリの初期化
	if (DxLib_Init() < 0)
		return -1;

	// 画像を読み込む
	Handle = LoadGraph("images/syounyudou.png");
	// マスク用の画面を作成
	MaskScreen = MakeScreen(640, 480, TRUE);

	// 円の回転角度を初期化
	Angle = 0.0f;

	// メインループ
	while (ProcessMessage() == 0)
	{
		// 円の回転角度を変更
		Angle += 0.05f;

		for (i = 0; i < 6; i++)
		{
			DrawGraph(i * 119, 0, Handle, TRUE);
		}

		// マスク用の画面に回転する円を描画
		SetDrawScreen(MaskScreen);
		ClearDrawScreen();

		DrawCircle(
			(int)(cos(Angle) * 160.0f) + 320,
			(int)(sin(Angle) * 120.0f) + 240,
			128, GetColor(255, 255, 255), TRUE);

		// 描画先を裏画面に変更
		SetDrawScreen(DX_SCREEN_BACK);
		ClearDrawScreen();
		// 裏画面の内容を表画面に反映
		ScreenFlip();
	}

	// ＤＸライブラリの後始末
	DxLib_End();

	return 0;
}
