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
}


void Puyo::RenderToLeft()
{
	switch (MyColor_)
	{
	case PuyoColor::RED:
		MyRenderer_->SetImage("IG_RED_LEFT.bmp");
		break;
	case PuyoColor::BLUE:
		MyRenderer_->SetImage("IG_BLUE_LEFT.bmp");
		break;
	case PuyoColor::GREEN:
		break;
	case PuyoColor::YELLO:
		break;
	case PuyoColor::PURPLE:
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
	case PuyoColor::YELLO:
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
	case PuyoColor::YELLO:
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
	case PuyoColor::YELLO:
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
	case PuyoColor::YELLO:
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
	case PuyoColor::YELLO:
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
	case PuyoColor::YELLO:
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
	case PuyoColor::YELLO:
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
	case PuyoColor::YELLO:
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
	case PuyoColor::YELLO:
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
	case PuyoColor::YELLO:
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
	case PuyoColor::YELLO:
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
	case PuyoColor::YELLO:
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
	case PuyoColor::YELLO:
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
	case PuyoColor::YELLO:
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
	case PuyoColor::YELLO:
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
	case PuyoColor::YELLO:
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
	case PuyoColor::YELLO:
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
	case PuyoColor::YELLO:
		break;
	case PuyoColor::PURPLE:
		break;
	}
}

