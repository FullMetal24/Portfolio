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

	CreateRenderer("OP_COMPANYLOGO.bmp");

}

void CompanyLogo::Update()
{


}

void CompanyLogo::Render()
{

}