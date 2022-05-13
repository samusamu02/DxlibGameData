#pragma once
#include <DxLib.h>
#include <list>
class Image
{
public:
	int blockPic_[10];
	void LoadImg(void)
	{
		blockPic_[0] = LoadGraph("img/cookies_001.png");
		blockPic_[1] = LoadGraph("img/cookies_002.png");
		blockPic_[2] = LoadGraph("img/cookies_003.png");
		blockPic_[3] = LoadGraph("img/cookies_004.png");
		blockPic_[4] = LoadGraph("img/cookies_011.png");
		blockPic_[5] = LoadGraph("img/cookies_010.png");
		blockPic_[6] = LoadGraph("img/cookies_009.png");
		blockPic_[7] = LoadGraph("img/cookies_013.png");
		blockPic_[8] = LoadGraph("img/cookies_020.png");
		blockPic_[9] = LoadGraph("img/cookies_019.png");
	}
	
	int explode[16];
	void LoadExplode(void)
	{
		LoadDivGraph("img/Exprosion.png", 16, 4, 4, 64, 64, explode, true);
	}

	int cntPic_[5];
	int cntPushPic_[5];
	void LoadCntImg(void)
	{

		cntPic_[0] = LoadGraph("img/Keyboard_Up.png");
		cntPic_[1] = LoadGraph("img/Keyboard_Down.png");
		cntPic_[2] = LoadGraph("img/Keyboard_Left.png");
		cntPic_[3] = LoadGraph("img/Keyboard_Right.png");
		cntPic_[4] = LoadGraph("img/Keyboard_Z.png");

		cntPushPic_[0] = LoadGraph("img/Keyboard_pushUp.png");
		cntPushPic_[1] = LoadGraph("img/Keyboard_pushDown.png");
		cntPushPic_[2] = LoadGraph("img/Keyboard_pushLeft.png");
		cntPushPic_[3] = LoadGraph("img/Keyboard_pushRight.png");
		cntPushPic_[4] = LoadGraph("img/Keyboard_pushZ.png");
	}

	int number[10];
	void NumBerImg(void)
	{
		LoadDivGraph("img/nunber.png", 10, 10, 1, 45, 320, number, true);
	}
};