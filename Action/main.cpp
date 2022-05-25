#include <DxLib.h>

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
	// ���C�����[�v�A�d�r�b�L�[�ŏI��
	while (!ProcessMessage() && !(CheckHitKey(KEY_INPUT_ESCAPE)))
	{
		// ��ʂ�������
		ClearDrawScreen();

		// ����ʂ̓��e��\��ʂɔ��f�����܂�
		ScreenFlip();

	}

	// �c�w���C�u�����g�p�̏I������
	DxLib_End();

	// �\�t�g�̏I��
	return 0;
}