#include "EnemySelect.h"
#include "EnemySelectActor.h"
#include "FadeInOutBackground.h"
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngine.h>
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngine/GameEngineImage.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngineBase/GameEngineMath.h>
#include "InGame.h"
#include "EnemyProfile.h"

EnemySelect::EnemySelect()
	: Enemys_{}
	, MyEnemy_(nullptr)
	, TwinkleTime_(0.f)
	, RouletteSpeed_(1.0f)
	, SpeedLimit_(0.01f)
	, LevelChangeCount_(2.5f)
	, RouletteIndex_(0)
	, LimitForce_(0)
	, IsSelect_(false)
	, IsKeyDown_(false)

{
}

EnemySelect::~EnemySelect()
{
}

void EnemySelect::Loading()
{
	//UI
	{
		GameEngineActor* ExpUi = CreateActor<EnemySelectActor>(4);
		ExpUi->SetPosition({ GameEngineWindow::GetScale().Half().x - 535.f, GameEngineWindow::GetScale().Half().y - 125.f });
		ExpUi->CreateRenderer("ES_EXP_UI.bmp");

		GameEngineActor* NextUi = CreateActor<EnemySelectActor>(4);
		NextUi->SetPosition({ GameEngineWindow::GetScale().Half().x - 525.f, GameEngineWindow::GetScale().Half().y - 65.f });
		NextUi->CreateRenderer("ES_NEXT_UI.bmp");

		GameEngineActor* RestUi = CreateActor<EnemySelectActor>(4);
		RestUi->SetPosition({ GameEngineWindow::GetScale().Half().x - 525.f, GameEngineWindow::GetScale().Half().y });
		RestUi->CreateRenderer("ES_REST_UI.bmp");

		GameEngineActor* ExpValneUi = CreateActor<EnemySelectActor>(4);
		ExpValneUi->SetPosition({ GameEngineWindow::GetScale().Half().x - 290.f, GameEngineWindow::GetScale().Half().y - 125.f });
		ExpValneUi->CreateRenderer("ES_0.bmp");

		GameEngineActor* NexValuetUi = CreateActor<EnemySelectActor>(4);
		NexValuetUi->SetPosition({ GameEngineWindow::GetScale().Half().x - 350.f, GameEngineWindow::GetScale().Half().y - 65.f });
		NexValuetUi->CreateRenderer("ES_15000.bmp");

		GameEngineActor* ResValuetUi = CreateActor<EnemySelectActor>(4);
		ResValuetUi->SetPosition({ GameEngineWindow::GetScale().Half().x - 350.f, GameEngineWindow::GetScale().Half().y });
		ResValuetUi->CreateRenderer("ES_15000.bmp");
	}

	if (false == GameEngineInput::GetInst()->IsKey("EnemySelect"))
	{
		GameEngineInput::GetInst()->CreateKey("EnemySelect", VK_SPACE);
	}
}


void EnemySelect::TopPositionInit()
{
	for (int i = 0; i < 6; ++i)
	{
		Top_[i] = CreateActor<EnemySelectActor>(2);
		Top_[i]->SetPosition({ GameEngineWindow::GetScale().Half().x , GameEngineWindow::GetScale().y - 150.f });
	}

	TopRenderer_[5] = Top_[5]->CreateRenderer("ES_TOP1.bmp");
	TopRenderer_[4] = Top_[4]->CreateRenderer("ES_TOP2.bmp");
	TopRenderer_[3] = Top_[3]->CreateRenderer("ES_TOP3.bmp");
	TopRenderer_[2] = Top_[2]->CreateRenderer("ES_TOP4.bmp");
	TopRenderer_[1] = Top_[1]->CreateRenderer("ES_TOP5.bmp");
	TopRenderer_[0] = Top_[0]->CreateRenderer("ES_TOP6.bmp");

	for (int i = 1; i < 6; i++)
	{
		Top_[i]->SetPosition({ GameEngineWindow::GetScale().Half().x , Top_[i - 1]->GetPosition().y - TopRenderer_[i - 1]->GetImage()->GetScale().y });
	}

	Top_[5]->SetMove({ 0, -13 });
}

