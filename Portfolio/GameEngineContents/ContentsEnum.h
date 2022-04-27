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
	Normal,
	Land,
	Fall,
	Destroy
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
	Lose
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
	Lose
};


enum class FireOwner
{
	NONE,
	Player,
	Enemy
};
