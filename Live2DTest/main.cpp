#include <DxLib.h>



int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	int backgrand;

	int ModelHandle;

	int x = 0;
	int y = 0;

	float sizeX = 1.0f;
	float sizeY = 1.0f;

	float spin = 0.0f;

	float speed = 0.01f;



	ChangeWindowMode(true);
	SetGraphMode(1280, 720, 32);

#ifdef _WIN64
	Live2D_SetCubism4CoreDLLPath("Live2D/Live2DCubismCore.dll");
#endif

	// ＤＸライブラリ初期化処理
	if (DxLib_Init() == -1)
	{
		return -1;
	}

	backgrand = LoadGraph("image/backgraund.png");

	// Live2Dモデルの読み込み
	ModelHandle = Live2D_LoadModel("hiyori_free_jp/runtime/hiyori_free_t08.model3.json");

	// 描画先を裏画面に変更
	SetDrawScreen(DX_SCREEN_BACK);

	// メインループ
	while (ProcessMessage() == 0)
	{
		// 画面の初期化
		ClearDrawScreen();

		DrawGraph(0, 0, backgrand, true);

		if (CheckHitKey(KEY_INPUT_RIGHT))
		{
			x++;
			Live2D_Model_SetTranslate(ModelHandle, x,y);
		}

		if (CheckHitKey(KEY_INPUT_LEFT))
		{
			x--;
			Live2D_Model_SetTranslate(ModelHandle, x, y);
		}

		if (CheckHitKey(KEY_INPUT_UP))
		{
			y++;
			Live2D_Model_SetTranslate(ModelHandle, x, y);
		}


		if (CheckHitKey(KEY_INPUT_DOWN))
		{
			y--;
			Live2D_Model_SetTranslate(ModelHandle, x, y);
		}


		if (CheckHitKey(KEY_INPUT_W))
		{
			sizeX += speed;
			sizeY += speed;
			Live2D_Model_SetExtendRate(ModelHandle, sizeX, sizeY);
		}

		if (CheckHitKey(KEY_INPUT_S))
		{
			sizeX -= speed;
			sizeY -= speed;
			Live2D_Model_SetExtendRate(ModelHandle, sizeX, sizeY);
		}

		if (CheckHitKey(KEY_INPUT_E))
		{
			spin += speed;
			Live2D_Model_SetRotate(ModelHandle, spin);
		}

		if (CheckHitKey(KEY_INPUT_Q))
		{
			spin -= speed;
			Live2D_Model_SetRotate(ModelHandle, spin);
		}

		// モーション再生が終了していたらアイドリングモーションをランダムで再生
		if (Live2D_Model_IsMotionFinished(ModelHandle) == true)
		{
			Live2D_Model_StartMotion(ModelHandle, "Idle", GetRand(10));
		}

		if (CheckHitKey(KEY_INPUT_1)==1)
		{
			Live2D_Model_StartMotion(ModelHandle, "Flick", 0);
		}

		// モデルの状態を120分の1秒分進める
		Live2D_Model_Update(ModelHandle, 1 / 120.0f);

		// Live2D描画の開始
		Live2D_RenderBegin();

		// モデルの描画
		Live2D_Model_Draw(ModelHandle);

		// Live2D描画の終了
		Live2D_RenderEnd();

		// 裏画面の内容を表画面に反映
		ScreenFlip();
	}

	// Live2D モデルの削除
	Live2D_DeleteModel(ModelHandle);

	// ＤＸライブラリ使用の終了処理
	DxLib_End();

	// ソフトの終了
	return 0;
}