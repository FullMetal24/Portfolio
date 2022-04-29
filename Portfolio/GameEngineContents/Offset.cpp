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

}

void Offset::Update()
{
	if (true == IsUpdate_ && nullptr != MyRenderer_)
	{
		SetMove(float4::DOWN + (float4::RIGHT * 6.f) * GameEngineTime::GetDeltaTime() * 15.f);

		if (250.f <= GetPosition().y)
		{
			IsUpdate_ = false;
			SetPosition(StartPos_);
			MyRenderer_->SetOrder(-1);
		}

		/*Alpha_ += GameEngineTime::GetDeltaTime();

		if (1.f <= Alpha_)
		{
			Alpha_ = 1.f;
		}

		SetPosition(float4::Lerp(StartPos_, EndPos_, Alpha_));

		if (1.f == Alpha_)
		{
			Alpha_ = 0.f;
			IsUpdate_ = false;
			SetPosition(StartPos_);

			MyRenderer_->SetOrder(0);
		}*/
	}
}

