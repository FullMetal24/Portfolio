#include "GameOver.h"
#include "BackGround.h"

GameOver::GameOver() 
{
}

GameOver::~GameOver() 
{
}


void GameOver::Loading()
{
	/*CreateActor<Puyo>("CompanyLogo", 0);
	CreateActor<Puyo>("BackGround1", 0);
	CreateActor<Puyo>("BackGround2", 0);
	CreateActor<Puyo>("BackGround3", 0);
	CreateActor<Puyo>("GameLogo", 0);*/

	CreateActor<BackGround>("OVER", 0);
}

void GameOver::Update()
{

}
