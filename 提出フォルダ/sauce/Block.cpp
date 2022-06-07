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
	// 画像をランダムに表示
	for (int y = 0; y < block_hight_; y++)
	{
		for (int x = 0; x < block_witdh_; x++)
		{
			// ブロックをランダムに表示
			nowBlock_.Type[x][y] = GetRand(9);

			// 値の初期化
			nowBlock_.Del[x][y] = 0;
			nowBlock_.Drop[x][y] = 0;
			nowBlock_.Explatioan[x][y] = 0;
		}
	}

	// 画像の読み込み
	image_.LoadImg();
	image_.LoadExplode();
	image_.NumBerImg();

	// 背景
	backImage_ = LoadGraph("img/Summer2.jpg");

	// 文字画像
	timePic_ = LoadGraph("img/Time.png");
	blockMoveCountPic_ = LoadGraph("img/Move.png");
	conditionPic_ = LoadGraph("img/ClearString.png");
	scorePic_ = LoadGraph("img/ScorePic.png");
	rankS_ = LoadGraph("img/S.png");
	rankA_ = LoadGraph("img/A.png");
	rankB_ = LoadGraph("img/B.png");
	rankC_ = LoadGraph("img/C.png");
	rankD_ = LoadGraph("img/D.png");
	StopPicS_ = LoadGraph("img/stopPic_S.png");
	StopPicA_ = LoadGraph("img/stopPic_A.png");
	StopPicB_ = LoadGraph("img/stopPic_B.png");
	StopPicC_ = LoadGraph("img/stopPic_C.png");
	StopPicD_ = LoadGraph("img/stopPic_D.png");

	// 枠組み
	blueFrameBlock_ = LoadGraph("img/blueBlockFrame.png");
	blueFrameMove_ = LoadGraph("img/blueFrameMove.png");
	blueFrameCong_ = LoadGraph("img/blueConditionFrame.png");
	blueFrameTimeAndUntilscore_ = LoadGraph("img/blueFrameTimeAndUntilscore.png");

	// 効果音
	ZkeySelectSE_ = LoadSoundMem("Sound/SE/Zselect.mp3");
	moveSE_ = LoadSoundMem("Sound/SE/select07.mp3");

	FontHundle = CreateFontToHandle("HG創英角ﾎﾟｯﾌﾟ体", 65, NULL, DX_FONTTYPE_ANTIALIASING);
	FontHundle2 = CreateFontToHandle("HG創英角ﾎﾟｯﾌﾟ体", 70, NULL, DX_FONTTYPE_ANTIALIASING);
	blockMoveCountFontHundle = CreateFontToHandle("HG創英角ﾎﾟｯﾌﾟ体", 30, NULL, DX_FONTTYPE_ANTIALIASING);
}

void Block::Update(void)
{
	// 開始の演出
	if (blockMult_ < 6.0)
	{
		blockMult_ += 0.05;
	}

	Move();

	if (ZkeyCount_ == 1)
	{
		// 一時変数で入れ替え処理
		int change_block;
		change_block = nowBlock_.Type[boxpos_.x_ / blockSize_.x_][boxpos_.y_ / blockSize_.y_];
		nowBlock_.Type[boxpos_.x_ / blockSize_.x_][boxpos_.y_ / blockSize_.y_] = nowBlock_.Type[boxSelpos_.x_ / blockSize_.x_][boxSelpos_.y_ / blockSize_.y_];
		nowBlock_.Type[boxSelpos_.x_ / blockSize_.x_][boxSelpos_.y_ / blockSize_.y_] = change_block;

		boxSelpos_.x_ = boxpos_.x_;
		boxSelpos_.y_ = boxpos_.y_;
	}
	else if (ZkeyCount_ == 2 || setTime < 0)
	{
		DeleBlock();

		ZkeyCount_ = 0;

		for (int y = 0; y < block_hight_; y++)
		{
			for (int x = 0; x < block_witdh_; x++)
			{
				// ブロックが消えたら
				if (nowBlock_.Type[x][y] == -1)
				{
					nowBlock_.Type[x][y] = GetRand(5);	// 再配置
					nowBlock_.Del[x][y] = 0;
					nowBlock_.Drop[x][y] = 0;
				}
			}
		}
	}
}

