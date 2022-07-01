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

	// �E�C���h�E���[�h�ŋN��
	ChangeWindowMode(true);

	// �c�w���C�u�����̏�����
	if (DxLib_Init() < 0)
	{
		return -1;
	}

	// �摜��ǂݍ���
	Handle = LoadGraph("images/syounyudou.png");
	player = LoadGraph("images/player.png");

	// �}�X�N�ƍ������邽�߂̉���ʂ��쐬
	TempScreen = MakeScreen(640, 480, true);

	// �}�X�N�p�̉�ʂ��쐬
	MaskScreen = MakeScreen(640, 480, true);
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