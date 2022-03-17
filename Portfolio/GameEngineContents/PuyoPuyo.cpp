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

	ChangeLevel("Title"); //������ Ÿ��Ʋ ���� ���� ������ �ٲ۴�
}

void PuyoPuyo::GameLoop()
{
}

void PuyoPuyo::GameEnd()
{
}