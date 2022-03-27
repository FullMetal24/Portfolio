#include "GameOver.h"
#include "KnockdownPlayer.h"

GameOver::GameOver() 
{
}

GameOver::~GameOver() 
{
}


void GameOver::Loading()
{

	CreateActor<KnockdownPlayer>(0); //뿌요 같은 경우 해당 조건이 되면 함수를 호출해서 다시 Crate

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
