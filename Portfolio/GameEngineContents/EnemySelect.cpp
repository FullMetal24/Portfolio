#include "EnemySelect.h"
#include "CS_BackGround.h"
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngineBase/GameEngineWindow.h>

EnemySelect::EnemySelect() 
{
}

EnemySelect::~EnemySelect()
{
}

void EnemySelect::Loading()
{
	GameEngineActor* Actor_ = CreateActor<CS_BackGround>();
	Actor_->SetPosition(GameEngineWindow::GetScale().Half());

	Actor_->CreateRenderer("CS_BACK.bmp");
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
