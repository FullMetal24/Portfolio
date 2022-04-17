#include "Puyo.h"
#include "ContentsEnum.h"
#include "GameEngineBase/GameEngineWindow.h"
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngine.h>
#include <GameEngineBase/GameEngineTime.h>

Puyo::Puyo()
	: MyRenderer_(nullptr)
	, MyColor_(PuyoColor::RED)
	, X_(0)
	, Y_(0)
	, IsLanding_(false)
	, IsVisited_(false)
	, IsLandPlay_(false)
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
		break;
	case PuyoColor::BLUE:
		break;
	case PuyoColor::GREEN:
		break;
	case PuyoColor::YELLOW:
		break;
	case PuyoColor::PURPLE:
		break;
	}
}

void Puyo::RenderToUp()
{

	switch (MyColor_)
	{
	case PuyoColor::RED:
		break;
	case PuyoColor::BLUE:
		break;
	case PuyoColor::GREEN:
		break;
	case PuyoColor::YELLOW:
		break;
	case PuyoColor::PURPLE:
		break;
	}
}

void Puyo::RenderToDown()
{
	switch (MyColor_)
	{
	case PuyoColor::RED:
		break;
	case PuyoColor::BLUE:
		break;
	case PuyoColor::GREEN:
		break;
	case PuyoColor::YELLOW:
		break;
	case PuyoColor::PURPLE:
		break;
	}
}

void Puyo::RenderToLeftRight()
{
	switch (MyColor_)
	{
	case PuyoColor::RED:
		break;
	case PuyoColor::BLUE:
		break;
	case PuyoColor::GREEN:
		break;
	case PuyoColor::YELLOW:
		break;
	case PuyoColor::PURPLE:
		break;
	}
}

void Puyo::RenderToLeftRightDown()
{
	switch (MyColor_)
	{
	case PuyoColor::RED:
		break;
	case PuyoColor::BLUE:
		break;
	case PuyoColor::GREEN:
		break;
	case PuyoColor::YELLOW:
		break;
	case PuyoColor::PURPLE:
		break;
	}
}

void Puyo::RenderToLefttUp()
{
	switch (MyColor_)
	{
	case PuyoColor::RED:
		break;
	case PuyoColor::BLUE:
		break;
	case PuyoColor::GREEN:
		break;
	case PuyoColor::YELLOW:
		break;
	case PuyoColor::PURPLE:
		break;
	}
}

void Puyo::RenderToLeftUpRight()
{
	switch (MyColor_)
	{
	case PuyoColor::RED:
		break;
	case PuyoColor::BLUE:
		break;
	case PuyoColor::GREEN:
		break;
	case PuyoColor::YELLOW:
		break;
	case PuyoColor::PURPLE:
		break;
	}
}

void Puyo::RenderToLeftUpDown()
{
	switch (MyColor_)
	{
	case PuyoColor::RED:
		break;
	case PuyoColor::BLUE:
		break;
	case PuyoColor::GREEN:
		break;
	case PuyoColor::YELLOW:
		break;
	case PuyoColor::PURPLE:
		break;
	}
}

void Puyo::RenderToLeftDown()
{
	switch (MyColor_)
	{
	case PuyoColor::RED:
		break;
	case PuyoColor::BLUE:
		break;
	case PuyoColor::GREEN:
		break;
	case PuyoColor::YELLOW:
		break;
	case PuyoColor::PURPLE:
		break;
	}
}

void Puyo::RenderToRightUp()
{
	switch (MyColor_)
	{
	case PuyoColor::RED:
		break;
	case PuyoColor::BLUE:
		break;
	case PuyoColor::GREEN:
		break;
	case PuyoColor::YELLOW:
		break;
	case PuyoColor::PURPLE:
		break;
	}
}

void Puyo::RenderToRightUpDown()
{
	switch (MyColor_)
	{
	case PuyoColor::RED:
		break;
	case PuyoColor::BLUE:
		break;
	case PuyoColor::GREEN:
		break;
	case PuyoColor::YELLOW:
		break;
	case PuyoColor::PURPLE:
		break;
	}
}

void Puyo::RenderToRightDown()
{
	switch (MyColor_)
	{
	case PuyoColor::RED:
		break;
	case PuyoColor::BLUE:
		break;
	case PuyoColor::GREEN:
		break;
	case PuyoColor::YELLOW:
		break;
	case PuyoColor::PURPLE:
		break;
	}
}

void Puyo::RenderToUpDown()
{
	switch (MyColor_)
	{
	case PuyoColor::RED:
		break;
	case PuyoColor::BLUE:
		break;
	case PuyoColor::GREEN:
		break;
	case PuyoColor::YELLOW:
		break;
	case PuyoColor::PURPLE:
		break;
	}
}

void Puyo::RenderToLeftRightUpDown()
{
	switch (MyColor_)
	{
	case PuyoColor::RED:
		break;
	case PuyoColor::BLUE:
		break;
	case PuyoColor::GREEN:
		break;
	case PuyoColor::YELLOW:
		break;
	case PuyoColor::PURPLE:
		break;
	}
}

void Puyo::RenderToLand()
{
	switch (MyColor_)
	{
	case PuyoColor::RED:
		break;
	case PuyoColor::BLUE:
		break;
	case PuyoColor::GREEN:
		break;
	case PuyoColor::YELLOW:
		break;
	case PuyoColor::PURPLE:
		break;
	}
}

void Puyo::RenderToDestroy()
{
	switch (MyColor_)
	{
	case PuyoColor::RED:
		break;
	case PuyoColor::BLUE:
		break;
	case PuyoColor::GREEN:
		break;
	case PuyoColor::YELLOW:
		break;
	case PuyoColor::PURPLE:
		break;
	}
}

void Puyo::RenderToIdle()
{
	switch (MyColor_)
	{
	case PuyoColor::RED:
		break;
	case PuyoColor::BLUE:
		break;
	case PuyoColor::GREEN:
		break;
	case PuyoColor::YELLOW:
		break;
	case PuyoColor::PURPLE:
		break;
	}
}

void Puyo::RenderToOtherIdle()
{
	switch (MyColor_)
	{
	case PuyoColor::RED:
		break;
	case PuyoColor::BLUE:
		break;
	case PuyoColor::GREEN:
		break;
	case PuyoColor::YELLOW:
		break;
	case PuyoColor::PURPLE:
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
			}
		}
		break;
	case PuyoColor::BLUE:
		if (true == MyRenderer_->IsAnimationName("IG_BLUE_LAND"))
		{
			if (true == MyRenderer_->IsEndAnimation())
			{
				MyRenderer_->ChangeAnimation("IG_BLUE_PUYO");
			}
		}
		break;
	case PuyoColor::GREEN:
		if (true == MyRenderer_->IsAnimationName("IG_GREEN_LAND"))
		{
			if (true == MyRenderer_->IsEndAnimation())
			{
				MyRenderer_->ChangeAnimation("IG_GREEN_PUYO");
			}
		}
		break;
	case PuyoColor::YELLOW:
		if (true == MyRenderer_->IsAnimationName("IG_YELLOW_LAND"))
		{
			if (true == MyRenderer_->IsEndAnimation())
			{
				MyRenderer_->ChangeAnimation("IG_YELLOW_PUYO");
			}
		}
		break;
	case PuyoColor::PURPLE:
		if (true == MyRenderer_->IsAnimationName("IG_PURPLE_LAND"))
		{
			if (true == MyRenderer_->IsEndAnimation())
			{
				MyRenderer_->ChangeAnimation("IG_PURPLE_PUYO");
			}
		}
		break;
	}
}

