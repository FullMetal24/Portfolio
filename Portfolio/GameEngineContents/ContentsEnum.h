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



enum class PuyoColor
{
	RED,
	BLUE,
	GREEN,
	YELLOW,
	PURPLE
};

enum class PuyoDir
{
	LEFT, // 0
	RIGHT, // 1
	DOWN, // 2
	UP // 3
};



enum class PlayerState
{
	NewPuyo,
	MovePuyo,
	LandPuyo,
	PuyoLandEnd,
	HindranceCheck,
	PuyoCheck,
	PuyoDestroy,
	PuyoDestroyEnd,
	Win,
	Lose
};


enum class FireOwner
{
	NONE,
	Player,
	Enemy
};
