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

}

void InGame::Loading()
{
	Stages_[0] = CreateActor<Stage>();

	Stages_[0]->SetPosition(GameEngineWindow::GetScale().Half());
	Stages_[0]->CreateRenderer("IG_STAGE1.bmp", 2);
	Stages_[0]->CreateRenderer("IG_STAGE1_BACK.bmp", 0);

	GameEngineActor* ActorNext = CreateActor<Stage>(3);
	ActorNext->CreateRenderer("IG_NEXT.bmp")->SetPivot({GameEngineWindow::GetScale().Half().x, GameEngineWindow::GetScale().Half().y - 360.f });
	
	Player_ = CreateActor<Player>();
	FSM_ = CreateActor<FSM>();

	CreatePuyoPair(true);
}

void InGame::Update()
{
	
}


void InGame::CreatePuyoPair(bool _IsPlayer)
{
	//센터 뿌요
	PuyoPair* NewPuyoPair = CreateActor<PuyoPair>();

	Puyo* CenterPuyo = NewPuyoPair->GetCenterPuyo();
	CenterPuyo = CreateActor<Puyo>(1);
	CenterPuyo->SetPosition({ 220.f, -30.f });
	CenterPuyo->CreateRenderer("IG_RED_PUYO_1.bmp");
	NewPuyoPair->SetCenterPuyo(CenterPuyo);

	//세컨드 뿌요
	Puyo* ScecondPuyo = NewPuyoPair->GetSecondPuyo();
	ScecondPuyo = CreateActor<Puyo>(1);
	ScecondPuyo->SetPosition({ 220.f, -90.f });
	 
	ScecondPuyo->CreateRenderer("IG_RED_PUYO_2.bmp");
	NewPuyoPair->SetSecondPuyo(ScecondPuyo);

	Player_->AddPuyoPair(NewPuyoPair);
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