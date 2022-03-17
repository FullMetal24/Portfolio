#include "TitleBackGround.h"
#include <GameEngineBase/GameEngineWindow.h>

TitleBackGround::TitleBackGround() 
{
}

TitleBackGround::~TitleBackGround() 
{
}

void TitleBackGround::Start()
{
	SetPosition(GameEngineWindow::GetScale().Half());
	SetScale({ 1280, 720 });
}

void TitleBackGround::Render()
{
	DebugRectRender();
}