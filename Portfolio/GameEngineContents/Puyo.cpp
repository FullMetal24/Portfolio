#include "Puyo.h"
#include "GameEngineBase/GameEngineWindow.h"
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngine/GameEngine.h>
#include <GameEngineBase/GameEngineTime.h>
#include "Player.h"
#include "EnemyFSM.h"
#include "PuyoDestroyEffect.h"


Puyo::Puyo()
	: PuyoState_{}
	, MyRenderer_(nullptr)
	, MyColor_(PuyoColor::RED)
	, CurDir_(PuyoDir::UP)
	, X_(0)
	, Y_(0)
	, OffsetX_(0)
	, TwinkleCount_(0)
	, StartPos_{}
	, EndPos_{}
	, Alpha_(0.f)
	, IsLand_(false)
	, IsDestroy_(false)
	, IsFall_(false)
	, IsLoseFall_(false)
	, IsSoundPlay_(false)
	, IsEffectOn_(false)
{
}

Puyo::~Puyo()
{
}

void Puyo::Start()
{
	PuyoState_ = PuyoState::Normal;

	IdleTime_ = Random_.RandomFloat(5.f, 10.f);
}

void Puyo::Update()
{
	switch (PuyoState_)
	{
	case PuyoState::Normal:
		if (true == IsLand_)
		{
			RandomIdleAnimation();
			IdleToNomal();

			if (nullptr != Player_)
			{
				LinkedPuyoAnimtaion(Player_->PlayerMap_);
			}

			else if (nullptr != Enemy_)
			{
				LinkedPuyoAnimtaion(Enemy_->EnemyMap_);
			}
		}
		break;
	case PuyoState::Linked:
		if (true == IsLand_)
		{
			if (nullptr != Player_)
			{
				LinkedPuyoAnimtaion(Player_->PlayerMap_);
			}

			else if (nullptr != Enemy_)
			{
				LinkedPuyoAnimtaion(Enemy_->EnemyMap_);
			}
		}
		break;
	case PuyoState::Land:
		RenderToLand();
		LandToNormal();
		break;
	case PuyoState::Fall:
		FallingPuyo();
		break;
	case PuyoState::Destroy:
		DestroyEffect();
		RenderToDestroy();
		SelfDestroy();
		TwinklePuyo();
		break;
	case PuyoState::LoseFall:
		LoseFall();
		break;
	}
}

