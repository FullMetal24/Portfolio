#include "GO_BackGround.h"

GO_BackGround::GO_BackGround() 
{
}

GO_BackGround::~GO_BackGround() 
{
}

void GO_BackGround::Start()
{
	SetPosition(GameEngineWindow::GetScale().Half());
	CreateRenderer("OVER.bmp");
}

void GO_BackGround::Update()
{

}

void GO_BackGround::Render()
{

}
