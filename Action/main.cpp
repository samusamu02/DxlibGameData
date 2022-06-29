#include <DxLib.h>
#include <math.h>

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	int Handle;
	int MaskScreen;
	float Angle;
	int i;

	// �E�C���h�E���[�h�ŋN��
	ChangeWindowMode(TRUE);

	// �c�w���C�u�����̏�����
	if (DxLib_Init() < 0)
		return -1;

	// �摜��ǂݍ���
	Handle = LoadGraph("images/syounyudou.png");
	// �}�X�N�p�̉�ʂ��쐬
	MaskScreen = MakeScreen(640, 480, TRUE);

	// �~�̉�]�p�x��������
	Angle = 0.0f;

	// ���C�����[�v
	while (ProcessMessage() == 0)
	{
		// �~�̉�]�p�x��ύX
		Angle += 0.05f;

		for (i = 0; i < 6; i++)
		{
			DrawGraph(i * 119, 0, Handle, TRUE);
		}

		// �}�X�N�p�̉�ʂɉ�]����~��`��
		SetDrawScreen(MaskScreen);
		ClearDrawScreen();

		DrawCircle(
			(int)(cos(Angle) * 160.0f) + 320,
			(int)(sin(Angle) * 120.0f) + 240,
			128, GetColor(255, 255, 255), TRUE);

		// �`���𗠉�ʂɕύX
		SetDrawScreen(DX_SCREEN_BACK);
		ClearDrawScreen();
		// ����ʂ̓��e��\��ʂɔ��f
		ScreenFlip();
	}

	// �c�w���C�u�����̌�n��
	DxLib_End();

	return 0;
}
