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
