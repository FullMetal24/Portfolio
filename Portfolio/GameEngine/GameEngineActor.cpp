#include "GameEngineActor.h"
#include <GameEngineBase/GameEngineWindow.h>
#include "GameEngine.h"

GameEngineActor::GameEngineActor()
	: Level_(nullptr)
	, Position_{}
	, Scale_{}
{
}

GameEngineActor::~GameEngineActor() 
{
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

