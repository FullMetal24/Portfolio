#include "Puyo.h"
#include "ContentsEnum.h"
#include "GameEngineBase/GameEngineWindow.h"
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngine/GameEngine.h>
#include <GameEngineBase/GameEngineTime.h>
#include "Player.h"

Puyo::Puyo()
	: MyRenderer_(nullptr)
	, MyColor_(PuyoColor::RED)
	, CurDir_(PuyoDir::UP)
	, X_(0)
	, Y_(0)
	, OffsetX_(0)
	, IsLand_(false)
	, IsVisited_(false)
	, IsLandPlay_(false)
	, IsDestroy_(false)
	, IsFall_(false)
	, IsConnect_{ false }
	, LandAnimationEnd_(false)
{
}

Puyo::~Puyo()
{
}

void Puyo::Start()
{
}

void Puyo::Update()
{
	LandAnimation();
	LandToNormal();

	SelfDestroy();
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
		MyRenderer_->CreateAnimation("IG_RED_LAND.bmp", "IG_RED_LAND", 0, 1, 0.1f, false);
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

		MyRenderer_->ChangeAnimation("IG_RED_PUYO");
		break;

	case PuyoColor::BLUE:
		MyRenderer_->CreateAnimation("IG_BLUE_PUYO.bmp", "IG_BLUE_PUYO", 0, 0, 0.f, false);
		MyRenderer_->CreateAnimation("IG_BLUE_CENTER.bmp", "IG_BLUE_CENTER", 0, 1, 0.1f, true);
		MyRenderer_->CreateAnimation("IG_BLUE_LAND.bmp", "IG_BLUE_LAND", 0, 1, 0.1f, false);
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

		MyRenderer_->ChangeAnimation("IG_BLUE_PUYO");
		break;
	case PuyoColor::GREEN:
		MyRenderer_->CreateAnimation("IG_GREEN_PUYO.bmp", "IG_GREEN_PUYO", 0, 0, 0.f, false);
		MyRenderer_->CreateAnimation("IG_GREEN_CENTER.bmp", "IG_GREEN_CENTER", 0, 1, 0.1f, true);
		MyRenderer_->CreateAnimation("IG_GREEN_LAND.bmp", "IG_GREEN_LAND", 0, 1, 0.1f, false);
		MyRenderer_->CreateAnimation("IG_GREEN_DESTROY.bmp", "IG_GREEN_DESTROY", 0, 5, 0.1f, false);

		MyRenderer_->CreateAnimation("IG_GREEN_LEFT.bmp", "IG_GREEN_LEFT", 0, 0, 0.f, false);
		MyRenderer_->CreateAnimation("IG_GREEN_RIGHT.bmp", "IG_GREEN_RIGHT", 0, 0, 0.f, false);
		MyRenderer_->CreateAnimation("IG_GREEN_UP.bmp", "IG_GREEN_UP", 0, 0, 0.f, false);
		MyRenderer_->CreateAnimation("IG_GREEN_DOWN.bmp", "IG_GREEN_DOWN", 0, 0, 0.f, false);

		MyRenderer_->CreateAnimation("IG_GREEN_LEFT_RIGHT.bmp", "IG_GREEN_LEFT_RIGHT", 0, 0, 0.f, false);
		MyRenderer_->CreateAnimation("IG_GREEN_LFET_RIGHT_UP.bmp", "IG_GREEN_LFET_RIGHT_UP", 0, 0, 0.f, false);
		MyRenderer_->CreateAnimation("IG_GREEN_LEFT_RIGHT_DOWN.bmp", "IG_GREEN_LEFT_RIGHT_DOWN", 0, 0, 0.f, false);
		MyRenderer_->CreateAnimation("IG_GREEN_LEFT_RIGHT_UP_DOWN.bmp", "IG_GREEN_LEFT_RIGHT_UP_DOWN", 0, 0, 0.f, false);
		MyRenderer_->CreateAnimation("IG_GREEN_LEFT_UP.bmp", "IG_GREEN_LEFT_UP", 0, 0, 0.f, false);
		MyRenderer_->CreateAnimation("IG_GREEN_LEFT_UP_DOWN.bmp", "IG_GREEN_LEFT_UP_DOWN", 0, 0, 0.f, false);
		MyRenderer_->CreateAnimation("IG_GREEN_LEFT_DOWN.bmp", "IG_GREEN_LEFT_DOWN", 0, 0, 0.f, false);

		MyRenderer_->CreateAnimation("IG_GREEN_RIGHT_UP.bmp", "IG_GREEN_RIGHT_UP", 0, 0, 0.f, false);
		MyRenderer_->CreateAnimation("IG_GREEN_RIGHT_DOWN.bmp", "IG_GREEN_RIGHT_DOWN", 0, 0, 0.f, false);
		MyRenderer_->CreateAnimation("IG_GREEN_RIGHT_UP_DOWN.bmp", "IG_GREEN_RIGHT_UP_DOWN", 0, 0, 0.f, false);

		MyRenderer_->CreateAnimation("IG_GREEN_UP_DOWN.bmp", "IG_GREEN_UP_DOWN", 0, 0, 0.f, false);

		MyRenderer_->ChangeAnimation("IG_GREEN_PUYO");
		break;
	case PuyoColor::YELLOW:
		MyRenderer_->CreateAnimation("IG_YELLOW_PUYO.bmp", "IG_YELLOW_PUYO", 0, 0, 0.f, false);
		MyRenderer_->CreateAnimation("IG_YELLOW_CENTER.bmp", "IG_YELLOW_CENTER", 0, 1, 0.1f, true);
		MyRenderer_->CreateAnimation("IG_YELLOW_LAND.bmp", "IG_YELLOW_LAND", 0, 1, 0.1f, false);
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

		MyRenderer_->ChangeAnimation("IG_YELLOW_PUYO");
		break;
	case PuyoColor::PURPLE:
		MyRenderer_->CreateAnimation("IG_PURPLE_PUYO.bmp", "IG_PURPLE_PUYO", 0, 0, 0.f, false);
		MyRenderer_->CreateAnimation("IG_PURPLE_CENTER.bmp", "IG_PURPLE_CENTER", 0, 1, 0.1f, true);
		MyRenderer_->CreateAnimation("IG_PURPLE_LAND.bmp", "IG_PURPLE_LAND", 0, 1, 0.1f, false);
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

		MyRenderer_->ChangeAnimation("IG_PURPLE_PUYO");
		break;
	}
}

