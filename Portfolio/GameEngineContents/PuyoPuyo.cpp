#include "PuyoPuyo.h"
#include "GameOver.h"
#include "Title.h"
#include "Play.h"
#include <GameEngineBase/GameEngineWindow.h>

PuyoPuyo::PuyoPuyo() 
{
}

PuyoPuyo::~PuyoPuyo() 
{
}


void PuyoPuyo::GameInit()
{
	GameEngineWindow::GetInst().SetWindowScaleAndPosition({ 100, 100 }, {1280, 720});

	CreateLevel<Title>("Title"); 
	CreateLevel<Play>("Play");
	CreateLevel<GameOver>("GameOver");

	ChangeLevel("Title"); //생성한 타이틀 씬을 현재 씬으로 바꾼다
}

void PuyoPuyo::GameLoop()
{
}

void PuyoPuyo::GameEnd()
{
}