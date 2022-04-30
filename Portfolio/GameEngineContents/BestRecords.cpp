#include "BestRecords.h"
#include "GameEngine/GameEngine.h"
#include "FadeInOutBackground.h"
#include "BestRecordsActor.h"
#include "GameEngine/GameEngineImage.h"
#include "EnemyProfile.h"
#include "GameOver.h"

BestRecords::BestRecords()
	: Time_(0.f)
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
	Record->SetPosition({ GameEngineWindow::GetScale().Half() });
	Record->CreateRenderer("BR_RECORD.bmp");

	BestRecordsActor* Arle = CreateActor<BestRecordsActor>(8);
	Arle->SetMyRenderer(Arle->CreateRenderer("BR_SD_ARLE.bmp"));
	Arle->SetPosition({ GameEngineWindow::GetScale().Half().x - 475, GameEngineWindow::GetScale().Half().y + 255 });
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
	if (nullptr != _PrevLevel)
	{
		GameEngineLevel* PrevLevel = _PrevLevel;
		GameOver* GameOver_ = dynamic_cast<GameOver*>(PrevLevel);

		EnemyProfile* CurEnemy = GameOver_->GetEnemyProfile();

		if (nullptr != CurEnemy)
		{
			BestRecordsActor* SDEnemy = CreateActor<BestRecordsActor>(4);
			SDEnemy->SetPosition({ GameEngineWindow::GetScale().Half() + float4{480.f, 240.f} });

			SDEnemy->CreateRenderer(CurEnemy->GetSD()->GetImage()->GetNameConstRef());
		}
	}

	MainMenuBgm_ = GameEngineSound::SoundPlayControl("MainMenu.mp3");
}

void BestRecords::LevelChangeEnd(GameEngineLevel* _NextLevel)
{
	ResetOn();
}

void BestRecords::UserResetEnd()
{
	Time_ = 0.f;

	FadeInOutBackground_ = CreateActor< FadeInOutBackground>(0);
	FadeInOutBackground_->SetMyRenderer(FadeInOutBackground_->CreateRenderer("GO_BACKGROUND.bmp"));

	BestRecordsActor* Back = CreateActor<BestRecordsActor>(3);
	Back->SetPosition({ GameEngineWindow::GetScale().Half() });
	Back->CreateRenderer("BR_BACK.bmp");

	BestRecordsActor* Record = CreateActor<BestRecordsActor>(5);
	Record->SetPosition({ GameEngineWindow::GetScale().Half() });
	Record->CreateRenderer("BR_RECORD.bmp");

	BestRecordsActor* Arle = CreateActor<BestRecordsActor>(8);
	Arle->SetMyRenderer(Arle->CreateRenderer("BR_SD_ARLE.bmp"));
	Arle->SetPosition({ GameEngineWindow::GetScale().Half().x - 475, GameEngineWindow::GetScale().Half().y + 255 });
}

