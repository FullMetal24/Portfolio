#include "Title.h"
#include "BlueLightning.h"
#include "CompanyLogo.h"
#include "Puyo.h"
#include "GameEngine/GameEngineLevel.h"

Title::Title() 
{
}

Title::~Title() 
{
}

void Title::Loading()
{
	CreateActor<CompanyLogo>(0, "CompanyLogo");
	CreateActor<Puyo>(1);
	//CreateActor<BlueLightning>(0); 
}

void Title::Update()
{

}

void Title::LevelChangeStart()
{
}

void Title::LevelChangeEnd()
{
}


