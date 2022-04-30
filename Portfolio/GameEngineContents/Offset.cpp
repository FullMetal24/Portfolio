#include "Offset.h"
#include <GameEngine/GameEngineRenderer.h>

Offset::Offset() 
	: MyRenderer_(nullptr)
	, IsUpdate_(false)
{
}

Offset::~Offset() 
{
}

void Offset::Start()
{
	MyRenderer_ = CreateRenderer("IG_OFFSET.bmp");
}

void Offset::Update()
{
	if (true == IsUpdate_)
	{
		SetMove(Dir_ * GameEngineTime::GetDeltaTime() * 250.f);

		if (250.f <= GetPosition().y)
		{
			IsUpdate_ = false;
			SetPosition(StartPos_);
			MyRenderer_->SetOrder(-1);
		}
	}
}

