#include "Title.h"
#include "Puyo.h"
#include "BackGround.h"
#include "GameEngine/GameEngineLevel.h"

Title::Title() 
{
}

Title::~Title() 
{
}

void Title::Loading()
{
	//CreateActor<Puyo>("CompanyLogo", 0);
	CreateActor<Puyo>("GameLogo", 0);

	//CreateActor<Puyo>("Puyo", 0); //�ѿ� ���� ��� �ش� ������ �Ǹ� �Լ��� ȣ���ؼ� �ٽ� Crate
}

void Title::Update()
{

}


