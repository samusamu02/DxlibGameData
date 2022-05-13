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

	// get�֐�
	unsigned int GetScore();				// �X�R�A�̎擾
	unsigned int GetClerarScore(void);		// �N���A�ɕK�v�ȃX�R�A�̎擾
	unsigned int GetBlcokMoveCont(void);	// �u���b�N�̈ړ�
	float GetLimitTime(void);


protected:
	unsigned int score_ = 0;				// �X�R�A
	unsigned int clearScore_ = 900;			// �N���A�ɕK�v�ȃX�R�A
	Key key_;
private:
	void Init(void);

	void Move(void);
	void DeleBlock(void);
	void DownBlock(void);
	unsigned int blockmoveCount_ = 3;		// �u���b�N�𓮂�����񐔂悤�̃J�E���^�[
	int keyCount_ = 0;
	// �u���b�N�̑傫��
	double blockMult_ = 0.0;

	// �u���b�N��Val�l
	int BlockValX = 80;
	int BlockValY = 200;

	// �{�b�N�X��Val�l
	int boxValX = 35;
	int boxValY = 155;

	// �u���b�N�̔z�u
	int block_hight_ = 6;
	int block_witdh_ = 6;

	// �摜�̑傫���ƍ��W
	Vector2 blockpos_;
	Vector2 blockSize_ = { 96,96 };

	unsigned int ZkeyCount_ = 0;				// Z�L�[�J�E���^�[

	Vector2 boxpos_;
	Vector2 boxSelpos_;							// �I��p�̉摜�̍��W

	// �^�C�}�[�n
	float setTime = 5.0f;
	float startTime = 4.0f;
	float limitTime = 30.0f;
	float moveTime = 3.0f;
	float respawnTime;	// �u���b�N�Ĕz�u�܂ł̎���
	float deltaTime = 0.018f;

	// �t�H���g�摜�̔{����傫��
	double stringExRate_ = 1.0;
	int StringPicSizeX_ = 10;
	int StringPicSizeY_ = 320;

	int animCount = 0;
	bool explotionFlag = false;

	int FontHundle;
	int FontHundle2;
	int blockMoveCountFontHundle;

	// �t�H���g�摜�̍��W
	Vector2 scorePicPos;
	Vector2 clearScorePicPos;
	Vector2 timePicPos;
	Vector2  blockMoveCountPicPos;

	NowBlock nowBlock_;		// ���݂̃u���b�N�̍폜
	Image image_;

	// �Z���N�^�[
	int selectImage_;
	int selectPicSizeX = 1019;
	int selectPicSizeY = 767;

	int selSelectorImage_;
	int selSelectorPicSizeX_ = 1019;
	int selSelectorPicSizeY_ = 767;
	// �w�i�摜
	int backImage_;
	int backPicSizeX = 1024;
	int backPicSizeY = 768;

	// �t�H���g�摜
	int ClearScorePic_;
	int timePic_;
	int blockMoveCountPic_;
	int scorePic_;
	int resultPic_;
	int conditionPic_;
	int untilscorePic_;

	// �g�g��
	int blueFrame_;
	int blueFrameBlock_;
	int blueFrameScore_;
	int blueFrameTime_;
	int blueFrameMove_;
	int blueFrameCong_;
	int blueFrameTimeAndUntilscore_;

	// BGM
	int GameBGM_;

	// ���ʉ�
	int ZkeySelectSE_;
	int moveSE_;
};
