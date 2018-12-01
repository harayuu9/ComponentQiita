#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

#define SCREE_NLENGTH 20

//�R���\�[���ɏo�͂��邽�߂̃o�b�t�@
class ScreenBuffer
{
public:
	union {
		char buffer[SCREE_NLENGTH * (SCREE_NLENGTH + 1) + 1];
		char buffer2[SCREE_NLENGTH][SCREE_NLENGTH + 1];
	};
	ScreenBuffer()
	{
		Clear();
	}

	void Clear()
	{
		//Buffer���X�y�[�X�ŃN���A
		for (int i = 0; i < SCREE_NLENGTH * (SCREE_NLENGTH + 1); i++)
		{
			buffer[i] = ' ';
		}
		//�s�̏I���ɉ��s�����
		for (int i = 0; i < SCREE_NLENGTH; i++)
			buffer2[i][SCREE_NLENGTH] = '\n';

		//�S�Ă̏I����NULL����
		buffer[SCREE_NLENGTH * (SCREE_NLENGTH + 1)] = '\0';
	}
};

class InputData
{
	static char Buffer;
public:
	static void Update()
	{
		if (_kbhit()) {
			Buffer = _getch();
		}
	}
	static bool KeyCheck(char key)
	{
		if (Buffer == key)
			return true;
		return false;
	}
};

extern ScreenBuffer g_ScreenBuffer;