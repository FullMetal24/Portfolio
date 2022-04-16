#include "InGame.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngineBase/GameEngineRandom.h>
#include <GameEngine/GameEngineActor.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngine/GameEngine.h>
#include "FadeInOutBackground.h"
#include "InGameActor.h"
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
	, LevelCount_(15.f)
	, IsStart_(true) //일단 트루
{ 
} 

InGame::~InGame()
{ 

}

void InGame::Loading()
{
	PuyoAnimationInit();

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


void InGame::PuyoAnimationInit()
{
	{
		GameEngineImage* NomalImage = GameEngineImageManager::GetInst()->Find("IG_RED_PUYO.bmp");
		NomalImage->CutCount(1, 1);

		GameEngineImage* CenterImage = GameEngineImageManager::GetInst()->Find("IG_RED_CENTER.bmp");
		CenterImage->CutCount(2, 1);

		GameEngineImage* DestroyImage = GameEngineImageManager::GetInst()->Find("IG_RED_DESTROY.bmp");
		DestroyImage->CutCount(3, 1);

		GameEngineImage* LandImage = GameEngineImageManager::GetInst()->Find("IG_RED_LAND.bmp");
		LandImage->CutCount(3, 1);
		
		GameEngineImage* IdleImage = GameEngineImageManager::GetInst()->Find("IG_RED_IDLE.bmp");
		IdleImage->CutCount(3, 1);

		GameEngineImage* IdleImage1 = GameEngineImageManager::GetInst()->Find("IG_RED_IDLE1.bmp");
		IdleImage1->CutCount(3, 1);

		GameEngineImage* LeftImage = GameEngineImageManager::GetInst()->Find("IG_RED_LEFT.bmp");
		LeftImage->CutCount(1, 1);

		GameEngineImage* RightImage = GameEngineImageManager::GetInst()->Find("IG_RED_RIGHT.bmp");
		RightImage->CutCount(1, 1);

		GameEngineImage* UpImage = GameEngineImageManager::GetInst()->Find("IG_RED_UP.bmp");
		UpImage->CutCount(1, 1);

		GameEngineImage* DownImage = GameEngineImageManager::GetInst()->Find("IG_RED_DOWN.bmp");
		DownImage->CutCount(1, 1);
	}

	{
		GameEngineImage* NomalImage = GameEngineImageManager::GetInst()->Find("IG_BLUE_PUYO.bmp");
		NomalImage->CutCount(1, 1);

		GameEngineImage* CenterImage = GameEngineImageManager::GetInst()->Find("IG_BLUE_CENTER.bmp");
		CenterImage->CutCount(2, 1);

		GameEngineImage* DestroyImage = GameEngineImageManager::GetInst()->Find("IG_BLUE_DESTROY.bmp");
		DestroyImage->CutCount(3, 1);

		GameEngineImage* LandImage = GameEngineImageManager::GetInst()->Find("IG_BLUE_LAND.bmp");
		LandImage->CutCount(2, 1);

		GameEngineImage* IdleImage = GameEngineImageManager::GetInst()->Find("IG_BLUE_IDLE.bmp");
		IdleImage->CutCount(3, 1);

		GameEngineImage* IdleImage1 = GameEngineImageManager::GetInst()->Find("IG_BLUE_IDLE1.bmp");
		IdleImage1->CutCount(3, 1);

		GameEngineImage* LeftImage = GameEngineImageManager::GetInst()->Find("IG_BLUE_LEFT.bmp");
		LeftImage->CutCount(1, 1);

		GameEngineImage* RightImage = GameEngineImageManager::GetInst()->Find("IG_BLUE_RIGHT.bmp");
		RightImage->CutCount(1, 1);

		GameEngineImage* UpImage = GameEngineImageManager::GetInst()->Find("IG_BLUE_UP.bmp");
		UpImage->CutCount(1, 1);

		GameEngineImage* DownImage = GameEngineImageManager::GetInst()->Find("IG_BLUE_DOWN.bmp");
		DownImage->CutCount(1, 1);
	}

	{
		GameEngineImage* NomalImage = GameEngineImageManager::GetInst()->Find("IG_GREEN_PUYO.bmp");
		NomalImage->CutCount(1, 1);

		GameEngineImage* CenterImage = GameEngineImageManager::GetInst()->Find("IG_GREEN_CENTER.bmp");
		CenterImage->CutCount(2, 1);

		GameEngineImage* DestroyImage = GameEngineImageManager::GetInst()->Find("IG_GREEN_DESTROY.bmp");
		DestroyImage->CutCount(3, 1);

		GameEngineImage* LandImage = GameEngineImageManager::GetInst()->Find("IG_GREEN_LAND.bmp");
		LandImage->CutCount(2, 1);

		GameEngineImage* IdleImage = GameEngineImageManager::GetInst()->Find("IG_GREEN_IDLE.bmp");
		IdleImage->CutCount(4, 1);

		GameEngineImage* IdleImage1 = GameEngineImageManager::GetInst()->Find("IG_GREEN_IDLE1.bmp");
		IdleImage1->CutCount(4, 1);

		GameEngineImage* LeftImage = GameEngineImageManager::GetInst()->Find("IG_GREEN_LEFT.bmp");
		LeftImage->CutCount(1, 1);

		GameEngineImage* RightImage = GameEngineImageManager::GetInst()->Find("IG_GREEN_RIGHT.bmp");
		RightImage->CutCount(1, 1);

		GameEngineImage* UpImage = GameEngineImageManager::GetInst()->Find("IG_GREEN_UP.bmp");
		UpImage->CutCount(1, 1);

		GameEngineImage* DownImage = GameEngineImageManager::GetInst()->Find("IG_GREEN_DOWN.bmp");
		DownImage->CutCount(1, 1);
	}

	{
		GameEngineImage* NomalImage = GameEngineImageManager::GetInst()->Find("IG_YELLOW_PUYO.bmp");
		NomalImage->CutCount(1, 1);

		GameEngineImage* CenterImage = GameEngineImageManager::GetInst()->Find("IG_YELLOW_CENTER.bmp");
		CenterImage->CutCount(2, 1);

		GameEngineImage* DestroyImage = GameEngineImageManager::GetInst()->Find("IG_YELLOW_DESTROY.bmp");
		DestroyImage->CutCount(3, 1);

		GameEngineImage* LandImage = GameEngineImageManager::GetInst()->Find("IG_YELLOW_LAND.bmp");
		LandImage->CutCount(2, 1);

		GameEngineImage* IdleImage = GameEngineImageManager::GetInst()->Find("IG_YELLOW_IDLE.bmp");
		IdleImage->CutCount(4, 1);

		GameEngineImage* IdleImage1 = GameEngineImageManager::GetInst()->Find("IG_YELLOW_IDLE1.bmp");
		IdleImage1->CutCount(3, 1);

		GameEngineImage* LeftImage = GameEngineImageManager::GetInst()->Find("IG_YELLOW_LEFT.bmp");
		LeftImage->CutCount(1, 1);

		GameEngineImage* RightImage = GameEngineImageManager::GetInst()->Find("IG_YELLOW_RIGHT.bmp");
		RightImage->CutCount(1, 1);

		GameEngineImage* UpImage = GameEngineImageManager::GetInst()->Find("IG_YELLOW_UP.bmp");
		UpImage->CutCount(1, 1);

		GameEngineImage* DownImage = GameEngineImageManager::GetInst()->Find("IG_YELLOW_DOWN.bmp");
		DownImage->CutCount(1, 1);
	}

	{
		GameEngineImage* NomalImage = GameEngineImageManager::GetInst()->Find("IG_PURPLE_PUYO.bmp");
		NomalImage->CutCount(1, 1);

		GameEngineImage* CenterImage = GameEngineImageManager::GetInst()->Find("IG_PURPLE_CENTER.bmp");
		CenterImage->CutCount(2, 1);

		GameEngineImage* DestroyImage = GameEngineImageManager::GetInst()->Find("IG_PURPLE_DESTROY.bmp");
		DestroyImage->CutCount(3, 1);

		GameEngineImage* LandImage = GameEngineImageManager::GetInst()->Find("IG_PURPLE_LAND.bmp");
		LandImage->CutCount(2, 1);

		GameEngineImage* IdleImage = GameEngineImageManager::GetInst()->Find("IG_PURPLE_IDLE.bmp");
		IdleImage->CutCount(5, 1);

		GameEngineImage* IdleImage1 = GameEngineImageManager::GetInst()->Find("IG_PURPLE_IDLE1.bmp");
		IdleImage1->CutCount(3, 1);

		GameEngineImage* LeftImage = GameEngineImageManager::GetInst()->Find("IG_PURPLE_LEFT.bmp");
		LeftImage->CutCount(1, 1);

		GameEngineImage* RightImage = GameEngineImageManager::GetInst()->Find("IG_PURPLE_RIGHT.bmp");
		RightImage->CutCount(1, 1);

		GameEngineImage* UpImage = GameEngineImageManager::GetInst()->Find("IG_PURPLE_UP.bmp");
		UpImage->CutCount(1, 1);

		GameEngineImage* DownImage = GameEngineImageManager::GetInst()->Find("IG_PURPLE_DOWN.bmp");
		DownImage->CutCount(1, 1);
	}

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
			InGameBgm_.Stop();
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
			GameEngineRenderer* NewRenderer = CenterPuyo->CreateRenderer();
			CenterPuyo->SetColor(PuyoColor::RED);
			CenterPuyo->SetMyRenderer(NewRenderer);
			CreatePuyoAnimation(NewRenderer, CenterPuyo->GetColor());

			NewRenderer->ChangeAnimation("IG_RED_CENTER");
		}
		break;
	case static_cast<int>(PuyoColor::BLUE):
		{
			GameEngineRenderer* NewRenderer = CenterPuyo->CreateRenderer();
			CenterPuyo->SetColor(PuyoColor::BLUE);
			CenterPuyo->SetMyRenderer(NewRenderer);
			CreatePuyoAnimation(NewRenderer, CenterPuyo->GetColor());

			NewRenderer->ChangeAnimation("IG_BLUE_CENTER");
		}
		break;
	case static_cast<int>(PuyoColor::GREEN):
		{
			GameEngineRenderer* NewRenderer = CenterPuyo->CreateRenderer();
			CenterPuyo->SetColor(PuyoColor::GREEN);
			CenterPuyo->SetMyRenderer(NewRenderer);
			CreatePuyoAnimation(NewRenderer, CenterPuyo->GetColor());

			NewRenderer->ChangeAnimation("IG_GREEN_CENTER");
		}
		break;
	case static_cast<int>(PuyoColor::YELLOW):
		{
			GameEngineRenderer* NewRenderer = CenterPuyo->CreateRenderer();
			CenterPuyo->SetColor(PuyoColor::YELLOW);
			CenterPuyo->SetMyRenderer(NewRenderer);
			CreatePuyoAnimation(NewRenderer, CenterPuyo->GetColor());

			NewRenderer->ChangeAnimation("IG_YELLOW_CENTER");
		}
		break;
	case static_cast<int>(PuyoColor::PURPLE):
		{
			GameEngineRenderer* NewRenderer = CenterPuyo->CreateRenderer();
			CenterPuyo->SetColor(PuyoColor::PURPLE);
			CenterPuyo->SetMyRenderer(NewRenderer);
			CreatePuyoAnimation(NewRenderer, CenterPuyo->GetColor());

			NewRenderer->ChangeAnimation("IG_PURPLE_CENTER");
		}
		break;
	}

	number = RandomColor_.RandomInt(0, 4);

	switch (number)
	{
	case static_cast<int>(PuyoColor::RED):
		{
			GameEngineRenderer* NewRenderer = ScecondPuyo->CreateRenderer();
			ScecondPuyo->SetColor(PuyoColor::RED);
			ScecondPuyo->SetMyRenderer(NewRenderer);
			CreatePuyoAnimation(NewRenderer, ScecondPuyo->GetColor());

			NewRenderer->ChangeAnimation("IG_RED_PUYO");
		}
		break;
	case static_cast<int>(PuyoColor::BLUE):
		{
			GameEngineRenderer* NewRenderer = ScecondPuyo->CreateRenderer();
			ScecondPuyo->SetColor(PuyoColor::BLUE);
			ScecondPuyo->SetMyRenderer(NewRenderer);
			CreatePuyoAnimation(NewRenderer, ScecondPuyo->GetColor());

			NewRenderer->ChangeAnimation("IG_BLUE_PUYO");
		}
		break;
	case static_cast<int>(PuyoColor::GREEN):
		{
			GameEngineRenderer* NewRenderer = ScecondPuyo->CreateRenderer();
			ScecondPuyo->SetColor(PuyoColor::GREEN);
			ScecondPuyo->SetMyRenderer(NewRenderer);
			CreatePuyoAnimation(NewRenderer, ScecondPuyo->GetColor());

			NewRenderer->ChangeAnimation("IG_GREEN_PUYO");
		}
		break;
	case static_cast<int>(PuyoColor::YELLOW):
		{
			GameEngineRenderer* NewRenderer = ScecondPuyo->CreateRenderer();
			ScecondPuyo->SetColor(PuyoColor::YELLOW);
			ScecondPuyo->SetMyRenderer(NewRenderer);
			CreatePuyoAnimation(NewRenderer, ScecondPuyo->GetColor());

			NewRenderer->ChangeAnimation("IG_YELLOW_PUYO");
		}
		break;
	case static_cast<int>(PuyoColor::PURPLE):
		{
			GameEngineRenderer* NewRenderer = ScecondPuyo->CreateRenderer();
			ScecondPuyo->SetColor(PuyoColor::PURPLE);
			ScecondPuyo->SetMyRenderer(NewRenderer);
			CreatePuyoAnimation(NewRenderer, ScecondPuyo->GetColor());

			NewRenderer->ChangeAnimation("IG_PURPLE_PUYO");
		}
		break;
	}

	if (nullptr == NewPuyoPair)
	{
		return nullptr;
	}

	return NewPuyoPair;
}

