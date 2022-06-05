#include <DxLib.h>
#include <time.h>
#include <math.h>
#include "Block.h"

Block::Block()
{
	Init();
}

Block::~Block()
{

}

void Block::Init(void)
{
	// �摜�������_���ɕ\��
	for (int y = 0; y < block_hight_; y++)
	{
		for (int x = 0; x < block_witdh_; x++)
		{
			// �u���b�N�������_���ɕ\��
			nowBlock_.Type[x][y] = GetRand(9);

			// �����_���ł͂Ȃ��u���b�N�̕\��
			//nowBlock_.Type[0][1] = 1;
			//nowBlock_.Type[1][1] = 1;
			//nowBlock_.Type[2][1] = 1;

			//nowBlock_.Type[5][3] = 2;
			//nowBlock_.Type[5][4] = 2;
			//nowBlock_.Type[5][5] = 2;

			// �l�̏�����
			nowBlock_.Del[x][y] = 0;
			nowBlock_.Drop[x][y] = 0;
			nowBlock_.Explatioan[x][y] = 0;
		}
	}

	// �摜�̓ǂݍ���
	image_.LoadImg();
	image_.LoadExplode();
	image_.NumBerImg();

	// �w�i
	backImage_ = LoadGraph("img/Summer2.jpg");

	// �����摜
	timePic_ = LoadGraph("img/Time.png");
	scorePic_ = LoadGraph("img/Score.png");
	blockMoveCountPic_ = LoadGraph("img/Move.png");
	conditionPic_ = LoadGraph("img/condition.png");
	untilscorePic_ = LoadGraph("img/Untilscore.png");

	// �g�g��
	blueFrameBlock_ = LoadGraph("img/blueBlockFrame.png");
	blueFrameMove_ = LoadGraph("img/blueFrameMove.png");
	blueFrameCong_ = LoadGraph("img/blueConditionFrame.png");
	blueFrameTimeAndUntilscore_ = LoadGraph("img/blueFrameTimeAndUntilscore.png");

	// BGM 
	GameBGM_ = LoadSoundMem("Sound/BGM/GameBGM.mp3");

	// ���ʉ�
	ZkeySelectSE_ = LoadSoundMem("Sound/SE/Zselect.mp3");
	moveSE_ = LoadSoundMem("Sound/SE/select07.mp3");

	FontHundle = CreateFontToHandle("HG�n�p�p�߯�ߑ�", 65, NULL, DX_FONTTYPE_ANTIALIASING);
	FontHundle2 = CreateFontToHandle("HG�n�p�p�߯�ߑ�", 70, NULL, DX_FONTTYPE_ANTIALIASING);
	blockMoveCountFontHundle = CreateFontToHandle("HG�n�p�p�߯�ߑ�", 30, NULL, DX_FONTTYPE_ANTIALIASING);
}

void Block::Update(void)
{
	// �J�n�̉��o
	if (blockMult_ < 6.0)
	{
		blockMult_ += 0.05;
	}

	Move();

	if (blockmoveCount_ > 0)
	{
		if (ZkeyCount_ == 1)
		{
			// �ꎞ�ϐ��œ���ւ�����
			int change_block;
			change_block = nowBlock_.Type[boxpos_.x_ / blockSize_.x_][boxpos_.y_ / blockSize_.y_];
			nowBlock_.Type[boxpos_.x_ / blockSize_.x_][boxpos_.y_ / blockSize_.y_] = nowBlock_.Type[boxSelpos_.x_ / blockSize_.x_][boxSelpos_.y_ / blockSize_.y_];
			nowBlock_.Type[boxSelpos_.x_ / blockSize_.x_][boxSelpos_.y_ / blockSize_.y_] = change_block;

			boxSelpos_.x_ = boxpos_.x_;
			boxSelpos_.y_ = boxpos_.y_;
		}
		else if (ZkeyCount_ == 2)
		{
			DeleBlock();

			respawnTime -= deltaTime;
			//if (respawnTime < 0)
			//{
				ZkeyCount_ = 0;
				respawnTime = 1.0f;

				if (blockmoveCount_ > 0)
				{
					blockmoveCount_--;
					setTime = 5;
				}

				for (int y = 0; y < block_hight_; y++)
				{
					for (int x = 0; x < block_witdh_; x++)
					{
						// �u���b�N����������
						if (nowBlock_.Type[x][y] == -1)
						{
							nowBlock_.Type[x][y] = GetRand(5);	// �Ĕz�u
							nowBlock_.Del[x][y] = 0;
							nowBlock_.Drop[x][y] = 0;
						}
					}
				}
			//}
		}
	}
}

