#include <DxLib.h>
#include "BaseScene.h"

BaseScene::BaseScene()
{
	SetDrawScreen(DX_SCREEN_BACK);		// 明示的にバックバッファを指定
	GetDrawScreenSize(&screenSize_.x_, &screenSize_.y_);	// 描画先のサイズを取得する(バッファ）
	screenID_ = MakeScreen(screenSize_.x_, screenSize_.y_, true);		// スクリーンのサイズ
}

BaseScene::~BaseScene()
{
}

void BaseScene::Draw(double delta)
{
	// screenIDに対して描画
	DrawGraph(0, 0, screenID_, true);
}