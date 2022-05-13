#include "Tutorial.h"
Tutorial::Tutorial()
{
	Init();
}

Tutorial::~Tutorial()
{

}

void Tutorial::Init()
{
	// 画像のロード
	image_.LoadImg();
	image_.LoadCntImg();

	for (int y = 0; y < 1; y++)
	{
		for (int x = 0; x < 3; x++)
		{
			nowBlock_.Type[x][y] = 1;
		}
	}


	FontHundle = CreateFontToHandle("HGｺﾞｼｯｸE", 40, NULL, DX_FONTTYPE_ANTIALIASING);
	blockMoveCountFontHundle = CreateFontToHandle("HGｺﾞｼｯｸE", 30, NULL, DX_FONTTYPE_ANTIALIASING);

	contPicVec_ = { 300,400 };
}

void Tutorial::Update()
{

}

void Tutorial::Draw()
{
	key_.GetKey();
	for (int y = 0; y < 1; y++)
	{
		for (int x = 0; x < 3; x++)
		{
			DrawRotaGraph(x * BlockSizeX_ + BlockValX + 50, y * BlockSizeY_ + BlcckValY - 50, 6.0, 0, image_.blockPic_[nowBlock_.Type[x][y]], true);
		}
	}

	// チュートリアル用のブロックの描画
	for (int y = 0; y < block_hight; y++)
	{
		for (int x = 0; x < block_witdh; x++)
		{

		}
	}
	DrawContImg();	// キー画像の描画
	SetString();
}

void Tutorial::DrawContImg(void)
{
	// キーの画像の描画
	key_.GetKey();
	DrawRotaGraph(contPicVec_.x_, contPicVec_.y_, 5.0, 0, image_.cntPic_[0], true);

	DrawRotaGraph(contPicVec_.x_, contPicVec_.y_ + contPicSizeY, 5.0, 0, image_.cntPic_[1], true);

	DrawRotaGraph(contPicVec_.x_ - contPicSizeX, contPicVec_.y_ + contPicSizeY, 5.0, 0, image_.cntPic_[2], true);

	DrawRotaGraph(contPicVec_.x_ + contPicSizeX, contPicVec_.y_ + contPicSizeY, 5.0, 0, image_.cntPic_[3], true);

	DrawRotaGraph(contPicVec_.x_ - contPicSizeX, contPicVec_.y_, 5.0, 0, image_.cntPic_[4], true);

	if (key_.input[KEY_INPUT_UP])
	{
		DrawRotaGraph(contPicVec_.x_, contPicVec_.y_, 5.0, 0, image_.cntPushPic_[0], true);
	}
	if (key_.input[KEY_INPUT_DOWN])
	{
		DrawRotaGraph(contPicVec_.x_, contPicVec_.y_ + contPicSizeY, 5.0, 0, image_.cntPushPic_[1], true);
	}
	if (key_.input[KEY_INPUT_LEFT])
	{
		DrawRotaGraph(contPicVec_.x_ - contPicSizeX, contPicVec_.y_ + contPicSizeY, 5.0, 0, image_.cntPushPic_[2], true);
	}
	if (key_.input[KEY_INPUT_RIGHT])
	{
		DrawRotaGraph(contPicVec_.x_ + contPicSizeX, contPicVec_.y_ + contPicSizeY, 5.0, 0, image_.cntPushPic_[3], true);
	}
	if (key_.input[KEY_INPUT_Z])
	{
		DrawRotaGraph(contPicVec_.x_ - contPicSizeX, contPicVec_.y_, 5.0, 0, image_.cntPushPic_[4], true);
	}
}

void Tutorial::SetString(void)
{
	DrawStringToHandle(BlockSizeX_ - 20, BlockSizeY_ - 30, "ブロックを３つ以上そろえると消えるよ！", 0xfffacd, FontHundle);
	DrawStringToHandle(BlockSizeX_ - 10, BlockSizeY_ + 120, "操作説明", 0xfffacd, FontHundle);
	DrawStringToHandle(BlockSizeX_ -10, BlockSizeY_ + 180, "矢印キーで移動", 0xfffacd, FontHundle);
	DrawStringToHandle(BlockSizeX_ + 400, BlockSizeY_ + 180, "Zキーで選択", 0xfffacd, FontHundle);
	DrawStringToHandle(50, BlockSizeY_ + 550, "Enterキーでチュートリアルを終了", 0xfffacd, FontHundle);
}


unsigned int Tutorial::GetBlcokMoveCont(void)
{
	return blockmoveCount_;
}