void Puyo::InitAnimation(PuyoColor color)
{
	MyColor_ = color;
	MyRenderer_ = CreateRenderer();

	switch (MyColor_)
	{
	case PuyoColor::RED:
		MyRenderer_->CreateAnimation("IG_RED_PUYO.bmp", "IG_RED_PUYO", 0, 0, 0.f, false);
		MyRenderer_->CreateAnimation("IG_RED_CENTER.bmp", "IG_RED_CENTER", 0, 1, 0.1f, true);
		MyRenderer_->CreateAnimation("IG_RED_LAND.bmp", "IG_RED_LAND", 0, 3, 0.07f, false);
		MyRenderer_->CreateAnimation("IG_RED_DESTROY.bmp", "IG_RED_DESTROY", 0, 5, 0.1f, false);

		MyRenderer_->CreateAnimation("IG_RED_LEFT.bmp", "IG_RED_LEFT", 0, 0, 0.f, false);
		MyRenderer_->CreateAnimation("IG_RED_RIGHT.bmp", "IG_RED_RIGHT", 0, 0, 0.f, false);
		MyRenderer_->CreateAnimation("IG_RED_UP.bmp", "IG_RED_UP", 0, 0, 0.f, false);
		MyRenderer_->CreateAnimation("IG_RED_DOWN.bmp", "IG_RED_DOWN", 0, 0, 0.f, false);

		MyRenderer_->CreateAnimation("IG_RED_LEFT_RIGHT.bmp", "IG_RED_LEFT_RIGHT", 0, 0, 0.f, false);
		MyRenderer_->CreateAnimation("IG_RED_LEFT_RIGHT_UP.bmp", "IG_RED_LEFT_RIGHT_UP", 0, 0, 0.f, false);
		MyRenderer_->CreateAnimation("IG_RED_LEFT_RIGHT_DOWN.bmp", "IG_RED_LEFT_RIGHT_DOWN", 0, 0, 0.f, false);
		MyRenderer_->CreateAnimation("IG_RED_LEFT_RIGHT_UP_DOWN.bmp", "IG_RED_LEFT_RIGHT_UP_DOWN", 0, 0, 0.f, false);
		MyRenderer_->CreateAnimation("IG_RED_LEFT_UP.bmp", "IG_RED_LEFT_UP", 0, 0, 0.f, false);
		MyRenderer_->CreateAnimation("IG_RED_LEFT_UP_DOWN.bmp", "IG_RED_LEFT_UP_DOWN", 0, 0, 0.f, false);
		MyRenderer_->CreateAnimation("IG_RED_LEFT_DOWN.bmp", "IG_RED_LEFT_DOWN", 0, 0, 0.f, false);

		MyRenderer_->CreateAnimation("IG_RED_RIGHT_UP.bmp", "IG_RED_RIGHT_UP", 0, 0, 0.f, false);
		MyRenderer_->CreateAnimation("IG_RED_RIGHT_DOWN.bmp", "IG_RED_RIGHT_DOWN", 0, 0, 0.f, false);
		MyRenderer_->CreateAnimation("IG_RED_RIGHT_UP_DOWN.bmp", "IG_RED_RIGHT_UP_DOWN", 0, 0, 0.f, false);

		MyRenderer_->CreateAnimation("IG_RED_UP_DOWN.bmp", "IG_RED_UP_DOWN", 0, 0, 0.f, false);
		MyRenderer_->CreateAnimation("IG_RED_IDLE.bmp", "IG_RED_IDLE", 0, 2, 0.15f, false);
		MyRenderer_->CreateAnimation("IG_RED_IDLE1.bmp", "IG_RED_IDLE1", 0, 5, 0.15f, false);

		MyRenderer_->ChangeAnimation("IG_RED_PUYO");
		break;

	case PuyoColor::BLUE:
		MyRenderer_->CreateAnimation("IG_BLUE_PUYO.bmp", "IG_BLUE_PUYO", 0, 0, 0.f, false);
		MyRenderer_->CreateAnimation("IG_BLUE_CENTER.bmp", "IG_BLUE_CENTER", 0, 1, 0.1f, true);
		MyRenderer_->CreateAnimation("IG_BLUE_LAND.bmp", "IG_BLUE_LAND", 0, 3, 0.07f, false);
		MyRenderer_->CreateAnimation("IG_BLUE_DESTROY.bmp", "IG_BLUE_DESTROY", 0, 5, 0.1f, false);

		MyRenderer_->CreateAnimation("IG_BLUE_LEFT.bmp", "IG_BLUE_LEFT", 0, 0, 0.f, false);
		MyRenderer_->CreateAnimation("IG_BLUE_RIGHT.bmp", "IG_BLUE_RIGHT", 0, 0, 0.f, false);
		MyRenderer_->CreateAnimation("IG_BLUE_UP.bmp", "IG_BLUE_UP", 0, 0, 0.f, false);
		MyRenderer_->CreateAnimation("IG_BLUE_DOWN.bmp", "IG_BLUE_DOWN", 0, 0, 0.f, false);

		MyRenderer_->CreateAnimation("IG_BLUE_LEFT_RIGHT.bmp", "IG_BLUE_LEFT_RIGHT", 0, 0, 0.f, false);
		MyRenderer_->CreateAnimation("IG_BLUE_LEFT_RIGHT_UP.bmp", "IG_BLUE_LEFT_RIGHT_UP", 0, 0, 0.f, false);
		MyRenderer_->CreateAnimation("IG_BLUE_LEFT_RIGHT_DOWN.bmp", "IG_BLUE_LEFT_RIGHT_DOWN", 0, 0, 0.f, false);
		MyRenderer_->CreateAnimation("IG_BLUE_LEFT_RIGHT_UP_DOWN.bmp", "IG_BLUE_LEFT_RIGHT_UP_DOWN", 0, 0, 0.f, false);
		MyRenderer_->CreateAnimation("IG_BLUE_LEFT_UP.bmp", "IG_BLUE_LEFT_UP", 0, 0, 0.f, false);
		MyRenderer_->CreateAnimation("IG_BLUE_LEFT_UP_DOWN.bmp", "IG_BLUE_LEFT_UP_DOWN", 0, 0, 0.f, false);
		MyRenderer_->CreateAnimation("IG_BLUE_LEFT_DOWN.bmp", "IG_BLUE_LEFT_DOWN", 0, 0, 0.f, false);

		MyRenderer_->CreateAnimation("IG_BLUE_RIGHT_UP.bmp", "IG_BLUE_RIGHT_UP", 0, 0, 0.f, false);
		MyRenderer_->CreateAnimation("IG_BLUE_RIGHT_DOWN.bmp", "IG_BLUE_RIGHT_DOWN", 0, 0, 0.f, false);
		MyRenderer_->CreateAnimation("IG_BLUE_RIGHT_UP_DOWN.bmp", "IG_BLUE_RIGHT_UP_DOWN", 0, 0, 0.f, false);

		MyRenderer_->CreateAnimation("IG_BLUE_UP_DOWN.bmp", "IG_BLUE_UP_DOWN", 0, 0, 0.f, false);
		MyRenderer_->CreateAnimation("IG_BLUE_IDLE.bmp", "IG_BLUE_IDLE", 0, 5, 0.15f, false);
		MyRenderer_->CreateAnimation("IG_BLUE_IDLE1.bmp", "IG_BLUE_IDLE1", 0, 7, 0.15f, false);

		MyRenderer_->ChangeAnimation("IG_BLUE_PUYO");
		break;

	case PuyoColor::GREEN:
		MyRenderer_->CreateAnimation("IG_GREEN_PUYO.bmp", "IG_GREEN_PUYO", 0, 0, 0.f, false);
		MyRenderer_->CreateAnimation("IG_GREEN_CENTER.bmp", "IG_GREEN_CENTER", 0, 1, 0.1f, true);
		MyRenderer_->CreateAnimation("IG_GREEN_LAND.bmp", "IG_GREEN_LAND", 0, 3, 0.07f, false);
		MyRenderer_->CreateAnimation("IG_GREEN_DESTROY.bmp", "IG_GREEN_DESTROY", 0, 5, 0.1f, false);

		MyRenderer_->CreateAnimation("IG_GREEN_LEFT.bmp", "IG_GREEN_LEFT", 0, 0, 0.f, false);
		MyRenderer_->CreateAnimation("IG_GREEN_RIGHT.bmp", "IG_GREEN_RIGHT", 0, 0, 0.f, false);
		MyRenderer_->CreateAnimation("IG_GREEN_UP.bmp", "IG_GREEN_UP", 0, 0, 0.f, false);
		MyRenderer_->CreateAnimation("IG_GREEN_DOWN.bmp", "IG_GREEN_DOWN", 0, 0, 0.f, false);

		MyRenderer_->CreateAnimation("IG_GREEN_LEFT_RIGHT.bmp", "IG_GREEN_LEFT_RIGHT", 0, 0, 0.f, false);
		MyRenderer_->CreateAnimation("IG_GREEN_LEFT_RIGHT_UP.bmp", "IG_GREEN_LEFT_RIGHT_UP", 0, 0, 0.f, false);
		MyRenderer_->CreateAnimation("IG_GREEN_LEFT_RIGHT_DOWN.bmp", "IG_GREEN_LEFT_RIGHT_DOWN", 0, 0, 0.f, false);
		MyRenderer_->CreateAnimation("IG_GREEN_LEFT_RIGHT_UP_DOWN.bmp", "IG_GREEN_LEFT_RIGHT_UP_DOWN", 0, 0, 0.f, false);
		MyRenderer_->CreateAnimation("IG_GREEN_LEFT_UP.bmp", "IG_GREEN_LEFT_UP", 0, 0, 0.f, false);
		MyRenderer_->CreateAnimation("IG_GREEN_LEFT_UP_DOWN.bmp", "IG_GREEN_LEFT_UP_DOWN", 0, 0, 0.f, false);
		MyRenderer_->CreateAnimation("IG_GREEN_LEFT_DOWN.bmp", "IG_GREEN_LEFT_DOWN", 0, 0, 0.f, false);

		MyRenderer_->CreateAnimation("IG_GREEN_RIGHT_UP.bmp", "IG_GREEN_RIGHT_UP", 0, 0, 0.f, false);
		MyRenderer_->CreateAnimation("IG_GREEN_RIGHT_DOWN.bmp", "IG_GREEN_RIGHT_DOWN", 0, 0, 0.f, false);
		MyRenderer_->CreateAnimation("IG_GREEN_RIGHT_UP_DOWN.bmp", "IG_GREEN_RIGHT_UP_DOWN", 0, 0, 0.f, false);

		MyRenderer_->CreateAnimation("IG_GREEN_UP_DOWN.bmp", "IG_GREEN_UP_DOWN", 0, 0, 0.f, false);
		MyRenderer_->CreateAnimation("IG_GREEN_IDLE.bmp", "IG_GREEN_IDLE", 0, 7, 0.15f, false);
		MyRenderer_->CreateAnimation("IG_GREEN_IDLE1.bmp", "IG_GREEN_IDLE1", 0, 7, 0.15f, false);

		MyRenderer_->ChangeAnimation("IG_GREEN_PUYO");
		break;
	case PuyoColor::YELLOW:
		MyRenderer_->CreateAnimation("IG_YELLOW_PUYO.bmp", "IG_YELLOW_PUYO", 0, 0, 0.f, false);
		MyRenderer_->CreateAnimation("IG_YELLOW_CENTER.bmp", "IG_YELLOW_CENTER", 0, 1, 0.1f, true);
		MyRenderer_->CreateAnimation("IG_YELLOW_LAND.bmp", "IG_YELLOW_LAND", 0, 3, 0.07f, false);
		MyRenderer_->CreateAnimation("IG_YELLOW_DESTROY.bmp", "IG_YELLOW_DESTROY", 0, 5, 0.1f, false);

		MyRenderer_->CreateAnimation("IG_YELLOW_LEFT.bmp", "IG_YELLOW_LEFT", 0, 0, 0.f, false);
		MyRenderer_->CreateAnimation("IG_YELLOW_RIGHT.bmp", "IG_YELLOW_RIGHT", 0, 0, 0.f, false);
		MyRenderer_->CreateAnimation("IG_YELLOW_UP.bmp", "IG_YELLOW_UP", 0, 0, 0.f, false);
		MyRenderer_->CreateAnimation("IG_YELLOW_DOWN.bmp", "IG_YELLOW_DOWN", 0, 0, 0.f, false);

		MyRenderer_->CreateAnimation("IG_YELLOW_LEFT_RIGHT.bmp", "IG_YELLOW_LEFT_RIGHT", 0, 0, 0.f, false);
		MyRenderer_->CreateAnimation("IG_YELLOW_LEFT_RIGHT_DOWN.bmp", "IG_YELLOW_LEFT_RIGHT_DOWN", 0, 0, 0.f, false);
		MyRenderer_->CreateAnimation("IG_YELLOW_LEFT_RIGHT_UP.bmp", "IG_YELLOW_LEFT_RIGHT_UP", 0, 0, 0.f, false);
		MyRenderer_->CreateAnimation("IG_YELLOW_LEFT_RIGHT_UP_DOWN.bmp", "IG_YELLOW_LEFT_RIGHT_UP_DOWN", 0, 0, 0.f, false);
		MyRenderer_->CreateAnimation("IG_YELLOW_LEFT_UP.bmp", "IG_YELLOW_LEFT_UP", 0, 0, 0.f, false);
		MyRenderer_->CreateAnimation("IG_YELLOW_LEFT_UP_DOWN.bmp", "IG_YELLOW_LEFT_UP_DOWN", 0, 0, 0.f, false);
		MyRenderer_->CreateAnimation("IG_YELLOW_LEFT_DOWN.bmp", "IG_YELLOW_LEFT_DOWN", 0, 0, 0.f, false);

		MyRenderer_->CreateAnimation("IG_YELLOW_RIGHT_UP.bmp", "IG_YELLOW_RIGHT_UP", 0, 0, 0.f, false);
		MyRenderer_->CreateAnimation("IG_YELLOW_RIGHT_DOWN.bmp", "IG_YELLOW_RIGHT_DOWN", 0, 0, 0.f, false);
		MyRenderer_->CreateAnimation("IG_YELLOW_RIGHT_UP_DOWN.bmp", "IG_YELLOW_RIGHT_UP_DOWN", 0, 0, 0.f, false);

		MyRenderer_->CreateAnimation("IG_YELLOW_UP_DOWN.bmp", "IG_YELLOW_UP_DOWN", 0, 0, 0.f, false);
		MyRenderer_->CreateAnimation("IG_YELLOW_IDLE.bmp", "IG_YELLOW_IDLE", 0, 7, 0.15f, false);
		MyRenderer_->CreateAnimation("IG_YELLOW_IDLE1.bmp", "IG_YELLOW_IDLE1", 0, 2, 0.15f, false);

		MyRenderer_->ChangeAnimation("IG_YELLOW_PUYO");
		break;
	case PuyoColor::PURPLE:
		MyRenderer_->CreateAnimation("IG_PURPLE_PUYO.bmp", "IG_PURPLE_PUYO", 0, 0, 0.f, false);
		MyRenderer_->CreateAnimation("IG_PURPLE_CENTER.bmp", "IG_PURPLE_CENTER", 0, 1, 0.1f, true);
		MyRenderer_->CreateAnimation("IG_PURPLE_LAND.bmp", "IG_PURPLE_LAND", 0, 3, 0.07f, false);
		MyRenderer_->CreateAnimation("IG_PURPLE_DESTROY.bmp", "IG_PURPLE_DESTROY", 0, 5, 0.1f, false);

		MyRenderer_->CreateAnimation("IG_PURPLE_LEFT.bmp", "IG_PURPLE_LEFT", 0, 0, 0.f, false);
		MyRenderer_->CreateAnimation("IG_PURPLE_RIGHT.bmp", "IG_PURPLE_RIGHT", 0, 0, 0.f, false);
		MyRenderer_->CreateAnimation("IG_PURPLE_UP.bmp", "IG_PURPLE_UP", 0, 0, 0.f, false);
		MyRenderer_->CreateAnimation("IG_PURPLE_DOWN.bmp", "IG_PURPLE_DOWN", 0, 0, 0.f, false);

		MyRenderer_->CreateAnimation("IG_PURPLE_LEFT_RIGHT.bmp", "IG_PURPLE_LEFT_RIGHT", 0, 0, 0.f, false);
		MyRenderer_->CreateAnimation("IG_PURPLE_LEFT_RIGHT_UP.bmp", "IG_PURPLE_LEFT_RIGHT_UP", 0, 0, 0.f, false);
		MyRenderer_->CreateAnimation("IG_PURPLE_LEFT_RIGHT_DOWN.bmp", "IG_PURPLE_LEFT_RIGHT_DOWN", 0, 0, 0.f, false);
		MyRenderer_->CreateAnimation("IG_PURPLE_LEFT_RIGHT_UP_DOWN.bmp", "IG_PURPLE_LEFT_RIGHT_UP_DOWN", 0, 0, 0.f, false);
		MyRenderer_->CreateAnimation("IG_PURPLE_LEFT_UP.bmp", "IG_PURPLE_LEFT_UP", 0, 0, 0.f, false);
		MyRenderer_->CreateAnimation("IG_PURPLE_LEFT_UP_DOWN.bmp", "IG_PURPLE_LEFT_UP_DOWN", 0, 0, 0.f, false);
		MyRenderer_->CreateAnimation("IG_PURPLE_LEFT_DOWN.bmp", "IG_PURPLE_LEFT_DOWN", 0, 0, 0.f, false);

		MyRenderer_->CreateAnimation("IG_PURPLE_RIGHT_DOWN.bmp", "IG_PURPLE_RIGHT_DOWN", 0, 0, 0.f, false);
		MyRenderer_->CreateAnimation("IG_PURPLE_RIGHT_UP.bmp", "IG_PURPLE_RIGHT_UP", 0, 0, 0.f, false);
		MyRenderer_->CreateAnimation("IG_PURPLE_RIGHT_UP_DOWN.bmp", "IG_PURPLE_RIGHT_UP_DOWN", 0, 0, 0.f, false);

		MyRenderer_->CreateAnimation("IG_PURPLE_UP_DOWN.bmp", "IG_PURPLE_UP_DOWN", 0, 0, 0.f, false);
		MyRenderer_->CreateAnimation("IG_PURPLE_IDLE.bmp", "IG_PURPLE_IDLE", 0, 4, 0.15f, false);
		MyRenderer_->CreateAnimation("IG_PURPLE_IDLE1.bmp", "IG_PURPLE_IDLE1", 0, 4, 0.15f, false);

		MyRenderer_->ChangeAnimation("IG_PURPLE_PUYO");
		break;

	case PuyoColor::Hindrance:
		MyRenderer_->CreateAnimation("IG_HINDRANCE_PUYO.bmp", "IG_HINDRANCE_PUYO", 0, 0, 0.f, false);
		MyRenderer_->CreateAnimation("IG_HINDRANCE_PUYO_DESTROY.bmp", "IG_HINDRANCE_PUYO_DESTROY", 0, 3, 0.1f, false);
		MyRenderer_->CreateAnimation("IG_HINDRANCE_PUYO_IDLE.bmp", "IG_HINDRANCE_PUYO_IDLE", 0, 2, 0.15f, false);
		MyRenderer_->ChangeAnimation("IG_HINDRANCE_PUYO");
		break;
	}
}

