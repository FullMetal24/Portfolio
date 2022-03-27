#include "CompanyLogo.h"

CompanyLogo::CompanyLogo() 
{
}

CompanyLogo::~CompanyLogo() 
{
}


void CompanyLogo::Start()
{
	SetPosition(GameEngineWindow::GetScale().Half());

	CreateRenderer("PuyoName.bmp");

}

void CompanyLogo::Update()
{


}

void CompanyLogo::Render()
{

}