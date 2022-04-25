#include "Puyo.h"
#include "ContentsEnum.h"
#include "GameEngineBase/GameEngineWindow.h"
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngine/GameEngineRenderer.h>
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
	, IsLanding_(false)
	, IsVisited_(false)
	, IsLandPlay_(false)
	, IsDestroy_(false)
	, IsFall_(false)
	, IsConnect_{false}
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


void Puyo::SetIndex(int _X, int _Y)
{
	SetX(_X);
	SetY(_Y);
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


//이동 관련 함수
Puyo* Puyo::LeftPuyo(Puyo* Map[15][6])
{
	if (0 <= X_ - 1)
	{
		if (nullptr != Map[Y_][X_ - 1])
		{
			return nullptr;
		}

		else if (nullptr == Map[Y_][X_ - 1])
		{
			Map[Y_][X_] = nullptr;
			Map[Y_][X_ - 1] = this;

			SetMove(float4::LEFT * 65.0f);

			--X_;
			return this;
		}
	}
}

Puyo* Puyo::RightPuyo(Puyo* Map[15][6])
{
	if (5 >= X_ + 1)
	{
		if (nullptr != Map[Y_][X_ + 1])
		{
			return nullptr;
		}

		else if (nullptr == Map[Y_][X_ + 1])
		{
			Map[Y_][X_] = nullptr;
			Map[Y_][X_ + 1] = this;
			
			SetMove(float4::RIGHT * 65.0f);
			
			++X_;
			return this;
		}
	}
}

Puyo* Puyo::DownPuyo(Puyo* Map[15][6])
{
	if (0 <= Y_ - 1)
	{
		if (nullptr != Map[Y_ - 1][X_])
		{
			return nullptr;
		}

		else if (nullptr == Map[Y_ - 1][X_])
		{
			Map[Y_][X_] = nullptr;
			Map[Y_ - 1][X_] = this;

			SetMove(float4::DOWN * 60.0f);

			--Y_;
			return this;
		}
	}
}

Puyo* Puyo::RotatePuyo(Puyo* Map[15][6], Puyo* _Puyo)
{
	Puyo* CenterPuyo = _Puyo;

	switch (CurDir_)
	{
	case PuyoDir::LEFT:
		break;
	case PuyoDir::RIGHT:
		break;
	case PuyoDir::DOWN:
		break;
	case PuyoDir::UP:
		break;
	}

	return nullptr;
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
	if (true == IsLanding_ && false == IsLandPlay_)
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