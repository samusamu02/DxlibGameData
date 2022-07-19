#include <DxLib.h>
#include <cassert>
#include <array>
#include <vector>
#include <cmath>

constexpr int screenSizex = 720;
constexpr int screenSizey = 480;

struct Vec2
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
	Vec2 pos{ 0.0f,0.0f };
	float k = 5000.0f;
	float pd = 0.0f;
};

void ShadeDrawGraph(int x, int y, int width, int height, int imageHandle,int psHandle)
{
	GetGraphSize(imageHandle, &width, &height);
	std::array<VERTEX2DSHADER, 4> vertx;

	for (auto& v : vertx)
	{
		v.rhw = 1.0;
		v.dif = DxLib::GetColorU8(255, 255, 255, 255);
		v.spc = DxLib::GetColorU8(255, 255, 255, 255);
		v.su = 0.0f;
		v.sv = 0.0f;
		v.pos.z = 0.0f;
	}

	// 左上
	vertx[0].rhw = 1.0;
	vertx[0].pos.x = x;
	vertx[0].pos.y = y;
	vertx[0].u = 0.0f;
	vertx[0].v = 0.0f;

	// 右上
	vertx[1].rhw = 1.0;
	vertx[1].pos.x = x + width;
	vertx[1].pos.y = y;
	vertx[1].u = 1.0f;
	vertx[1].v = 0.0f;

	// 左下
	vertx[2].rhw = 1.0;
	vertx[2].pos.x = x;
	vertx[2].pos.y = y + height;
	vertx[2].u = 0.0f;
	vertx[2].v = 1.0f;

	// 右下
	vertx[3].rhw = 1.0;
	vertx[3].pos.x = x + width;
	vertx[3].pos.y = y + height;
	vertx[3].u = 1.0f;
	vertx[3].v = 1.0f;

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
	SetUsePixelShader(psHandle);
	SetUseTextureToShader(0, imageHandle);
	DrawPrimitive2DToShader(vertx.data(), vertx.size(), DX_PRIMTYPE_TRIANGLESTRIP);
}

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
	SetGraphMode(screenSizex, screenSizey, 32);
	ChangeWindowMode(true);
	assert(DxLib_Init() != -1);
	int ps = LoadPixelShader("PointLight.pso");


	int scr = MakeScreen(screenSizex, screenSizey, true);
	int MaskScreen = MakeScreen(screenSizex, screenSizey, true);
	int image = LoadGraph("images/syounyudou.png");
	int pChara = LoadGraph("images/player.png");
	std::vector<PointLight> light;

	// ライト二つ用意
	light.resize(2);

	auto size = sizeof(light[0]) * light.size();

	int cbuf = CreateShaderConstantBuffer(size);
	PointLight* buff = reinterpret_cast<PointLight*>(GetBufferShaderConstantBuffer(cbuf));

	light[1].pos.x = 0.0f;
	light[1].pos.y = 0.0f;
	light[1].k = 10000.0f;

	std::copy(light.begin(), light.end(), buff);
	UpdateShaderConstantBuffer(cbuf);

	while (ProcessMessage() == 0)
	{
		//int x, y;
		//GetMousePoint(&x, &y);
		//light[0].pos.x = x;
		//light[0].pos.y = y;
		int speed = 3;
		if (CheckHitKey(KEY_INPUT_LEFT))
		{
			light[0].pos.x -= speed;
		}
		if (CheckHitKey(KEY_INPUT_RIGHT))
		{
			light[0].pos.x += speed;
		}
		if (CheckHitKey(KEY_INPUT_UP))
		{
			// light[0].k += 100.0f;
			light[0].pos.y -= speed;
		}
		if (CheckHitKey(KEY_INPUT_DOWN))
		{
			// light[0].k -= 100.0f;
			light[0].pos.y += speed;
		}
		light[0].k = 3000.0f;
		std::copy(light.begin(), light.end(), buff);

		SetDrawScreen(scr);
		ClsDrawScreen();

		// 黒く塗る
		//DrawBox(0, 0, 1280, 720, 0x000000, true);

		// 黒く塗った上にライトの色を塗る
		UpdateShaderConstantBuffer(cbuf);
		SetShaderConstantBuffer(cbuf, DX_SHADERTYPE_PIXEL, 0);
		ShadeDrawGraph(0, 0, screenSizex, screenSizey, scr, ps);

		SetDrawScreen(DX_SCREEN_BACK);
		ClsDrawScreen();
		DrawGraph(0, 0, image, true);
		DrawGraph(light[0].pos.x - 25, light[0].pos.y - 20, pChara, true);

		// 背景とライトの色を乗算合成
		SetDrawBlendMode(DX_BLENDMODE_MUL, 255);
		DrawGraph(0, 0, scr, true);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);

		ScreenFlip();
	}
	DxLib_End();
	return 0;
}