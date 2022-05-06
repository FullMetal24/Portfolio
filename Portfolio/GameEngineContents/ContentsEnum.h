#pragma once


enum class LevelType
{
	TITLE,
	MAINMENU,
	INGAME,
	CHARACTERSELECT,
	GAMEOVER
};


enum class MenuType
{
	ALONE,
	TOGETHER,
	TRAINING,
	PUZZLE,
	OPTION,
	END
};


enum class PuyoState
{
	Normal, //ȥ�� ���� ��
	Linked, //���� ����
	Land, //������
	Fall, //��������
	Destroy, //�ı���
	LoseFall //�й� �� ����
};

enum class PuyoColor
{
	RED,
	BLUE,
	GREEN,
	YELLOW,
	PURPLE,
	Hindrance
};

enum class PuyoDir
{
	UP, // 0
	DOWN, // 1
	LEFT, // 2
	RIGHT // 3
};



enum class PlayerState
{
	NewPuyo,
	MovePuyo,
	PuyoCheck,
	PuyoDestroy,
	LandPuyo,
	HindranceCheck,
	Win,
	Lose,
	Rest
};

enum class EnemyState
{
	NewPuyo,
	MovePuyo,
	PuyoCheck,
	PuyoDestroy,
	LandPuyo,
	HindranceCheck,
	Win,
	Lose,
	Rest
};


enum class FireOwner
{
	NONE,
	Player,
	Enemy
};