void Puyo::InitAllAnimation()
{
	MyRenderer_ = CreateRenderer();

	MyRenderer_->CreateAnimation("IG_RED_PUYO.bmp", "IG_RED_PUYO", 0, 0, 0.f, false);
	MyRenderer_->CreateAnimation("IG_RED_CENTER.bmp", "IG_RED_CENTER", 0, 1, 0.1f, true);
	MyRenderer_->CreateAnimation("IG_RED_LAND.bmp", "IG_RED_LAND", 0, 1, 0.1f, false);
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
	MyRenderer_->CreateAnimation("IG_BLUE_LAND.bmp", "IG_BLUE_LAND", 0, 1, 0.1f, false);
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
	MyRenderer_->CreateAnimation("IG_GREEN_LAND.bmp", "IG_GREEN_LAND", 0, 1, 0.1f, false);
	MyRenderer_->CreateAnimation("IG_GREEN_DESTROY.bmp", "IG_GREEN_DESTROY", 0, 5, 0.1f, false);

	MyRenderer_->CreateAnimation("IG_GREEN_LEFT.bmp", "IG_GREEN_LEFT", 0, 0, 0.f, false);
	MyRenderer_->CreateAnimation("IG_GREEN_RIGHT.bmp", "IG_GREEN_RIGHT", 0, 0, 0.f, false);
	MyRenderer_->CreateAnimation("IG_GREEN_UP.bmp", "IG_GREEN_UP", 0, 0, 0.f, false);
	MyRenderer_->CreateAnimation("IG_GREEN_DOWN.bmp", "IG_GREEN_DOWN", 0, 0, 0.f, false);

	MyRenderer_->CreateAnimation("IG_GREEN_LEFT_RIGHT.bmp", "IG_GREEN_LEFT_RIGHT", 0, 0, 0.f, false);
	MyRenderer_->CreateAnimation("IG_GREEN_LFET_RIGHT_UP.bmp", "IG_GREEN_LFET_RIGHT_UP", 0, 0, 0.f, false);
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
	MyRenderer_->CreateAnimation("IG_YELLOW_LAND.bmp", "IG_YELLOW_LAND", 0, 1, 0.1f, false);
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
	MyRenderer_->CreateAnimation("IG_PURPLE_LAND.bmp", "IG_PURPLE_LAND", 0, 1, 0.1f, false);
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

void  Puyo::CoordinateMove(Player* _Player, int x, int y)
{
	SetIndex(x, y);
	SetPosition(_Player->GetPosition() + float4{ static_cast<float>((x * 65)), static_cast<float>(y * -60) });
}

float4 Puyo::CoordinatePos(Player* _Player, int x, int y)
{
	return float4{ _Player->GetPosition() + float4{ static_cast<float>((x * 65)), static_cast<float>(y * -60) } };
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

			SetMove(float4::LEFT * 65.0f);

			--X_;
			return this;
		}

		else if (nullptr == Map[Y_][X_ - 1]
			&& this == Map[_Other->GetY()][_Other->GetX() - 1])
		{
			Map[Y_][X_] = nullptr;
			Map[Y_][X_ - 1] = this;

			SetMove(float4::LEFT * 65.0f);

			--X_;
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

			SetMove(float4::RIGHT * 65.0f);

			++X_;
			return this;
		}

		else if (nullptr == Map[Y_][X_ + 1]
			&& this == Map[_Other->GetY()][_Other->GetX() + 1])
		{
			Map[Y_][X_] = nullptr;
			Map[Y_][X_ + 1] = this;

			SetMove(float4::RIGHT * 65.0f);

			++X_;
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

				SetPosition(CenterPuyo->GetPosition() + float4{ -65.0f, 0.0f });

				CenterPuyo->SetDir(PuyoDir::LEFT);
			}
			else if (0 > CenterX - 1)
			{
				if (nullptr != Map[CenterY][CenterX + 1])
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

				CenterPuyo->CoordinateMove(Player_, CenterX, CenterY);
				this->CoordinateMove(Player_, X_, Y_);

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
				SetPosition(CenterPuyo->GetPosition() + float4{ 0.f, 65.0f });

				CenterPuyo->SetDir(PuyoDir::DOWN);
			}
			else if (0 > CenterY - 1)
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

				CenterPuyo->CoordinateMove(Player_, CenterX, CenterY);
				this->CoordinateMove(Player_, X_, Y_);

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
				SetPosition(CenterPuyo->GetPosition() + float4{ 65.f, 0.f });

				CenterPuyo->SetDir(PuyoDir::RIGHT);
			}
			else if (5 < CenterX + 1)
			{
				if (nullptr != Map[CenterY + 1][CenterX])
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

				CenterPuyo->CoordinateMove(Player_, CenterX, CenterY);
				this->CoordinateMove(Player_, X_, Y_);

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
				SetPosition(CenterPuyo->GetPosition() + float4{ 0.f, -65.0f });

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
		CoordinateMove(Player_, X_, Y_);
	}
}