void Puyo::InitAllAnimation()
{
	MyRenderer_ = CreateRenderer();

	MyRenderer_->CreateAnimation("IG_RED_PUYO.bmp", "IG_RED_PUYO", 0, 0, 0.f, false);
	MyRenderer_->CreateAnimation("IG_RED_CENTER.bmp", "IG_RED_CENTER", 0, 1, 0.1f, true);
	MyRenderer_->CreateAnimation("IG_RED_LAND.bmp", "IG_RED_LAND", 0, 3, 0.07f, false);
	MyRenderer_->CreateAnimation("IG_RED_DESTROY.bmp", "IG_RED_DESTROY", 0, 5, 0.1f, false);

	MyRenderer_->CreateAnimation("IG_RED_LEFT.bmp", "IG_RED_LEFT", 0, 0, 0.f, false);
	MyRenderer_->CreateAnimation("IG_RED_RIGHT.bmp", "IG_RED_RIGHT", 0, 0, 0.f, false);
	MyRenderer_->CreateAnimation("IG_RED_UP.bmp", "IG_RED_UP", 0, 0, 0.f, false);
	MyRenderer_->CreateAnimation("IG_RED_DOWN.bmp", "IG_RED_DOWN", 0, 0, 0.f, false);

	MyRenderer_->CreateAnimation("IG_RED_LEFT_RIGHT.bmp", "IG_RED_LEFT_RIGHT", 0, 0, 0.f, false);
	MyRenderer_->CreateAnimation("IG_RED_LEFT_RIGHT_UP.bmp", "IG_RED_LEFT_RIGHT_UP", 0, 0, 0.f, false);
	MyRenderer_->CreateAnimation("IG_RED_LEFT_RIGHT_DOWN.bmp", "IG_RED_LEFT_RIGHT_DOWN", 0, 0, 0.f, false);
	MyRenderer_->CreateAnimation("IG_RED_LEFT_RIGHT_UP_DOWN.bmp", "IG_RED_LEFT_RIGHT_UP_DOWN", 0, 0, 0.f, false);
	MyRenderer_->CreateAnimation("IG_RED_LEFT_UP.bmp", "IG_RED_LEFT_UP", 0, 0, 0.f, false);
	MyRenderer_->CreateAnimation("IG_RED_LEFT_UP_DOWN.bmp", "IG_RED_LEFT_UP_DOWN", 0, 0, 0.f, false);
	MyRenderer_->CreateAnimation("IG_RED_LEFT_DOWN.bmp", "IG_RED_LEFT_DOWN", 0, 0, 0.f, false);

	MyRenderer_->CreateAnimation("IG_RED_RIGHT_UP.bmp", "IG_RED_RIGHT_UP", 0, 0, 0.f, false);
	MyRenderer_->CreateAnimation("IG_RED_RIGHT_DOWN.bmp", "IG_RED_RIGHT_DOWN", 0, 0, 0.f, false);
	MyRenderer_->CreateAnimation("IG_RED_RIGHT_UP_DOWN.bmp", "IG_RED_RIGHT_UP_DOWN", 0, 0, 0.f, false);

	MyRenderer_->CreateAnimation("IG_RED_UP_DOWN.bmp", "IG_RED_UP_DOWN", 0, 0, 0.f, false);

	MyRenderer_->CreateAnimation("IG_BLUE_PUYO.bmp", "IG_BLUE_PUYO", 0, 0, 0.f, false);
	MyRenderer_->CreateAnimation("IG_BLUE_CENTER.bmp", "IG_BLUE_CENTER", 0, 1, 0.1f, true);
	MyRenderer_->CreateAnimation("IG_BLUE_LAND.bmp", "IG_BLUE_LAND", 0, 3, 0.07f, false);
	MyRenderer_->CreateAnimation("IG_BLUE_DESTROY.bmp", "IG_BLUE_DESTROY", 0, 5, 0.1f, false);

	MyRenderer_->CreateAnimation("IG_BLUE_LEFT.bmp", "IG_BLUE_LEFT", 0, 0, 0.f, false);
	MyRenderer_->CreateAnimation("IG_BLUE_RIGHT.bmp", "IG_BLUE_RIGHT", 0, 0, 0.f, false);
	MyRenderer_->CreateAnimation("IG_BLUE_UP.bmp", "IG_BLUE_UP", 0, 0, 0.f, false);
	MyRenderer_->CreateAnimation("IG_BLUE_DOWN.bmp", "IG_BLUE_DOWN", 0, 0, 0.f, false);

	MyRenderer_->CreateAnimation("IG_BLUE_LEFT_RIGHT.bmp", "IG_BLUE_LEFT_RIGHT", 0, 0, 0.f, false);
	MyRenderer_->CreateAnimation("IG_BLUE_LEFT_RIGHT_UP.bmp", "IG_BLUE_LEFT_RIGHT_UP", 0, 0, 0.f, false);
	MyRenderer_->CreateAnimation("IG_BLUE_LEFT_RIGHT_DOWN.bmp", "IG_BLUE_LEFT_RIGHT_DOWN", 0, 0, 0.f, false);
	MyRenderer_->CreateAnimation("IG_BLUE_LEFT_RIGHT_UP_DOWN.bmp", "IG_BLUE_LEFT_RIGHT_UP_DOWN", 0, 0, 0.f, false);
	MyRenderer_->CreateAnimation("IG_BLUE_LEFT_UP.bmp", "IG_BLUE_LEFT_UP", 0, 0, 0.f, false);
	MyRenderer_->CreateAnimation("IG_BLUE_LEFT_UP_DOWN.bmp", "IG_BLUE_LEFT_UP_DOWN", 0, 0, 0.f, false);
	MyRenderer_->CreateAnimation("IG_BLUE_LEFT_DOWN.bmp", "IG_BLUE_LEFT_DOWN", 0, 0, 0.f, false);

	MyRenderer_->CreateAnimation("IG_BLUE_RIGHT_UP.bmp", "IG_BLUE_RIGHT_UP", 0, 0, 0.f, false);
	MyRenderer_->CreateAnimation("IG_BLUE_RIGHT_DOWN.bmp", "IG_BLUE_RIGHT_DOWN", 0, 0, 0.f, false);
	MyRenderer_->CreateAnimation("IG_BLUE_RIGHT_UP_DOWN.bmp", "IG_BLUE_RIGHT_UP_DOWN", 0, 0, 0.f, false);

	MyRenderer_->CreateAnimation("IG_BLUE_UP_DOWN.bmp", "IG_BLUE_UP_DOWN", 0, 0, 0.f, false);

	MyRenderer_->CreateAnimation("IG_GREEN_PUYO.bmp", "IG_GREEN_PUYO", 0, 0, 0.f, false);
	MyRenderer_->CreateAnimation("IG_GREEN_CENTER.bmp", "IG_GREEN_CENTER", 0, 1, 0.1f, true);
	MyRenderer_->CreateAnimation("IG_GREEN_LAND.bmp", "IG_GREEN_LAND", 0, 3, 0.07f, false);
	MyRenderer_->CreateAnimation("IG_GREEN_DESTROY.bmp", "IG_GREEN_DESTROY", 0, 5, 0.1f, false);

	MyRenderer_->CreateAnimation("IG_GREEN_LEFT.bmp", "IG_GREEN_LEFT", 0, 0, 0.f, false);
	MyRenderer_->CreateAnimation("IG_GREEN_RIGHT.bmp", "IG_GREEN_RIGHT", 0, 0, 0.f, false);
	MyRenderer_->CreateAnimation("IG_GREEN_UP.bmp", "IG_GREEN_UP", 0, 0, 0.f, false);
	MyRenderer_->CreateAnimation("IG_GREEN_DOWN.bmp", "IG_GREEN_DOWN", 0, 0, 0.f, false);

	MyRenderer_->CreateAnimation("IG_GREEN_LEFT_RIGHT.bmp", "IG_GREEN_LEFT_RIGHT", 0, 0, 0.f, false);
	MyRenderer_->CreateAnimation("IG_GREEN_LEFT_RIGHT_UP.bmp", "IG_GREEN_LEFT_RIGHT_UP", 0, 0, 0.f, false);
	MyRenderer_->CreateAnimation("IG_GREEN_LEFT_RIGHT_DOWN.bmp", "IG_GREEN_LEFT_RIGHT_DOWN", 0, 0, 0.f, false);
	MyRenderer_->CreateAnimation("IG_GREEN_LEFT_RIGHT_UP_DOWN.bmp", "IG_GREEN_LEFT_RIGHT_UP_DOWN", 0, 0, 0.f, false);
	MyRenderer_->CreateAnimation("IG_GREEN_LEFT_UP.bmp", "IG_GREEN_LEFT_UP", 0, 0, 0.f, false);
	MyRenderer_->CreateAnimation("IG_GREEN_LEFT_UP_DOWN.bmp", "IG_GREEN_LEFT_UP_DOWN", 0, 0, 0.f, false);
	MyRenderer_->CreateAnimation("IG_GREEN_LEFT_DOWN.bmp", "IG_GREEN_LEFT_DOWN", 0, 0, 0.f, false);

	MyRenderer_->CreateAnimation("IG_GREEN_RIGHT_UP.bmp", "IG_GREEN_RIGHT_UP", 0, 0, 0.f, false);
	MyRenderer_->CreateAnimation("IG_GREEN_RIGHT_DOWN.bmp", "IG_GREEN_RIGHT_DOWN", 0, 0, 0.f, false);
	MyRenderer_->CreateAnimation("IG_GREEN_RIGHT_UP_DOWN.bmp", "IG_GREEN_RIGHT_UP_DOWN", 0, 0, 0.f, false);

	MyRenderer_->CreateAnimation("IG_GREEN_UP_DOWN.bmp", "IG_GREEN_UP_DOWN", 0, 0, 0.f, false);

	MyRenderer_->CreateAnimation("IG_YELLOW_PUYO.bmp", "IG_YELLOW_PUYO", 0, 0, 0.f, false);
	MyRenderer_->CreateAnimation("IG_YELLOW_CENTER.bmp", "IG_YELLOW_CENTER", 0, 1, 0.1f, true);
	MyRenderer_->CreateAnimation("IG_YELLOW_LAND.bmp", "IG_YELLOW_LAND", 0, 3, 0.07f, false);
	MyRenderer_->CreateAnimation("IG_YELLOW_DESTROY.bmp", "IG_YELLOW_DESTROY", 0, 5, 0.1f, false);

	MyRenderer_->CreateAnimation("IG_YELLOW_LEFT.bmp", "IG_YELLOW_LEFT", 0, 0, 0.f, false);
	MyRenderer_->CreateAnimation("IG_YELLOW_RIGHT.bmp", "IG_YELLOW_RIGHT", 0, 0, 0.f, false);
	MyRenderer_->CreateAnimation("IG_YELLOW_UP.bmp", "IG_YELLOW_UP", 0, 0, 0.f, false);
	MyRenderer_->CreateAnimation("IG_YELLOW_DOWN.bmp", "IG_YELLOW_DOWN", 0, 0, 0.f, false);

	MyRenderer_->CreateAnimation("IG_YELLOW_LEFT_RIGHT.bmp", "IG_YELLOW_LEFT_RIGHT", 0, 0, 0.f, false);
	MyRenderer_->CreateAnimation("IG_YELLOW_LEFT_RIGHT_DOWN.bmp", "IG_YELLOW_LEFT_RIGHT_DOWN", 0, 0, 0.f, false);
	MyRenderer_->CreateAnimation("IG_YELLOW_LEFT_RIGHT_UP_DOWN.bmp", "IG_YELLOW_LEFT_RIGHT_UP_DOWN", 0, 0, 0.f, false);
	MyRenderer_->CreateAnimation("IG_YELLOW_LEFT_UP.bmp", "IG_YELLOW_LEFT_UP", 0, 0, 0.f, false);
	MyRenderer_->CreateAnimation("IG_YELLOW_LEFT_UP_DOWN.bmp", "IG_YELLOW_LEFT_UP_DOWN", 0, 0, 0.f, false);
	MyRenderer_->CreateAnimation("IG_YELLOW_LEFT_DOWN.bmp", "IG_YELLOW_LEFT_DOWN", 0, 0, 0.f, false);

	MyRenderer_->CreateAnimation("IG_YELLOW_RIGHT_UP.bmp", "IG_YELLOW_RIGHT_UP", 0, 0, 0.f, false);
	MyRenderer_->CreateAnimation("IG_YELLOW_RIGHT_DOWN.bmp", "IG_YELLOW_RIGHT_DOWN", 0, 0, 0.f, false);
	MyRenderer_->CreateAnimation("IG_YELLOW_RIGHT_UP_DOWN.bmp", "IG_YELLOW_RIGHT_UP_DOWN", 0, 0, 0.f, false);

	MyRenderer_->CreateAnimation("IG_YELLOW_UP_DOWN.bmp", "IG_YELLOW_UP_DOWN", 0, 0, 0.f, false);

	MyRenderer_->CreateAnimation("IG_PURPLE_PUYO.bmp", "IG_PURPLE_PUYO", 0, 0, 0.f, false);
	MyRenderer_->CreateAnimation("IG_PURPLE_CENTER.bmp", "IG_PURPLE_CENTER", 0, 1, 0.1f, true);
	MyRenderer_->CreateAnimation("IG_PURPLE_LAND.bmp", "IG_PURPLE_LAND", 0, 3, 0.07f, false);
	MyRenderer_->CreateAnimation("IG_PURPLE_DESTROY.bmp", "IG_PURPLE_DESTROY", 0, 5, 0.1f, false);

	MyRenderer_->CreateAnimation("IG_PURPLE_LEFT.bmp", "IG_PURPLE_LEFT", 0, 0, 0.f, false);
	MyRenderer_->CreateAnimation("IG_PURPLE_RIGHT.bmp", "IG_PURPLE_RIGHT", 0, 0, 0.f, false);
	MyRenderer_->CreateAnimation("IG_PURPLE_UP.bmp", "IG_PURPLE_UP", 0, 0, 0.f, false);
	MyRenderer_->CreateAnimation("IG_PURPLE_DOWN.bmp", "IG_PURPLE_DOWN", 0, 0, 0.f, false);

	MyRenderer_->CreateAnimation("IG_PURPLE_LEFT_RIGHT.bmp", "IG_PURPLE_LEFT_RIGHT", 0, 0, 0.f, false);
	MyRenderer_->CreateAnimation("IG_PURPLE_LEFT_RIGHT_UP.bmp", "IG_PURPLE_LEFT_RIGHT_UP", 0, 0, 0.f, false);
	MyRenderer_->CreateAnimation("IG_PURPLE_LEFT_RIGHT_DOWN.bmp", "IG_PURPLE_LEFT_RIGHT_DOWN", 0, 0, 0.f, false);
	MyRenderer_->CreateAnimation("IG_PURPLE_LEFT_RIGHT_UP_DOWN.bmp", "IG_PURPLE_LEFT_RIGHT_UP_DOWN", 0, 0, 0.f, false);
	MyRenderer_->CreateAnimation("IG_PURPLE_LEFT_UP.bmp", "IG_PURPLE_LEFT_UP", 0, 0, 0.f, false);
	MyRenderer_->CreateAnimation("IG_PURPLE_LEFT_UP_DOWN.bmp", "IG_PURPLE_LEFT_UP_DOWN", 0, 0, 0.f, false);
	MyRenderer_->CreateAnimation("IG_PURPLE_LEFT_DOWN.bmp", "IG_PURPLE_LEFT_DOWN", 0, 0, 0.f, false);

	MyRenderer_->CreateAnimation("IG_PURPLE_RIGHT_DOWN.bmp", "IG_PURPLE_RIGHT_DOWN", 0, 0, 0.f, false);
	MyRenderer_->CreateAnimation("IG_PURPLE_RIGHT_UP.bmp", "IG_PURPLE_RIGHT_UP", 0, 0, 0.f, false);
	MyRenderer_->CreateAnimation("IG_PURPLE_RIGHT_UP_DOWN.bmp", "IG_PURPLE_RIGHT_UP_DOWN", 0, 0, 0.f, false);

	MyRenderer_->CreateAnimation("IG_PURPLE_UP_DOWN.bmp", "IG_PURPLE_UP_DOWN", 0, 0, 0.f, false);
}

