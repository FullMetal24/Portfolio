

#include "FadeInOutBackground.h"
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngine/GameEngineRenderer.h.>
#include <GameEngine/GameEngineEnum.h>

FadeInOutBackground::FadeInOutBackground() 
	: MyRenderer_(nullptr)
	, AlphaValue_(0)
	, FadeSpeed_(0.f)
	, IsIn_(false)
	, IsOut_(false)
	, IsInChange_(false)
	, IsOutChange_(false)
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
	if (true == IsIn_)
	{
		AlphaValue_ += static_cast<int>(GameEngineTime::GetDeltaTime() * FadeSpeed_);
		MyRenderer_->SetAlpha(AlphaValue_);

		if (255 <= AlphaValue_)
		{
			IsIn_ = false;
			IsInChange_ = true;
		}
	}

	if (true == IsOut_)
	{
		AlphaValue_ -= static_cast<int>(GameEngineTime::GetDeltaTime() * FadeSpeed_);
		MyRenderer_->SetAlpha(AlphaValue_);

		if (0 >= AlphaValue_)
		{
			IsOut_ = false;
			IsOutChange_ = true;
		}
	}
}

void FadeInOutBackground::Render()
{
}

