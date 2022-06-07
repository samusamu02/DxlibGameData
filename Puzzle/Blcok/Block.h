#pragma once
#include <list>
#include <memory>
#include "image.h"
#include "../common/Vector2.h"
#include "../common/Dec.h"

class Block
{
public:
	Block();
	~Block();

	void Update(void);
	void Draw(void);

	// get関数
	unsigned int GetScore();				// スコアの取得
	float GetLimitTime(void);
private:
	void Init(void);

	void Move(void);
	void DeleBlock(void);
	void DownBlock(void);

	unsigned int score_ = 0;				// スコア
	Key key_;

	int keyCount_ = 0;
	// ブロックの大きさ
	double blockMult_ = 0.0;

	// ブロックのVal値
	int BlockValX = 80;
	int BlockValY = 200;

	// ボックスのVal値
	int boxValX = 35;
	int boxValY = 155;

	// ブロックの配置
	int block_hight_ = 6;
	int block_witdh_ = 6;

	// 画像の大きさと座標
	Vector2 blockpos_;
	Vector2 blockSize_ = { 96,96 };

	unsigned int ZkeyCount_ = 0;				// Zキーカウンター

	Vector2 boxpos_;
	Vector2 boxSelpos_;							// 選択用の画像の座標

	// タイマー系
	float setTime = 5.0f;
	float startTime = 4.0f;
	float limitTime = 90.0f;
	float respawnTime;							// ブロック再配置までの時間
	float deltaTime = 0.018f;

	// フォント画像の倍率を大きさ
	double stringExRate_ = 1.0;
	int StringPicSizeX_ = 10;
	int StringPicSizeY_ = 320;

	int animCount = 0;
	bool explotionFlag = false;

	int FontHundle;
	int FontHundle2;
	int blockMoveCountFontHundle;

	// フォント画像の座標
	Vector2 scorePicPos;
	Vector2 clearScorePicPos;
	Vector2 timePicPos;
	Vector2  blockMoveCountPicPos;
	Vector2 rankFontPic;

	NowBlock nowBlock_;		// 現在のブロックの削除
	Image image_;

	// セレクター
	int selectImage_;
	int selectPicSizeX = 1019;
	int selectPicSizeY = 767;

	int selSelectorImage_;
	int selSelectorPicSizeX_ = 1019;
	int selSelectorPicSizeY_ = 767;

	// 背景画像
	int backImage_;
	int backPicSizeX = 1024;
	int backPicSizeY = 768;

	// フォント画像
	int ClearScorePic_;
	int timePic_;
	int blockMoveCountPic_;
	int scorePic_;
	int resultPic_;
	int conditionPic_;

	int rankS_;
	int rankA_;
	int rankB_;
	int rankC_;
	int rankD_;

	int StopPicS_;
	int StopPicA_;
	int StopPicB_;
	int StopPicC_;
	int StopPicD_;

	// 枠組み
	int blueFrame_;
	int blueFrameBlock_;
	int blueFrameScore_;
	int blueFrameTime_;
	int blueFrameMove_;
	int blueFrameCong_;
	int blueFrameTimeAndUntilscore_;

	// 効果音
	int ZkeySelectSE_;
	int moveSE_;
};

