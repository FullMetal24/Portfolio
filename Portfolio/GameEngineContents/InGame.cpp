#include "InGame.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngineBase/GameEngineRandom.h>
#include <GameEngine/GameEngineActor.h>
#include <GameEngine/GameEngineImageManager.h>
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
	case static_cast<int>(PuyoColor::RED):
		{
			GameEngineRenderer* NewRenderer = CenterPuyo->CreateRenderer("IG_RED_PUYO.bmp");
			CenterPuyo->SetMyRenderer(NewRenderer);
			CenterPuyo->SetColor(PuyoColor::RED);
		}
		break;
	case static_cast<int>(PuyoColor::BLUE):
		{
			GameEngineRenderer* NewRenderer = CenterPuyo->CreateRenderer("IG_BLUE_PUYO.bmp");
			CenterPuyo->SetMyRenderer(NewRenderer);
			CenterPuyo->SetColor(PuyoColor::BLUE);
		}
		break;
	case static_cast<int>(PuyoColor::GREEN):
		{
			GameEngineRenderer* NewRenderer = CenterPuyo->CreateRenderer("IG_GREEN_PUYO.bmp");
			CenterPuyo->SetMyRenderer(NewRenderer);
			CenterPuyo->SetColor(PuyoColor::GREEN);
		}
		break;
	case static_cast<int>(PuyoColor::YELLO):
		{
			GameEngineRenderer* NewRenderer = CenterPuyo->CreateRenderer("IG_YELLOW_PUYO.bmp");
			CenterPuyo->SetMyRenderer(NewRenderer);
			CenterPuyo->SetColor(PuyoColor::YELLO);
		}
		break;
	case static_cast<int>(PuyoColor::PURPLE):
		{
			GameEngineRenderer* NewRenderer = CenterPuyo->CreateRenderer("IG_PURPLE_PUYO.bmp");
			CenterPuyo->SetMyRenderer(NewRenderer);
			CenterPuyo->SetColor(PuyoColor::PURPLE);
		}
		break;
	}

	number = RandomColor_.RandomInt(0, 4);

	switch (number)
	{
	case static_cast<int>(PuyoColor::RED):
		{
			GameEngineRenderer* NewRenderer = ScecondPuyo->CreateRenderer("IG_RED_PUYO.bmp");
			ScecondPuyo->SetMyRenderer(NewRenderer);
			ScecondPuyo->SetColor(PuyoColor::RED);
		}
		break;
	case static_cast<int>(PuyoColor::BLUE):
		{
			GameEngineRenderer* NewRenderer = ScecondPuyo->CreateRenderer("IG_BLUE_PUYO.bmp");
			ScecondPuyo->SetMyRenderer(NewRenderer);
			ScecondPuyo->SetColor(PuyoColor::BLUE);
		}
		break;
	case static_cast<int>(PuyoColor::GREEN):
		{
			GameEngineRenderer* NewRenderer = ScecondPuyo->CreateRenderer("IG_GREEN_PUYO.bmp");
			ScecondPuyo->SetMyRenderer(NewRenderer);
			ScecondPuyo->SetColor(PuyoColor::GREEN);
		}
		break;
	case static_cast<int>(PuyoColor::YELLO):
		{
			GameEngineRenderer* NewRenderer = ScecondPuyo->CreateRenderer("IG_YELLOW_PUYO.bmp");
			ScecondPuyo->SetMyRenderer(NewRenderer);
			ScecondPuyo->SetColor(PuyoColor::YELLO);
		}
		break;
	case static_cast<int>(PuyoColor::PURPLE):
		{
			GameEngineRenderer* NewRenderer = ScecondPuyo->CreateRenderer("IG_PURPLE_PUYO.bmp");
			ScecondPuyo->SetMyRenderer(NewRenderer);
			ScecondPuyo->SetColor(PuyoColor::PURPLE);
		}
		break;
	}

	if (nullptr == NewPuyoPair)
	{
		return nullptr;
	}

	return NewPuyoPair;
}

void InGame::PuyoAnimationInit()
{
	{
		GameEngineImage* CenterImage = GameEngineImageManager::GetInst()->Find("IG_RED_CENTER.bmp");
		CenterImage->CutCount(2, 1);

		GameEngineImage* DestroyImage = GameEngineImageManager::GetInst()->Find("IG_RED_DESTROY.bmp");
		DestroyImage->CutCount(3, 1);

		GameEngineImage* LandImage = GameEngineImageManager::GetInst()->Find("IG_RED_LAND.bmp");
		LandImage->CutCount(3, 1);


		GameEngineImage* IdleImage = GameEngineImageManager::GetInst()->Find("IG_RED_CRY.bmp");
		IdleImage->CutCount(3, 1);

		GameEngineImage* IdleImage1 = GameEngineImageManager::GetInst()->Find("IG_RED_ROTATE.bmp");
		IdleImage1->CutCount(3, 1);
	}

	{
		GameEngineImage* CenterImage = GameEngineImageManager::GetInst()->Find("IG_BLUE_CENTER.bmp");
		CenterImage->CutCount(2, 1);

		GameEngineImage* DestroyImage = GameEngineImageManager::GetInst()->Find("IG_BLUE_DESTROY.bmp");
		DestroyImage->CutCount(3, 1);

		GameEngineImage* LandImage = GameEngineImageManager::GetInst()->Find("IG_BLUE_LAND.bmp");
		LandImage->CutCount(2, 1);

		GameEngineImage* IdleImage = GameEngineImageManager::GetInst()->Find("IG_BLUE_IDLE1.bmp");
		IdleImage->CutCount(3, 1);

		GameEngineImage* IdleImage1 = GameEngineImageManager::GetInst()->Find("IG_BLUE_IDLE2.bmp");
		IdleImage1->CutCount(3, 1);
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