void InGame::CreatePuyoAnimation(GameEngineRenderer* _Renderer, PuyoColor _Color)
{
	switch (_Color)
	{
	case PuyoColor::RED:
		_Renderer->CreateAnimation("IG_RED_PUYO.bmp", "IG_RED_PUYO", 0, 0, 0.f, false);
		_Renderer->CreateAnimation("IG_RED_CENTER.bmp", "IG_RED_CENTER", 0, 1, 0.1f, true);
		_Renderer->CreateAnimation("IG_RED_LAND.bmp", "IG_RED_LAND", 0, 2, 0.1f, false);

		_Renderer->CreateAnimation("IG_RED_LEFT.bmp", "IG_RED_LEFT", 0, 0, 0.f, false);
		_Renderer->CreateAnimation("IG_RED_RIGHT.bmp", "IG_RED_RIGHT", 0, 0, 0.f, false);
		_Renderer->CreateAnimation("IG_RED_UP.bmp", "IG_RED_UP", 0, 0, 0.f, false);
		_Renderer->CreateAnimation("IG_RED_DOWN.bmp", "IG_RED_DOWN", 0, 0, 0.f, false);
		break;
	case PuyoColor::BLUE:
		_Renderer->CreateAnimation("IG_BLUE_PUYO.bmp", "IG_BLUE_PUYO", 0, 0, 0.f, false);
		_Renderer->CreateAnimation("IG_BLUE_CENTER.bmp", "IG_BLUE_CENTER", 0, 1, 0.1f, true);
		_Renderer->CreateAnimation("IG_BLUE_LAND.bmp", "IG_BLUE_LAND", 0, 1, 0.1f, false);

		_Renderer->CreateAnimation("IG_BLUE_LEFT.bmp", "IG_BLUE_LEFT", 0, 0, 0.f, false);
		_Renderer->CreateAnimation("IG_BLUE_RIGHT.bmp", "IG_BLUE_RIGHT", 0, 0, 0.f, false);
		_Renderer->CreateAnimation("IG_BLUE_UP.bmp", "IG_BLUE_UP", 0, 0, 0.f, false);
		_Renderer->CreateAnimation("IG_BLUE_DOWN.bmp", "IG_BLUE_DOWN", 0, 0, 0.f, false);
		break;
	case PuyoColor::GREEN:
		_Renderer->CreateAnimation("IG_GREEN_PUYO.bmp", "IG_GREEN_PUYO", 0, 0, 0.f, false);
		_Renderer->CreateAnimation("IG_GREEN_CENTER.bmp", "IG_GREEN_CENTER", 0, 1, 0.1f, true);
		_Renderer->CreateAnimation("IG_GREEN_LAND.bmp", "IG_GREEN_LAND", 0, 1, 0.1f, true);

		_Renderer->CreateAnimation("IG_GREEN_LEFT.bmp", "IG_GREEN_LEFT", 0, 0, 0.f, false);
		_Renderer->CreateAnimation("IG_GREEN_RIGHT.bmp", "IG_GREEN_RIGHT", 0, 0, 0.f, false);
		_Renderer->CreateAnimation("IG_GREEN_UP.bmp", "IG_GREEN_UP", 0, 0, 0.f, false);
		_Renderer->CreateAnimation("IG_GREEN_DOWN.bmp", "IG_GREEN_DOWN", 0, 0, 0.f, false);
		break;
	case PuyoColor::YELLOW:
		_Renderer->CreateAnimation("IG_YELLOW_PUYO.bmp", "IG_YELLOW_PUYO", 0, 0, 0.f, false);
		_Renderer->CreateAnimation("IG_YELLOW_CENTER.bmp", "IG_YELLOW_CENTER", 0, 1, 0.1f, true);
		_Renderer->CreateAnimation("IG_YELLOW_LAND.bmp", "IG_YELLOW_LAND", 0, 1, 0.1f, true);

		_Renderer->CreateAnimation("IG_YELLOW_LEFT.bmp", "IG_YELLOW_LEFT", 0, 0, 0.f, false);
		_Renderer->CreateAnimation("IG_YELLOW_RIGHT.bmp", "IG_YELLOW_RIGHT", 0, 0, 0.f, false);
		_Renderer->CreateAnimation("IG_YELLOW_UP.bmp", "IG_YELLOW_UP", 0, 0, 0.f, false);
		_Renderer->CreateAnimation("IG_YELLOW_DOWN.bmp", "IG_YELLOW_DOWN", 0, 0, 0.f, false);
		break;
	case PuyoColor::PURPLE:
		_Renderer->CreateAnimation("IG_PURPLE_PUYO.bmp", "IG_PURPLE_PUYO", 0, 0, 0.f, false);
		_Renderer->CreateAnimation("IG_PURPLE_CENTER.bmp", "IG_PURPLE_CENTER", 0, 1, 0.1f, true);
		_Renderer->CreateAnimation("IG_PURPLE_LAND.bmp", "IG_PURPLE_LAND", 0, 1, 0.1f, true);

		_Renderer->CreateAnimation("IG_PURPLE_LEFT.bmp", "IG_PURPLE_LEFT", 0, 0, 0.f, false);
		_Renderer->CreateAnimation("IG_PURPLE_RIGHT.bmp", "IG_PURPLE_RIGHT", 0, 0, 0.f, false);
		_Renderer->CreateAnimation("IG_PURPLE_UP.bmp", "IG_PURPLE_UP", 0, 0, 0.f, false);
		_Renderer->CreateAnimation("IG_PURPLE_DOWN.bmp", "IG_PURPLE_DOWN", 0, 0, 0.f, false);
		break;
	}
}

void InGame::LevelChangeStart()
{
	InGameBgm_ = GameEngineSound::SoundPlayControl("InGame.mp3");

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