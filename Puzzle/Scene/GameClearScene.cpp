#include<DxLib.h>
#include "GameClearScene.h"
#include "TitleScene.h"

GameClearScene::GameClearScene()
{
	//�C�j�V�����C�Y���Ăяo���Y��h�~
	Init();
	// ������ʂ��o��̂Ń_�~�[�ň��ǂ�ł�����
	DrawOwnScreen(0.0);
}

GameClearScene::~GameClearScene()
{
}

bool GameClearScene::Init(void)
{
	return true;
}

uniqueScene GameClearScene::Updata(double delta, uniqueScene ownScene)
{
	DrawOwnScreen(delta);
	key_.GetKey();
	if (key_.input[KEY_INPUT_R])
	{
		return std::make_unique<TitleScene>();
	}
	return ownScene;
}

void GameClearScene::DrawOwnScreen(double delta)
{
	// �������g�̃X�N���[���ɑ΂���Draw
	SetDrawScreen(screenID_);
	ClsDrawScreen();
	DrawString(450, 250, "�Q�[���N���A�I", 0xffffff);
	DrawString(435, 350, "R�Ń^�C�g���ɖ߂�", 0xffffff);
}