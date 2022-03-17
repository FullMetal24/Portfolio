#include "PuyoPuyo.h"
#include "EndingLevel.h"
#include "TitleLevel.h"
#include "playLevel.h"
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

	CreateLevel<TitleLevel>("Title"); 
	CreateLevel<PlayLevel>("Play");
	CreateLevel<EndingLevel>("Ending");

	ChangeLevel("Title"); //������ Ÿ��Ʋ ���� ���� ������ �ٲ۴�
}

void PuyoPuyo::GameLoop()
{
}

void PuyoPuyo::GameEnd()
{
}