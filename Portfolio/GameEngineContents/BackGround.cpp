#include "BackGround.h"
#include <GameEngine/GameEngineImage.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngineBase/GameEngineDebug.h>
#include <GameEngine/GameEngine.h>
#include <GameEngineBase/GameEngineWindow.h>

BackGround::BackGround() 
{
}

BackGround::~BackGround() 
{
}

void BackGround::Start()
{
	SetPosition(GameEngineWindow::GetScale().Half());
	SetScale({ 100, 100 });

	CreateRenderer("OVER.bmp");
}

void BackGround::Render()
{

	//GameEngineImage* FindeImage = GameEngineImageManager::GetInst()->Find("CompanyLogo.bmp");

	//if (nullptr == FindeImage)
	//{
	//	MsgBoxAssert("Error");
	//}

	//GameEngine::BackBufferImage()->BitCopyCenter(FindeImage, GetPosition());

	//GameEngineImage* FindeImage0 = GameEngineImageManager::GetInst()->Find("GameLogo.bmp");

	//if (nullptr == FindeImage0)
	//{
	//	MsgBoxAssert("Error");
	//}

	//GameEngine::BackBufferImage()->BitCopyCenter(FindeImage0, GetPosition());
}


void BackGround::Update()
{

}


