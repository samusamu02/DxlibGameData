#include <DxLib.h>
#include "GameOverScene.h"
#include "TitleScene.h"
GameOverScene::GameOverScene()
{
	//イニシャライズを呼び出し忘れ防止
	Init();
	// 黒い画面が出るのでダミーで一回読んであげる
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
	// 自分自身のスクリーンに対してDraw
	SetDrawScreen(screenID_);
	ClsDrawScreen();
	DrawString(450,250, "ゲームオーバー", 0xffffff);
	DrawString(435, 350, "Rでタイトルに戻る", 0xffffff);
}