void Block::Move(void)
{

	key_.GetKey();	// �L�[���̎擾

	// I never be able to give up on you

	if (static_cast<int>(limitTime) > 0)
	{
		// �ړ��Ɣ͈͎w��
		if (blockMult_ > 6)
		{
			if (key_.input[KEY_INPUT_RIGHT] == 1)
			{
				// 1�u���b�N���i�߂�
				boxpos_.x_ = boxpos_.x_ + blockSize_.x_;
				// �͈�
				if (boxpos_.x_ > (blockSize_.x_ * 5))
				{
					boxpos_.x_ = blockSize_.x_ * 5;
				}

				PlaySoundMem(moveSE_, DX_PLAYTYPE_BACK);
			}
			if (key_.input[KEY_INPUT_LEFT] == 1)
			{
				boxpos_.x_ = boxpos_.x_ - blockSize_.x_;
				if (boxpos_.x_ < 0)
				{
					boxpos_.x_ = 0;
				}

				PlaySoundMem(moveSE_, DX_PLAYTYPE_BACK);
			}
			if (key_.input[KEY_INPUT_UP] == 1)
			{
				boxpos_.y_ = boxpos_.y_ - blockSize_.y_;
				if (boxpos_.y_ < 0)
				{
					boxpos_.y_ = 0;
				}

				PlaySoundMem(moveSE_, DX_PLAYTYPE_BACK);
			}
			if (key_.input[KEY_INPUT_DOWN] == 1)
			{
				boxpos_.y_ = boxpos_.y_ + blockSize_.y_;
				if (boxpos_.y_ > (blockSize_.y_ * 5))
				{
					boxpos_.y_ = (blockSize_.y_ * 5);
				}

				PlaySoundMem(moveSE_, DX_PLAYTYPE_BACK);
			}

			if (key_.input[KEY_INPUT_Z] == 1)
			{
				PlaySoundMem(ZkeySelectSE_, DX_PLAYTYPE_BACK);

				boxSelpos_ = boxpos_;
				ZkeyCount_++;
			}
		}
	}
}

void Block::DeleBlock(void)
{
	// X�����̏����鏈��
	for (int y = 0; y < block_hight_; y++)
	{
		for (int x = 0; x < block_witdh_ - 2; x++)
		{
			// 3�u���b�N�ȏオ��v���Ă��邩���m�F����
			if (nowBlock_.Type[x + 0][y] == nowBlock_.Type[x + 1][y] &&
				nowBlock_.Type[x + 1][y] == nowBlock_.Type[x + 2][y] &&
				nowBlock_.Type[x + 2][y] == nowBlock_.Type[x + 0][y] &&
				nowBlock_.Type[x + 0][y] != -1 &&
				nowBlock_.Type[x + 1][y] != -1 &&
				nowBlock_.Type[x + 2][y] != -1)
			{
				for (int i = 0; i < 3; i++)
				{
					nowBlock_.Explatioan[x + i][y] = 1;
					nowBlock_.Del[x + i][y] = 1;	// ������v������u���b�N������
				}
			}
		}
	}
	// Y�����̏����鏈��
	for (int y = 0; y < block_hight_ - 2; y++)
	{
		for (int x = 0; x < block_witdh_; x++)
		{
			// 3�u���b�N���ȏオ��v���Ă��邩���m�F����
			if (nowBlock_.Type[x][y + 0] == nowBlock_.Type[x][y + 1] &&
				nowBlock_.Type[x][y + 1] == nowBlock_.Type[x][y + 2] &&
				nowBlock_.Type[x][y + 2] == nowBlock_.Type[x][y + 0] &&
				nowBlock_.Type[x][y + 0] != -1 &&
				nowBlock_.Type[x][y + 1] != -1 &&
				nowBlock_.Type[x][y + 2] != -1)
			{
				for (int i = 0; i < 3; i++)
				{
					nowBlock_.Explatioan[x][y + i] = 1;
					nowBlock_.Del[x][y + i] = 1;	// ������v������u���b�N������
				}
			}
		}
	}
	// �����������̂Ŏ��ۂɏ����鏈��
	for (int y = 0; y < block_hight_; y++)
	{
		for (int x = 0; x < block_witdh_; x++)
		{
			// �u���b�N����������
			if (nowBlock_.Del[x][y] == 1)
			{

				nowBlock_.Del[x][y] = 0;	// �l��߂�
				nowBlock_.Explatioan[x][y] = 1;
				nowBlock_.Type[x][y] = -1;
				score_ = score_ + 100;
			}
		}
	}

}

void Block::DownBlock(void)
{
	// �u���b�N����������u���b�N�𗎂Ƃ�
	// �u���b�N���������炠��ꍇ
	for (int y = 0; y < block_hight_; y++)
	{
		for (int x = 0; x < block_witdh_; x++)
		{
			if (nowBlock_.Type[x][y] != -1)
			{
				for (int ye = y + 1; ye < 6; ye = ye + 1)
				{
					if (nowBlock_.Type[x][ye] == -1)
					{
						nowBlock_.Drop[x][y] = nowBlock_.Drop[x][y] + 1;
					}
				}
			}

			// �����鏈�������ۂɓ�����
			for (int y = 6 - 1; y > -1; y = y - 1)
			{
				for (int x = 0; x < 6; x = x + 1)
				{
					if (nowBlock_.Drop[x][y] != 0)
					{
						nowBlock_.Type[x][y + nowBlock_.Drop[x][y]] = nowBlock_.Type[x][y];
						nowBlock_.Type[x][y] = -1;
						nowBlock_.Drop[x][y + nowBlock_.Drop[x][y]] = 0;
						nowBlock_.Drop[x][y] = 0;
					}
				}
			}
		}
	}
}

