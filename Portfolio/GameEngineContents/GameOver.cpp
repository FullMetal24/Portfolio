#include "GameOver.h"
#include "FadeInOutBackground.h"

GameOver::GameOver() 
{
}

GameOver::~GameOver() 
{
}


void GameOver::Loading()
{
	Background_ = CreateActor<FadeInOutBackground>();
	GameEngineRenderer* ARLE = Background_->CreateRenderer("GO_ARLE.bmp");
	ARLE->SetPivot({ 0, 100.f });
	ARLE->SetOrder(2);
}

void GameOver::Update()
{
}

void GameOver::LevelChangeStart()
{
	GameOverBgm_ = GameEngineSound::SoundPlayControl("GameOver.mp3");

}

void GameOver::LevelChangeEnd()
{

}