void Block::Move(void)
{

	key_.GetKey();	// キー情報の取得

	// I never be able to give up on you

	if (static_cast<int>(limitTime) > 0)
	{
		// 移動と範囲指定
		if (blockMult_ > 6)
		{
			if (key_.input[KEY_INPUT_RIGHT] == 1)
			{
				// 1ブロック分進める
				boxpos_.x_ = boxpos_.x_ + blockSize_.x_;
				// 範囲
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
	// X方向の消える処理
	for (int y = 0; y < block_hight_; y++)
	{
		for (int x = 0; x < block_witdh_ - 2; x++)
		{
			// 3ブロック以上が一致しているかを確認する
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
					nowBlock_.Del[x + i][y] = 1;	// もし一致したらブロックを消す
				}
			}
		}
	}
	// Y方向の消える処理
	for (int y = 0; y < block_hight_ - 2; y++)
	{
		for (int x = 0; x < block_witdh_; x++)
		{
			// 3ブロックが以上が一致しているかを確認する
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
					nowBlock_.Del[x][y + i] = 1;	// もし一致したらブロックを消す
				}
			}
		}
	}
	// 処理をしたので実際に消える処理
	for (int y = 0; y < block_hight_; y++)
	{
		for (int x = 0; x < block_witdh_; x++)
		{
			// ブロックが消えたら
			if (nowBlock_.Del[x][y] == 1)
			{

				nowBlock_.Del[x][y] = 0;	// 値を戻す
				nowBlock_.Explatioan[x][y] = 1;
				nowBlock_.Type[x][y] = -1;
				score_ = score_ + 100;
			}
		}
	}

}

void Block::DownBlock(void)
{
	// ブロックが消えたらブロックを落とす
	// ブロックが何かしらある場合
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

			// 落ちる処理を実際に動かす
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

	// ブロックの背景
	DrawGraph(0, 0, backImage_, true);

	// 文字画像の描画
	DrawGraph(0,-30, timePic_, true);
	DrawGraph(720, 400, blockMoveCountPic_, true);
	DrawGraph(0, 0, conditionPic_, true);
	DrawGraph(0, 0, scorePic_, true);

	if (score_ < 3000)
	{
		DrawGraph(0, 0, rankD_, true);
	}
	else if (score_ >= 3000 && score_ < 6000)
	{
		DrawGraph(0, 0, rankC_, true);
	}
	else if (score_ >= 6000 && score_ < 10000)
	{
		DrawGraph(0, 0, rankB_, true);
	}
	else if (score_ >= 10000 && score_ < 20000)
	{
		DrawGraph(0, 0, rankA_, true);
	}
	else if (score_ >= 20000)
	{
		DrawGraph(0, 0, rankS_, true);
	}

	// 枠組みの表示
	DrawGraph(30, -35, blueFrameBlock_, true);
	DrawGraph(0, -30, blueFrameTime_, true);
	DrawGraph(0, -30, blueFrameTimeAndUntilscore_, true);
	DrawGraph(0, -30, blueFrameMove_, true);
	DrawGraph(0, -32, blueFrameCong_, true);

	// フォント
	DrawFormatStringToHandle(800, 350, 0xffa500, FontHundle, "%d", static_cast<int>(limitTime));
	DrawFormatStringToHandle(800, 230, 0xffa500, FontHundle, "%u", score_);

	// 画像の描画
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
				// 選択用のブロック
				if ((static_cast<int>(limitTime) >= 0))
				{
					if (x == boxpos_.x_ / blockSize_.x_ &&
						y == boxpos_.y_ / blockSize_.y_)
					{
						switch (ZkeyCount_)
						{
						case 0:
							setTime = 5;
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
								ZkeyCount_ = 0;
							}

							DrawFormatString(boxSelpos_.x_ + boxValX + 30, boxSelpos_.y_ + boxValY, 0x0000ff, "%d", static_cast<int>(setTime));
							break;
						}
					}
				}
			}
		}
	}

	if ((static_cast<int>(limitTime) <= 0))
	{
		for (int y = 0; y < block_hight_; y++)
		{
			for (int x = 0; x < block_witdh_; x++)
			{
				GraphFilter(image_.blockPic_[nowBlock_.Type[x][y]], DX_GRAPH_FILTER_MONO, -1, 45);

				if (score_ < 3000)
				{
					DrawGraph(0, 0, StopPicD_, true);
				}
				else if (score_ >= 3000 && score_ < 6000)
				{
					DrawGraph(0, 0, StopPicC_, true);
				}
				else if (score_ >= 6000 && score_ < 10000)
				{
					DrawGraph(0, 0, StopPicB_, true);
				}
				else if (score_ >= 10000 && score_ < 20000)
				{
					DrawGraph(0, 0, StopPicA_, true);
				}
				else if (score_ >= 20000)
				{
					DrawGraph(0, 0, StopPicS_, true);
				}
			}
		}
	}

	if (startTime >= 0)
	{
		startTime -= deltaTime;
	}

	if (startTime <= 0)
	{
		if (limitTime >= 0)
		{
			limitTime -= deltaTime;
		}
		// DrawNumber(score_, 1000, 350, 350, 9, 10, false)
	}
}

unsigned int Block::GetScore()
{
   	return score_;
}

float Block::GetLimitTime(void)
{
	return limitTime;
}

