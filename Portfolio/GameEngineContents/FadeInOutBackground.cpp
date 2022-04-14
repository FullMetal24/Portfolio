

#include "FadeInOutBackground.h"
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngine/GameEngineRenderer.h.>
#include <GameEngine/GameEngineEnum.h>

FadeInOutBackground::FadeInOutBackground()
	: Background_(nullptr)
	, FadeValue_(0)
	, IsOn_(false)
	, IsOff_(true)
{
}

FadeInOutBackground::~FadeInOutBackground()
{
}

void FadeInOutBackground::Start()
{
	Background_ = CreateRenderer("GO_BACKGROUND.bmp");
}

void FadeInOutBackground::Update()
{

	if (false == IsOn_)
	{
		FadeValue_ -= GameEngineTime::GetDeltaTime();
		Background_->SetAlpha(FadeValue_);

		if (0 >= FadeValue_)
		{
			IsOn_ = true;
		}
	}
}

void FadeInOutBackground::Render()
{
}

