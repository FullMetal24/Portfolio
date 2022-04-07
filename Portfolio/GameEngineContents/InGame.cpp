#include "InGame.h"
#include "PuyoPair.h"
#include "Player.h"
#include "FSM.h"
#include <GameEngine/GameEngineActor.h>
#include <GameEngineBase/GameEngineWindow.h>
#include "Stage.h"
#include "Puyo.h"

InGame::InGame() 
	: Stages_{ }
	, Player_(nullptr)
	, FSM_(nullptr)
	, EnemyProfile_(nullptr)
	, Stage_(nullptr)
	, StageClear_(0)
	, IsStart_(true) //일단 트루
{ 
} 

InGame::~InGame()
{ 
	if (nullptr != Player_)
	{
		delete Player_;
		Player_ = nullptr;
	}

	if (nullptr != FSM_)
	{
		delete FSM_;
		FSM_ = nullptr;
	}
}

void InGame::Loading()
{
	Stages_[0] = CreateActor<Stage>();

	Stages_[0]->SetPosition(GameEngineWindow::GetScale().Half());
	Stages_[0]->CreateRenderer("IG_STAGE1.bmp", 2);
	Stages_[0]->CreateRenderer("IG_STAGE1_BACK.bmp", 0);

	GameEngineActor* ActorNext = CreateActor<Stage>(3);
	ActorNext->CreateRenderer("IG_NEXT.bmp")->SetPivot({GameEngineWindow::GetScale().Half().x, GameEngineWindow::GetScale().Half().y - 360.f });
	
	Player_ = new Player();
	Player_->Start();

	FSM_ = new FSM();
	FSM_->Start();
}

void InGame::Update()
{
	if (true == IsStart_)
	{
		Player_->Update();
		FSM_->Update();
		IsStart_ = false;
	}
}


PuyoPair* InGame::CreatePuyoPair()
{
	//인게임에서 저장하고 있다고 전부 지우는 편이 맞는듯
	PuyoPair* NewPair = new PuyoPair();

	NewPair->SetCenterPuyo(CreateActor<Puyo>());
	NewPair->SetCenterPuyo(CreateActor<Puyo>());

	NewPair->GetCenterPuyo()->CreateRenderer("IG_RED_PUYO_1.bmp");
	NewPair->GetSecondPuyo()->CreateRenderer("IG_RED_PUYO_1.bmp");
	NewPair->Start();
	return NewPair; 
}


void InGame::LevelChangeStart()
{
	if (nullptr != EnemyProfile_)
	{
		GameEngineActor* Profile = CreateActor<Stage>(4);
		GameEngineRenderer* Renderer = Profile->CreateRenderer();
		Renderer->SetImage(EnemyProfile_->GetImage());

		Renderer->SetImageScale();
		Renderer->SetPivot({ GameEngineWindow::GetScale().Half().x, GameEngineWindow::GetScale().Half().y + 70.f });
	}
}

void InGame::LevelChangeEnd()
{

}