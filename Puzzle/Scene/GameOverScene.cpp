#include <DxLib.h>
#include "GameOverScene.h"
#include "TitleScene.h"
GameOverScene::GameOverScene()
{
	//�C�j�V�����C�Y���Ăяo���Y��h�~
	Init();
	// ������ʂ��o��̂Ń_�~�[�ň��ǂ�ł�����
	DrawOwnScreen(0.0);
}

GameOverScene::~GameOverScene()
{
}

bool GameOverScene::Init(void)
{
	return true;
}

uniqueScene GameOverScene::Updata(double delta, uniqueScene ownScene)
{
	DrawOwnScreen(delta);
	key_.GetKey();
	if (key_.input[KEY_INPUT_R])
	{
		return std::make_unique<TitleScene>();
	}

	return ownScene;
}

void GameOverScene::DrawOwnScreen(double delta)
{
	// �������g�̃X�N���[���ɑ΂���Draw
	SetDrawScreen(screenID_);
	ClsDrawScreen();
	DrawString(450,250, "�Q�[���I�[�o�[", 0xffffff);
	DrawString(435, 350, "R�Ń^�C�g���ɖ߂�", 0xffffff);
}
