#include "TutorialScene.h"
#include "GameScene.h"
#include "../Blcok/Tutorial.h"
#include "../Blcok/image.h"
TutorialScene::TutorialScene()
{
	//�C�j�V�����C�Y���Ăяo���Y��h�~
	Init();
	// ������ʂ��o��̂Ń_�~�[�ň��ǂ�ł�����
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
	key_.GetKey();	// �L�[�̏��擾
	tutorial_->Update();

	if (key_.input[KEY_INPUT_RETURN] == 1)
	{
		return std::make_unique<GameScene>();
	}

	DrawOwnScreen(delta);		// �����̃X�N���[���΂��ĕ`�����^����
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