void Puyo::SetIndex(int _X, int _Y)
{
	SetX(_X);
	SetY(_Y);
}

void Puyo::SetColorImage(PuyoColor _Color)
{
	MyColor_ = _Color;

	switch (MyColor_)
	{
	case PuyoColor::RED:
		MyRenderer_->ChangeAnimation("IG_RED_PUYO");
		break;
	case PuyoColor::BLUE:
		MyRenderer_->ChangeAnimation("IG_BLUE_PUYO");
		break;
	case PuyoColor::GREEN:
		MyRenderer_->ChangeAnimation("IG_GREEN_PUYO");
		break;
	case PuyoColor::YELLOW:
		MyRenderer_->ChangeAnimation("IG_YELLOW_PUYO");
		break;
	case PuyoColor::PURPLE:
		MyRenderer_->ChangeAnimation("IG_PURPLE_PUYO");
		break;
	}

}

void Puyo::ChangeState(PuyoState _State)
{
	if (PuyoState::Land == _State)
	{
		PuyoSound_.SoundPlayOneShot("PUYO_LAND.mp3");
	}

	PuyoState_ = _State;
}

void Puyo::ChangeHindraceState(PuyoState _State)
{
	if (PuyoColor::Hindrance == MyColor_)
	{
		return;
	}

	PuyoState_ = _State;
}

void Puyo::DestroyHindracePuyo(Puyo* Map[15][6])
{
	float4 ArrDir[4] = { float4::LEFT, float4::RIGHT, float4::UP, float4::DOWN };

	for (int i = 0; i < 4; i++)
	{
		Y_;

		float4 Index = ArrDir[i] + GetIndex();

		if (0 > Index.x || 6 <= Index.x || 0 > Index.y || 15 <= Index.y)
		{
			continue;
		}

		if (nullptr != Map[Index.iy()][Index.ix()]
			&& PuyoColor::Hindrance == Map[Index.iy()][Index.ix()]->GetColor())
		{
			Map[Index.iy()][Index.ix()]->ChangeState(PuyoState::Destroy);
			Map[Index.iy()][Index.ix()] = nullptr;
		}
	}
}

void Puyo::Init(Player* _Player, int x, int y, PuyoColor _Color)
{
	Player_ = _Player;
	SetIndex(x, y);
	InitAnimation(_Color);

	SetPosition(_Player->GetPosition() + float4{ static_cast<float>((x * 65) + OffsetX_), static_cast<float>(y * -60) });

	OffsetX_ += 30;

	if (x == 5)
	{
		OffsetX_ = 0;
	}
}

void Puyo::Init(EnemyFSM* _Enemy, int x, int y, PuyoColor _Color)
{
	Enemy_ = _Enemy;
	SetIndex(x, y);
	InitAnimation(_Color);

	SetPosition(Enemy_->GetPosition() + float4{ static_cast<float>((x * 65) + OffsetX_), static_cast<float>(y * -60) });

	OffsetX_ += 30;

	if (x == 5)
	{
		OffsetX_ = 0;
	}
}

