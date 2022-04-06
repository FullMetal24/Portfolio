#include "EnemySelect.h"
#include "CS_BackGround.h"
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngine.h>
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineImage.h>
#include <GameEngineBase/GameEngineTime.h>
#include "InGame.h"
#include "Enemy.h"

EnemySelect::EnemySelect() 
	: RouletteSpeed_(0.1f)
	, RouletteIndex_(0)
	, SpeedLimit_(0.01f)
{
}

EnemySelect::~EnemySelect()
{
}

void EnemySelect::Loading()
{
	GameEngineActor* Actor_ = CreateActor<CS_BackGround>(0);
	Actor_->SetPosition(GameEngineWindow::GetScale().Half());
	Actor_->CreateRenderer("ES_BACK.bmp");

	GameEngineActor* Enemys_ = CreateActor<CS_BackGround>(3);
	Enemys_->SetPosition({ GameEngineWindow::GetScale().Half().x, GameEngineWindow::GetScale().Half().y + 300.f });
	Enemys_->CreateRenderer("ES_ENEMIES.bmp");

	//EnemyRoulette_ = CreateActor<EnemyRoulette>(0);

	TopPositionInit();
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
		Top_[i] = CreateActor<CS_BackGround>(1);
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
	for (int i = 0; i < 8; ++i)
	{
		Enemys_[i] = CreateActor<Enemy>(0);
	}

	float Offset_;
	Offset_ = GameEngineWindow::GetScale().Half().x - 305.f;

	Enemys_[0]->SetProfile(Enemys_[0]->CreateRenderer("LV1.bmp"));
	Enemys_[0]->GetProfile()->SetPivot({1070.f, 190.f});
	Enemys_[0]->SetIcon(Enemys_[0]->CreateRenderer("SELECT_L.bmp"));
	Enemys_[0]->GetIcon()->SetPivot({ Offset_, 748.f });

	Enemys_[1]->SetProfile(Enemys_[1]->CreateRenderer("LV2.bmp"));
	Enemys_[1]->GetProfile()->SetPivot({ 1070.f, 190.f });
	Enemys_[1]->SetIcon(Enemys_[1]->CreateRenderer("SELECT_L1.bmp"));
	Enemys_[1]->GetIcon()->SetPivot({ Offset_ + Enemys_[0]->GetIcon()->GetImage()->GetScale().x, 748.f});

	Offset_ += Enemys_[0]->GetIcon()->GetImage()->GetScale().x;

	Enemys_[2]->SetProfile(Enemys_[2]->CreateRenderer("LV3.bmp"));
	Enemys_[2]->GetProfile()->SetPivot({ 1070.f, 190.f });
	Enemys_[2]->SetIcon(Enemys_[2]->CreateRenderer("SELECT_L2.bmp"));
	Enemys_[2]->GetIcon()->SetPivot({ Offset_ + Enemys_[1]->GetIcon()->GetImage()->GetScale().x, 748.f });

	Offset_ += Enemys_[1]->GetIcon()->GetImage()->GetScale().x;

	Enemys_[3]->SetProfile(Enemys_[3]->CreateRenderer("LV4.bmp"));
	Enemys_[3]->GetProfile()->SetPivot({ 1070.f, 190.f });
	Enemys_[3]->SetIcon(Enemys_[3]->CreateRenderer("SELECT_L3.bmp"));
	Enemys_[3]->GetIcon()->SetPivot({ Offset_ + Enemys_[2]->GetIcon()->GetImage()->GetScale().x, 748.f });

	Offset_ += Enemys_[2]->GetIcon()->GetImage()->GetScale().x;

	Enemys_[4]->SetProfile(Enemys_[4]->CreateRenderer("LV5.bmp"));
	Enemys_[4]->GetProfile()->SetPivot({ 1070.f, 190.f });
	Enemys_[4]->SetIcon(Enemys_[4]->CreateRenderer("SELECT_L4.bmp"));
	Enemys_[4]->GetIcon()->SetPivot({ Offset_ + Enemys_[3]->GetIcon()->GetImage()->GetScale().x, 748.f });

	Offset_ += Enemys_[3]->GetIcon()->GetImage()->GetScale().x;

	Enemys_[5]->SetProfile(Enemys_[5]->CreateRenderer("LV6.bmp"));
	Enemys_[5]->GetProfile()->SetPivot({ 1070.f, 190.f });
	Enemys_[5]->SetIcon(Enemys_[5]->CreateRenderer("SELECT_L5.bmp"));
	Enemys_[5]->GetIcon()->SetPivot({ Offset_ + Enemys_[4]->GetIcon()->GetImage()->GetScale().x, 748.f });

	Offset_ += Enemys_[4]->GetIcon()->GetImage()->GetScale().x;

	Enemys_[6]->SetProfile(Enemys_[6]->CreateRenderer("LV7.bmp"));
	Enemys_[6]->GetProfile()->SetPivot({ 1070.f, 190.f });
	Enemys_[6]->SetIcon(Enemys_[6]->CreateRenderer("SELECT_L6.bmp"));
	Enemys_[6]->GetIcon()->SetPivot({ Offset_ + Enemys_[5]->GetIcon()->GetImage()->GetScale().x, 748.f });

	Offset_ += Enemys_[5]->GetIcon()->GetImage()->GetScale().x;

	Enemys_[7]->SetProfile(Enemys_[7]->CreateRenderer("LV8.bmp"));
	Enemys_[7]->GetProfile()->SetPivot({ 1070.f, 190.f });
	Enemys_[7]->SetIcon(Enemys_[7]->CreateRenderer("SELECT_L7.bmp"));
	Enemys_[7]->GetIcon()->SetPivot({ Offset_ + Enemys_[6]->GetIcon()->GetImage()->GetScale().x, 748.f });
}


