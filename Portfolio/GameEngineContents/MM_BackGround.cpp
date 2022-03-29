#include "MM_BackGround.h"

MM_BackGround::MM_BackGround() 
{
}

MM_BackGround::~MM_BackGround() 
{
}

void MM_BackGround::Start()
{
	SetPosition(GameEngineWindow::GetScale().Half() + (float4::UP * 300));

	CreateRenderer("MENU_RO.bmp");

}

void MM_BackGround::Update()
{

}

void MM_BackGround::Render()
{

}