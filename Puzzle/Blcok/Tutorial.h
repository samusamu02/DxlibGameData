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

	unsigned int GetBlcokMoveCont(void);	// �u���b�N�̈ړ�
private:
	void Init();
	void DrawContImg(void);

	unsigned int blockmoveCount_ = 1;

	// �`���[�g���A���p�̉摜�̑傫��
	int TuBlockSizeX_ = 96;
	int TuBlockSizeY_ = 96;

	// �摜�̑傫��
	int BlockSizeX_ = 96;
	int BlockSizeY_ = 96;

	// �u���b�N�̊Ԋu
	int BlockValX = 80;
	int BlcckValY = 200;

	// �{�b�N�X�̊Ԋu
	int boxValX = 185;
	int boxValY = 305;

	// �L�[�̉摜�̃T�C�Y
	int contPicSizeX = 80;
	int contPicSizeY = 80;

	unsigned int ZkeyFlag_ = 0;				// Z�L�[�J�E���^�[


	int block_hight = 3;
	int block_witdh = 3;


	int FontHundle;
	int blockMoveCountFontHundle;

	Vector2 blockpos_;		// �u���b�N�p�̉摜�̍��W
	Vector2 blockSelpos_;	// �I��p�̉摜�̍��W
	Vector2 contPicVec_;	// ��������p�̉摜�̍��W

	Image image_;	// �摜�̓ǂݍ���

	NowBlock nowBlock_;	// ���݂̃u���b�N�̏��
};

