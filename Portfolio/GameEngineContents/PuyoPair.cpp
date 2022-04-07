#include "PuyoPair.h"
#include <GameEngine/GameEngineLevel.h>
#include "Puyo.h"

PuyoPair::PuyoPair() 
{

}

PuyoPair::~PuyoPair() 
{
	if (nullptr != CenterPuyo_)
	{
		delete CenterPuyo_;
		CenterPuyo_ = nullptr;
	}

	if (nullptr != SecondPuyo_)
	{
		delete SecondPuyo_;
		SecondPuyo_ = nullptr;
	}
}

void PuyoPair::Start()
{
	//CenterPuyo_ = new Puyo();
	//SecondPuyo_ = new Puyo();

	
}

void PuyoPair::Update()
{

}



void PuyoPair::Rotate()
{

}
