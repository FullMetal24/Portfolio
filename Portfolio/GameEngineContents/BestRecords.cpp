#include "BestRecords.h"
#include "GameEngine/GameEngine.h"
#include "FadeInOutBackground.h"
#include "BestRecordsActor.h"
#include "GameEngine/GameEngineImage.h"
#include "EnemyProfile.h"
#include "GameOver.h"

BestRecords::BestRecords()
	: MainMenuBgm_{}
	, FadeInOutBackground_(nullptr)
	, EnemyProfile_(nullptr)
	, Time_(0.f)
{
}

BestRecords::~BestRecords()
{
}

void BestRecords::Loading()
{	
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

	BestRecordsActor* SDEnemy = CreateActor<BestRecordsActor>(4);
	SDEnemy->SetPosition({ GameEngineWindow::GetScale().Half() + float4{480.f, 240.f} });

	SDEnemy->CreateRenderer(EnemyProfile_->GetSD()->GetImage()->GetNameConstRef());
	MainMenuBgm_ = GameEngineSound::SoundPlayControl("MainMenu.mp3");
}

void BestRecords::LevelChangeEnd(GameEngineLevel* _NextLevel)
{
	FadeInOutBackground_->Death();
	FadeInOutBackground_ = nullptr;

	EnemyProfile_->Death();
	EnemyProfile_ = nullptr;

	Time_ = 0.f;
}


