#include "GameEngineRenderer.h"
#include "GameEngineImageManager.h"
#include <GameEngineBase/GameEngineDebug.h>
#include <GameEngine/GameEngine.h>

GameEngineRenderer::GameEngineRenderer() 
{
}

GameEngineRenderer::~GameEngineRenderer() 
{
}

void GameEngineRenderer::SetImage(const std::string& _Name)
{
	GameEngineImage* FindeImage = GameEngineImageManager::GetInst()->Find("CompanyLogo.bmp");

	if (nullptr == FindeImage)
	{
		MsgBoxAssertString(_Name + "�������� �ʴ� �̹����� �������� �����Ϸ��� �߽��ϴ�.");
		return;
	}

	Image_ = FindeImage;
}

void GameEngineRenderer::Render()
{
	GameEngineImage* FindeImage = GameEngineImageManager::GetInst()->Find("CompanyLogo.bmp");

	if (nullptr == FindeImage)
	{
		MsgBoxAssert("Error");
	}

	//GameEngine::BackBufferImage()->BitCopyCenter(Image_, GetPosition());
}

