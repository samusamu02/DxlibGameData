#include <DxLib.h>
#include "TitleScene.h"
#include "TutorialScene.h"
#include "MenuScene.h"
#include "../SceneMag.h"
#include "../Blcok/image.h"
#include "../common/Dec.h"
TitleScene::TitleScene()
{
	//イニシャライズを呼び出し忘れ防止
	Init();
	// 黒い画面が出るのでダミーで一回読んであげる
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
	key_.GetKey();	// キーの情報取得
	if (key_.input[KEY_INPUT_SPACE] == 2)
	{
		return std::make_unique<MenuScene>();
	}

	DrawOwnScreen(delta);		// 自分のスクリーン対して描画情報を与える
	return ownScene;
}

void TitleScene::DrawOwnScreen(double delta)
{
	// 自分自身のスクリーンに対してDraw
	SetDrawScreen(screenID_);
	ClsDrawScreen();
	DrawGraph(0, 0, TitleBackGPic_, true);
	DrawRotaGraph((titlePos_.x_ + (titlePicSizeX_ / 2)) + 250, titlePos_.y_ + (titlePicSizeY_ / 2) + 150, titleExrate, 0.0, TitlePic_, true);
	// 徐々に小さくする
	if (titleExrate < 1.0)
	{
		titleExrate += 0.01;
	}
	// タイトルロゴの大きさが1になったら
	if (titleExrate >= 1.0)
	{
		// 点滅表示
		if ((count / 50) % 2 == 0)
		{
			DrawGraph(playKeyPicPos_.x_ + (titlePicSizeX_ / 2) - 50, playKeyPicPos_.y_ + (playKeyPicSizeY_ / 2) + 350, PlayKeyPic_, true);
		}
		count++;
	}
}