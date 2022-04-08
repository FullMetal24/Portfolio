#include "InGame.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngineBase/GameEngineRandom.h>
#include <GameEngine/GameEngineActor.h>
#include "PuyoPair.h"
#include "Puyo.h"
#include "FSM.h"

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
	PuyoPair* NewPuyoPair = CreateActor<PuyoPair>();

	Puyo* CenterPuyo = NewPuyoPair->GetCenterPuyo();
	CenterPuyo = CreateActor<Puyo>(1);
	NewPuyoPair->SetCenterPuyo(CenterPuyo);

	Puyo* ScecondPuyo = NewPuyoPair->GetSecondPuyo();
	ScecondPuyo = CreateActor<Puyo>(1);
	NewPuyoPair->SetSecondPuyo(ScecondPuyo);

	GameEngineRandom Ran;
	int number = Ran.RandomInt(0, 5);

	switch (number)
	{
	case static_cast<int>(Color::RED):
		CenterPuyo->CreateRenderer("IG_RED_PUYO_1.bmp");
		break;
	case static_cast<int>(Color::BLUE):
		CenterPuyo->CreateRenderer("IG_RED_PUYO_4.bmp");
		break;
	case static_cast<int>(Color::GREEN):
		CenterPuyo->CreateRenderer("IG_RED_PUYO_5.bmp");
		break;
	case static_cast<int>(Color::YELLO):
		CenterPuyo->CreateRenderer("IG_RED_PUYO_2.bmp");
		break;
	case static_cast<int>(Color::PURPLE):
		CenterPuyo->CreateRenderer("IG_RED_PUYO_3.bmp");
		break;
	}

	number = Ran.RandomInt(0, 5);

	switch (number)
	{
	case static_cast<int>(Color::RED):
		ScecondPuyo->CreateRenderer("IG_RED_PUYO_1.bmp");
		break;
	case static_cast<int>(Color::BLUE):
		ScecondPuyo->CreateRenderer("IG_RED_PUYO_4.bmp");
		break;
	case static_cast<int>(Color::GREEN):
		ScecondPuyo->CreateRenderer("IG_RED_PUYO_5.bmp");
		break;
	case static_cast<int>(Color::YELLO):
		ScecondPuyo->CreateRenderer("IG_RED_PUYO_2.bmp");
		break;
	case static_cast<int>(Color::PURPLE):
		ScecondPuyo->CreateRenderer("IG_RED_PUYO_3.bmp");
		break;
	}

	if (true == _IsPlayer)
	{
		CenterPuyo->SetPosition({ 220.f, -30.f });
		ScecondPuyo->SetPosition({ 220.f, -90.f });

		Player_->AddPuyoPair(NewPuyoPair);
	}

	else
	{
		CenterPuyo->SetPosition({ 620.f, -30.f });
		ScecondPuyo->SetPosition({ 620.f, -90.f });

		FSM_->AddPuyoPair(NewPuyoPair);
	}
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