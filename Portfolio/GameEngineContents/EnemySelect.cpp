#include "EnemySelect.h"
#include "EnemySelectActor.h"
#include "FadeInOutBackground.h"
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngine.h>
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineImage.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngineBase/GameEngineMath.h>
#include "InGame.h"
#include "Enemy.h"

EnemySelect::EnemySelect() 
	: Enemys_{}
	, MyEnemy_(nullptr)
	, Backgrounds_{}
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

	GameEngineActor* Enemys = CreateActor<EnemySelectActor>(4);
	Enemys->SetPosition({ GameEngineWindow::GetScale().Half().x, GameEngineWindow::GetScale().Half().y + 300.f });
	Enemys->CreateRenderer("ES_ENEMIES.bmp");

	GameEngineActor* ArleProfile = CreateActor<EnemySelectActor>(4);
	ArleProfile->CreateRenderer("ES_ARLE_PROFILE.bmp")->SetPivot({ 210.f, 190.f });

	GameEngineActor* SelectEnemy = CreateActor<EnemySelectActor>(4);
	SelectEnemy->CreateRenderer("ES_SELECT_ENEMY.bmp")->SetPivot(GameEngineWindow::GetScale().Half());

	FadeBackground_ = CreateActor<FadeInOutBackground>();

	BackgroundInit();
	TopPositionInit();
	EnemyInit();
	FrameInit();

	if (false == GameEngineInput::GetInst()->IsKey("EnemySelect"))
	{
		GameEngineInput::GetInst()->CreateKey("EnemySelect", VK_SPACE);
	}
}


void EnemySelect::BackgroundInit()
{
	{
		EnemySelectActor* Background = CreateActor<EnemySelectActor>();
		Background->SetMyRenderer(Background->CreateRenderer("ES_BACK.bmp"));
		Background->SetPosition(GameEngineWindow::GetScale().Half());

		EnemySelectActor* Background1 = CreateActor<EnemySelectActor>();
		Background1->SetMyRenderer(Background1->CreateRenderer("ES_BACK.bmp"));
		Background1->SetPosition(GameEngineWindow::GetScale().Half() + Background1->GetMyRenderer()->GetImageScale());

		EnemySelectActor* Background2 = CreateActor<EnemySelectActor>();
		Background2->SetMyRenderer(Background2->CreateRenderer("ES_BACK.bmp"));
		Background2->SetPosition(GameEngineWindow::GetScale().Half() - Background2->GetMyRenderer()->GetImageScale());

		EnemySelectActor* Background3 = CreateActor<EnemySelectActor>();
		Background3->SetMyRenderer(Background3->CreateRenderer("ES_BACK.bmp"));
		Background3->SetPosition(GameEngineWindow::GetScale().Half() - Background3->GetMyRenderer()->GetImageScale() * 2.f);

		MidLine_.push_back(Background);
		MidLine_.push_back(Background1);
		MidLine_.push_back(Background2);
		MidLine_.push_back(Background3);
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
	for (int i = 0; i < 8; ++i)
	{
		Enemys_[i] = CreateActor<Enemy>(0);
	}

	float Offset_;
	Offset_ = GameEngineWindow::GetScale().Half().x - 320.f;

	Enemys_[0]->SetProfile(Enemys_[0]->CreateRenderer("ES_LV1.bmp"));
	Enemys_[0]->GetProfile()->SetPivot({1070.f, 190.f});
	Enemys_[0]->SetIcon(Enemys_[0]->CreateRenderer("ES_SELECT_L.bmp"));
	Enemys_[0]->GetIcon()->SetPivot({ Offset_, 748.f });

	Enemys_[1]->SetProfile(Enemys_[1]->CreateRenderer("ES_LV2.bmp"));
	Enemys_[1]->GetProfile()->SetPivot({ 1070.f, 190.f });
	Enemys_[1]->SetIcon(Enemys_[1]->CreateRenderer("ES_SELECT_L1.bmp"));
	Enemys_[1]->GetIcon()->SetPivot({ Offset_ + Enemys_[0]->GetIcon()->GetImage()->GetScale().x, 749.f});

	Offset_ += Enemys_[0]->GetIcon()->GetImage()->GetScale().x;

	Enemys_[2]->SetProfile(Enemys_[2]->CreateRenderer("ES_LV3.bmp"));
	Enemys_[2]->GetProfile()->SetPivot({ 1070.f, 190.f });
	Enemys_[2]->SetIcon(Enemys_[2]->CreateRenderer("ES_SELECT_L2.bmp"));
	Enemys_[2]->GetIcon()->SetPivot({ Offset_ + Enemys_[1]->GetIcon()->GetImage()->GetScale().x, 749.f });

	Offset_ += Enemys_[1]->GetIcon()->GetImage()->GetScale().x;

	Enemys_[3]->SetProfile(Enemys_[3]->CreateRenderer("ES_LV4.bmp"));
	Enemys_[3]->GetProfile()->SetPivot({ 1070.f, 190.f });
	Enemys_[3]->SetIcon(Enemys_[3]->CreateRenderer("ES_SELECT_L3.bmp"));
	Enemys_[3]->GetIcon()->SetPivot({ Offset_ + Enemys_[2]->GetIcon()->GetImage()->GetScale().x, 749.f });

	Offset_ += Enemys_[2]->GetIcon()->GetImage()->GetScale().x + 2;

	Enemys_[4]->SetProfile(Enemys_[4]->CreateRenderer("ES_LV5.bmp"));
	Enemys_[4]->GetProfile()->SetPivot({ 1070.f, 190.f });
	Enemys_[4]->SetIcon(Enemys_[4]->CreateRenderer("ES_SELECT_L4.bmp"));
	Enemys_[4]->GetIcon()->SetPivot({ Offset_ + Enemys_[3]->GetIcon()->GetImage()->GetScale().x, 749.f });

	Offset_ += Enemys_[3]->GetIcon()->GetImage()->GetScale().x;

	Enemys_[5]->SetProfile(Enemys_[5]->CreateRenderer("ES_LV6.bmp"));
	Enemys_[5]->GetProfile()->SetPivot({ 1070.f, 190.f });
	Enemys_[5]->SetIcon(Enemys_[5]->CreateRenderer("ES_SELECT_L5.bmp"));
	Enemys_[5]->GetIcon()->SetPivot({ Offset_ + Enemys_[4]->GetIcon()->GetImage()->GetScale().x, 749.f });

	Offset_ += Enemys_[4]->GetIcon()->GetImage()->GetScale().x;

	Enemys_[6]->SetProfile(Enemys_[6]->CreateRenderer("ES_LV7.bmp"));
	Enemys_[6]->GetProfile()->SetPivot({ 1070.f, 190.f });
	Enemys_[6]->SetIcon(Enemys_[6]->CreateRenderer("ES_SELECT_L6.bmp"));
	Enemys_[6]->GetIcon()->SetPivot({ Offset_ + Enemys_[5]->GetIcon()->GetImage()->GetScale().x, 749.f });

	Offset_ += Enemys_[5]->GetIcon()->GetImage()->GetScale().x + 1;

	Enemys_[7]->SetProfile(Enemys_[7]->CreateRenderer("ES_LV8.bmp"));
	Enemys_[7]->GetProfile()->SetPivot({ 1070.f, 190.f });
	Enemys_[7]->SetIcon(Enemys_[7]->CreateRenderer("ES_SELECT_L7.bmp"));
	Enemys_[7]->GetIcon()->SetPivot({ Offset_ + Enemys_[6]->GetIcon()->GetImage()->GetScale().x, 749.f });
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
		//LevelChangeCount_ -= GameEngineTime::GetDeltaTime();

		if (0.0f >= LevelChangeCount_)
		{
			FadeBackground_->FadeOn();
			FadeBackground_->GetMyRenderer()->SetOrder(20);
			FadeBackground_->SetFadeSpeed(500.f);

			if (true == FadeBackground_->GetIsChage())
			{
				GameEngine::GetInst().ChangeLevel("InGame");
				EnemySelectBgm_.Stop();

				GameEngineLevel* NextLevel = GameEngine::GetNextLevel();
				InGame* InGame_ = dynamic_cast<InGame*>(NextLevel);

				//���߿� ���׹̰� �ڱ� �����Ӿִϸ��̼ǵ� ���� �ֵ��� ����
				InGame_->SetEnemy(MyEnemy_->GetProfile());
			}
		}
	}
	
	if (GameEngineInput::GetInst()->IsDown("EnemySelect"))
	{
		IsKeyDown_ = true;
	}

	for (int i = 0; i < MidLine_.size(); ++i)
	{
		MidLine_[i]->SetMove(float4::DOWN + float4::RIGHT * GameEngineTime::GetDeltaTime() * 10.f);

		if (GameEngineWindow::GetScale().x < MidLine_[i]->GetPosition().x 
			&& GameEngineWindow::GetScale().y < MidLine_[i]->GetPosition().y)
		{
			MidLine_[i]->SetPosition(float4{0, 0} - MidLine_[i]->GetMyRenderer()->GetImageScale());
		}
	}

}


