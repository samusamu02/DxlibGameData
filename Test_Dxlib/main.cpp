// メニュ－処理基本
#include <DxLib.h>

// 反転円の描画
int DrawReversalCircle(int x, int y, int r, int Color);


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow)
{
	int i, Mode;
	int GraphHandle1, GraphHandle2;

	SetGraphMode(640, 480, 16);
	ChangeWindowMode(true);	

	// ＤＸライブラリ初期化処理
	if (DxLib_Init() == -1)
	{
		// エラーが起きたら直ちに終了
		return -1;
	}

	// グラフィックのロード
	GraphHandle1 = LoadGraph("image/backgraund1.jpg");
	GraphHandle2 = LoadGraph("image/backgraund2.jpg");


	// 描画先を裏画面にします
	SetDrawScreen(DX_SCREEN_BACK);

	// 状態推移モードをセット
	Mode = 0;

	// メインループ、ＥＳＣキーで終了
	while (!ProcessMessage() && !(CheckHitKey(KEY_INPUT_ESCAPE)))
	{
		// ループ
		for (i = 0; i <= 400; i += 4)
		{
			// 画面を初期化
			ClearDrawScreen();

			// グラフィック１を描画します
			DrawGraph(0, 0, GraphHandle1, FALSE);

			// 描画したグラフィックの上に反転円を描きます
			DrawReversalCircle(320, 240, Mode == 0 ? i : 399 - i, 0);

			// 裏画面の内容を表画面に反映させます
			ScreenFlip();
		}

		// キー入力待ち
		while (!ProcessMessage() && CheckHitKeyAll()) {}
		while (!ProcessMessage() && !CheckHitKeyAll()) {}

		// グラフィックハンドルをとりかえる
		if (Mode == 1)
		{
			i = GraphHandle1;
			GraphHandle1 = GraphHandle2;
			GraphHandle2 = i;
		}

		// 状態推移モードの変更
		Mode = Mode == 0 ? 1 : 0;

	}

	// ＤＸライブラリ使用の終了処理
	DxLib_End();

	// ソフトの終了
	return 0;
}

// 反転円の描画
int DrawReversalCircle(int x, int y, int r, int Color)
{
	// 円反転描画領域の外側を描画
	DrawBox(0, 0, 640, y - r, Color, true);
	DrawBox(0, y - r, x - r, 480, Color, true);
	DrawBox(x - r, y + r + 1, 640, 480, Color, true);
	DrawBox(x + r, y - r, 640, y + r + 1, Color, true);

	// 描画処理
	{
		int Dx, Dy, F, j;
		int x1, x2, y1;

		// 初期値セット
		Dx = r; Dy = 0; F = -2 * r + 3;

		j = 0;
		// 描画開始
		{
			// まず最初に座標データを進める
			if (F >= 0)
			{
				x2 = Dy + x; x1 = -Dy + x; y1 = Dx + y;
				DrawLine(0, y1, x1, y1, Color);
				DrawLine(x2, y1, 640, y1, Color);
				x2 = Dy + x; x1 = -Dy + x; y1 = -Dx + y;
				DrawLine(0, y1, x1, y1, Color);
				DrawLine(x2, y1, 640, y1, Color);

				Dx--;
				F -= 4 * Dx;
			}

			Dy++;
			F += 4 * Dy + 2;

			// 描き切るまでループ
			while (Dx >= Dy)
			{
				// ラインを描く
				x2 = Dx + x; x1 = -Dx + x; y1 = Dy + y;
				DrawLine(0, y1, x1, y1, Color);
				DrawLine(x2, y1, 640, y1, Color);
				x2 = Dx + x; x1 = -Dx + x; y1 = -Dy + y;
				DrawLine(0, y1, x1, y1, Color);
				DrawLine(x2, y1, 640, y1, Color);

				// 座標データを進める
				if (F >= 0)
				{
					x2 = Dy + x; x1 = -Dy + x; y1 = Dx + y;
					DrawLine(0, y1, x1, y1, Color);
					DrawLine(x2, y1, 640, y1, Color);
					x2 = Dy + x; x1 = -Dy + x; y1 = -Dx + y;
					DrawLine(0, y1, x1, y1, Color);
					DrawLine(x2, y1, 640, y1, Color);

					Dx--;
					F -= 4 * Dx;
				}

				Dy++;
				F += 4 * Dy + 2;
			}
		}
	}


	// 終了
	return 0;
}

