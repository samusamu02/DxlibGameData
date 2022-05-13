#include <DxLib.h>

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
    ChangeWindowMode(TRUE), DxLib_Init(), SetDrawScreen(DX_SCREEN_BACK);

    int ModelHandle, AttachIndex;
    float TotalTime, PlayTime;

    // �R�c���f���̓ǂݍ���
    ModelHandle = MV1LoadModel("ModelData/TokinoSora.pmx");

    //���s0.1�`1000�܂ł��J�����̕`��͈͂Ƃ���
    SetCameraNearFar(0.1f, 1000.0f);

    //(0,10,-20)�̎��_����(0,10,0)�̃^�[�Q�b�g������p�x�ɃJ������ݒu
    SetCameraPositionAndTarget_UpVecY(VGet(0, 10, -20), VGet(0.0f, 10.0f, 0.0f));

    // �R�c���f����1�Ԗڂ̃A�j���[�V�������A�^�b�`����
    AttachIndex = MV1AttachAnim(ModelHandle, 1, -1, FALSE);

    // �A�^�b�`�����A�j���[�V�����̑��Đ����Ԃ��擾����
    TotalTime = MV1GetAttachAnimTotalTime(ModelHandle, AttachIndex);

    // �Đ����Ԃ̏�����
    PlayTime = 0.0f;


    int MaterialNum = DxLib::MV1GetMaterialNum(ModelHandle);
    for (int i = 0; i < MaterialNum; i++)
    {
        // �}�e���A���̗֊s���̑������擾 
        float dotwidth = DxLib::MV1GetMaterialOutLineDotWidth(ModelHandle, i);
        // �}�e���A���̗֊s���̑������g�債�������������� 
        DxLib::MV1SetMaterialOutLineDotWidth(ModelHandle, i, dotwidth / ModelHandle);
    }


    // �����L�[��������邩�E�C���h�E��������܂Ń��[�v
    while (!ScreenFlip() && !ProcessMessage() && !ClearDrawScreen()) {

        // �Đ����Ԃ�i�߂�
        PlayTime += 0.2f;

        // �Đ����Ԃ��A�j���[�V�����̑��Đ����ԂɒB������Đ����Ԃ��O�ɖ߂�
        if (PlayTime >= TotalTime) {
            PlayTime = 0.0f;
        }

        // �Đ����Ԃ��Z�b�g����
        MV1SetAttachAnimTime(ModelHandle, AttachIndex, PlayTime);

        // �R�c���f���̕`��
        MV1DrawModel(ModelHandle);
    }

    // �c�w���C�u�����̌�n��
    DxLib_End();
}

    // �\�t�g�̏I��
