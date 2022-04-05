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
	: RouletteSpeed(100.f)
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

	TopPositionInit();
	EnemyInit();

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
		Enemys_[i] = new Enemy();
		Enemys_[i]->SetProfile(CreateActor<CS_BackGround>(5));
		Enemys_[i]->SetIcon(CreateActor<CS_BackGround>(5));
	}

	Enemys_[0]->GetProfile()->CreateRenderer("LV1.bmp")->SetPivot(GameEngineWindow::GetScale().Half());
	Enemys_[0]->GetIcon()->CreateRenderer("SELECT_L.bmp")->SetPivot(GameEngineWindow::GetScale().Half());

	Enemys_[1]->GetProfile()->CreateRenderer("LV2.bmp");
	Enemys_[1]->GetIcon()->CreateRenderer("SELECT_L1.bmp");

	Enemys_[2]->GetProfile()->CreateRenderer("LV3.bmp");
	Enemys_[2]->GetIcon()->CreateRenderer("SELECT_L2.bmp");

	Enemys_[3]->GetProfile()->CreateRenderer("LV4.bmp");
	Enemys_[3]->GetIcon()->CreateRenderer("SELECT_L3.bmp");

	Enemys_[4]->GetProfile()->CreateRenderer("LV5.bmp");
	Enemys_[4]->GetIcon()->CreateRenderer("SELECT_L4.bmp");

	Enemys_[5]->GetProfile()->CreateRenderer("LV6.bmp");
	Enemys_[5]->GetIcon()->CreateRenderer("SELECT_L5.bmp");

	Enemys_[6]->GetProfile()->CreateRenderer("LV7.bmp");
	Enemys_[6]->GetIcon()->CreateRenderer("SELECT_L6.bmp");

	Enemys_[7]->GetProfile()->CreateRenderer("LV8.bmp");
	Enemys_[7]->GetIcon()->CreateRenderer("SELECT_L7.bmp");
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

void EnemySelect::Update()
{
	SelectEnemy();
}


void EnemySelect::LevelChangeStart()
{
	
}

void EnemySelect::LevelChangeEnd()
{

}

