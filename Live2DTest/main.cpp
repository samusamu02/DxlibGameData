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

	// �c�w���C�u��������������
	if (DxLib_Init() == -1)
	{
		return -1;
	}

	backgrand = LoadGraph("image/backgraund.png");

	// Live2D���f���̓ǂݍ���
	ModelHandle = Live2D_LoadModel("hiyori_free_jp/runtime/hiyori_free_t08.model3.json");

	// �`���𗠉�ʂɕύX
	SetDrawScreen(DX_SCREEN_BACK);

	// ���C�����[�v
	while (ProcessMessage() == 0)
	{
		// ��ʂ̏�����
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

		// ���[�V�����Đ����I�����Ă�����A�C�h�����O���[�V�����������_���ōĐ�
		if (Live2D_Model_IsMotionFinished(ModelHandle) == true)
		{
			Live2D_Model_StartMotion(ModelHandle, "Idle", GetRand(10));
		}

		if (CheckHitKey(KEY_INPUT_1)==1)
		{
			Live2D_Model_StartMotion(ModelHandle, "Flick", 0);
		}

		// ���f���̏�Ԃ�120����1�b���i�߂�
		Live2D_Model_Update(ModelHandle, 1 / 120.0f);

		// Live2D�`��̊J�n
		Live2D_RenderBegin();

		// ���f���̕`��
		Live2D_Model_Draw(ModelHandle);

		// Live2D�`��̏I��
		Live2D_RenderEnd();

		// ����ʂ̓��e��\��ʂɔ��f
		ScreenFlip();
	}

	// Live2D ���f���̍폜
	Live2D_DeleteModel(ModelHandle);

	// �c�w���C�u�����g�p�̏I������
	DxLib_End();

	// �\�t�g�̏I��
	return 0;
}