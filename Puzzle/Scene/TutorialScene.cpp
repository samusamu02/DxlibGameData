#include "TutorialScene.h"
#include "GameScene.h"
#include "../Blcok/Tutorial.h"
#include "../Blcok/image.h"
TutorialScene::TutorialScene()
{
	//イニシャライズを呼び出し忘れ防止
	Init();
	// 黒い画面が出るのでダミーで一回読んであげる
	DrawOwnScreen(0.0);
}

TutorialScene::~TutorialScene()
{
}

bool TutorialScene::Init(void)
{
	tutorial_ = new Tutorial();
	return true;
}

uniqueScene TutorialScene::Updata(double delta, uniqueScene ownScene)
{
	key_.GetKey();	// キーの情報取得
	tutorial_->Update();

	if (key_.input[KEY_INPUT_RETURN] == 1)
	{
		return std::make_unique<GameScene>();
	}

	DrawOwnScreen(delta);		// 自分のスクリーン対して描画情報を与える
	return ownScene;
}

void TutorialScene::DrawOwnScreen(double delta)
{
	SetDrawScreen(screenID_);
	ClsDrawScreen();
	DrawBox(0, 0, 1024, 768, 0xb38e6f, true);
	//for (int y = 0; y < 3; y++)
	//{
	//	for (int x = 0; x < 8; x++)
	//	{
	//		DrawCircle((x * 120) + 80, (y * 120) + 80, 35, 0xe73562, true);
	//	}
	//}
	tutorial_->Draw();
}
