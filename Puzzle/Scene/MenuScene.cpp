#include <DxLib.h>
#include "MenuScene.h"
#include "GameScene.h"
#include "../common/Dec.h"

const static int GAME_Y = 240;    //�u�Q�[���v������y�ʒu
const static int EX_Y = 300;    //�u�ݒ�v������y�ʒu

typedef enum {
    eMenu_Game,        //�Q�[��
    eMenu_Ex,

    eMenu_Num,        //�{���ڂ̐�
} eMenu;

static int NowSelect = eMenu_Game;    //���݂̑I�����(�����̓Q�[���I��)

MenuScene::MenuScene()
{
    Init();
}

MenuScene::~MenuScene()
{
}

bool MenuScene::Init(void)
{


	return true;
}

uniqueScene MenuScene::Updata(double delta, uniqueScene ownScene)
{
    key_.GetKey();

    if (key_.input[KEY_INPUT_DOWN] == 1) {//���L�[��������Ă�����
        NowSelect = (NowSelect + 1) % eMenu_Num;//�I����Ԃ��������
    }
    if (key_.input[KEY_INPUT_UP] == 1) {//��L�[��������Ă�����
        NowSelect = (NowSelect + (eMenu_Num - 1)) % eMenu_Num;//�I����Ԃ���グ��
    }
    if (key_.input[KEY_INPUT_RETURN] == 1) {//�G���^�[�L�[�������ꂽ��
        switch (NowSelect) {//���ݑI�𒆂̏�Ԃɂ���ď����𕪊�
        case eMenu_Game://�ݒ�I�𒆂Ȃ�
            return std::make_unique<GameScene>();//�V�[����ݒ��ʂɕύX
            break;
        }
    }

    DrawOwnScreen(delta);		// �����̃X�N���[���΂��ĕ`�����^����
    return ownScene;
}

void MenuScene::DrawOwnScreen(double delta)
{
    SetDrawScreen(screenID_);
    ClsDrawScreen();

    DrawString(200, 150, "���j���[��ʁB", GetColor(255, 255, 255));
    DrawString(200, 170, "�㉺�L�[�������A�G���^�[�������ĉ������B", GetColor(255, 255, 255));
    DrawString(280, GAME_Y, "�Q�[��", GetColor(255, 255, 255));
    DrawString(280, EX_Y, "�G�N�X�g��", GetColor(255, 255, 255));
    int y = 0;
    switch (NowSelect) {//���݂̑I����Ԃɏ]���ď����𕪊�
    case eMenu_Game://�Q�[���I�𒆂Ȃ�
        y = GAME_Y;    //�Q�[���̍��W���i�[
        break;
    case eMenu_Ex://�ݒ�I�𒆂Ȃ�
        y = EX_Y;    //�ݒ�̍��W���i�[
        break;
    }
    DrawString(250, y, "��", GetColor(255, 255, 255));
}