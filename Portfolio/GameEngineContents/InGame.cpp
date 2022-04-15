#include "InGame.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngineBase/GameEngineRandom.h>
#include <GameEngine/GameEngineActor.h>
#include <GameEngine/GameEngine.h>
#include "FadeInOutBackground.h"
#include "PuyoPair.h"
#include "Puyo.h"
#include "FSM.h"

InGame::InGame() 
	: Stages_{ }
	, Player_(nullptr)
	, FSM_(nullptr)
	, EnemyProfile_(nullptr)
	, Stage_(nullptr)
	, RandomColor_{}
	, StageClear_(0)
	, LevelCount_(7.f)
	, IsStart_(true) //일단 트루
{ 
} 

InGame::~InGame()
{ 

}

void InGame::Loading()
{
	FadeBackground_ = CreateActor<FadeInOutBackground>();

	Stages_[0] = CreateActor<Stage>();

	Stages_[0]->SetPosition(GameEngineWindow::GetScale().Half());
	Stages_[0]->CreateRenderer("IG_STAGE1.bmp", 2);
	Stages_[0]->CreateRenderer("IG_STAGE1_BACK.bmp", 0);

	GameEngineActor* ActorNext = CreateActor<Stage>(3);
	ActorNext->CreateRenderer("IG_NEXT.bmp")->SetPivot({GameEngineWindow::GetScale().Half().x, GameEngineWindow::GetScale().Half().y - 360.f });
	
	GameEngineActor* PlayerName_ = CreateActor<Stage>(1);
	PlayerName_->CreateRenderer("IG_ARLENAME.bmp")->SetPivot({ GameEngineWindow::GetScale().Half().x - 96.f, GameEngineWindow::GetScale().Half().y - 290.f });

	Player_ = CreateActor<Player>();
	FSM_ = CreateActor<FSM>();

	Player_->SetCurrentPair(CreatePuyoPair());
	Player_->SetNextPair(CreatePuyoPair());
	Player_->SetNextNextPair(CreatePuyoPair());

	Player_->CurrentPairInit();

	//FSM_->CurrentPair_ = CreatePuyoPair();
	//FSM_->NextPair_ = CreatePuyoPair();
	//FSM_->NextNextPair_ = CreatePuyoPair();
}

void InGame::Update()
{
	LevelCount_ -= GameEngineTime::GetDeltaTime();

	if (true == Player_->GetAllLanding() && false == Player_->GetLose())
	{
		Player_->AddPuyoPair(CreatePuyoPair());
	}

	else if (true == Player_->GetAllLanding() && true == Player_->GetLose() && 0 >= LevelCount_)
	{
		FadeBackground_->FadeOn();
		FadeBackground_->GetMyRenderer()->SetOrder(20);
		FadeBackground_->SetFadeSpeed(500.f);

		if (true == FadeBackground_->GetIsChage())
		{
			GameEngine::GetInst().ChangeLevel("GameOver");
		}
	}
}


PuyoPair* InGame::CreatePuyoPair()
{
	PuyoPair* NewPuyoPair = CreateActor<PuyoPair>();

	Puyo* CenterPuyo = NewPuyoPair->GetCenterPuyo();
	CenterPuyo = CreateActor<Puyo>(1);
	NewPuyoPair->SetCenterPuyo(CenterPuyo);

	Puyo* ScecondPuyo = NewPuyoPair->GetSecondPuyo();
	ScecondPuyo = CreateActor<Puyo>(1);
	NewPuyoPair->SetSecondPuyo(ScecondPuyo);

	int number = RandomColor_.RandomInt(0, 4);

	switch (number)
	{
	case static_cast<int>(Color::RED):
		CenterPuyo->CreateRenderer("IG_RED_PUYO_1.bmp");
		CenterPuyo->SetColor(Color::RED);
		break;
	case static_cast<int>(Color::BLUE):
		CenterPuyo->CreateRenderer("IG_RED_PUYO_4.bmp");
		CenterPuyo->SetColor(Color::BLUE);
		break;
	case static_cast<int>(Color::GREEN):
		CenterPuyo->CreateRenderer("IG_RED_PUYO_5.bmp");
		CenterPuyo->SetColor(Color::GREEN);
		break;
	case static_cast<int>(Color::YELLO):
		CenterPuyo->CreateRenderer("IG_RED_PUYO_2.bmp");
		CenterPuyo->SetColor(Color::YELLO);
		break;
	case static_cast<int>(Color::PURPLE):
		CenterPuyo->CreateRenderer("IG_RED_PUYO_3.bmp");
		CenterPuyo->SetColor(Color::PURPLE);
		break;
	}

	number = RandomColor_.RandomInt(0, 4);

	switch (number)
	{
	case static_cast<int>(Color::RED):
		ScecondPuyo->CreateRenderer("IG_RED_PUYO_1.bmp");
		ScecondPuyo->SetColor(Color::RED);
		break;
	case static_cast<int>(Color::BLUE):
		ScecondPuyo->CreateRenderer("IG_RED_PUYO_4.bmp");
		ScecondPuyo->SetColor(Color::BLUE);
		break;
	case static_cast<int>(Color::GREEN):
		ScecondPuyo->CreateRenderer("IG_RED_PUYO_5.bmp");
		ScecondPuyo->SetColor(Color::GREEN);
		break;
	case static_cast<int>(Color::YELLO):
		ScecondPuyo->CreateRenderer("IG_RED_PUYO_2.bmp");
		ScecondPuyo->SetColor(Color::YELLO);
		break;
	case static_cast<int>(Color::PURPLE):
		ScecondPuyo->CreateRenderer("IG_RED_PUYO_3.bmp");
		ScecondPuyo->SetColor(Color::PURPLE);
		break;
	}

	if (nullptr == NewPuyoPair)
	{
		return nullptr;
	}

	return NewPuyoPair;
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