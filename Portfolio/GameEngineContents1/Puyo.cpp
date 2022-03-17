#include "Puyo.h"
#include "GameEngineBase/GameEngineWindow.h"

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
}

void Puyo::Update()
{
	DebugRectRender();
}

void Puyo::Render()
{
}