void EnemySelect::EnemyInit()
{
	float Offset_;
	Offset_ = GameEngineWindow::GetScale().Half().x - 320.f;

	Enemys_[0]->SetProfile(Enemys_[0]->CreateRenderer("ES_LV1.bmp"));
	Enemys_[0]->GetProfile()->SetPivot({ 1070.f, 190.f });
	Enemys_[0]->SetIcon(Enemys_[0]->CreateRenderer("ES_SELECT_L.bmp"));
	Enemys_[0]->GetIcon()->SetPivot({ Offset_, 748.f });
	Enemys_[0]->SetSD(Enemys_[0]->CreateRenderer("BR_SD01.bmp"));
	Enemys_[0]->SetRenderName(Enemys_[0]->CreateRenderer("ES_ENEMY_NAME.bmp"));
	Enemys_[0]->SetMyLevel(1);

	Enemys_[0]->GetRenderName()->SetOrder(5);
	Enemys_[0]->GetRenderName()->SetPivot({ GameEngineWindow::GetScale().Half() + float4{430, -70} });

	Enemys_[1]->SetProfile(Enemys_[1]->CreateRenderer("ES_LV2.bmp"));
	Enemys_[1]->GetProfile()->SetPivot({ 1070.f, 190.f });
	Enemys_[1]->SetIcon(Enemys_[1]->CreateRenderer("ES_SELECT_L1.bmp"));
	Enemys_[1]->GetIcon()->SetPivot({ Offset_ + Enemys_[0]->GetIcon()->GetImage()->GetScale().x, 749.f });
	Enemys_[1]->SetSD(Enemys_[1]->CreateRenderer("BR_SD02.bmp"));
	Enemys_[1]->SetRenderName(Enemys_[1]->CreateRenderer("ES_ENEMY_NAME1.bmp"));
	Enemys_[1]->SetMyLevel(2);

	Enemys_[1]->GetRenderName()->SetOrder(5);
	Enemys_[1]->GetRenderName()->SetPivot({ GameEngineWindow::GetScale().Half() + float4{430, -50} });

	Offset_ += Enemys_[0]->GetIcon()->GetImage()->GetScale().x;

	Enemys_[2]->SetProfile(Enemys_[2]->CreateRenderer("ES_LV3.bmp"));
	Enemys_[2]->GetProfile()->SetPivot({ 1070.f, 190.f });
	Enemys_[2]->SetIcon(Enemys_[2]->CreateRenderer("ES_SELECT_L2.bmp"));
	Enemys_[2]->GetIcon()->SetPivot({ Offset_ + Enemys_[1]->GetIcon()->GetImage()->GetScale().x, 749.f });
	Enemys_[2]->SetSD(Enemys_[2]->CreateRenderer("BR_SD03.bmp"));
	Enemys_[2]->SetRenderName(Enemys_[1]->CreateRenderer("ES_ENEMY_NAME2.bmp"));
	Enemys_[2]->SetMyLevel(3);

	Enemys_[2]->GetRenderName()->SetOrder(5);
	Enemys_[2]->GetRenderName()->SetPivot({ GameEngineWindow::GetScale().Half() + float4{430, -70} });

	Offset_ += Enemys_[1]->GetIcon()->GetImage()->GetScale().x;

	Enemys_[3]->SetProfile(Enemys_[3]->CreateRenderer("ES_LV4.bmp"));
	Enemys_[3]->GetProfile()->SetPivot({ 1070.f, 190.f });
	Enemys_[3]->SetIcon(Enemys_[3]->CreateRenderer("ES_SELECT_L3.bmp"));
	Enemys_[3]->GetIcon()->SetPivot({ Offset_ + Enemys_[2]->GetIcon()->GetImage()->GetScale().x, 749.f });
	Enemys_[3]->SetSD(Enemys_[3]->CreateRenderer("BR_SD04.bmp"));
	Enemys_[3]->SetRenderName(Enemys_[1]->CreateRenderer("ES_ENEMY_NAME3.bmp"));
	Enemys_[3]->SetMyLevel(4);

	Enemys_[3]->GetRenderName()->SetOrder(5);
	Enemys_[3]->GetRenderName()->SetPivot({ GameEngineWindow::GetScale().Half() + float4{430, -50} });

	Offset_ += Enemys_[2]->GetIcon()->GetImage()->GetScale().x + 2;

	Enemys_[4]->SetProfile(Enemys_[4]->CreateRenderer("ES_LV5.bmp"));
	Enemys_[4]->GetProfile()->SetPivot({ 1070.f, 190.f });
	Enemys_[4]->SetIcon(Enemys_[4]->CreateRenderer("ES_SELECT_L4.bmp"));
	Enemys_[4]->GetIcon()->SetPivot({ Offset_ + Enemys_[3]->GetIcon()->GetImage()->GetScale().x, 749.f });
	Enemys_[4]->SetSD(Enemys_[4]->CreateRenderer("BR_SD05.bmp"));
	Enemys_[4]->SetRenderName(Enemys_[1]->CreateRenderer("ES_ENEMY_NAME4.bmp"));
	Enemys_[4]->SetMyLevel(5);

	Enemys_[4]->GetRenderName()->SetOrder(5);
	Enemys_[4]->GetRenderName()->SetPivot({ GameEngineWindow::GetScale().Half() + float4{430, -70} });

	Offset_ += Enemys_[3]->GetIcon()->GetImage()->GetScale().x - 2.f;

	Enemys_[5]->SetProfile(Enemys_[5]->CreateRenderer("ES_LV6.bmp"));
	Enemys_[5]->GetProfile()->SetPivot({ 1070.f, 190.f });
	Enemys_[5]->SetIcon(Enemys_[5]->CreateRenderer("ES_SELECT_L5.bmp"));
	Enemys_[5]->GetIcon()->SetPivot({ Offset_ + Enemys_[4]->GetIcon()->GetImage()->GetScale().x, 749.f });
	Enemys_[5]->SetSD(Enemys_[4]->CreateRenderer("BR_SD06.bmp"));
	Enemys_[5]->SetRenderName(Enemys_[1]->CreateRenderer("ES_ENEMY_NAME5.bmp"));
	Enemys_[5]->SetMyLevel(6);

	Enemys_[5]->GetRenderName()->SetOrder(5);
	Enemys_[5]->GetRenderName()->SetPivot({ GameEngineWindow::GetScale().Half() + float4{430, -70} });

	Offset_ += Enemys_[4]->GetIcon()->GetImage()->GetScale().x + 3.f;

	Enemys_[6]->SetProfile(Enemys_[6]->CreateRenderer("ES_LV7.bmp"));
	Enemys_[6]->GetProfile()->SetPivot({ 1070.f, 190.f });
	Enemys_[6]->SetIcon(Enemys_[6]->CreateRenderer("ES_SELECT_L6.bmp"));
	Enemys_[6]->GetIcon()->SetPivot({ Offset_ + Enemys_[5]->GetIcon()->GetImage()->GetScale().x, 749.f });
	Enemys_[6]->SetSD(Enemys_[6]->CreateRenderer("BR_SD07.bmp"));
	Enemys_[6]->SetRenderName(Enemys_[1]->CreateRenderer("ES_ENEMY_NAME6.bmp"));
	Enemys_[6]->SetMyLevel(7);

	Enemys_[6]->GetRenderName()->SetOrder(5);
	Enemys_[6]->GetRenderName()->SetPivot({ GameEngineWindow::GetScale().Half() + float4{430, -70} });

	Offset_ += Enemys_[5]->GetIcon()->GetImage()->GetScale().x;

	Enemys_[7]->SetProfile(Enemys_[7]->CreateRenderer("ES_LV8.bmp"));
	Enemys_[7]->GetProfile()->SetPivot({ 1070.f, 190.f });
	Enemys_[7]->SetIcon(Enemys_[7]->CreateRenderer("ES_SELECT_L7.bmp"));
	Enemys_[7]->GetIcon()->SetPivot({ Offset_ + Enemys_[6]->GetIcon()->GetImage()->GetScale().x, 749.f });
	Enemys_[7]->SetSD(Enemys_[7]->CreateRenderer("BR_SD08.bmp"));
	Enemys_[7]->SetMyLevel(8);
	Enemys_[7]->SetRenderName(Enemys_[7]->CreateRenderer("ES_ENEMY_NAME7.bmp"));

	Enemys_[7]->GetRenderName()->SetOrder(5);
	Enemys_[7]->GetRenderName()->SetPivot({ GameEngineWindow::GetScale().Half() + float4{430, -70} });
}

