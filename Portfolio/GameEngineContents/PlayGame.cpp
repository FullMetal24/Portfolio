#include "PlayGame.h"
#include "BackGround.h"

PlayGame::PlayGame() 
{
}

PlayGame::~PlayGame() 
{
}

void PlayGame::Loading()
{
	CreateActor<BackGround>("Stage", 0);
}

void PlayGame::Update()
{

}
