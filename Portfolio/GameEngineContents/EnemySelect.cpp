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
	, Backgrounds_{}
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
		ExpUi->SetPosition({ GameEngineWindow::GetScale().Half().x - 540.f, GameEngineWindow::GetScale().Half().y - 125.f});
		ExpUi->CreateRenderer("ES_EXP_UI.bmp");

		GameEngineActor* NextUi = CreateActor<EnemySelectActor>(4);
		NextUi->SetPosition({ GameEngineWindow::GetScale().Half().x - 525.f, GameEngineWindow::GetScale().Half().y - 65.f });
		NextUi->CreateRenderer("ES_NEXT_UI.bmp");

		GameEngineActor* RestUi = CreateActor<EnemySelectActor>(4);
		RestUi->SetPosition({ GameEngineWindow::GetScale().Half().x - 525.f, GameEngineWindow::GetScale().Half().y});
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

	for (int i = 0; i < 8; ++i)
	{
		Enemys_[i] = CreateActor<EnemyProfile>(0);
	}

	EnemySelectActor* Background = CreateActor<EnemySelectActor>(1);
	Background->SetMyRenderer(Background->CreateRenderer("ES_BACK.bmp"));
	Background->SetPosition(GameEngineWindow::GetScale().Half());

	TopPositionInit();
	EnemyAnimationInit();
	EnemyInit();
	FrameInit();

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

