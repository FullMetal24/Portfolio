#include "GameOver.h"
#include "KnockdownPlayer.h"
#include "GO_BackGround.h"

GameOver::GameOver() 
{
}

GameOver::~GameOver() 
{
}


void GameOver::Loading()
{
	CreateActor<GO_BackGround>(); //�ѿ� ���� ��� �ش� ������ �Ǹ� �Լ��� ȣ���ؼ� �ٽ� Crate

	/*CreateActor<Puyo>("CompanyLogo", 0);
	CreateActor<Puyo>("BackGround1", 0);
	CreateActor<Puyo>("BackGround2", 0);
	CreateActor<Puyo>("BackGround3", 0);
	CreateActor<Puyo>("GameLogo", 0);*/

	//CreateActor<BackGround>("OVER", 0);
}

void GameOver::Update()
{

}

void GameOver::LevelChangeStart()
{

}

void GameOver::LevelChangeEnd()
{

}
