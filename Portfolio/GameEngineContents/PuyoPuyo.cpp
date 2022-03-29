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

	//�� ����� ��� ������ ������
	std::vector<GameEngineFile> AllImageFileList = ResourecesDir.GetAllFile("Bmp");

	for (size_t i = 0; i < AllImageFileList.size(); i++)
	{
		GameEngineImageManager::GetInst()->Load(AllImageFileList[i].GetFullPath());
	}

	GameEngineImage* Image = GameEngineImageManager::GetInst()->Find("Kirby_Walk_Right.bmp");
	Image->CutCount(4, 1);

	//GameEngineImage* Image = GameEngineImageManager::GetInst()->Find(".bmp");
	//Image->Cut({32, 32});

	CreateLevel<Title>("Title"); 
	CreateLevel<MainMenu>("MainMenu");
	CreateLevel<CharacterSelect>("ChracterSelect");
	CreateLevel<InGame>("InGame");
	CreateLevel<GameOver>("GameOver");

	ChangeLevel("Title"); //������ Ÿ��Ʋ ���� ���� ������ �ٲ۴�
}

void PuyoPuyo::GameLoop()
{
}

void PuyoPuyo::GameEnd()
{
}