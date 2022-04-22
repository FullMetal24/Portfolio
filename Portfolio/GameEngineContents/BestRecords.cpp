#include "BestRecords.h"
#include "GameEngine/GameEngine.h"
#include "FadeInOutBackground.h"
#include "BestRecordsActor.h"
#include "GameEngine/GameEngineImage.h"

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


	BestRecordsActor* Enemy_ = CreateActor<BestRecordsActor>(8);
	Enemy_->SetMyRenderer(Enemy_->CreateRenderer("BR_SD01.bmp"));
	Enemy_->SetPosition({ GameEngineWindow::GetScale().Half().x + 475, GameEngineWindow::GetScale().Half().y + 250 });


}

void BestRecords::Update()
{
	//Time_ += GameEngineTime::GetDeltaTime();

	if (Time_ >= 3.f)
	{
		FadeInOutBackground_->FadeInOn();
		FadeInOutBackground_->GetMyRenderer()->SetOrder(10);
		FadeInOutBackground_->SetFadeSpeed(900.f);

		if (true == FadeInOutBackground_->GetIsInChange())
		{
			GameEngine::GetInst().ChangeLevel("Title");
			MainMenuBgm_.Stop();
		}
	}
}

void BestRecords::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	switch (true)
	{
	default:
		break;
	}
	Enemy_->GetMyRenderer()->SetImage("");

	MainMenuBgm_ = GameEngineSound::SoundPlayControl("MainMenu.mp3");
}

void BestRecords::LevelChangeEnd(GameEngineLevel* _NextLevel)
{
	
}

