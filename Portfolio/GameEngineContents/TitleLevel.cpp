#include "TitleLevel.h"
#include "GameEngine/GameEngine.h"
#include "TitleLogo.h"
#include "TitleBackGround.h"

TitleLevel::TitleLevel() 
{
}

TitleLevel::~TitleLevel() 
{
}

void TitleLevel::Loading()
{
	CreateActor<TitleBackGround>("TitleBackGround", 0);
	CreateActor<TitleLogo>("TitleLogo", 1);
}


void TitleLevel::Update()
{
	//타이틀 레벨이 되자마자 변경
	//GameEngine::GlobalEngine().ChangeLevel("Play");
}