#pragma once
#include<DxLib.h>
#include"../Blcok/Block.h"

// ���݂̃u���b�N�̏��
struct NowBlock
{
	int Type[6][6];
	int tuType[6][6];
	int  Drop[6][6];
	int Expro[6][6];
	bool Del[6][6];
	int Explatioan[6][6];
};

class Key
{
public:
	// �L�[���i�ǂꂭ�炢������Ă��邩�j
	char input[256];
	// �L�[���͗p�֐�
	int GetKey(void)
	{
		char allKey[256];
		GetHitKeyStateAll(allKey);
		for (int i = 0; i < 256; i = i + 1)
		{
			if (allKey[i] == 1)
			{
				input[i]++;
			}
			else if (allKey[i] == 0)
			{
				input[i] = 0;
			}
		}
		return 0;
	}
private:
};

