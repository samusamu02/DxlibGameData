#include <DxLib.h>

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
    ChangeWindowMode(true), DxLib_Init(), SetDrawScreen(DX_SCREEN_BACK); //�E�B���h�E���[�h�ύX�Ə������Ɨ���ʐݒ�

    int image[16];
    LoadDivGraph("images/Characters/player.png", 16, 4, 4, 48, 48, image); // �摜�̕����ǂݍ���

        // while(����ʂ�\��ʂɔ��f, ���b�Z�[�W����, ��ʃN���A)
    while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0) {

        DrawGraph(0, 0, image[1], true);      // �摜��\��
    }

    DxLib_End(); // DX���C�u�����I������
    return 0;
}