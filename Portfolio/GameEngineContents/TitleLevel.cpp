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
	//Ÿ��Ʋ ������ ���ڸ��� ����
	//GameEngine::GlobalEngine().ChangeLevel("Play");
}