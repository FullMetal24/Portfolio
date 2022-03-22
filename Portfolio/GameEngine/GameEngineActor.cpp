#include "GameEngineActor.h"
#include <GameEngineBase/GameEngineWindow.h>
#include "GameEngine.h"
#include <GameEngine/GameEngineRenderer.h>

GameEngineActor::GameEngineActor()
	: Level_(nullptr)
	, Position_{}
	, Scale_{}
{
}

GameEngineActor::~GameEngineActor() 
{
	std::list<GameEngineRenderer*>::iterator StartIter = RenderList_.begin();
	std::list<GameEngineRenderer*>::iterator EndIter = RenderList_.end();

	for (; StartIter != EndIter; ++StartIter)
	{
		if (nullptr == (*StartIter))
		{
			continue;
		}

		delete (*StartIter);
		(*StartIter) = nullptr;
	}

}

void GameEngineActor::DebugRectRender()
{
	GameEngineRect DebuegRect(Position_, Scale_);

	Rectangle(GameEngine::BackBufferDC(),
		DebuegRect.CenterLeft(), 
		DebuegRect.CenterTop(), 
		DebuegRect.CenterRight(), 
		DebuegRect.CenterBot());
}

GameEngineRenderer* GameEngineActor::CreateRenderer(const std::string& _Image, RenderPivot _PivotType, const float4& _PivotPos)
{
	GameEngineRenderer* NewRenderer = new GameEngineRenderer();

	NewRenderer->SetActor(this);
	NewRenderer->SetImage(_Image);
	NewRenderer->SetPivot(_PivotPos);
	NewRenderer->SetType(_PivotType);

	RenderList_.push_back(NewRenderer);

	return NewRenderer;
}

void GameEngineActor::Rendering()
{
	StartRenderIter = RenderList_.begin();
	EndRenderIter = RenderList_.end();

	for (; StartRenderIter != EndRenderIter; ++StartRenderIter)
	{
		(*StartRenderIter)->Render();
	}
}

