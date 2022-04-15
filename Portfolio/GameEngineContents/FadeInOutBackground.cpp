

#include "FadeInOutBackground.h"
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngine/GameEngineRenderer.h.>
#include <GameEngine/GameEngineEnum.h>

FadeInOutBackground::FadeInOutBackground() 
	: MyRenderer_(nullptr)
	, AlphaValue_(0)
	, FadeSpeed_(0.f)
	, IsOn_(false)
	, IsChange_(false)
{
}

FadeInOutBackground::~FadeInOutBackground() 
{
}

void FadeInOutBackground::Start()
{
	MyRenderer_ = CreateRenderer("GO_BACKGROUND.bmp");
	SetPosition({GameEngineWindow::GetScale().Half().x, GameEngineWindow::GetScale().Half().y });
}

void FadeInOutBackground::Update()
{
	if (true == IsOn_)
	{
		AlphaValue_ += static_cast<int>(GameEngineTime::GetDeltaTime() * FadeSpeed_);
		MyRenderer_->SetAlpha(AlphaValue_);

		if (255 <= AlphaValue_)
		{
			IsOn_ = false;
			IsChange_ = true;
		}
	}
}

void FadeInOutBackground::Render()
{
}