void  Puyo::CoordinateMove(Player* _Player, int x, int y)
{
	SetIndex(x, y);
	SetPosition(_Player->GetPosition() + float4{ static_cast<float>((x * 65)), static_cast<float>(y * -60) });
}

void Puyo::CoordinateMove(EnemyFSM* _Enemy, int x, int y)
{
	SetIndex(x, y);
	SetPosition(_Enemy->GetPosition() + float4{ static_cast<float>((x * 65)), static_cast<float>(y * -60) });
}

float4 Puyo::CoordinatePos(Player* _Player, int x, int y)
{
	return float4{ _Player->GetPosition() + float4{ static_cast<float>((x * 65)), static_cast<float>(y * -60) } };
}

float4 Puyo::CoordinatePos(EnemyFSM* _Enemy, int x, int y)
{
	return float4{ _Enemy->GetPosition() + float4{ static_cast<float>((x * 65)), static_cast<float>(y * -60) } };
}


//이동 관련 함수
Puyo* Puyo::LeftPuyo(Puyo* Map[15][6], Puyo* _Other)
{
	if (0 <= X_ - 1)
	{
		if (nullptr == Map[Y_][X_ - 1]
			&& nullptr == Map[_Other->GetY()][_Other->GetX() - 1])
		{
			Map[Y_][X_] = nullptr;
			Map[Y_][X_ - 1] = this;

			--X_;

			if (nullptr != Player_)
			{
				this->CoordinateMove(Player_, X_, Y_);
			}

			else if (nullptr != Enemy_)
			{
				this->CoordinateMove(Enemy_, X_, Y_);
			}

			return this;
		}

		else if (nullptr == Map[Y_][X_ - 1]
			&& nullptr != Map[_Other->GetY()][_Other->GetX() - 1])
		{
			Map[Y_][X_] = nullptr;
			Map[Y_][X_ - 1] = this;

			--X_;

			if (nullptr != Player_)
			{
				this->CoordinateMove(Player_, X_, Y_);
			}

			else if (nullptr != Enemy_)
			{
				this->CoordinateMove(Enemy_, X_, Y_);
			}

			return this;
		}

		else if (nullptr == Map[Y_][X_ - 1]
			&& this == Map[_Other->GetY()][_Other->GetX() - 1])
		{
			Map[Y_][X_] = nullptr;
			Map[Y_][X_ - 1] = this;

			--X_;

			if (nullptr != Player_)
			{
				this->CoordinateMove(Player_, X_, Y_);
			}

			else if (nullptr != Enemy_)
			{
				this->CoordinateMove(Enemy_, X_, Y_);
			}

			return this;
		}
	}
}


Puyo* Puyo::RightPuyo(Puyo* Map[15][6], Puyo* _Other)
{
	if (5 >= X_ + 1)
	{
		if (nullptr == Map[Y_][X_ + 1]
			&& nullptr == Map[_Other->GetY()][_Other->GetX() + 1])
		{
			Map[Y_][X_] = nullptr;
			Map[Y_][X_ + 1] = this;

			++X_;

			if (nullptr != Player_)
			{
				this->CoordinateMove(Player_, X_, Y_);
			}

			else if (nullptr != Enemy_)
			{
				this->CoordinateMove(Enemy_, X_, Y_);
			}

			return this;
		}

		else if (nullptr == Map[Y_][X_ + 1]
			&& nullptr != Map[_Other->GetY()][_Other->GetX() + 1])
		{
			Map[Y_][X_] = nullptr;
			Map[Y_][X_ + 1] = this;

			++X_;

			if (nullptr != Player_)
			{
				this->CoordinateMove(Player_, X_, Y_);
			}

			else if (nullptr != Enemy_)
			{
				this->CoordinateMove(Enemy_, X_, Y_);
			}

			return this;
		}

		else if (nullptr == Map[Y_][X_ + 1]
			&& this == Map[_Other->GetY()][_Other->GetX() + 1])
		{
			Map[Y_][X_] = nullptr;
			Map[Y_][X_ + 1] = this;

			++X_;

			if (nullptr != Player_)
			{
				this->CoordinateMove(Player_, X_, Y_);
			}

			else if (nullptr != Enemy_)
			{
				this->CoordinateMove(Enemy_, X_, Y_);
			}

			return this;
		}
	}

	return nullptr;
}


Puyo* Puyo::DownPuyo(Puyo* Map[15][6], Puyo* _Other)
{
	if (0 <= Y_ - 1)
	{
		if (nullptr != Map[Y_ - 1][X_])
		{
			return nullptr;
		}

		else if (nullptr == Map[Y_ - 1][X_])
		{
			SetMove(float4::DOWN * 60.0f);

			Map[Y_][X_] = nullptr;
			Map[Y_ - 1][X_] = this;

			--Y_;

			return this;
		}
	}

	return nullptr;
}

Puyo* Puyo::RotatePuyo(Puyo* Map[15][6], Puyo* _Center)
{
	Puyo* CenterPuyo = _Center;

	int CenterX = CenterPuyo->GetX();
	int CenterY = CenterPuyo->GetY();

	while (true)
	{
		switch (CenterPuyo->CurDir_)
		{
		case PuyoDir::UP:
			if (0 <= CenterX - 1 && nullptr == Map[CenterY][CenterX - 1])
			{
				Map[Y_][X_] = nullptr;

				Y_ = CenterY;
				X_ = CenterX - 1;

				Map[Y_][X_] = this;

				if (nullptr != Player_)
				{
					this->CoordinateMove(Player_, X_, Y_);
				}

				else if (nullptr != Enemy_)
				{
					this->CoordinateMove(Enemy_, X_, Y_);
				}

				CenterPuyo->SetDir(PuyoDir::LEFT);
			}
			else if (0 > CenterX - 1 || nullptr != Map[CenterY][CenterX - 1])
			{
				if (5 < CenterX + 1 || nullptr != Map[CenterY][CenterX + 1])
				{
					CenterPuyo->SetDir(PuyoDir::LEFT);
					continue;
				}

				Map[Y_][X_] = nullptr;
				Map[CenterY][CenterX] = nullptr;

				X_ = CenterX;
				Y_ = CenterY;

				CenterX += 1;

				Map[Y_][X_] = this;
				Map[CenterY][CenterX] = CenterPuyo;

				if (nullptr != Player_)
				{
					CenterPuyo->CoordinateMove(Player_, CenterX, CenterY);
					this->CoordinateMove(Player_, X_, Y_);
				}

				else if (nullptr != Enemy_)
				{
					CenterPuyo->CoordinateMove(Enemy_, CenterX, CenterY);
					this->CoordinateMove(Enemy_, X_, Y_);
				}

				CenterPuyo->SetDir(PuyoDir::LEFT);
			}
			break;

		case PuyoDir::LEFT:
			if (0 <= CenterY - 1 && nullptr == Map[CenterY - 1][CenterX])
			{
				Map[Y_][X_] = nullptr;

				Y_ = CenterY - 1;
				X_ = CenterX;

				Map[Y_][X_] = this;

				if (nullptr != Player_)
				{
					this->CoordinateMove(Player_, X_, Y_);
				}

				else if (nullptr != Enemy_)
				{
					this->CoordinateMove(Enemy_, X_, Y_);
				}

				CenterPuyo->SetDir(PuyoDir::DOWN);
			}
			else if (0 > CenterY - 1 || nullptr != Map[CenterY - 1][CenterX])
			{
				if (nullptr != Map[CenterY + 1][CenterX])
				{
					CenterPuyo->SetDir(PuyoDir::DOWN);
					continue;
				}

				Map[Y_][X_] = nullptr;
				Map[CenterY][CenterX] = nullptr;

				Y_ = CenterY;
				X_ = CenterX;

				CenterY += 1;

				Map[Y_][X_] = this;
				Map[CenterY][CenterX] = CenterPuyo;

				if (nullptr != Player_)
				{
					CenterPuyo->CoordinateMove(Player_, CenterX, CenterY);
					this->CoordinateMove(Player_, X_, Y_);
				}

				else if (nullptr != Enemy_)
				{
					CenterPuyo->CoordinateMove(Enemy_, CenterX, CenterY);
					this->CoordinateMove(Enemy_, X_, Y_);
				}

				CenterPuyo->SetDir(PuyoDir::DOWN);
			}
			break;

		case PuyoDir::DOWN:
			if (5 >= CenterX + 1 && nullptr == Map[CenterY][CenterX + 1])
			{
				Map[Y_][X_] = nullptr;

				Y_ = CenterY;
				X_ = CenterX + 1;

				Map[Y_][X_] = this;

				if (nullptr != Player_)
				{
					this->CoordinateMove(Player_, X_, Y_);
				}

				else if (nullptr != Enemy_)
				{
					this->CoordinateMove(Enemy_, X_, Y_);
				}

				CenterPuyo->SetDir(PuyoDir::RIGHT);
			}
			else if (5 < CenterX + 1 || nullptr != Map[CenterY][CenterX + 1])
			{
				if (0 > CenterY - 1 || nullptr != Map[CenterY][CenterX - 1])
				{
					CenterPuyo->SetDir(PuyoDir::RIGHT);
					continue;
				}

				Map[Y_][X_] = nullptr;
				Map[CenterY][CenterX] = nullptr;

				Y_ = CenterY;
				X_ = CenterX;

				CenterX -= 1;

				Map[Y_][X_] = this;
				Map[CenterY][CenterX] = CenterPuyo;

				if (nullptr != Player_)
				{
					CenterPuyo->CoordinateMove(Player_, CenterX, CenterY);
					this->CoordinateMove(Player_, X_, Y_);
				}

				else if (nullptr != Enemy_)
				{
					CenterPuyo->CoordinateMove(Enemy_, CenterX, CenterY);
					this->CoordinateMove(Enemy_, X_, Y_);
				}

				CenterPuyo->SetDir(PuyoDir::RIGHT);
			}
			break;

		case PuyoDir::RIGHT:
			if (14 >= CenterY + 1 && nullptr == Map[CenterY + 1][CenterX])
			{
				Map[Y_][X_] = nullptr;

				Y_ = CenterY + 1;
				X_ = CenterX;

				Map[Y_][X_] = this;

				if (nullptr != Player_)
				{
					this->CoordinateMove(Player_, X_, Y_);
				}

				else if (nullptr != Enemy_)
				{
					this->CoordinateMove(Enemy_, X_, Y_);
				}

				CenterPuyo->SetDir(PuyoDir::UP);
			}
			break;
		}
		break;
	}

	return nullptr;
}


