#include "FSM.h"
#include "PuyoPair.h"
#include "Puyo.h"

FSM::FSM() 
{
}

FSM::~FSM() 
{
	for (size_t x = 0; x < 6; x++)
	{
		for (size_t y = 0; y < 13; y++)
		{
			if (nullptr != EnemyMap_[x][y])
			{
				delete EnemyMap_[x][y];
				EnemyMap_[x][y] = nullptr;
			}
		}
	}
}

void FSM::Start()
{
}

void FSM::Update()
{
}

void FSM::Render()
{
}

void FSM::AddPuyo()
{
	EnemyMap_[CurrnetPair_->GetCenterPuyo()->GetX()][CurrnetPair_->GetCenterPuyo()->GetY()] = CurrnetPair_->GetCenterPuyo();
	EnemyMap_[CurrnetPair_->GetSecondPuyo()->GetX()][CurrnetPair_->GetSecondPuyo()->GetX()] = CurrnetPair_->GetSecondPuyo();

	if (nullptr != EnemyMap_[CurrnetPair_->GetCenterPuyo()->GetX()][CurrnetPair_->GetCenterPuyo()->GetY() + 1])
	{
		EnemyMap_[CurrnetPair_->GetCenterPuyo()->GetX()][CurrnetPair_->GetCenterPuyo()->GetY()] = CurrnetPair_->GetCenterPuyo();
	}
}
