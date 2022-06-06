#include<DxLib.h>
#include "GameScene.h"
#include "TitleScene.h"
GameScene::GameScene()
{
	Init();
	DrawOwnScreen(0.0);
}

GameScene::~GameScene()
{
}

bool GameScene::Init(void)
{
	block_ = new Block();
	return true;
}

uniqueScene GameScene::Updata(double delta, uniqueScene ownScene)
{
	key_.GetKey();	// �L�[�̏��擾
	block_->Update();

	// �V�[������i�Q�[���N���A�A�Q�[���I�[�o�[�j
	if (block_->GetLimitTime() < 0.0f)
	{
		if (key_.input[KEY_INPUT_SPACE] == 1)
		{
			delete block_;
			return std::make_unique<TitleScene>();
		}
	}
	DrawOwnScreen(delta);
	return ownScene;
}

void GameScene::DrawOwnScreen(double delta)
{
	// �������g�̃X�N���[���ɑ΂���Draw
	SetDrawScreen(screenID_);
	ClsDrawScreen();
	block_->Draw();
}