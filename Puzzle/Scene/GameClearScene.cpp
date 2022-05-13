#include<DxLib.h>
#include "GameClearScene.h"
#include "TitleScene.h"

GameClearScene::GameClearScene()
{
	//イニシャライズを呼び出し忘れ防止
	Init();
	// 黒い画面が出るのでダミーで一回読んであげる
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
	// 自分自身のスクリーンに対してDraw
	SetDrawScreen(screenID_);
	ClsDrawScreen();
	DrawString(450, 250, "ゲームクリア！", 0xffffff);
	DrawString(435, 350, "Rでタイトルに戻る", 0xffffff);
}