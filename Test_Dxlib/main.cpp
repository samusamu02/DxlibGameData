// ���j���|������{
#include <DxLib.h>

// ���]�~�̕`��
int DrawReversalCircle(int x, int y, int r, int Color);


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow)
{
	int i, Mode;
	int GraphHandle1, GraphHandle2;

	SetGraphMode(640, 480, 16);
	ChangeWindowMode(true);	

	// �c�w���C�u��������������
	if (DxLib_Init() == -1)
	{
		// �G���[���N�����璼���ɏI��
		return -1;
	}

	// �O���t�B�b�N�̃��[�h
	GraphHandle1 = LoadGraph("image/backgraund1.jpg");
	GraphHandle2 = LoadGraph("image/backgraund2.jpg");


	// �`���𗠉�ʂɂ��܂�
	SetDrawScreen(DX_SCREEN_BACK);

	// ��Ԑ��ڃ��[�h���Z�b�g
	Mode = 0;

	// ���C�����[�v�A�d�r�b�L�[�ŏI��
	while (!ProcessMessage() && !(CheckHitKey(KEY_INPUT_ESCAPE)))
	{
		// ���[�v
		for (i = 0; i <= 400; i += 4)
		{
			// ��ʂ�������
			ClearDrawScreen();

			// �O���t�B�b�N�P��`�悵�܂�
			DrawGraph(0, 0, GraphHandle1, FALSE);

			// �`�悵���O���t�B�b�N�̏�ɔ��]�~��`���܂�
			DrawReversalCircle(320, 240, Mode == 0 ? i : 399 - i, 0);

			// ����ʂ̓��e��\��ʂɔ��f�����܂�
			ScreenFlip();
		}

		// �L�[���͑҂�
		while (!ProcessMessage() && CheckHitKeyAll()) {}
		while (!ProcessMessage() && !CheckHitKeyAll()) {}

		// �O���t�B�b�N�n���h�����Ƃ肩����
		if (Mode == 1)
		{
			i = GraphHandle1;
			GraphHandle1 = GraphHandle2;
			GraphHandle2 = i;
		}

		// ��Ԑ��ڃ��[�h�̕ύX
		Mode = Mode == 0 ? 1 : 0;

	}

	// �c�w���C�u�����g�p�̏I������
	DxLib_End();

	// �\�t�g�̏I��
	return 0;
}

// ���]�~�̕`��
int DrawReversalCircle(int x, int y, int r, int Color)
{
	// �~���]�`��̈�̊O����`��
	DrawBox(0, 0, 640, y - r, Color, true);
	DrawBox(0, y - r, x - r, 480, Color, true);
	DrawBox(x - r, y + r + 1, 640, 480, Color, true);
	DrawBox(x + r, y - r, 640, y + r + 1, Color, true);

	// �`�揈��
	{
		int Dx, Dy, F, j;
		int x1, x2, y1;

		// �����l�Z�b�g
		Dx = r; Dy = 0; F = -2 * r + 3;

		j = 0;
		// �`��J�n
		{
			// �܂��ŏ��ɍ��W�f�[�^��i�߂�
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

			// �`���؂�܂Ń��[�v
			while (Dx >= Dy)
			{
				// ���C����`��
				x2 = Dx + x; x1 = -Dx + x; y1 = Dy + y;
				DrawLine(0, y1, x1, y1, Color);
				DrawLine(x2, y1, 640, y1, Color);
				x2 = Dx + x; x1 = -Dx + x; y1 = -Dy + y;
				DrawLine(0, y1, x1, y1, Color);
				DrawLine(x2, y1, 640, y1, Color);

				// ���W�f�[�^��i�߂�
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


	// �I��
	return 0;
}

