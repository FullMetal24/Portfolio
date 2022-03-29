#include "InGame.h"
#include "PuyoPair.h"
#include "Player.h"
#include "Enemy.h"
#include <GameEngine/GameEngineActor.h>
#include "Stage.h"

InGame::InGame() 
{
}

InGame::~InGame()
{
}

void InGame::Loading()
{
	Stages_[0] = CreateActor<Stage>();

	Stages_[0]->SetPosition(GameEngineWindow::GetScale().Half());
	Stages_[0]->CreateRenderer("Stage1.bmp");


	Stages_[1] = CreateActor<Stage>();

	Stages_[1]->SetPosition(GameEngineWindow::GetScale().Half());
	Stages_[1]->CreateRenderer("Stage2.bmp");


	Stages_[1] = CreateActor<Stage>();

	Stages_[1]->SetPosition(GameEngineWindow::GetScale().Half());
	Stages_[1]->CreateRenderer("Stage3.bmp");

	
	//���ù��� ũ�� ���ϱ�

	//Stages_[0] = new Stage();

	
	/*Stages_[0].SetPosition(GameEngineWindow::GetScale().Half());
	Stages_[0].CreateRenderer("Stage1.bmp");

	Stages_[1].SetPosition(GameEngineWindow::GetScale().Half() + (float4::DOWN * 100));
	Stages_[1].CreateRenderer("Stage2.bmp");

	Stages_[2].SetPosition(GameEngineWindow::GetScale().Half() + (float4::DOWN * 200));
	Stages_[2].CreateRenderer("Stage3.bmp");*/
}

void InGame::Update()
{

}

void InGame::LevelChangeStart()
{
}

void InGame::LevelChangeEnd()
{

}

PuyoPair* InGame::CreatePuyoPair()
{
	PuyoPair* NewPair = new PuyoPair();

	return NewPair; //�÷��̾�, ���׹̿��� ������� ��
}