void EnemySelect::FrameInit()
{
	GameEngineActor* Frame = CreateActor<EnemySelectActor>(1);
	Frame->SetPosition(GameEngineWindow::GetScale().Half());
	GameEngineRenderer* PlayerFrame = Frame->CreateRenderer("ES_FRAME.bmp");
	PlayerFrame->SetPivot({ -430.f, -150.f }); //Player
	PlayerFrame->SetTransColor(RGB(255, 0, 255));
	GameEngineRenderer* EnemyFrame = Frame->CreateRenderer("ES_FRAME.bmp");
	EnemyFrame->SetPivot({ 430.f, -150.f }); //Enemy
	EnemyFrame->SetTransColor(RGB(255, 0, 255));

	LimitForce_ = 1;
}

void EnemySelect::Update()
{
	PlayRoulette();

	if (true == IsSelect_)
	{
		LevelChangeCount_ -= GameEngineTime::GetDeltaTime();
		TwinkleEnemyIcon();

		if (0.0f >= LevelChangeCount_)
		{
			FadeBackground_->FadeInOn();
			FadeBackground_->GetMyRenderer()->SetOrder(20);
			FadeBackground_->SetFadeSpeed(500.f);

			if (true == FadeBackground_->GetIsInChange())
			{
				IsSelect_ = false;
				GameEngine::GetInst().ChangeLevel("InGame");
				EnemySelectBgm_.Stop();

				InGame* InGame_ = nullptr;

				GameEngineLevel* NextLevel = GameEngine::GetNextLevel();
				InGame_ = dynamic_cast<InGame*>(NextLevel);

				InGame_->SetEnemyProfile(MyEnemy_);
			}
		}
	}

	if (GameEngineInput::GetInst()->IsDown("EnemySelect"))
	{
		IsKeyDown_ = true;
		EffectSound_.SoundPlayOneShot("SELECT_EFFECT.mp3");
	}

}

