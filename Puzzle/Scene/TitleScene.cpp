#include <DxLib.h>
#include "TitleScene.h"
#include "TutorialScene.h"
#include "MenuScene.h"
#include "../SceneMag.h"
#include "../Blcok/image.h"
#include "../common/Dec.h"
TitleScene::TitleScene()
{
	//�C�j�V�����C�Y���Ăяo���Y��h�~
	Init();
	// ������ʂ��o��̂Ń_�~�[�ň��ǂ�ł�����
	DrawOwnScreen(0.0);
}

TitleScene::~TitleScene()
{
}

bool TitleScene::Init(void)
{
	TitlePic_ = LoadGraph("img/TitlePic.png");
	PlayKeyPic_ = LoadGraph("img/press th space key.png");
	TitleBackGPic_ = LoadGraph("img/nightbackgroundwithmoon.png");
	image_.LoadImg();
	return true;
}

uniqueScene TitleScene::Updata(double delta, uniqueScene ownScene)
{
	key_.GetKey();	// �L�[�̏��擾
	if (key_.input[KEY_INPUT_SPACE] == 2)
	{
		return std::make_unique<MenuScene>();
	}

	DrawOwnScreen(delta);		// �����̃X�N���[���΂��ĕ`�����^����
	return ownScene;
}

void TitleScene::DrawOwnScreen(double delta)
{
	// �������g�̃X�N���[���ɑ΂���Draw
	SetDrawScreen(screenID_);
	ClsDrawScreen();
	DrawGraph(0, 0, TitleBackGPic_, true);
	DrawRotaGraph((titlePos_.x_ + (titlePicSizeX_ / 2)) + 250, titlePos_.y_ + (titlePicSizeY_ / 2) + 150, titleExrate, 0.0, TitlePic_, true);
	// ���X�ɏ���������
	if (titleExrate < 1.0)
	{
		titleExrate += 0.01;
	}
	// �^�C�g�����S�̑傫����1�ɂȂ�����
	if (titleExrate >= 1.0)
	{
		// �_�ŕ\��
		if ((count / 50) % 2 == 0)
		{
			DrawGraph(playKeyPicPos_.x_ + (titlePicSizeX_ / 2) - 50, playKeyPicPos_.y_ + (playKeyPicSizeY_ / 2) + 350, PlayKeyPic_, true);
		}
		count++;
	}
}