//_Other를 제외하고 널 체크한다
void Puyo::LandPuyo(Puyo* Map[15][6], Puyo* _Other)
{
	if (0 == Y_)
	{
		IsLand_ = true;
	}

	else if (nullptr != Map[Y_ - 1][X_]
		&& _Other != Map[Y_ - 1][X_])
	{
		IsLand_ = true;
	}

	else if (true == _Other->GetLand()
		&& nullptr != Map[Y_ - 1][X_])
	{
		IsLand_ = true;
	}
}

void Puyo::AloneFallPuyo(Puyo* Map[15][6])
{
	if (0 <= Y_ - 1 && nullptr == Map[Y_ - 1][X_])
	{
		Map[Y_][X_] = nullptr;
		Map[Y_ - 1][X_] = this;

		Y_ -= 1;

		if (nullptr != Player_)
		{
			CoordinateMove(Player_, X_, Y_);
		}

		else if (nullptr != Enemy_)
		{
			CoordinateMove(Enemy_, X_, Y_);
		}
	}
}

void Puyo::FallPuyo(Puyo* Map[15][6], Player* _Player)
{
	//if (0 == Y_ 
	//	&& PuyoColor::Hindrance != MyColor_)
	//{
	//	return;
	//}

	int Count = 0;

	for (int i = Y_; i >= 0; --i)
	{
		if (nullptr == Map[i][X_])
		{
			++Count;
		}
	}

	if (0 == Count)
	{
		return;
	}

	Alpha_ = 0.f;

	Map[Y_][X_] = nullptr;

	int PuyoCount = 0;

	for (int i = 0; i < Y_; ++i)
	{
		if (nullptr != Map[i][X_]
			&& false == Map[i][X_]->GetDestroy())
		{
			++PuyoCount;
		}
	}

	SetY(PuyoCount);

	StartPos_ = GetPosition();
	EndPos_ = CoordinatePos(_Player, X_, Y_);
	Map[Y_][X_] = this;

	ChangeState(PuyoState::Fall);
}

void Puyo::FallPuyo(Puyo* Map[15][6], EnemyFSM* _Enemy)
{
	//if (0 == Y_)
	//{
	//	return;
	//}

	int Count = 0;

	for (int i = Y_; i >= 0; --i)
	{
		if (nullptr == Map[i][X_])
		{
			++Count;
		}
	}

	if (0 == Count)
	{
		return;
	}


	Alpha_ = 0.f;

	Map[Y_][X_] = nullptr;

	int PuyoCount = 0;

	for (int i = 0; i < Y_; ++i)
	{
		if (nullptr != Map[i][X_]
			&& false == Map[i][X_]->GetDestroy())
		{
			++PuyoCount;
		}
	}

	RenderToNormal();

	SetY(PuyoCount);

	StartPos_ = GetPosition();
	EndPos_ = CoordinatePos(_Enemy, X_, Y_);
	Map[Y_][X_] = this;

	ChangeState(PuyoState::Fall);
}

void Puyo::FallingPuyo()
{
	if (PuyoColor::Hindrance == MyColor_)
	{
		Alpha_ += GameEngineTime::GetDeltaTime() * 1.5f;

		if (1.f <= Alpha_)
		{
			Alpha_ = 1.f;
		}

		SetPosition(LerpPuyo(StartPos_, EndPos_, Alpha_));

		if (1.f <= Alpha_)
		{
			ChangeState(PuyoState::Land);
		}
	}

	else
	{
		Alpha_ += GameEngineTime::GetDeltaTime() * 4;

		if (1.f <= Alpha_)
		{
			Alpha_ = 1.f;
		}

		SetPosition(LerpPuyo(StartPos_, EndPos_, Alpha_));

		if (1.f <= Alpha_)
		{
			ChangeState(PuyoState::Land);
		}

	}
}

float4 Puyo::LerpPuyo(float4 A, float4 B, float Alpha)
{
	return A * (1 - Alpha) + B * Alpha;
}



//애니메이션 관련 함수
void Puyo::RenderToNormal()
{
	switch (MyColor_)
	{
	case PuyoColor::RED:
		MyRenderer_->ChangeAnimation("IG_RED_PUYO");
		break;
	case PuyoColor::BLUE:
		MyRenderer_->ChangeAnimation("IG_BLUE_PUYO");
		break;
	case PuyoColor::GREEN:
		MyRenderer_->ChangeAnimation("IG_GREEN_PUYO");
		break;
	case PuyoColor::YELLOW:
		MyRenderer_->ChangeAnimation("IG_YELLOW_PUYO");
		break;
	case PuyoColor::PURPLE:
		MyRenderer_->ChangeAnimation("IG_PURPLE_PUYO");
		break;
	}
}

void Puyo::RenderToLeft()
{
	switch (MyColor_)
	{
	case PuyoColor::RED:
		MyRenderer_->ChangeAnimation("IG_RED_LEFT");
		break;
	case PuyoColor::BLUE:
		MyRenderer_->ChangeAnimation("IG_BLUE_LEFT");
		break;
	case PuyoColor::GREEN:
		MyRenderer_->ChangeAnimation("IG_GREEN_LEFT");
		break;
	case PuyoColor::YELLOW:
		MyRenderer_->ChangeAnimation("IG_YELLOW_LEFT");
		break;
	case PuyoColor::PURPLE:
		MyRenderer_->ChangeAnimation("IG_PURPLE_LEFT");
		break;
	}
}

void Puyo::RenderToRight()
{
	switch (MyColor_)
	{
	case PuyoColor::RED:
		MyRenderer_->ChangeAnimation("IG_RED_RIGHT");
		break;
	case PuyoColor::BLUE:
		MyRenderer_->ChangeAnimation("IG_BLUE_RIGHT");
		break;
	case PuyoColor::GREEN:
		MyRenderer_->ChangeAnimation("IG_GREEN_RIGHT");
		break;
	case PuyoColor::YELLOW:
		MyRenderer_->ChangeAnimation("IG_YELLOW_RIGHT");
		break;
	case PuyoColor::PURPLE:
		MyRenderer_->ChangeAnimation("IG_PURPLE_RIGHT");
		break;
	}
}

void Puyo::RenderToUp()
{
	switch (MyColor_)
	{
	case PuyoColor::RED:
		MyRenderer_->ChangeAnimation("IG_RED_UP");
		break;
	case PuyoColor::BLUE:
		MyRenderer_->ChangeAnimation("IG_BLUE_UP");
		break;
	case PuyoColor::GREEN:
		MyRenderer_->ChangeAnimation("IG_GREEN_UP");
		break;
	case PuyoColor::YELLOW:
		MyRenderer_->ChangeAnimation("IG_YELLOW_UP");
		break;
	case PuyoColor::PURPLE:
		MyRenderer_->ChangeAnimation("IG_PURPLE_UP");
		break;
	}
}

void Puyo::RenderToDown()
{
	switch (MyColor_)
	{
	case PuyoColor::RED:
		MyRenderer_->ChangeAnimation("IG_RED_DOWN");
		break;
	case PuyoColor::BLUE:
		MyRenderer_->ChangeAnimation("IG_BLUE_DOWN");
		break;
	case PuyoColor::GREEN:
		MyRenderer_->ChangeAnimation("IG_GREEN_DOWN");
		break;
	case PuyoColor::YELLOW:
		MyRenderer_->ChangeAnimation("IG_YELLOW_DOWN");
		break;
	case PuyoColor::PURPLE:
		MyRenderer_->ChangeAnimation("IG_PURPLE_DOWN");
		break;
	}
}

void Puyo::RenderToLeftRight()
{
	switch (MyColor_)
	{
	case PuyoColor::RED:
		MyRenderer_->ChangeAnimation("IG_RED_LEFT_RIGHT");
		break;
	case PuyoColor::BLUE:
		MyRenderer_->ChangeAnimation("IG_BLUE_LEFT_RIGHT");
		break;
	case PuyoColor::GREEN:
		MyRenderer_->ChangeAnimation("IG_GREEN_LEFT_RIGHT");
		break;
	case PuyoColor::YELLOW:
		MyRenderer_->ChangeAnimation("IG_YELLOW_LEFT_RIGHT");
		break;
	case PuyoColor::PURPLE:
		MyRenderer_->ChangeAnimation("IG_PURPLE_LEFT_RIGHT");
		break;
	}
}

void Puyo::RenderToLeftRightDown()
{
	switch (MyColor_)
	{
	case PuyoColor::RED:
		MyRenderer_->ChangeAnimation("IG_RED_LEFT_RIGHT_DOWN");
		break;
	case PuyoColor::BLUE:
		MyRenderer_->ChangeAnimation("IG_BLUE_LEFT_RIGHT_DOWN");
		break;
	case PuyoColor::GREEN:
		MyRenderer_->ChangeAnimation("IG_GREEN_LEFT_RIGHT_DOWN");
		break;
	case PuyoColor::YELLOW:
		MyRenderer_->ChangeAnimation("IG_YELLOW_LEFT_RIGHT_DOWN");
		break;
	case PuyoColor::PURPLE:
		MyRenderer_->ChangeAnimation("IG_PURPLE_LEFT_RIGHT_DOWN");
		break;
	}
}

void Puyo::RenderToLefttUp()
{
	switch (MyColor_)
	{
	case PuyoColor::RED:
		MyRenderer_->ChangeAnimation("IG_RED_LEFT_UP");
		break;
	case PuyoColor::BLUE:
		MyRenderer_->ChangeAnimation("IG_BLUE_LEFT_UP");
		break;
	case PuyoColor::GREEN:
		MyRenderer_->ChangeAnimation("IG_GREEN_LEFT_UP");
		break;
	case PuyoColor::YELLOW:
		MyRenderer_->ChangeAnimation("IG_YELLOW_LEFT_UP");
		break;
	case PuyoColor::PURPLE:
		MyRenderer_->ChangeAnimation("IG_PURPLE_LEFT_UP");
		break;
	}
}

