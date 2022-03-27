#include "InGame.h"
#include "PuyoPair.h"

InGame::InGame() 
{
}

InGame::~InGame()
{
}

void InGame::Loading()
{
	//CreateActor<Puyo>(0);
	
	//리시버로 크기 정하기
}

void InGame::Update()
{

}

PuyoPair* InGame::CreatePuyoPair()
{
	PuyoPair* NewPair = new PuyoPair();

	return NewPair;
}
