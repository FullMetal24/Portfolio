#include "Enemy.h"

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