void EnemySelect::EnemyAnimationInit()
{
	//LV1
	{
		GameEngineImage* LV1IdleImage = GameEngineImageManager::GetInst()->Find("IG_LV1_IDLE.bmp");
		LV1IdleImage->CutCount(4, 1);

		GameEngineImage* LV1LoseImage = GameEngineImageManager::GetInst()->Find("IG_LV1_LOSE.bmp");
		LV1LoseImage->CutCount(4, 1);

		GameEngineImage* LV1WinImage = GameEngineImageManager::GetInst()->Find("IG_LV1_WIN.bmp");
		LV1WinImage->CutCount(1, 1);

		Enemys_[0]->SetMyAnimation(Enemys_[0]->CreateRenderer());

		Enemys_[0]->GetMyAnimation()->CreateAnimation("IG_LV1_IDLE.bmp", "IG_LV1_IDLE", 0, 3, 0.5f, true);
		Enemys_[0]->GetMyAnimation()->CreateAnimation("IG_LV1_LOSE.bmp", "IG_LV1_LOSE", 0, 3, 0.5f, true);
		Enemys_[0]->GetMyAnimation()->CreateAnimation("IG_LV1_WIN.bmp", "IG_LV1_WIN", 0, 3, 0.5f, true);

		Enemys_[0]->GetMyAnimation()->ChangeAnimation("IG_LV1_IDLE");
		Enemys_[0]->GetMyAnimation()->SetOrder(-1);
	}

	//LV2
	{
		GameEngineImage* LV2IdleImage = GameEngineImageManager::GetInst()->Find("IG_LV2_IDLE.bmp");
		LV2IdleImage->CutCount(1, 1);

		GameEngineImage* LV2LoseImage = GameEngineImageManager::GetInst()->Find("IG_LV2_LOSE.bmp");
		LV2LoseImage->CutCount(4, 1);

		GameEngineImage* LV2WinImage = GameEngineImageManager::GetInst()->Find("IG_LV2_WIN.bmp");
		LV2WinImage->CutCount(1, 1);

		Enemys_[1]->SetMyAnimation(Enemys_[1]->CreateRenderer());

		Enemys_[1]->GetMyAnimation()->CreateAnimation("IG_LV2_IDLE.bmp", "IG_LV2_IDLE", 0, 0, 0.5f, true);
		Enemys_[1]->GetMyAnimation()->CreateAnimation("IG_LV2_LOSE.bmp", "IG_LV2_LOSE", 0, 3, 0.5f, true);
		Enemys_[1]->GetMyAnimation()->CreateAnimation("IG_LV2_WIN.bmp", "IG_LV2_WIN", 0, 0, 0.5f, true);

		Enemys_[1]->GetMyAnimation()->ChangeAnimation("IG_LV2_IDLE");
		Enemys_[1]->GetMyAnimation()->SetOrder(-1);
	}

	//LV3
	{
		GameEngineImage* LV3IdleImage = GameEngineImageManager::GetInst()->Find("IG_LV3_IDLE.bmp");
		LV3IdleImage->CutCount(4, 1);

		GameEngineImage* LV3LoseImage = GameEngineImageManager::GetInst()->Find("IG_LV3_LOSE.bmp");
		LV3LoseImage->CutCount(4, 1);

		GameEngineImage* LV3WinImage = GameEngineImageManager::GetInst()->Find("IG_LV3_WIN.bmp");
		LV3WinImage->CutCount(1, 1);

		Enemys_[2]->SetMyAnimation(Enemys_[2]->CreateRenderer());

		Enemys_[2]->GetMyAnimation()->CreateAnimation("IG_LV3_IDLE.bmp", "IG_LV3_IDLE", 0, 0, 0.5f, true);
		Enemys_[2]->GetMyAnimation()->CreateAnimation("IG_LV3_LOSE.bmp", "IG_LV3_LOSE", 0, 3, 0.5f, true);
		Enemys_[2]->GetMyAnimation()->CreateAnimation("IG_LV3_WIN.bmp", "IG_LV3_WIN", 0, 0, 0.5f, true);

		Enemys_[2]->GetMyAnimation()->ChangeAnimation("IG_LV3_IDLE");
		Enemys_[2]->GetMyAnimation()->SetOrder(-1);
	}


	//LV4
	{
		GameEngineImage* LV4IdleImage = GameEngineImageManager::GetInst()->Find("IG_LV4_IDLE.bmp");
		LV4IdleImage->CutCount(1, 1);

		GameEngineImage* LV4LoseImage = GameEngineImageManager::GetInst()->Find("IG_LV4_LOSE.bmp");
		LV4LoseImage->CutCount(1, 1);

		GameEngineImage* LV4WinImage = GameEngineImageManager::GetInst()->Find("IG_LV4_WIN.bmp");
		LV4WinImage->CutCount(1, 1);

		Enemys_[3]->SetMyAnimation(Enemys_[3]->CreateRenderer());

		Enemys_[3]->GetMyAnimation()->CreateAnimation("IG_LV4_IDLE.bmp", "IG_LV4_IDLE", 0, 0, 0.5f, true);
		Enemys_[3]->GetMyAnimation()->CreateAnimation("IG_LV4_LOSE.bmp", "IG_LV4_LOSE", 0, 0, 0.5f, true);
		Enemys_[3]->GetMyAnimation()->CreateAnimation("IG_LV4_WIN.bmp", "IG_LV4_WIN", 0, 0, 0.5f, true);

		Enemys_[3]->GetMyAnimation()->ChangeAnimation("IG_LV4_IDLE");
		Enemys_[3]->GetMyAnimation()->SetOrder(-1);
	}

	//LV5
	{
		GameEngineImage* LV5IdleImage = GameEngineImageManager::GetInst()->Find("IG_LV5_IDLE.bmp");
		LV5IdleImage->CutCount(1, 1);

		GameEngineImage* LV5LoseImage = GameEngineImageManager::GetInst()->Find("IG_LV5_LOSE.bmp");
		LV5LoseImage->CutCount(1, 1);

		GameEngineImage* LV5WinImage = GameEngineImageManager::GetInst()->Find("IG_LV5_WIN.bmp");
		LV5WinImage->CutCount(1, 1);

		Enemys_[4]->SetMyAnimation(Enemys_[4]->CreateRenderer());

		Enemys_[4]->GetMyAnimation()->CreateAnimation("IG_LV5_IDLE.bmp", "IG_LV5_IDLE", 0, 0, 0.5f, true);
		Enemys_[4]->GetMyAnimation()->CreateAnimation("IG_LV5_LOSE.bmp", "IG_LV5_LOSE", 0, 0, 0.5f, true);
		Enemys_[4]->GetMyAnimation()->CreateAnimation("IG_LV5_WIN.bmp", "IG_LV5_WIN", 0, 0, 0.5f, true);

		Enemys_[4]->GetMyAnimation()->ChangeAnimation("IG_LV5_IDLE");
		Enemys_[4]->GetMyAnimation()->SetOrder(-1);
	}

	//LV6
	{
		GameEngineImage* LV6IdleImage = GameEngineImageManager::GetInst()->Find("IG_LV6_IDLE.bmp");
		LV6IdleImage->CutCount(1, 1);

		GameEngineImage* LV6LoseImage = GameEngineImageManager::GetInst()->Find("IG_LV6_LOSE.bmp");
		LV6LoseImage->CutCount(1, 1);

		GameEngineImage* LV6WinImage = GameEngineImageManager::GetInst()->Find("IG_LV6_WIN.bmp");
		LV6WinImage->CutCount(1, 1);

		Enemys_[5]->SetMyAnimation(Enemys_[5]->CreateRenderer());

		Enemys_[5]->GetMyAnimation()->CreateAnimation("IG_LV6_IDLE.bmp", "IG_LV6_IDLE", 0, 0, 0.5f, true);
		Enemys_[5]->GetMyAnimation()->CreateAnimation("IG_LV6_LOSE.bmp", "IG_LV6_LOSE", 0, 0, 0.5f, true);
		Enemys_[5]->GetMyAnimation()->CreateAnimation("IG_LV6_WIN.bmp", "IG_LV6_WIN", 0, 0, 0.5f, true);

		Enemys_[5]->GetMyAnimation()->ChangeAnimation("IG_LV6_IDLE");
		Enemys_[5]->GetMyAnimation()->SetOrder(-1);
	}

	//LV7
	{
		GameEngineImage* LV7IdleImage = GameEngineImageManager::GetInst()->Find("IG_LV7_IDLE.bmp");
		LV7IdleImage->CutCount(1, 1);

		GameEngineImage* LV7LoseImage = GameEngineImageManager::GetInst()->Find("IG_LV7_LOSE.bmp");
		LV7LoseImage->CutCount(1, 1);

		GameEngineImage* LV7WinImage = GameEngineImageManager::GetInst()->Find("IG_LV7_WIN.bmp");
		LV7WinImage->CutCount(1, 1);

		Enemys_[6]->SetMyAnimation(Enemys_[6]->CreateRenderer());

		Enemys_[6]->GetMyAnimation()->CreateAnimation("IG_LV7_IDLE.bmp", "IG_LV7_IDLE", 0, 0, 0.5f, true);
		Enemys_[6]->GetMyAnimation()->CreateAnimation("IG_LV7_LOSE.bmp", "IG_LV7_LOSE", 0, 0, 0.5f, true);
		Enemys_[6]->GetMyAnimation()->CreateAnimation("IG_LV7_WIN.bmp", "IG_LV7_WIN", 0, 0, 0.5f, true);

		Enemys_[6]->GetMyAnimation()->ChangeAnimation("IG_LV7_IDLE");
		Enemys_[6]->GetMyAnimation()->SetOrder(-1);
	}

	//LV8
	{
		GameEngineImage* LV8IdleImage = GameEngineImageManager::GetInst()->Find("IG_LV8_IDLE.bmp");
		LV8IdleImage->CutCount(1, 1);

		GameEngineImage* LV8LoseImage = GameEngineImageManager::GetInst()->Find("IG_LV8_LOSE.bmp");
		LV8LoseImage->CutCount(1, 1);

		GameEngineImage* LV8WinImage = GameEngineImageManager::GetInst()->Find("IG_LV8_WIN.bmp");
		LV8WinImage->CutCount(1, 1);

		Enemys_[7]->SetMyAnimation(Enemys_[7]->CreateRenderer());

		Enemys_[7]->GetMyAnimation()->CreateAnimation("IG_LV8_IDLE.bmp", "IG_LV8_IDLE", 0, 0, 0.5f, true);
		Enemys_[7]->GetMyAnimation()->CreateAnimation("IG_LV8_LOSE.bmp", "IG_LV8_LOSE", 0, 0, 0.5f, true);
		Enemys_[7]->GetMyAnimation()->CreateAnimation("IG_LV8_WIN.bmp", "IG_LV8_WIN", 0, 0, 0.5f, true);

		Enemys_[7]->GetMyAnimation()->ChangeAnimation("IG_LV8_IDLE");
		Enemys_[7]->GetMyAnimation()->SetOrder(-1);
	}
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
	Enemys_[1]->GetIcon()->SetPivot({ Offset_ + Enemys_[0]->GetIcon()->GetImage()->GetScale().x, 749.f});
	Enemys_[1]->SetSD(Enemys_[1]->CreateRenderer("BR_SD02.bmp"));
	Enemys_[1]->SetRenderName(Enemys_[1]->CreateRenderer("ES_ENEMY_NAME1.bmp"));
	Enemys_[1]->SetMyLevel(2);

	Enemys_[1]->GetRenderName()->SetOrder(5);
	Enemys_[1]->GetRenderName()->SetPivot({ GameEngineWindow::GetScale().Half() + float4{430, -70} });

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
	Enemys_[3]->GetRenderName()->SetPivot({ GameEngineWindow::GetScale().Half() + float4{430, -70} });

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

	Offset_ += Enemys_[3]->GetIcon()->GetImage()->GetScale().x;

	Enemys_[5]->SetProfile(Enemys_[5]->CreateRenderer("ES_LV6.bmp"));
	Enemys_[5]->GetProfile()->SetPivot({ 1070.f, 190.f });
	Enemys_[5]->SetIcon(Enemys_[5]->CreateRenderer("ES_SELECT_L5.bmp"));
	Enemys_[5]->GetIcon()->SetPivot({ Offset_ + Enemys_[4]->GetIcon()->GetImage()->GetScale().x, 749.f });
	Enemys_[5]->SetSD(Enemys_[4]->CreateRenderer("BR_SD06.bmp"));
	Enemys_[5]->SetRenderName(Enemys_[1]->CreateRenderer("ES_ENEMY_NAME5.bmp"));
	Enemys_[5]->SetMyLevel(6);

	Enemys_[5]->GetRenderName()->SetOrder(5);
	Enemys_[5]->GetRenderName()->SetPivot({ GameEngineWindow::GetScale().Half() + float4{430, -70} });

	Offset_ += Enemys_[4]->GetIcon()->GetImage()->GetScale().x;

	Enemys_[6]->SetProfile(Enemys_[6]->CreateRenderer("ES_LV7.bmp"));
	Enemys_[6]->GetProfile()->SetPivot({ 1070.f, 190.f });
	Enemys_[6]->SetIcon(Enemys_[6]->CreateRenderer("ES_SELECT_L6.bmp"));
	Enemys_[6]->GetIcon()->SetPivot({ Offset_ + Enemys_[5]->GetIcon()->GetImage()->GetScale().x, 749.f });
	Enemys_[6]->SetSD(Enemys_[6]->CreateRenderer("BR_SD07.bmp"));
	Enemys_[6]->SetRenderName(Enemys_[1]->CreateRenderer("ES_ENEMY_NAME6.bmp"));
	Enemys_[6]->SetMyLevel(7);

	Enemys_[6]->GetRenderName()->SetOrder(5);
	Enemys_[6]->GetRenderName()->SetPivot({ GameEngineWindow::GetScale().Half() + float4{430, -70} });

	Offset_ += Enemys_[5]->GetIcon()->GetImage()->GetScale().x + 1;

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
				GameEngine::GetInst().ChangeLevel("InGame");
				EnemySelectBgm_.Stop();
			}
		}
	}
	
	if (GameEngineInput::GetInst()->IsDown("EnemySelect"))
	{
		IsKeyDown_ = true;
	}

	float4 Dir = float4::RadianToDirectionFloat4(0.5f);

	for (int i = 0; i < MidLine_.size(); ++i)
	{
		MidLine_[i]->SetMove(float4::RIGHT + float4::DOWN * GameEngineTime::GetDeltaTime() * 400.f);

		if (GameEngineWindow::GetScale().x < MidLine_[i]->GetPosition().x 
			&& GameEngineWindow::GetScale().y < MidLine_[i]->GetPosition().y)
		{
			MidLine_[i]->SetPosition(float4{0, 0} - MidLine_[i]->GetMyRenderer()->GetImageScale());
		}
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

void EnemySelect::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	EnemySelectBgm_ = GameEngineSound::SoundPlayControl("MainMenu.mp3");
}

void EnemySelect::LevelChangeEnd(GameEngineLevel* _NextLevel)
{

}



