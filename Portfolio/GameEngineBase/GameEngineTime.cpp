#include "GameEngineTime.h"
#include <Windows.h>

GameEngineTime* GameEngineTime::Inst_ = new GameEngineTime();

GameEngineTime::GameEngineTime() 
{
}

GameEngineTime::~GameEngineTime() 
{

}

void GameEngineTime::Reset()
{
	QueryPerformanceCounter(reinterpret_cast<LARGE_INTEGER*>(&CurrentCount));
	QueryPerformanceCounter(reinterpret_cast<LARGE_INTEGER*>(&PrevCount));
	QueryPerformanceFrequency(reinterpret_cast<LARGE_INTEGER*>(&SecondCount));
	Update();
}

void GameEngineTime::Update()
{
	QueryPerformanceCounter(reinterpret_cast<LARGE_INTEGER*>(&CurrentCount));

	RealDeltaTime_ = (static_cast<double>(CurrentCount) - static_cast<double>(PrevCount)) / static_cast<double>(SecondCount);
	PrevCount = CurrentCount; 

	DeltaTime_ = static_cast<float>(RealDeltaTime_);
}
