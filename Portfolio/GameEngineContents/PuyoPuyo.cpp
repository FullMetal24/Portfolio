#include "PuyoPuyo.h"
#include "GameOver.h"
#include "Title.h"
#include "InGame.h"
#include "CharacterSelect.h"
#include "MainMenu.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEngineBase/GameEngineFile.h>
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

	GameEngineDirectory ResourecesDir;
	ResourecesDir.MoveParent("Portfolio");
	ResourecesDir.Move("APIResources");

	//이미지 파일 저장
	std::vector<GameEngineFile> AllImageFileList = ResourecesDir.GetAllFile("Bmp");

	for (size_t i = 0; i < AllImageFileList.size(); i++)
	{
		GameEngineImageManager::GetInst()->Load(AllImageFileList[i].GetFullPath());
	};

	CreateLevel<Title>("Title"); 
	CreateLevel<MainMenu>("MainMenu");
	CreateLevel<CharacterSelect>("CharacterSelect");
	CreateLevel<InGame>("InGame");
	CreateLevel<GameOver>("GameOver");

	ChangeLevel("Title");
}

void PuyoPuyo::GameLoop()
{
}

void PuyoPuyo::GameEnd()
{


}