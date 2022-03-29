#include "Enemy.h"
#include "PuyoPair.h"
#include "Puyo.h"

Enemy::Enemy() 
{
}

Enemy::~Enemy() 
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

void Enemy::Start()
{

}

void Enemy::Update()
{

}

void Enemy::Render()
{

}

void Enemy::AddPuyo()
{
	EnemyMap_[CurrnetPair_->GetCenterPuyo()->GetX()][CurrnetPair_->GetCenterPuyo()->GetY()] = CurrnetPair_->GetCenterPuyo();
	EnemyMap_[CurrnetPair_->GetSecondPuyo()->GetX()][CurrnetPair_->GetSecondPuyo()->GetX()] = CurrnetPair_->GetSecondPuyo();

	if (nullptr != EnemyMap_[CurrnetPair_->GetCenterPuyo()->GetX()][CurrnetPair_->GetCenterPuyo()->GetY() + 1])
	{
		EnemyMap_[CurrnetPair_->GetCenterPuyo()->GetX()][CurrnetPair_->GetCenterPuyo()->GetY()] = CurrnetPair_->GetCenterPuyo();
	}
}