void EnemySelect::PlayRoulette()
{
	while (false == IsSelect_) //상대가 선택되지 않았다면
	{
		Enemys_[RouletteIndex_]->GetProfile()->SetOrder(8);
		Enemys_[RouletteIndex_]->GetIcon()->SetOrder(8);
		Enemys_[RouletteIndex_]->GetRenderName()->SetOrder(8);

		if (SpeedLimit_ < RouletteSpeed_) //제한속도보다 값이 크다면 제한 속도를 올린다.
		{
			//지금 선택된 캐릭터는 가리고
			Enemys_[RouletteIndex_]->GetProfile()->SetOrder(-1);
			Enemys_[RouletteIndex_]->GetIcon()->SetOrder(0);
			Enemys_[RouletteIndex_]->GetRenderName()->SetOrder(0);

			EffectSound_.SoundPlayOneShot("INPUT_EFFECT.mp3");

			RouletteSpeed_ = 0.0f; //룰렛속도를 0으로 초기화
			++RouletteIndex_;

			if (8 == RouletteIndex_)
			{
				RouletteIndex_ = 0;
			}

			LimitForce_ += 0.3f;
			SpeedLimit_ += GameEngineTime::GetDeltaTime() * LimitForce_;

			if (0.2f < SpeedLimit_ || true == IsKeyDown_)
			{
				IsSelect_ = true;
				Enemys_[RouletteIndex_]->GetProfile()->SetOrder(8);
				Enemys_[RouletteIndex_]->GetIcon()->SetOrder(8);
				Enemys_[RouletteIndex_]->GetRenderName()->SetOrder(8);

				MyEnemy_ = Enemys_[RouletteIndex_];
			}

			break;
		}

		RouletteSpeed_ += GameEngineTime::GetDeltaTime() * 0.5f;
		break;
	}

}

