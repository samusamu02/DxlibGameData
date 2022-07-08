#include <DxLib.h>
#include <math.h>
#include <array>
#include <vector>
#include <cassert>

struct Vector2
{
	float x;
	float y;
};

struct Color
{
	float r = 1.0f;
	float g = 1.0f;
	float b = 1.0f;
	float a = 1.0f;
};

struct PointLight
{
	Color color;
	Vector2 pos{0.0f,0.0f};
	float k = 5000.0f;
	float pd = 0.0f;
};

void MyDrawGraph(int x,int y,int width,int height,int firstHandle,int psHandle)
{
	std::array<VERTEX2DSHADER, 4> verts;

	GetGraphSize(firstHandle, &width, &height);

	for (auto& v : verts)
	{
		v.rhw = 1.0;
		v.dif = DxLib::GetColorU8(255, 255, 255, 255);
		v.spc = DxLib::GetColorU8(255, 255, 255, 255);
		v.su = 0.0f;
		v.sv = 0.0f;
		v.pos.z = 0.0f;
	}

	// 左上
	verts[0].rhw = 1.0;
	verts[0].pos.x = x;
	verts[0].pos.y = y;
	verts[0].u = 0.0f;
	verts[0].v = 0.0f;

	// 右上
	verts[1].rhw = 1.0;
	verts[1].pos.x = x + width;
	verts[1].pos.y = y;
	verts[1].u = 1.0f;
	verts[1].v = 0.0f;

	// 左下
	verts[2].rhw = 1.0;
	verts[2].pos.x = x;
	verts[2].pos.y = y + height;
	verts[2].u = 0.0f;
	verts[2].v = 1.0f;

	// 右下
	verts[3].rhw = 1.0;
	verts[3].pos.x = x + width;
	verts[3].pos.y = y + height;
	verts[3].u = 1.0f;
	verts[3].v = 1.0f;

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
	SetUsePixelShader(psHandle);
	SetUseTextureToShader(0, firstHandle);
	DrawPrimitive2DToShader(verts.data(), verts.size(), DX_PRIMTYPE_TRIANGLESTRIP);
}

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

	// ピクセルシェーダーの読み込み
	int ps = LoadPixelShader("PixelShader.pso");

	// 画像を読み込む
	Handle = LoadGraph("images/syounyudou.png");
	player = LoadGraph("images/player.png");

	// マスクと合成するための仮画面を作成
	TempScreen = MakeScreen(640, 480, true);

	// マスク用の画面を作成
	MaskScreen = MakeScreen(640, 480, true);

	std::vector<PointLight> light;

	light.resize(2);

	auto size = sizeof(light[0]) * light.size();

	int cbuf = CreateShaderConstantBuffer(size);
	PointLight* buff = reinterpret_cast<PointLight*>(GetBufferShaderConstantBuffer(cbuf));

	light[0].pos.x = 0.0f;


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