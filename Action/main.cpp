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

	// ����
	verts[0].rhw = 1.0;
	verts[0].pos.x = x;
	verts[0].pos.y = y;
	verts[0].u = 0.0f;
	verts[0].v = 0.0f;

	// �E��
	verts[1].rhw = 1.0;
	verts[1].pos.x = x + width;
	verts[1].pos.y = y;
	verts[1].u = 1.0f;
	verts[1].v = 0.0f;

	// ����
	verts[2].rhw = 1.0;
	verts[2].pos.x = x;
	verts[2].pos.y = y + height;
	verts[2].u = 0.0f;
	verts[2].v = 1.0f;

	// �E��
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

	// �E�C���h�E���[�h�ŋN��
	ChangeWindowMode(true);

	// �c�w���C�u�����̏�����
	if (DxLib_Init() < 0)
	{
		return -1;
	}

	// �s�N�Z���V�F�[�_�[�̓ǂݍ���
	int ps = LoadPixelShader("PixelShader.pso");

	// �摜��ǂݍ���
	Handle = LoadGraph("images/syounyudou.png");
	player = LoadGraph("images/player.png");

	// �}�X�N�ƍ������邽�߂̉���ʂ��쐬
	TempScreen = MakeScreen(640, 480, true);

	// �}�X�N�p�̉�ʂ��쐬
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

	// ���C�����[�v
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

		// ����ʑS�̂ɉ摜��`��
		SetDrawScreen(TempScreen);
		ClearDrawScreen();

		DrawGraph(0, 0, Handle, true);
		DrawGraph(posX + 295, posY + 220, player, true);

		// �}�X�N�p�̉~��`��
		SetDrawScreen(MaskScreen);
		ClearDrawScreen();

		DrawCircle(
			posX + 320,
			posY + 240,
			size, 0x000000, true);


		// �`���𗠉�ʂɕύX
		SetDrawScreen(DX_SCREEN_BACK);
		ClearDrawScreen();

		// �`�掞�̍����摜�Ƀ}�X�N��ʂ�ݒ�
		// ( �}�X�N��ʂ̃A���t�@�l�Ɖ���ʂ̃A���t�@�l���������� )
		SetBlendGraphParam(MaskScreen, DX_BLENDGRAPHTYPE_ALPHA);
		// ����ʂ𗠉�ʂɕ`��( �}�X�N��ʂ̃A���t�@�l���g�p���� )
		DrawGraph(0, 0, TempScreen, true);
		// �����ݒ������
		SetBlendGraphParam(-1, DX_BLENDGRAPHTYPE_NORMAL);

		// ����ʂ̓��e��\��ʂɔ��f
		ScreenFlip();
	}

	// �c�w���C�u�����̌�n��
	DxLib_End();

	return 0;
}