void Puyo::FallPuyo(Puyo* Map[15][6])
{
	if (0 == Y_)
	{
		return;
	}

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
	CoordinateMove(Player_, X_, Y_);
	Map[Y_][X_] = this;
}


float4 Puyo::LerpPuyo(float4 A, float4 B, float Alpha)
{
	return A * (1 - Alpha) + B * Alpha;
}


void Puyo::Destroy(Puyo* Map[15][6])
{
	Map[Y_][X_] = nullptr;
	RenderToDestroy();
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

void Puyo::RenderToRightUpDown()
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
	IsDestroy_ = true;
	LandAnimationEnd_ = false;

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


void Puyo::LandAnimation()
{
	if (true == IsLand_ && false == IsLandPlay_)
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

		IsLandPlay_ = true;
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
				LandAnimationEnd_ = true;
			}
		}
		break;
	case PuyoColor::BLUE:
		if (true == MyRenderer_->IsAnimationName("IG_BLUE_LAND"))
		{
			if (true == MyRenderer_->IsEndAnimation())
			{
				MyRenderer_->ChangeAnimation("IG_BLUE_PUYO");
				LandAnimationEnd_ = true;
			}
		}
		break;
	case PuyoColor::GREEN:
		if (true == MyRenderer_->IsAnimationName("IG_GREEN_LAND"))
		{
			if (true == MyRenderer_->IsEndAnimation())
			{
				MyRenderer_->ChangeAnimation("IG_GREEN_PUYO");
				LandAnimationEnd_ = true;
			}
		}
		break;
	case PuyoColor::YELLOW:
		if (true == MyRenderer_->IsAnimationName("IG_YELLOW_LAND"))
		{
			if (true == MyRenderer_->IsEndAnimation())
			{
				MyRenderer_->ChangeAnimation("IG_YELLOW_PUYO");
				LandAnimationEnd_ = true;
			}
		}
		break;
	case PuyoColor::PURPLE:
		if (true == MyRenderer_->IsAnimationName("IG_PURPLE_LAND"))
		{
			if (true == MyRenderer_->IsEndAnimation())
			{
				MyRenderer_->ChangeAnimation("IG_PURPLE_PUYO");
				LandAnimationEnd_ = true;
			}
		}
		break;
	}

}

