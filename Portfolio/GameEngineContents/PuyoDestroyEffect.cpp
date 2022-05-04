#include "PuyoDestroyEffect.h"
#include <GameEngine/GameEngineRenderer.h>
#include "InGameActor.h"

PuyoDestroyEffect::PuyoDestroyEffect()
	: Count_(0)
	, Speed_(600.f)
	, DirForce_(0.f)
	, Gravity_(0.f)
	, IsPlay_(false)
	, IsSetColor_(false)
{
}

PuyoDestroyEffect::~PuyoDestroyEffect() 
{
}

void PuyoDestroyEffect::Start()
{
	for (int i = 0; i < 4; i++)
	{
		Effects_[i] = GetLevel()->CreateActor<InGameActor>();
	}
}

void PuyoDestroyEffect::Update()
{
	if (true == IsPlay_)
	{
		PlayEffect();
		EndEffect();
	}
}

void PuyoDestroyEffect::CreateEffect()
{
	if (true == IsSetColor_)
	{
		switch (MyColor_)
		{
		case PuyoColor::RED:
			for (int i = 0; i < 4; i++)
			{
				Effects_[i]->SetMyRenderer(Effects_[i]->CreateRenderer());

				Effects_[i]->GetMyRenderer()->CreateAnimation("IG_RED_EFFECT.bmp", "IG_RED_EFFECT", 0, 2, 0.17f, false);
				Effects_[i]->GetMyRenderer()->ChangeAnimation("IG_RED_EFFECT");
				Effects_[i]->GetMyRenderer()->PauseOn();
			}
			break;
		case PuyoColor::BLUE:
			for (int i = 0; i < 4; i++)
			{
				Effects_[i]->SetMyRenderer(Effects_[i]->CreateRenderer());

				Effects_[i]->GetMyRenderer()->CreateAnimation("IG_BLUE_EFFECT.bmp", "IG_BLUE_EFFECT", 0, 2, 0.17f, false);
				Effects_[i]->GetMyRenderer()->ChangeAnimation("IG_BLUE_EFFECT");
				Effects_[i]->GetMyRenderer()->PauseOn();
			}
			break;
		case PuyoColor::GREEN:
			for (int i = 0; i < 4; i++)
			{
				Effects_[i]->SetMyRenderer(Effects_[i]->CreateRenderer());

				Effects_[i]->GetMyRenderer()->CreateAnimation("IG_GREEN_EFFECT.bmp", "IG_GREEN_EFFECT", 0, 2, 0.17f, false);
				Effects_[i]->GetMyRenderer()->ChangeAnimation("IG_GREEN_EFFECT");
				Effects_[i]->GetMyRenderer()->PauseOn();
			}
			break;
		case PuyoColor::YELLOW:
			for (int i = 0; i < 4; i++)
			{
				Effects_[i]->SetMyRenderer(Effects_[i]->CreateRenderer());

				Effects_[i]->GetMyRenderer()->CreateAnimation("IG_YELLOW_EFFECT.bmp", "IG_YELLOW_EFFECT", 0, 2, 0.17f, false);
				Effects_[i]->GetMyRenderer()->ChangeAnimation("IG_YELLOW_EFFECT");
				Effects_[i]->GetMyRenderer()->PauseOn();
			}
			break;
		case PuyoColor::PURPLE:
			for (int i = 0; i < 4; i++)
			{
				Effects_[i]->SetMyRenderer(Effects_[i]->CreateRenderer());

				Effects_[i]->GetMyRenderer()->CreateAnimation("IG_PURPLE_EFFECT.bmp", "IG_PURPLE_EFFECT", 0, 2, 0.17f, false);
				Effects_[i]->GetMyRenderer()->ChangeAnimation("IG_PURPLE_EFFECT");
				Effects_[i]->GetMyRenderer()->PauseOn();
			}
			break;
		}
	}

	for (int i = 0; i < 4; i++)
	{
		Effects_[i]->SetPosition(GetPosition());
	}

}

void PuyoDestroyEffect::PlayEffect()
{
	DirForce_ += GameEngineTime::GetDeltaTime();
	Gravity_ += GameEngineTime::GetDeltaTime() * 2.5f;
	
	for (int i = 0; i < 4; i++)
	{
		if (nullptr == Effects_[i])
		{
			return;
		}

		Effects_[i]->GetMyRenderer()->SetOrder(20);
		Effects_[i]->GetMyRenderer()->PauseOff();

		if (0 == i)
		{
			float4 Dir = float4::UP + (float4::DOWN * Gravity_) + (float4::LEFT * DirForce_);
			Effects_[i]->SetMove(Dir * GameEngineTime::GetDeltaTime() * Speed_);
		}

		if (1 == i)
		{
			float4 Dir = float4::UP + (float4::DOWN * Gravity_) + (float4::LEFT * DirForce_ * 1.5f);
			Effects_[i]->SetMove(Dir * GameEngineTime::GetDeltaTime() * Speed_);
		}

		if (2 == i)
		{
			float4 Dir = float4::UP + (float4::DOWN * Gravity_) + (float4::RIGHT * DirForce_);
			Effects_[i]->SetMove(Dir * GameEngineTime::GetDeltaTime() * Speed_);
		}

		if (3 == i)
		{
			float4 Dir = float4::UP + (float4::DOWN * Gravity_) + (float4::RIGHT * DirForce_ * 1.5f);
			Effects_[i]->SetMove(Dir * GameEngineTime::GetDeltaTime() * Speed_);
		}
	}
}

void PuyoDestroyEffect::EndEffect()
{
	for (int i = 0; i < 4; i++)
	{
		if (true == Effects_[i]->GetMyRenderer()->IsEndAnimation())
		{
			++Count_;
			Effects_[i]->Death();
		}
	}

	if (4 == Count_)
	{
		DirForce_;
		Gravity_;

		IsPlay_ = false;
	}
}

