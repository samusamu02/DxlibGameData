#include<DxLib.h>
#include "GameScene.h"
#include "TitleScene.h"
#include "GameOverScene.h"
#include "GameClearScene.h"
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
	key_.GetKey();	// キーの情報取得
	block_->Update();

	// シーン分岐（ゲームクリア、ゲームオーバー）
	if ((block_->GetBlcokMoveCont() == 0) || block_->GetLimitTime())
	{
		if (block_->GetScore() >= block_->GetClerarScore())
		{
			if (key_.input[KEY_INPUT_SPACE] == 1)
			{
				delete block_;
				return std::make_unique<GameClearScene>();
			}
		}
		else
		{
			if (key_.input[KEY_INPUT_SPACE] == 1)
			{
				delete block_;
				return std::make_unique<GameOverScene>();
			}
		}
	}
	DrawOwnScreen(delta);
	return ownScene;
}

void GameScene::DrawOwnScreen(double delta)
{
	// 自分自身のスクリーンに対してDraw
	SetDrawScreen(screenID_);
	ClsDrawScreen();
	block_->Draw();
}