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
	
	//���ù��� ũ�� ���ϱ�
}

void InGame::Update()
{

}

PuyoPair* InGame::CreatePuyoPair()
{
	PuyoPair* NewPair = new PuyoPair();

	return NewPair;
}