void EnemySelect::TwinkleEnemyIcon()
{
	TwinkleTime_ += GameEngineTime::GetDeltaTime() * 150.f;

	if (5.f <= TwinkleTime_)
	{
		MyEnemy_->GetIcon()->SetOrder(0);
	}

	if (10.f <= TwinkleTime_)
	{
		MyEnemy_->GetIcon()->SetOrder(10);
		TwinkleTime_ = 0.0f;
	}
}

void EnemySelect::LockLoseEnemyIcon(int _Level)
{
	//Enemys_[_Level]->GetIcon()->SetImage("ES_SELECT_LOCK.bmp");
	//Enemys_[_Level]->GetIcon()->SetOrder(8);
}

void EnemySelect::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	EnemySelectBgm_ = GameEngineSound::SoundPlayControl("MainMenu.mp3");

	for (int i = 0; i < 8; ++i)
	{
		Enemys_[i] = CreateActor<EnemyProfile>(0);
	}

	GameEngineActor* Level = CreateActor<EnemySelectActor>(5);
	Level->SetPosition({ GameEngineWindow::GetScale().Half().x, GameEngineWindow::GetScale().Half().y - 200.f });
	Level->CreateRenderer("ES_LEVEL1.bmp");

	GameEngineActor* Enemys = CreateActor<EnemySelectActor>(4);
	Enemys->SetPosition({ GameEngineWindow::GetScale().Half().x, GameEngineWindow::GetScale().Half().y + 300.f });
	Enemys->CreateRenderer("ES_ENEMIES.bmp");

	GameEngineActor* ArleProfile = CreateActor<EnemySelectActor>(4);
	ArleProfile->CreateRenderer("ES_ARLE_PROFILE.bmp")->SetPivot({ 210.f, 190.f });

	GameEngineActor* SelectEnemy = CreateActor<EnemySelectActor>(4);
	SelectEnemy->CreateRenderer("ES_SELECT_ENEMY.bmp")->SetPivot(GameEngineWindow::GetScale().Half());

	FadeBackground_ = CreateActor<FadeInOutBackground>();
	
	EnemySelectActor* Background = CreateActor<EnemySelectActor>(1);
	Background->SetMyRenderer(Background->CreateRenderer("ES_BACK.bmp"));
	Background->SetPosition(GameEngineWindow::GetScale().Half());

	TopPositionInit();
	EnemyInit();
	FrameInit();

}

void EnemySelect::LevelChangeEnd(GameEngineLevel* _NextLevel)
{
	for (int i = 0; i < 8; ++i)
	{
		Enemys_[i]->Death();
		Enemys_[i] = nullptr;
	}

	MyEnemy_->Death();
	MyEnemy_ = nullptr;

	for (int i = 0; i < 6; i++)
	{
		Top_[i]->Death();
		Top_[i] = nullptr;

		TopRenderer_[i]->Death();
		TopRenderer_[i] = nullptr;
	}

	FadeBackground_->Death();
	FadeBackground_ = nullptr;

	RouletteSpeed_ = 1.0f;
	TwinkleTime_ = 0.f;
	SpeedLimit_ = 0.01f;
	LevelChangeCount_ = 2.5f;
	RouletteIndex_ = 0;
	LimitForce_ = 0;
	IsSelect_ = false;
	IsKeyDown_ = false;
}




