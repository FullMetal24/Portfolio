#include "OffsetStar.h"
#include <GameEngine/GameEngineRenderer.h>

OffsetStar::OffsetStar()
	: MyAnimation_(nullptr)
	, StartPos_(float4::ZERO)
	, Dir_(float4::ZERO)
	, IsUpdate_(false)
{	

}

OffsetStar::~OffsetStar() 
{
}

void OffsetStar::Start()
{
	MyAnimation_ = CreateRenderer();

	MyAnimation_->CreateAnimation("IG_OffsetStar.bmp", "IG_OffsetStar", 0, 4, 0.15f, true);
	MyAnimation_->ChangeAnimation("IG_OffsetStar");
	MyAnimation_->PauseOn();
}

void OffsetStar::Update()
{
	if (true == IsUpdate_)
	{
		MyAnimation_->PauseOff();
		SetMove(Dir_ * GameEngineTime::GetDeltaTime() * 350.f);

		if (true == MyAnimation_->IsEndAnimation())
		{
			MyAnimation_->PauseOn();
			MyAnimation_->SetOrder(-1);
			SetPosition(StartPos_);
		}
	}
}