void Block::Draw(void)
{

	// �u���b�N�̔w�i
	DrawGraph(0, 0, backImage_, true);

	// �����摜�̕`��
	DrawGraph(0,-30, timePic_, true);
	DrawGraph(720, 400, blockMoveCountPic_, true);
	DrawGraph(0, -30, conditionPic_, true);
	DrawGraph(0, -30, untilscorePic_, true);

	// �g�g�݂̕\��
	DrawGraph(30, -35, blueFrameBlock_, true);
	DrawGraph(0, -30, blueFrameTime_, true);
	DrawGraph(0, -30, blueFrameTimeAndUntilscore_, true);
	DrawGraph(0, -30, blueFrameMove_, true);
	DrawGraph(0, -32, blueFrameCong_, true);

	// �t�H���g
	DrawFormatStringToHandle(800, 350, 0xffa500, FontHundle, "%d", static_cast<int>(limitTime));
	DrawFormatStringToHandle(800, 230, 0xffa500, FontHundle, "%u", score_);
	//DrawFormatStringToHandle(550, 30, 0xffa500, FontHundle, "%u", clearScore_);
	//DrawFormatStringToHandle(800, 500, 0xffa500, FontHundle, "%u", blockmoveCount_);



	//

	// �摜�̕`��
	for (int y = 0; y < block_hight_; y++)
	{
		for (int x = 0; x < block_witdh_; x++)
		{
			if (nowBlock_.Type[x][y] != -1)
			{
				DrawRotaGraph(x * blockSize_.x_ + BlockValX + 30, y * blockSize_.y_ + BlockValY, blockMult_, 0, image_.blockPic_[nowBlock_.Type[x][y]], true);
			}
			if (blockMult_ >= 6)
			{
				// �I��p�̃u���b�N
				if (blockmoveCount_ > 0 || (static_cast<int>(limitTime) >= 0))
				{
					if (x == boxpos_.x_ / blockSize_.x_ &&
						y == boxpos_.y_ / blockSize_.y_)
					{
						switch (ZkeyCount_)
						{
						case 0:
							DrawBox(boxpos_.x_ + boxValX + 30, boxpos_.y_ + boxValY, boxpos_.x_ + blockSize_.x_ + boxValX + 30, boxpos_.y_ + blockSize_.y_ + boxValY, 0x00ffff, false);
							break;
						case 1:
							DrawBox(boxSelpos_.x_ + boxValX + 30, boxSelpos_.y_ + boxValY, boxSelpos_.x_ + blockSize_.x_ + boxValX + 30, boxSelpos_.y_ + blockSize_.y_ + boxValY, 0xff00ff, false);


							if (setTime >= 0)
							{
								setTime -= deltaTime;
							}
							else if (setTime <= 0)
							{
								blockmoveCount_--;
								ZkeyCount_ = 0;
								setTime = 5;
							}

							DrawFormatString(boxSelpos_.x_ + boxValX, boxSelpos_.y_ + boxValY, 0xffffff, "%d", static_cast<int>(setTime));
							break;
						}
					}
				}
			}
		}
	}

	if ((blockmoveCount_ == 0) || (static_cast<int>(limitTime) <= 0))
	{

		// �Q�[���N���A�p�̃t�B���^�[
		if (score_ >= clearScore_)
		{
			for (int y = 0; y < block_hight_; y++)
			{
				for (int x = 0; x < block_witdh_; x++)
				{
					GraphFilter(image_.blockPic_[nowBlock_.Type[x][y]], DX_GRAPH_FILTER_MONO, -1, 45);
				}
			}
		}

		// �Q�[�����s�p�̃t�B���^�[
		if (score_ < clearScore_)
		{
			for (int y = 0; y < block_hight_; y++)
			{
				for (int x = 0; x < block_witdh_; x++)
				{
					GraphFilter(image_.blockPic_[nowBlock_.Type[x][y]], DX_GRAPH_FILTER_MONO, 0, 30);
				}
			}
		}
	}
	if (startTime >= 0)
	{
		startTime -= deltaTime;
	}

	//if (startTime <= 0)
	//{
	//	if (limitTime >= 0)
	//	{
	//		limitTime -= deltaTime;

	//		if (blockmoveCount_ == 0)
	//		{
	//			limitTime = 0;
	//		}
	//	}
	//	// DrawNumber(score_, 1000, 350, 350, 9, 10, false)
	//}
}

unsigned int Block::GetScore()
{
   	return score_;
}

unsigned int Block::GetBlcokMoveCont(void)
{
	return blockmoveCount_;
}

unsigned int Block::GetClerarScore(void)
{
	return clearScore_;
}

float Block::GetLimitTime(void)
{
	return limitTime;
}

