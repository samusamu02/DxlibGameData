#include <DxLib.h>
#include <math.h>

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	int Handle;
	int player;
	int posX;
	int posY;

	int MaskScreen;
	int TempScreen;
	int i;
	float speed;
	int size;

	// ウインドウモードで起動
	ChangeWindowMode(true);

	// ＤＸライブラリの初期化
	if (DxLib_Init() < 0)
	{
		return -1;
	}

	// 画像を読み込む
	Handle = LoadGraph("images/syounyudou.png");
	player = LoadGraph("images/player.png");

	// マスクと合成するための仮画面を作成
	TempScreen = MakeScreen(640, 480, true);

	// マスク用の画面を作成
	MaskScreen = MakeScreen(640, 480, true);
	posX = 0;
	posY = 0;
	speed = 3.0f;

	// メインループ
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE)==0)
	{

		if (CheckHitKey(KEY_INPUT_RIGHT))
		{
			posX += speed;
		}
		if (CheckHitKey(KEY_INPUT_LEFT))
		{
			posX -= speed;
		}
		if (CheckHitKey(KEY_INPUT_UP))
		{
			posY -= speed;
		}
		if (CheckHitKey(KEY_INPUT_DOWN))
		{
			posY += speed;
		}
		if (CheckHitKey(KEY_INPUT_SPACE))
		{
			size = 100;
		}
		else
		{
			size = 50;
		}
		


		// 仮画面全体に画像を描画
		SetDrawScreen(TempScreen);
		ClearDrawScreen();

		DrawGraph(0, 0, Handle, true);
		DrawGraph(posX + 295, posY + 220, player, true);

		// マスク用の円を描画
		SetDrawScreen(MaskScreen);
		ClearDrawScreen();

		DrawCircle(
			posX + 320,
			posY + 240,
			size, 0x000000, true);


		// 描画先を裏画面に変更
		SetDrawScreen(DX_SCREEN_BACK);
		ClearDrawScreen();

		// 描画時の合成画像にマスク画面を設定
		// ( マスク画面のアルファ値と仮画面のアルファ値を合成する )
		SetBlendGraphParam(MaskScreen, DX_BLENDGRAPHTYPE_ALPHA);
		// 仮画面を裏画面に描画( マスク画面のアルファ値も使用しつつ )
		DrawGraph(0, 0, TempScreen, true);
		// 合成設定を解除
		SetBlendGraphParam(-1, DX_BLENDGRAPHTYPE_NORMAL);

		// 裏画面の内容を表画面に反映
		ScreenFlip();
	}

	// ＤＸライブラリの後始末
	DxLib_End();

	return 0;
}