#include <DxLib.h>
#include <array>
#include<math.h>
/// <summary>
/// �V�F�[�_�[�p��DrawGraph
/// </summary>
/// <param name="x">x���W</param>
/// <param name="y">y���W</param>
/// <param name="imageHandle">��ڂ̉摜�n���h��ID</param>
/// <param name="secondHandle">��ڂ̉摜�n���h��ID</param>
/// <param name="psHandle">�s�N�Z���V�F�[�_�̃n���h��</param>
void ShadeDrawGraph(int x, int y,int imageHandle,int secondHandle,int tharerdimag,int psHandle)
{
	int width, hight;
	GetGraphSize(imageHandle, &width, &hight);
	std::array<VERTEX2DSHADER,4> vertx;

	for (auto&v : vertx)
	{
		v.rhw = 1.0;
		v.dif = DxLib::GetColorU8(255,255,255,255);
		v.spc = DxLib::GetColorU8(255, 255, 255, 255);
		v.su = 0.0f;
		v.sv = 0.0f;
		v.pos.z = 0.0f;
	}

	// ����
	vertx[0].rhw = 1.0;
	vertx[0].pos.x = x;
	vertx[0].pos.y = y;
	vertx[0].u = 0.0f;
	vertx[0].v = 0.0f;

	// �E��
	vertx[1].rhw = 1.0;
	vertx[1].pos.x = x + width;
	vertx[1].pos.y = y;
	vertx[1].u = 1.0f;
	vertx[1].v = 0.0f;

	// ����
	vertx[2].rhw = 1.0;
	vertx[2].pos.x = x;
	vertx[2].pos.y = y + hight;
	vertx[2].u = 0.0f;
	vertx[2].v = 1.0f;

	// �E��
	vertx[3].rhw = 1.0;
	vertx[3].pos.x = x + width;
	vertx[3].pos.y = y + hight;
	vertx[3].u = 1.0f;
	vertx[3].v = 1.0f;

	SetDrawBlendMode(DX_BLENDMODE_ALPHA,255);
	SetUsePixelShader(psHandle);
	SetUseTextureToShader(0, imageHandle);
	SetUseTextureToShader(1, secondHandle);
	SetUseTextureToShader(2, tharerdimag);
	DrawPrimitive2DToShader(vertx.data(),vertx.size(),DX_PRIMTYPE_TRIANGLESTRIP);
}

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
	ChangeWindowMode(true);
	DxLib_Init();
	SetDrawScreen(DX_SCREEN_BACK);

	int image = LoadGraph(L"image/cookie.png");
	int normImg = LoadGraph(L"image/cookie_n.png");
	int bg = LoadGraph(L"image/bg.jpg");
	int pt = LoadGraph(L"image/ptn.png");
	int ps = LoadPixelShader(L"SamplePS.pso");


	// �@�萔�o�b�t�@�̊m��(VRAM��̃��������m�ہj
	int cBuff = DxLib::CreateShaderConstantBuffer(sizeof(float) * 4);		// �n���h��ID�݂����Ȃ��
	// �O���{�̃������͂�����Ȃ��B
	// RAM��̃������ŃV�~�����[�V�������Ă���B
	float* threshold = static_cast<float*>(DxLib::GetBufferShaderConstantBuffer(cBuff));
	float data = 0.0f;
	float angle = 0.0f;
	char keystate[256];
	while (ProcessMessage() != -1)
	{
		angle += 0.001f;
		GetHitKeyStateAll(keystate);
		if (keystate[KEY_INPUT_UP])
		{
			data -= 0.01f;
		}
		if (keystate[KEY_INPUT_DOWN])
		{
			data += 0.01f;
		}
		ClearDrawScreen();
		// DrawGraph(0,0,image,true);
		DrawGraph(0, 0, bg, true);
		threshold[0] = data;
		threshold[1] = angle;
		DxLib::UpdateShaderConstantBuffer(cBuff);
		SetShaderConstantBuffer(cBuff, DX_SHADERTYPE_PIXEL, 0);
		ShadeDrawGraph(50, -20, image, pt, ps, normImg);

		ScreenFlip();
	}
	DxLib_End();
	return 0;
}