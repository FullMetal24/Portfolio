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
	GameEngineWindow::GetInst().SetWindowScaleAndPosition({ 100, 100 }, {1280, 896});

	GameEngineImageManager::GetInst()->Load("C:\\Users\\Isaac\\Portfolio\\Portfolio\\APIResources\\CompanyLogo.bmp", "CompanyLogo.bmp");
	GameEngineImageManager::GetInst()->Load("C:\\Users\\Isaac\\Portfolio\\Portfolio\\APIResources\\GameLogo.bmp", "GameLogo.bmp");
	GameEngineImageManager::GetInst()->Load("C:\\Users\\Isaac\\Portfolio\\Portfolio\\APIResources\\Stage.bmp", "Stage.bmp");
	GameEngineImageManager::GetInst()->Load("C:\\Users\\Isaac\\Portfolio\\Portfolio\\APIResources\\VS1.bmp", "VS1.bmp");
	GameEngineImageManager::GetInst()->Load("C:\\Users\\Isaac\\Portfolio\\Portfolio\\APIResources\\OVER.bmp", "OVER.bmp");

	CreateLevel<Title>("Title"); 
	CreateLevel<MainMenu>("MainMenu");
	CreateLevel<CharacterSelect>("ChracterSelect");
	CreateLevel<PlayGame>("PlayGame");
	CreateLevel<GameOver>("GameOver");

	ChangeLevel("PlayGame"); //������ Ÿ��Ʋ ���� ���� ������ �ٲ۴�
}

void PuyoPuyo::GameLoop()
{
}

void PuyoPuyo::GameEnd()
{
}