void Puyo::RenderToLeftRightUp()
{
	switch (MyColor_)
	{
	case PuyoColor::RED:
		MyRenderer_->ChangeAnimation("IG_RED_LEFT_RIGHT_UP");
		break;
	case PuyoColor::BLUE:
		MyRenderer_->ChangeAnimation("IG_BLUE_LEFT_RIGHT_UP");
		break;
	case PuyoColor::GREEN:
		MyRenderer_->ChangeAnimation("IG_GREEN_LEFT_RIGHT_UP");
		break;
	case PuyoColor::YELLOW:
		MyRenderer_->ChangeAnimation("IG_YELLOW_LEFT_RIGHT_UP");
		break;
	case PuyoColor::PURPLE:
		MyRenderer_->ChangeAnimation("IG_PURPLE_LEFT_RIGHT_UP");
		break;
	}
}

void Puyo::RenderToLeftUpDown()
{
	switch (MyColor_)
	{
	case PuyoColor::RED:
		MyRenderer_->ChangeAnimation("IG_RED_LEFT_UP_DOWN");
		break;
	case PuyoColor::BLUE:
		MyRenderer_->ChangeAnimation("IG_BLUE_LEFT_UP_DOWN");
		break;
	case PuyoColor::GREEN:
		MyRenderer_->ChangeAnimation("IG_GREEN_LEFT_UP_DOWN");
		break;
	case PuyoColor::YELLOW:
		MyRenderer_->ChangeAnimation("IG_YELLOW_LEFT_UP_DOWN");
		break;
	case PuyoColor::PURPLE:
		MyRenderer_->ChangeAnimation("IG_PURPLE_LEFT_UP_DOWN");
		break;
	}
}

void Puyo::RenderToLeftDown()
{
	switch (MyColor_)
	{
	case PuyoColor::RED:
		MyRenderer_->ChangeAnimation("IG_RED_LEFT_DOWN");
		break;
	case PuyoColor::BLUE:
		MyRenderer_->ChangeAnimation("IG_BLUE_LEFT_DOWN");
		break;
	case PuyoColor::GREEN:
		MyRenderer_->ChangeAnimation("IG_GREEN_LEFT_DOWN");
		break;
	case PuyoColor::YELLOW:
		MyRenderer_->ChangeAnimation("IG_YELLOW_LEFT_DOWN");
		break;
	case PuyoColor::PURPLE:
		MyRenderer_->ChangeAnimation("IG_PURPLE_LEFT_DOWN");
		break;
	}
}

void Puyo::RenderToRightUp()
{
	switch (MyColor_)
	{
	case PuyoColor::RED:
		MyRenderer_->ChangeAnimation("IG_RED_RIGHT_UP");
		break;
	case PuyoColor::BLUE:
		MyRenderer_->ChangeAnimation("IG_BLUE_RIGHT_UP");
		break;
	case PuyoColor::GREEN:
		MyRenderer_->ChangeAnimation("IG_GREEN_RIGHT_UP");
		break;
	case PuyoColor::YELLOW:
		MyRenderer_->ChangeAnimation("IG_YELLOW_RIGHT_UP");
		break;
	case PuyoColor::PURPLE:
		MyRenderer_->ChangeAnimation("IG_PURPLE_RIGHT_UP");
		break;
	}
}

void Puyo::RenderToRightUpDown()
{
	switch (MyColor_)
	{
	case PuyoColor::RED:
		MyRenderer_->ChangeAnimation("IG_RED_RIGHT_UP_DOWN");
		break;
	case PuyoColor::BLUE:
		MyRenderer_->ChangeAnimation("IG_BLUE_RIGHT_UP_DOWN");
		break;
	case PuyoColor::GREEN:
		MyRenderer_->ChangeAnimation("IG_GREEN_RIGHT_UP_DOWN");
		break;
	case PuyoColor::YELLOW:
		MyRenderer_->ChangeAnimation("IG_YELLOW_RIGHT_UP_DOWN");
		break;
	case PuyoColor::PURPLE:
		MyRenderer_->ChangeAnimation("IG_PURPLE_RIGHT_UP_DOWN");
		break;
	}
}

void Puyo::RenderToRightDown()
{
	switch (MyColor_)
	{
	case PuyoColor::RED:
		MyRenderer_->ChangeAnimation("IG_RED_RIGHT_DOWN");
		break;
	case PuyoColor::BLUE:
		MyRenderer_->ChangeAnimation("IG_BLUE_RIGHT_DOWN");
		break;
	case PuyoColor::GREEN:
		MyRenderer_->ChangeAnimation("IG_GREEN_RIGHT_DOWN");
		break;
	case PuyoColor::YELLOW:
		MyRenderer_->ChangeAnimation("IG_YELLOW_RIGHT_DOWN");
		break;
	case PuyoColor::PURPLE:
		MyRenderer_->ChangeAnimation("IG_PURPLE_RIGHT_DOWN");
		break;
	}
}

void Puyo::RenderToUpDown()
{
	switch (MyColor_)
	{
	case PuyoColor::RED:
		MyRenderer_->ChangeAnimation("IG_RED_UP_DOWN");
		break;
	case PuyoColor::BLUE:
		MyRenderer_->ChangeAnimation("IG_BLUE_UP_DOWN");
		break;
	case PuyoColor::GREEN:
		MyRenderer_->ChangeAnimation("IG_GREEN_UP_DOWN");
		break;
	case PuyoColor::YELLOW:
		MyRenderer_->ChangeAnimation("IG_YELLOW_UP_DOWN");
		break;
	case PuyoColor::PURPLE:
		MyRenderer_->ChangeAnimation("IG_PURPLE_UP_DOWN");
		break;
	}
}

void Puyo::RenderToLeftRightUpDown()
{
	switch (MyColor_)
	{
	case PuyoColor::RED:
		MyRenderer_->ChangeAnimation("IG_RED_LEFT_RIGHT_UP_DOWN");
		break;
	case PuyoColor::BLUE:
		MyRenderer_->ChangeAnimation("IG_BLUE_LEFT_RIGHT_UP_DOWN");
		break;
	case PuyoColor::GREEN:
		MyRenderer_->ChangeAnimation("IG_GREEN_LEFT_RIGHT_UP_DOWN");
		break;
	case PuyoColor::YELLOW:
		MyRenderer_->ChangeAnimation("IG_YELLOW_LEFT_RIGHT_UP_DOWN");
		break;
	case PuyoColor::PURPLE:
		MyRenderer_->ChangeAnimation("IG_PURPLE_LEFT_RIGHT_UP_DOWN");
		break;
	}
}

void Puyo::RenderToDestroy()
{
	switch (MyColor_)
	{
	case PuyoColor::RED:
		MyRenderer_->ChangeAnimation("IG_RED_DESTROY");
		break;
	case PuyoColor::BLUE:
		MyRenderer_->ChangeAnimation("IG_BLUE_DESTROY");
		break;
	case PuyoColor::GREEN:
		MyRenderer_->ChangeAnimation("IG_GREEN_DESTROY");
		break;
	case PuyoColor::YELLOW:
		MyRenderer_->ChangeAnimation("IG_YELLOW_DESTROY");
		break;
	case PuyoColor::PURPLE:
		MyRenderer_->ChangeAnimation("IG_PURPLE_DESTROY");
		break;
	case PuyoColor::Hindrance:
		MyRenderer_->ChangeAnimation("IG_HINDRANCE_PUYO_DESTROY");
		break;
	}
}

void Puyo::RandomIdleAnimation()
{
	NormalTime_ += GameEngineTime::GetDeltaTime();

	if (NormalTime_ >= IdleTime_)
	{
		IsIdle_ = true;
	}

	if (true == IsIdle_)
	{
		IsIdle_ = false;
		NormalTime_ = 0.f;
		IdleTime_ = Random_.RandomFloat(5.f, 15.f);

		int Rand = Random_.RandomInt(0, 1);

		if (0 == Rand)
		{
			RenderToIdle();
		}

		else
		{
			RenderToOtherIdle();
		}
	}
}

void Puyo::RenderToIdle()
{
	switch (MyColor_)
	{
	case PuyoColor::RED:
		MyRenderer_->ChangeAnimation("IG_RED_IDLE");
		break;
	case PuyoColor::BLUE:
		MyRenderer_->ChangeAnimation("IG_BLUE_IDLE");
		break;
	case PuyoColor::GREEN:
		MyRenderer_->ChangeAnimation("IG_GREEN_IDLE");
		break;
	case PuyoColor::YELLOW:
		MyRenderer_->ChangeAnimation("IG_YELLOW_IDLE");
		break;
	case PuyoColor::PURPLE:
		MyRenderer_->ChangeAnimation("IG_PURPLE_IDLE");
		break;
	case PuyoColor::Hindrance:
		MyRenderer_->ChangeAnimation("IG_HINDRANCE_PUYO_IDLE");
		break;
	}
}

void Puyo::RenderToOtherIdle()
{
	switch (MyColor_)
	{
	case PuyoColor::RED:
		MyRenderer_->ChangeAnimation("IG_RED_IDLE1");
		break;
	case PuyoColor::BLUE:
		MyRenderer_->ChangeAnimation("IG_BLUE_IDLE1");
		break;
	case PuyoColor::GREEN:
		MyRenderer_->ChangeAnimation("IG_GREEN_IDLE1");
		break;
	case PuyoColor::YELLOW:
		MyRenderer_->ChangeAnimation("IG_YELLOW_IDLE1");
		break;
	case PuyoColor::PURPLE:
		MyRenderer_->ChangeAnimation("IG_PURPLE_IDLE1");
		break;
	case PuyoColor::Hindrance:
		MyRenderer_->ChangeAnimation("IG_HINDRANCE_PUYO_IDLE");
		break;
	}
}


