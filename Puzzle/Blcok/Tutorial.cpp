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
	// �摜�̃��[�h
	image_.LoadImg();
	image_.LoadCntImg();

	for (int y = 0; y < 1; y++)
	{
		for (int x = 0; x < 3; x++)
		{
			nowBlock_.Type[x][y] = 1;
		}
	}


	FontHundle = CreateFontToHandle("HG�޼��E", 40, NULL, DX_FONTTYPE_ANTIALIASING);
	blockMoveCountFontHundle = CreateFontToHandle("HG�޼��E", 30, NULL, DX_FONTTYPE_ANTIALIASING);

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

	// �`���[�g���A���p�̃u���b�N�̕`��
	for (int y = 0; y < block_hight; y++)
	{
		for (int x = 0; x < block_witdh; x++)
		{

		}
	}
	DrawContImg();	// �L�[�摜�̕`��
	SetString();
}

void Tutorial::DrawContImg(void)
{
	// �L�[�̉摜�̕`��
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
	DrawStringToHandle(BlockSizeX_ - 20, BlockSizeY_ - 30, "�u���b�N���R�ȏセ�낦��Ə������I", 0xfffacd, FontHundle);
	DrawStringToHandle(BlockSizeX_ - 10, BlockSizeY_ + 120, "�������", 0xfffacd, FontHundle);
	DrawStringToHandle(BlockSizeX_ -10, BlockSizeY_ + 180, "���L�[�ňړ�", 0xfffacd, FontHundle);
	DrawStringToHandle(BlockSizeX_ + 400, BlockSizeY_ + 180, "Z�L�[�őI��", 0xfffacd, FontHundle);
	DrawStringToHandle(50, BlockSizeY_ + 550, "Enter�L�[�Ń`���[�g���A�����I��", 0xfffacd, FontHundle);
}


unsigned int Tutorial::GetBlcokMoveCont(void)
{
	return blockmoveCount_;
}
