#include "GameOver.h"
#include <GameEngine/GameEngine.h>
#include "FadeInOutBackground.h"
#include <GameEngineBase/GameEngineInput.h>
#include "GameOverActor.h"
#include "InGame.h"

GameOver::GameOver()
	:BackRenderer_(nullptr)
	, Background_(nullptr)
	, Count_(0)
	, Time_(0.f)
	, IsLevelStart_(false)
{
}

GameOver::~GameOver() 
{
}


void GameOver::Loading()
{
	FadeBack_ = CreateActor<FadeInOutBackground>();
	FadeBack_->SetMyRenderer(FadeBack_->CreateRenderer("GO_BACKGROUND.bmp"));

	Background_ = CreateActor<GameOverActor>(1);
	Background_->SetPosition({GameEngineWindow::GetScale().Half()});
	BackRenderer_ = Background_->CreateRenderer("GO_IMAGE0.bmp");

	if (false == GameEngineInput::GetInst()->IsKey("ReTry"))
	{
		GameEngineInput::GetInst()->CreateKey("ReTry", VK_SPACE);
		GameEngineInput::GetInst()->CreateKey("Next", VK_LSHIFT);
	}
}

void GameOver::Update()
{
	Time_ += GameEngineTime::GetDeltaTime();

	if (Time_ >= 0.08f && Count_ != 412)
	{
		BackRenderer_->SetImage("GO_IMAGE" + std::to_string(Count_) + ".bmp");
		Time_ = 0.f;
		Count_++;
	}

	if (Count_ >= 400)
	{
		FadeBack_->GetMyRenderer()->SetOrder(1);
		FadeBack_->FadeInOn();
		FadeBack_->SetFadeSpeed(1000);

		if (true == FadeBack_->GetIsInChange())
		{
			GameEngine::GetInst().ChangeLevel("BestRecords");
		}
	}


	if (true == GameEngineInput::GetInst()->IsDown("ReTry"))
	{
		GameOverBgm_.Stop();
		GameEngine::GetInst().ChangeLevel("InGame");
	}
	

	if (true == GameEngineInput::GetInst()->IsDown("Next"))
	{
		GameOverBgm_.Stop();
		GameEngine::GetInst().ChangeLevel("BestRecords");
	}


	if (true == IsLevelStart_)
	{
		FadeBack_->FadeOutOn();
		FadeBack_->SetFadeSpeed(300);

		if (true == FadeBack_->GetIsOutChange())
		{
			IsLevelStart_ = false;
			FadeBack_->GetMyRenderer()->SetOrder(0);
			FadeBack_->SetAlphaValue(0);
			FadeBack_->SetIsChage(false);
		}
	}
}

void GameOver::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	if (nullptr != _PrevLevel)
	{
		GameEngineLevel* PrevLevel = _PrevLevel;
		InGame* InGame_ = dynamic_cast<InGame*>(PrevLevel);

		EnemyProfile* CurEnemy = InGame_->GetEnemyProfile();
	}

	GameOverBgm_ = GameEngineSound::SoundPlayControl("GameOver.mp3");
}

void GameOver::LevelChangeEnd(GameEngineLevel* _NextLevel)
{
	ResetOn();
}

void GameOver::UserResetEnd()
{
	IsLevelStart_ = true;
	FadeBack_->SetAlphaValue(255);
	FadeBack_->GetMyRenderer()->SetOrder(3);
	Time_ = 0.f;
	Count_ = 0;

	FadeBack_ = CreateActor<FadeInOutBackground>();
	FadeBack_->SetMyRenderer(FadeBack_->CreateRenderer("GO_BACKGROUND.bmp"));

	Background_ = CreateActor<GameOverActor>(1);
	Background_->SetPosition({ GameEngineWindow::GetScale().Half() });
	BackRenderer_ = Background_->CreateRenderer("GO_IMAGE0.bmp");

	if (false == GameEngineInput::GetInst()->IsKey("ReTry"))
	{
		GameEngineInput::GetInst()->CreateKey("ReTry", VK_SPACE);
		GameEngineInput::GetInst()->CreateKey("Next", VK_LSHIFT);
	}
}
