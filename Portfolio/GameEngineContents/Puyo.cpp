#include "Puyo.h"
#include "GameEngineBase/GameEngineWindow.h"
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngine/GameEngine.h>

Puyo::Puyo() 
{
}

Puyo::~Puyo() 
{
}

void Puyo::Start()
{
	SetPosition(GameEngineWindow::GetScale().Half());
	SetScale({ 100, 100 });

	CreateRenderer("CompanyLogo.bmp");
}

void Puyo::Update()
{

}

void Puyo::Render()
{
	//DebugRectRender();

	//GameEngineImage* FindeImage = GameEngineImageManager::GetInst()->Find("CompanyLogo.bmp");

	//if (nullptr == FindeImage)
	//{
	//	MsgBoxAssert("Error");
	//}

	//GameEngine::BackBufferImage()->BitCopyCenter(FindeImage, GetPosition());
}
