#include "BestRecords.h"
#include "GameEngine/GameEngine.h"
#include "FadeInOutBackground.h"
#include "BestRecordsActor.h"
#include "GameEngine/GameEngineImage.h"
#include "EnemyProfile.h"

BestRecords::BestRecords() 
{
}

BestRecords::~BestRecords() 
{
}

void BestRecords::Loading()
{
	FadeInOutBackground_ = CreateActor< FadeInOutBackground>(0);
	FadeInOutBackground_->SetMyRenderer(FadeInOutBackground_->CreateRenderer("GO_BACKGROUND.bmp"));

	BestRecordsActor* Back = CreateActor<BestRecordsActor>(3);
	Back->SetPosition({ GameEngineWindow::GetScale().Half() });
	Back->CreateRenderer("BR_BACK.bmp");

	BestRecordsActor* Record = CreateActor<BestRecordsActor>(5);
	Record->SetPosition({GameEngineWindow::GetScale().Half()});
	Record->CreateRenderer("BR_RECORD.bmp");

	BestRecordsActor* Arle = CreateActor<BestRecordsActor>(8);
	Arle->SetMyRenderer(Arle->CreateRenderer("BR_SD_ARLE.bmp"));
	Arle->SetPosition({ GameEngineWindow::GetScale().Half().x - 475, GameEngineWindow::GetScale().Half().y + 255});
}

void BestRecords::Update()
{
	Time_ += GameEngineTime::GetDeltaTime();

	if (Time_ >= 3.f)
	{
		FadeInOutBackground_->FadeInOn();
		FadeInOutBackground_->GetMyRenderer()->SetOrder(10);
		FadeInOutBackground_->SetFadeSpeed(900.f);

		if (true == FadeInOutBackground_->GetIsInChange())
		{
			MainMenuBgm_.Stop();
			GameEngine::GetInst().ChangeLevel("Title");
		}
	}
}

void BestRecords::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	if (nullptr != EnemyProfile_)
	{
		BestRecordsActor* SDEnemy_ = CreateActor<BestRecordsActor>(9);
		SDEnemy_->SetPosition({ GameEngineWindow::GetScale().Half().x, GameEngineWindow::GetScale().Half().y + 70.f });
		GameEngineRenderer* Renderer = EnemyProfile_->CreateRenderer();
		Renderer->SetImage(EnemyProfile_->GetSD()->GetImage());
		SDEnemy_->SetMyRenderer(Renderer);
	}
	
	MainMenuBgm_ = GameEngineSound::SoundPlayControl("MainMenu.mp3");
}

void BestRecords::LevelChangeEnd(GameEngineLevel* _NextLevel)
{
	
}

