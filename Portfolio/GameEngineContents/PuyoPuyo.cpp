#include "PuyoPuyo.h"
#include "GameOver.h"
#include "Title.h"
#include "PlayGame.h"
#include "CharacterSelect.h"
#include "MainMenu.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineImageManager.h>

PuyoPuyo::PuyoPuyo() 
{
}

PuyoPuyo::~PuyoPuyo() 
{
}


void PuyoPuyo::GameInit()
{
	GameEngineWindow::GetInst().SetWindowScaleAndPosition({ 100, 100 }, {1280, 720});

	GameEngineImageManager::GetInst()->Load("C:\\Users\\Isaac\\Portfolio\\Portfolio\\APIResources\\CompanyLogo.bmp", "CompanyLogo.bmp");

	CreateLevel<Title>("Title"); 
	CreateLevel<MainMenu>("MainMenu");
	CreateLevel<CharacterSelect>("ChracterSelect");
	CreateLevel<PlayGame>("PlayGame");
	CreateLevel<GameOver>("GameOver");

	ChangeLevel("Title"); //생성한 타이틀 씬을 현재 씬으로 바꾼다
}

void PuyoPuyo::GameLoop()
{
}

void PuyoPuyo::GameEnd()
{
}