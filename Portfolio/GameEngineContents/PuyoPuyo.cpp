#include "PuyoPuyo.h"
#include "Title.h"
#include "MainMenu.h"
#include "Option.h"
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
	
	//이미지 파일 불러오기
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
		ResourecesDir.Move("Actor");

		std::vector<GameEngineFile> AllImageFileList = ResourecesDir.GetAllFile("Bmp");

		for (size_t i = 0; i < AllImageFileList.size(); i++)
		{
			GameEngineImageManager::GetInst()->Load(AllImageFileList[i].GetFullPath());
		};
	}

	//게임오버 화면 이미지 불러오기
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

	//게임 사운드 불러오기
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
	CreateLevel<Option>("Option");
	CreateLevel<EnemySelect>("EnemySelect");
	CreateLevel<InGame>("InGame");
	CreateLevel<GameOver>("GameOver");
	CreateLevel<BestRecords>("BestRecords");

	ChangeLevel("Title");
}

void PuyoPuyo::GameLoop()
{
}

void PuyoPuyo::GameEnd()
{


}