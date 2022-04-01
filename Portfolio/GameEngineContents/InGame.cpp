#include "InGame.h"
#include "PuyoPair.h"
#include "Player.h"
#include "Enemy.h"
#include <GameEngine/GameEngineActor.h>
#include <GameEngineBase/GameEngineWindow.h>
#include "Stage.h"

InGame::InGame() 
	: Player_(nullptr)
	, CurrentEnemy_(nullptr)
{ 
} 

InGame::~InGame()
{ 
	if (nullptr != Player_)
	{
		delete Player_;
		Player_ = nullptr;
	}

	if (nullptr != CurrentEnemy_)
	{
		delete CurrentEnemy_;
		CurrentEnemy_ = nullptr;
	}
}

void InGame::Loading()
{
	Stages_[0] = CreateActor<Stage>();

	Stages_[0]->SetPosition(GameEngineWindow::GetScale().Half());
	Stages_[0]->CreateRenderer("Stage1.bmp");


	Player_ = new Player();
	CurrentEnemy_ = new Enemy();

	Player_->Start();
	CurrentEnemy_->Start();
}

void InGame::Update()
{
	Player_->Update();
	CurrentEnemy_->Update();
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

	return NewPair; //플레이어, 에네미에서 지워줘야 함
}
