#include "CompanyLogo.h"
#include <GameEngine/GameEngineRenderer.h>

CompanyLogo::CompanyLogo() 
{
}

CompanyLogo::~CompanyLogo() 
{
}


void CompanyLogo::Start()
{
	SetPosition(GameEngineWindow::GetScale().Half());
	GameEngineRenderer* Renderer1 = CreateRenderer("OP_COMPANYLOGO.bmp");
}

void CompanyLogo::Update()
{


}

void CompanyLogo::Render()
{

}