void Puyo::SelfDestroy()
{
	if (true == IsDestroy_)
	{
		switch (MyColor_)
		{
		case PuyoColor::RED:
			if (true == MyRenderer_->IsAnimationName("IG_RED_DESTROY"))
			{
				if (true == MyRenderer_->IsEndAnimation())
				{
					DestroyAnimationEnd_ = true;
					Death();
				}
			}
			break;
		case PuyoColor::BLUE:
			if (true == MyRenderer_->IsAnimationName("IG_BLUE_DESTROY"))
			{
				if (true == MyRenderer_->IsEndAnimation())
				{
					DestroyAnimationEnd_ = true;
					Death();
				}
			}
			break;
		case PuyoColor::GREEN:
		{
			if (true == MyRenderer_->IsEndAnimation())
			{
				DestroyAnimationEnd_ = true;
				Death();
			}
		}
		break;
		case PuyoColor::YELLOW:
			if (true == MyRenderer_->IsAnimationName("IG_YELLOW_DESTROY"))
			{
				if (true == MyRenderer_->IsEndAnimation())
				{
					DestroyAnimationEnd_ = true;
					Death();
				}
			}
			break;
		case PuyoColor::PURPLE:
			if (true == MyRenderer_->IsAnimationName("IG_PURPLE_DESTROY"))
			{
				if (true == MyRenderer_->IsEndAnimation())
				{
					DestroyAnimationEnd_ = true;
					Death();
				}
			}
			break;
		}
	}
}


void Puyo::LinkedPuyoAnimtaion(Puyo* Map[15][6])
{
	int Value = GradeLinkAnimation(Map);

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
}

int Puyo::GradeLinkAnimation(Puyo* Map[15][6])
{
	int INumber = 0;
	bool* ConnectPtr = GetConnect();

	if (Y_ - 1 < 0 || 14 < Y_ + 1
		&& X_ - 1 < 0 || X_ + 1 > 5)
	{
		return 0;
	}

	if (nullptr != Map[Y_][X_ - 1]
		&& MyColor_ == Map[Y_][X_ - 1]->GetColor())
	{
		INumber += 10;
		SetConnect(static_cast<int>(PuyoDir::LEFT), true);

		if (true == ConnectPtr[static_cast<int>(PuyoDir::RIGHT)])
		{
			++INumber;
			SetConnect(static_cast<int>(PuyoDir::RIGHT), true);
		}

		else if (true == ConnectPtr[static_cast<int>(PuyoDir::DOWN)])
		{
			INumber += 100;
			SetConnect(static_cast<int>(PuyoDir::DOWN), true);
		}

		else if (true == ConnectPtr[static_cast<int>(PuyoDir::UP)])
		{
			INumber += 1000;
			SetConnect(static_cast<int>(PuyoDir::UP), true);
		}

		return INumber;
	}

	else if (nullptr != Map[Y_][X_ + 1]
		&& MyColor_ == Map[Y_][X_ + 1]->GetColor())
	{
		++INumber;
		SetConnect(static_cast<int>(PuyoDir::RIGHT), true);

		if (true == ConnectPtr[static_cast<int>(PuyoDir::LEFT)])
		{
			INumber += 10;
			SetConnect(static_cast<int>(PuyoDir::LEFT), true);
		}

		else if (true == ConnectPtr[static_cast<int>(PuyoDir::DOWN)])
		{
			INumber += 100;
			SetConnect(static_cast<int>(PuyoDir::DOWN), true);
		}

		else if (true == ConnectPtr[static_cast<int>(PuyoDir::UP)])
		{
			INumber += 1000;
			SetConnect(static_cast<int>(PuyoDir::UP), true);
		}

		return INumber;

	}

	else if (nullptr != Map[Y_ + 1][X_]
		&& MyColor_ == Map[Y_ + 1][X_]->GetColor())
	{
		INumber += 1000;
		SetConnect(static_cast<int>(PuyoDir::UP), true);

		if (true == ConnectPtr[static_cast<int>(PuyoDir::RIGHT)])
		{
			++INumber;
			SetConnect(static_cast<int>(PuyoDir::RIGHT), true);
		}

		else if (true == ConnectPtr[static_cast<int>(PuyoDir::LEFT)])
		{
			INumber += 10;
			SetConnect(static_cast<int>(PuyoDir::LEFT), true);
		}

		else if (true == ConnectPtr[static_cast<int>(PuyoDir::DOWN)])
		{
			INumber += 100;
			SetConnect(static_cast<int>(PuyoDir::DOWN), true);
		}

		return INumber;
	}

	else if (nullptr != Map[Y_ - 1][X_]
		&& MyColor_ == Map[Y_ - 1][X_]->GetColor())
	{
		INumber += 100;
		SetConnect(static_cast<int>(PuyoDir::DOWN), true);

		if (true == ConnectPtr[static_cast<int>(PuyoDir::RIGHT)])
		{
			++INumber;
			SetConnect(static_cast<int>(PuyoDir::RIGHT), true);
		}

		else if (true == ConnectPtr[static_cast<int>(PuyoDir::LEFT)])
		{
			INumber += 10;
			SetConnect(static_cast<int>(PuyoDir::LEFT), true);
		}

		if (true == ConnectPtr[static_cast<int>(PuyoDir::UP)])
		{
			INumber += 1000;
			SetConnect(static_cast<int>(PuyoDir::UP), true);
		}

		return INumber;
	}
}