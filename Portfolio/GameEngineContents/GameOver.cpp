#include "GameOver.h"
#include "FadeInOutBackground.h"

GameOver::GameOver()
	:BackRenderer_(nullptr)
	, Background_(nullptr)
	, GameOverBgm_{}
	, Count_(0)
	, Time_(0.f)
{
}

GameOver::~GameOver() 
{
}


void GameOver::Loading()
{

	Background_ = CreateActor<FadeInOutBackground>();
	Background_->SetPosition({GameEngineWindow::GetScale().Half()});
	BackRenderer_ = Background_->CreateRenderer("GO_IMAGE0.bmp");
}

void GameOver::Update()
{
	Time_ += GameEngineTime::GetDeltaTime();

	if (Time_ >= 0.05f && Count_ != 412)
	{
		BackRenderer_->SetImage("GO_IMAGE" + std::to_string(Count_) + ".bmp");
		Time_ = 0.f;
		Count_++;
	}
	
}

void GameOver::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	Time_ = 0.f;
	Count_ = 0;

	GameOverBgm_ = GameEngineSound::SoundPlayControl("GameOver.mp3");

}

void GameOver::LevelChangeEnd(GameEngineLevel* _NextLevel)
{

}
