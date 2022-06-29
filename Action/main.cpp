#include <DxLib.h>

int cPosX = 300;
int cPosY = 100;

int bg;
int circle;

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	SetGraphMode(640, 480, 16);
	ChangeWindowMode(true);

	// �c�w���C�u��������������
	if (DxLib_Init() == -1)
	{
		// �G���[���N�����璼���ɏI��
		return -1;
	}

	SetDrawScreen(DX_SCREEN_BACK);


	bg = LoadGraph("images/syounyudou.png");

	// ���C�����[�v�A�d�r�b�L�[�ŏI��
	while (!ProcessMessage() && !(CheckHitKey(KEY_INPUT_ESCAPE)))
	{
		// ��ʂ�������
		ClearDrawScreen();

		if (CheckHitKey(KEY_INPUT_UP) == 0)
		{
			cPosY++;
		}
		if (CheckHitKey(KEY_INPUT_DOWN) == 0)
		{
			cPosY--;
		}
		if (CheckHitKey(KEY_INPUT_LEFT) == 0)
		{
			cPosX++;
		}
		if (CheckHitKey(KEY_INPUT_RIGHT) == 0)
		{
			cPosX--;
		}
		DrawGraph(0, 0, bg, true);
		CreateMaskScreen();
		DrawMask(cPosX, cPosY, circle, DX_MASKTRANS_BLACK);

		DeleteMaskScreen();
		// ����ʂ̓��e��\��ʂɔ��f�����܂�
		ScreenFlip();

	}

	// �c�w���C�u�����g�p�̏I������
	DxLib_End();

	// �\�t�g�̏I��
	return 0;
}