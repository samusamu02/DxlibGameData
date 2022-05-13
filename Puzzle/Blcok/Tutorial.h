#pragma once
#include "Block.h"
#include "image.h"
class Tutorial :
	public Block
{
public:
	Tutorial();
	~Tutorial();
	void Update(void);
	void Draw(void);
	void SetString(void);

	unsigned int GetBlcokMoveCont(void);	// ブロックの移動
private:
	void Init();
	void DrawContImg(void);

	unsigned int blockmoveCount_ = 1;

	// チュートリアル用の画像の大きさ
	int TuBlockSizeX_ = 96;
	int TuBlockSizeY_ = 96;

	// 画像の大きさ
	int BlockSizeX_ = 96;
	int BlockSizeY_ = 96;

	// ブロックの間隔
	int BlockValX = 80;
	int BlcckValY = 200;

	// ボックスの間隔
	int boxValX = 185;
	int boxValY = 305;

	// キーの画像のサイズ
	int contPicSizeX = 80;
	int contPicSizeY = 80;

	unsigned int ZkeyFlag_ = 0;				// Zキーカウンター


	int block_hight = 3;
	int block_witdh = 3;


	int FontHundle;
	int blockMoveCountFontHundle;

	Vector2 blockpos_;		// ブロック用の画像の座標
	Vector2 blockSelpos_;	// 選択用の画像の座標
	Vector2 contPicVec_;	// 操作説明用の画像の座標

	Image image_;	// 画像の読み込み

	NowBlock nowBlock_;	// 現在のブロックの状態
};