void Puyo::IdleToNomal()
{
	switch (MyColor_)
	{
	case PuyoColor::RED:
		if (true == MyRenderer_->IsEndAnimation()
			&& true == MyRenderer_->IsAnimationName("IG_RED_IDLE"))
		{
			MyRenderer_->ChangeAnimation("IG_RED_PUYO");
		}

		else if (true == MyRenderer_->IsEndAnimation()
			&& true == MyRenderer_->IsAnimationName("IG_RED_IDLE1"))
		{
			MyRenderer_->ChangeAnimation("IG_RED_PUYO");
		}
		break;
	case PuyoColor::BLUE:
		if (true == MyRenderer_->IsEndAnimation()
			&& true == MyRenderer_->IsAnimationName("IG_BLUE_IDLE"))
		{
			MyRenderer_->ChangeAnimation("IG_BLUE_PUYO");
		}

		else if (true == MyRenderer_->IsEndAnimation()
			&& true == MyRenderer_->IsAnimationName("IG_BLUE_IDLE1"))
		{
			MyRenderer_->ChangeAnimation("IG_BLUE_PUYO");
		}
		break;
	case PuyoColor::GREEN:
		if (true == MyRenderer_->IsEndAnimation()
			&& true == MyRenderer_->IsAnimationName("IG_GREEN_IDLE"))
		{
			MyRenderer_->ChangeAnimation("IG_GREEN_PUYO");
		}

		else if (true == MyRenderer_->IsEndAnimation()
			&& true == MyRenderer_->IsAnimationName("IG_GREEN_IDLE1"))
		{
			MyRenderer_->ChangeAnimation("IG_GREEN_PUYO");
		}
		break;
	case PuyoColor::YELLOW:
		if (true == MyRenderer_->IsEndAnimation()
			&& true == MyRenderer_->IsAnimationName("IG_YELLOW_IDLE"))
		{
			MyRenderer_->ChangeAnimation("IG_YELLOW_PUYO");
		}

		else if (true == MyRenderer_->IsEndAnimation()
			&& true == MyRenderer_->IsAnimationName("IG_YELLOW_IDLE1"))
		{
			MyRenderer_->ChangeAnimation("IG_YELLOW_PUYO");
		}
		break;
	case PuyoColor::PURPLE:
		if (true == MyRenderer_->IsEndAnimation()
			&& true == MyRenderer_->IsAnimationName("IG_PURPLE_IDLE"))
		{
			MyRenderer_->ChangeAnimation("IG_PURPLE_PUYO");
		}

		else if (true == MyRenderer_->IsEndAnimation()
			&& true == MyRenderer_->IsAnimationName("IG_PURPLE_IDLE1"))
		{
			MyRenderer_->ChangeAnimation("IG_PURPLE_PUYO");
		}
		break;
	case PuyoColor::Hindrance:
		if (true == MyRenderer_->IsEndAnimation()
			&& true == MyRenderer_->IsAnimationName("IG_HINDRANCE_PUYO_IDLE"))
		{
			MyRenderer_->ChangeAnimation("IG_HINDRANCE_PUYO");
		}
		break;
	}
}

void Puyo::RenderToLand()
{
	switch (MyColor_)
	{
	case PuyoColor::RED:
		MyRenderer_->ChangeAnimation("IG_RED_LAND");
		break;
	case PuyoColor::BLUE:
		MyRenderer_->ChangeAnimation("IG_BLUE_LAND");
		break;
	case PuyoColor::GREEN:
		MyRenderer_->ChangeAnimation("IG_GREEN_LAND");
		break;
	case PuyoColor::YELLOW:
		MyRenderer_->ChangeAnimation("IG_YELLOW_LAND");
		break;
	case PuyoColor::PURPLE:
		MyRenderer_->ChangeAnimation("IG_PURPLE_LAND");
		break;
	}
}

void Puyo::LandToNormal()
{
	switch (MyColor_)
	{
	case PuyoColor::RED:
		if (true == MyRenderer_->IsAnimationName("IG_RED_LAND"))
		{
			if (true == MyRenderer_->IsEndAnimation())
			{
				MyRenderer_->ChangeAnimation("IG_RED_PUYO");
				PuyoState_ = PuyoState::Normal;
			}
		}
		break;
	case PuyoColor::BLUE:
		if (true == MyRenderer_->IsAnimationName("IG_BLUE_LAND"))
		{
			if (true == MyRenderer_->IsEndAnimation())
			{
				MyRenderer_->ChangeAnimation("IG_BLUE_PUYO");
				PuyoState_ = PuyoState::Normal;
			}
		}
		break;
	case PuyoColor::GREEN:
		if (true == MyRenderer_->IsAnimationName("IG_GREEN_LAND"))
		{
			if (true == MyRenderer_->IsEndAnimation())
			{
				MyRenderer_->ChangeAnimation("IG_GREEN_PUYO");
				PuyoState_ = PuyoState::Normal;
			}
		}
		break;
	case PuyoColor::YELLOW:
		if (true == MyRenderer_->IsAnimationName("IG_YELLOW_LAND"))
		{
			if (true == MyRenderer_->IsEndAnimation())
			{
				MyRenderer_->ChangeAnimation("IG_YELLOW_PUYO");
				PuyoState_ = PuyoState::Normal;
			}
		}
		break;
	case PuyoColor::PURPLE:
		if (true == MyRenderer_->IsAnimationName("IG_PURPLE_LAND"))
		{
			if (true == MyRenderer_->IsEndAnimation())
			{
				MyRenderer_->ChangeAnimation("IG_PURPLE_PUYO");
				PuyoState_ = PuyoState::Normal;
			}
		}
		break;
	case PuyoColor::Hindrance:
		IsLand_ = true;
		PuyoState_ = PuyoState::Normal;
		break;

	}
}

void Puyo::SelfDestroy()
{
	switch (MyColor_)
	{
	case PuyoColor::RED:
		if (true == MyRenderer_->IsAnimationName("IG_RED_DESTROY"))
		{
			if (true == MyRenderer_->IsEndAnimation())
			{
				Death();
			}
		}
		break;
	case PuyoColor::BLUE:
		if (true == MyRenderer_->IsAnimationName("IG_BLUE_DESTROY"))
		{
			if (true == MyRenderer_->IsEndAnimation())
			{
				Death();
			}
		}
		break;
	case PuyoColor::GREEN:
	{
		if (true == MyRenderer_->IsEndAnimation())
		{
			Death();
		}
	}
	break;
	case PuyoColor::YELLOW:
		if (true == MyRenderer_->IsAnimationName("IG_YELLOW_DESTROY"))
		{
			if (true == MyRenderer_->IsEndAnimation())
			{
				Death();
			}
		}
		break;
	case PuyoColor::PURPLE:
		if (true == MyRenderer_->IsAnimationName("IG_PURPLE_DESTROY"))
		{
			if (true == MyRenderer_->IsEndAnimation())
			{
				Death();
			}
		}
		break;
	case PuyoColor::Hindrance:
		if (true == MyRenderer_->IsAnimationName("IG_HINDRANCE_PUYO_DESTROY"))
		{
			if (true == MyRenderer_->IsEndAnimation())
			{
				Death();
			}
		}
		break;
	}
}


void Puyo::LinkedPuyoAnimtaion(Puyo* Map[15][6])
{
	int Value = GradeLinkAnimation(Map);

	if (0 == Value)
	{
		ChangeState(PuyoState::Normal);
		return;
	}

	switch (Value)
	{
		//우
	case 1:
		RenderToRight();
		break;

		//좌
	case 10:
		RenderToLeft();
		break;

		//좌우
	case 11:
		RenderToLeftRight();
		break;

		//하
	case 100:
		RenderToDown();
		break;

		//하좌
	case 110:
		RenderToLeftDown();
		break;

		//하우
	case 101:
		RenderToRightDown();
		break;

		//하좌우
	case 111:
		RenderToLeftRightDown();
		break;

		//상
	case 1000:
		RenderToUp();
		break;

		//상하
	case 1100:
		RenderToUpDown();
		break;

		//상하좌
	case 1110:
		RenderToLeftUpDown();
		break;

		//상하우
	case 1101:
		RenderToRightUpDown();
		break;

		//상좌
	case 1010:
		RenderToLefttUp();
		break;

		//상우
	case 1001:
		RenderToRightUp();
		break;

		//상좌우
	case 1011:
		RenderToLeftRightUp();
		break;

		//상하좌우
	case 1111:
		RenderToLeftRightUpDown();
		break;
	}

	ChangeState(PuyoState::Linked);
}

int Puyo::GradeLinkAnimation(Puyo* Map[15][6])
{
	int Value = 0;

	int Dx[4] = { 1, -1, 0, 0 };
	int Dy[4] = { 0, 0, 1, -1 };

	for (int i = 0; i < 4; ++i)
	{
		int X = Dx[i] + X_;
		int Y = Dy[i] + Y_;

		if (0 > X || 0 > Y || 6 <= X || 15 <= Y)
		{
			continue;
		}

		if (nullptr == Map[Y][X])
		{
			continue;
		}

		if (MyColor_ == Map[Y][X]->GetColor()
			&& false == Map[Y][X]->GetIsNewPuyo())
		{
			if (1 == Dx[i])
			{
				Value += 1;
			}

			if (-1 == Dx[i])
			{
				Value += 10;
			}

			if (-1 == Dy[i])
			{
				Value += 100;
			}

			if (1 == Dy[i])
			{
				Value += 1000;
			}
		}
	}

	return Value;
}

void Puyo::LoseFall()
{
	if (false == IsLoseFall_)
	{
		IsLoseFall_ = true;

		Alpha_ = 0.f;
		StartPos_ = GetPosition();
		EndPos_ = GetPosition() + float4{ 0, 2000 };
	}

	Alpha_ += GameEngineTime::GetDeltaTime() * 0.5f;

	if (1.f <= Alpha_)
	{
		Alpha_ = 1.f;
		Death();
	}

	SetPosition(float4::Lerp(StartPos_, EndPos_, Alpha_));
}

void Puyo::TwinklePuyo()
{
	++TwinkleCount_;

	if (0 == TwinkleCount_ % 2)
	{
		TwinkleCount_ = 0;
		MyRenderer_->SetOrder(1);
	}

	else
	{
	 	MyRenderer_->SetOrder(-1);
	}
}

void Puyo::DestroyEffect()
{
	if (false == IsEffectOn_ 
		&& PuyoColor::Hindrance != MyColor_)
	{ 
		IsEffectOn_ = true;

		Effect_ = GetLevel()->CreateActor<PuyoDestroyEffect>();
		Effect_->SetPosition(GetPosition());
		Effect_->SetColor(MyColor_);
		Effect_->CreateEffect();
		Effect_->SetPlay(true);
	}
}