void EnemySelect::PlayRoulette()
{
	while (false == IsSelect_) //��밡 ���õ��� �ʾҴٸ�
	{
		Enemys_[RouletteIndex_]->GetProfile()->SetOrder(8);
		Enemys_[RouletteIndex_]->GetIcon()->SetOrder(8);

		if (SpeedLimit_ < RouletteSpeed_) //���Ѽӵ����� ���� ũ�ٸ� ���� �ӵ��� �ø���.
		{
			//���� ���õ� ĳ���ʹ� ������
			Enemys_[RouletteIndex_]->GetProfile()->SetOrder(0);
			Enemys_[RouletteIndex_]->GetIcon()->SetOrder(0);

			RouletteSpeed_ = 0.0f; //�귿�ӵ��� 0���� �ʱ�ȭ
			++RouletteIndex_;

			if (8 == RouletteIndex_)
			{
				RouletteIndex_ = 0;
			}

			LimitForce_ += 1;
			SpeedLimit_ += GameEngineTime::GetDeltaTime() * LimitForce_;

			if (1.f < SpeedLimit_ || true == IsKeyDown_)
			{
  				IsSelect_ = true;
				Enemys_[RouletteIndex_]->GetProfile()->SetOrder(8);
				Enemys_[RouletteIndex_]->GetIcon()->SetOrder(8);

				MyEnemy_ = Enemys_[RouletteIndex_];
			}

			break;
		}

		RouletteSpeed_ += GameEngineTime::GetDeltaTime();
		break;
	}

}

void EnemySelect::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	EnemySelectBgm_ = GameEngineSound::SoundPlayControl("MainMenu.mp3");
}

void EnemySelect::LevelChangeEnd(GameEngineLevel* _NextLevel)
{

}



