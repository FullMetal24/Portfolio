#include "WarningPuyo.h"
#include <GameEngine/GameEngineRenderer.h>

WarningPuyo::WarningPuyo() 
	: Renderer_(nullptr)
	,StartPos_(float4::ZERO)
	, EndPos_(float4::ZERO)
	, Alpha_(0.f)
{
}

WarningPuyo::~WarningPuyo() 
{
}

void WarningPuyo::Start()
{
	Renderer_ = CreateRenderer("IG_WARNING_PUYO_1.bmp");
}
 
void WarningPuyo::Update()
{
	if (true == MoveLeft_)
	{
		MoveLeftPuyo();
	}

	else if (true == MoveRight_)
	{
		MoveRightPuyo();
	}
}

void WarningPuyo::MoveLeftPuyo()
{
	Alpha_ += GameEngineTime::GetDeltaTime() * 2.f;

	SetPosition(float4::Lerp(StartPos_, EndPos_, Alpha_));

	if (1.f <= Alpha_)
	{
		Alpha_ = 0.f;
		MoveLeft_ = false;
	}
}

void WarningPuyo::MoveRightPuyo()
{
	Alpha_ += GameEngineTime::GetDeltaTime() * 2.f;

	SetPosition(float4::Lerp(EndPos_, StartPos_, Alpha_));

	if (1.f <= Alpha_)
	{
		Alpha_ = 0.f;
		MoveRight_ = false;
		Renderer_->SetOrder(0);
	}
}

