#include "PuyoPuyo.h"
#include "Title.h"
#include "MainMenu.h"
#include "InGame.h"
#include "EnemySelect.h"
#include "GameOver.h"
#include "BestRecords.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEngineBase/GameEngineFile.h>
#include <GameEngineBase/GameEngineSound.h>
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

	//이미지 파일 저장
	{
		GameEngineDirectory ResourecesDir;
		ResourecesDir.MoveParent("Portfolio");
		ResourecesDir.Move("APIResources");
		ResourecesDir.Move("Level");

		std::vector<GameEngineFile> AllImageFileList = ResourecesDir.GetAllFile("Bmp");

		for (size_t i = 0; i < AllImageFileList.size(); i++)
		{
			GameEngineImageManager::GetInst()->Load(AllImageFileList[i].GetFullPath());
		};
	}

	{
		GameEngineDirectory ResourecesDir;
		ResourecesDir.MoveParent("Portfolio");
		ResourecesDir.Move("APIResources");
		ResourecesDir.Move("Level");
		ResourecesDir.Move("GO_IMAGES");

		std::vector<GameEngineFile> AllImageFileList = ResourecesDir.GetAllFile("Bmp");

		for (size_t i = 0; i < AllImageFileList.size(); i++)
		{
			GameEngineImageManager::GetInst()->Load(AllImageFileList[i].GetFullPath());
		};
	}

	{
		GameEngineDirectory ResourecesDir;
		ResourecesDir.MoveParent("Portfolio");
		ResourecesDir.Move("APIResources");
		ResourecesDir.Move("Actor");

		std::vector<GameEngineFile> AllImageFileList = ResourecesDir.GetAllFile("Bmp");

		for (size_t i = 0; i < AllImageFileList.size(); i++)
		{
			GameEngineImageManager::GetInst()->Load(AllImageFileList[i].GetFullPath());
		};
	}

	{
		GameEngineDirectory ResourcesDir;
		ResourcesDir.MoveParent("Portfolio");
		ResourcesDir.Move("APIResources");
		ResourcesDir.Move("Sound");

		std::vector<GameEngineFile> AllImageFileList = ResourcesDir.GetAllFile();

		for (size_t i = 0; i < AllImageFileList.size(); i++)
		{
			GameEngineSound::LoadRes(AllImageFileList[i].GetFullPath());
		}
	}


	CreateLevel<Title>("Title"); 
	CreateLevel<MainMenu>("MainMenu");
	CreateLevel<EnemySelect>("EnemySelect");
	CreateLevel<InGame>("InGame");
	CreateLevel<GameOver>("GameOver");
	CreateLevel<BestRecords>("BestRecords");

	ChangeLevel("MainMenu");
}

void PuyoPuyo::GameLoop()
{
}

void PuyoPuyo::GameEnd()
{


}