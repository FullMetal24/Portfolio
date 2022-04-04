#include "EnemySelect.h"
#include "CS_BackGround.h"
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineImage.h>

EnemySelect::EnemySelect() 
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
}


void EnemySelect::TopPositionInit()
{
	for (int i = 0; i < 6; ++i)
	{
		Top[i] = CreateActor<CS_BackGround>(1);
		Top[i]->SetPosition({ GameEngineWindow::GetScale().Half().x , GameEngineWindow::GetScale().y - 150.f });
	}


	TopRenderer[5] = Top[5]->CreateRenderer("ES_TOP1.bmp");
	TopRenderer[4] = Top[4]->CreateRenderer("ES_TOP2.bmp");
	TopRenderer[3] = Top[3]->CreateRenderer("ES_TOP3.bmp");
	TopRenderer[2] = Top[2]->CreateRenderer("ES_TOP4.bmp");
	TopRenderer[1] = Top[1]->CreateRenderer("ES_TOP5.bmp");
	TopRenderer[0] = Top[0]->CreateRenderer("ES_TOP6.bmp");

	for (int i = 1; i < 6; i++)
	{
		Top[i]->SetPosition({ GameEngineWindow::GetScale().Half().x , Top[i - 1]->GetPosition().y - TopRenderer[i - 1]->GetImage()->GetScale().y });
	}

	Top[5]->SetMove({ 0, -13 });
}


void EnemySelect::SelectEnemy()
{
	
}

void EnemySelect::Update()
{
}


void EnemySelect::LevelChangeStart()
{
	
}

void EnemySelect::LevelChangeEnd()
{

}