void EnemySelect::FrameInit()
{
	GameEngineActor* Frame = CreateActor<CS_BackGround>(0);
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
	SelectEnemy();
	PlayRoulette();
}


void EnemySelect::PlayRoulette()
{
	while (false == IsSelect_) //상대가 선택되지 않았다면
	{
		Enemys_[RouletteIndex_]->GetProfile()->SetOrder(8);
		Enemys_[RouletteIndex_]->GetIcon()->SetOrder(8);

		if (SpeedLimit_ < RouletteSpeed_) //제한속도보다 값이 크다면 제한 속도를 올린다.
		{
			//지금 선택된 캐릭터는 가리고
			Enemys_[RouletteIndex_]->GetProfile()->SetOrder(0);
			Enemys_[RouletteIndex_]->GetIcon()->SetOrder(0);

			RouletteSpeed_ = 0.0f; //룰렛속도를 0으로 초기화
			++RouletteIndex_;

			if (8 == RouletteIndex_)
			{
				RouletteIndex_ = 0;
			}

			LimitForce_ += 1;
			SpeedLimit_ += GameEngineTime::GetDeltaTime() * LimitForce_;

			if (1.f < SpeedLimit_)
			{
				IsSelect_ = true;
				Enemys_[RouletteIndex_]->GetProfile()->SetOrder(8);
				Enemys_[RouletteIndex_]->GetIcon()->SetOrder(8);
			}
			break;
		}

		RouletteSpeed_ += GameEngineTime::GetDeltaTime();
		break;
	}

}


void EnemySelect::SelectEnemy()
{
	if (true == GameEngineInput::GetInst()->IsDown("EnemySelect"))
	{
		GameEngine::GetInst().ChangeLevel("InGame");

		//GameEngineLevel* NextLevel = GameEngine::GetNextLevel();
		//InGame* InGame_ = dynamic_cast<InGame*>(NextLevel);

		//InGame_->CurrentEnemy_;
	}
}

void EnemySelect::LevelChangeStart()
{
}

void EnemySelect::LevelChangeEnd()
{

}



