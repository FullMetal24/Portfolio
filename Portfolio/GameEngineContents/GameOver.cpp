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
	CreateActor<GO_BackGround>(); //뿌요 같은 경우 해당 조건이 되면 함수를 호출해서 다시 Crate
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
