#include "Title.h"
#include "BlueLightning.h"
#include "CompanyLogo.h"
#include "GameEngine/GameEngineLevel.h"

Title::Title() 
{
}

Title::~Title() 
{
}

void Title::Loading()
{
	CreateActor<CompanyLogo>(1);
	CreateActor<BlueLightning>(0); 
}

void Title::Update()
{

}


