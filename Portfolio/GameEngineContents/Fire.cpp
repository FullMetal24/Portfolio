#include "Fire.h"
#include <GameEngine/GameEngineRenderer.h>

Fire::Fire()
	: FireOwner_(FireOwner::NONE)
	, Acc_(0.f)
{
}

Fire::~Fire() 
{
}

void Fire::Start()
{
	MyRenderer_ = CreateRenderer();
	MyRenderer_->CreateAnimation("IG_PLAYER_LIGHT.bmp", "IG_PLAYER_LIGHT", 0, 3, 0.1f, true);
	MyRenderer_->CreateAnimation("IG_PLAYER_LIGHT_EXPLOSION.bmp", "IG_PLAYER_LIGHT_EXPLOSION", 0, 3, 0.1f, false);
	MyRenderer_->CreateAnimation("IG_ENEMY_LIGHT.bmp", "IG_ENEMY_LIGHT", 0, 3, 0.1f, true);
	MyRenderer_->CreateAnimation("IG_ENEMY_LIGHT_EXPLOSION.bmp", "IG_ENEMY_LIGHT_EXPLOSION", 0, 3, 0.1f, false);

	MyRenderer_->ChangeAnimation("IG_PLAYER_LIGHT");
	MyRenderer_->SetOrder(0);
}

void Fire::Update()
{
	PlayerFire();
	EnemyFire();

	ExplosionCheck();
}

void Fire::PlayerFire()
{
	if (FireOwner_ == FireOwner::Player)
	{
		if (true == IsAttack_)
		{
			MyRenderer_->SetOrder(10);
			Acc_ += GameEngineTime::GetDeltaTime();

			float4 Dir = TargetPos_ - GetPosition();
			SetMove(Dir * GameEngineTime::GetDeltaTime() * 5.f * Acc_);

			if (GetPosition().y <= 50.f)
 			{
				MyRenderer_->ChangeAnimation("IG_PLAYER_LIGHT_EXPLOSION");
				IsAttack_ = false;
				Acc_ = 0.f;
			}
		}
	}
} 

void Fire::EnemyFire()
{
	if (FireOwner_ == FireOwner::Enemy)
	{
		if (true == IsAttack_)
		{
			MyRenderer_->ChangeAnimation("IG_ENEMY_LIGHT");
			MyRenderer_->SetOrder(10);

			Acc_ += GameEngineTime::GetDeltaTime();

			float4 Dir = TargetPos_ - GetPosition();
			SetMove(Dir * GameEngineTime::GetDeltaTime() * 5.f * Acc_);

			if (GetPosition().y <= 50.f)
			{
				MyRenderer_->ChangeAnimation("IG_ENEMY_LIGHT_EXPLOSION");
				IsAttack_ = false;
				Acc_ = 0.f;
			}
		}
	}
}


void Fire::ExplosionCheck()
{
	if (true == MyRenderer_->IsEndAnimation()
		&& true ==  MyRenderer_->IsAnimationName("IG_PLAYER_LIGHT_EXPLOSION"))
	{
		MyRenderer_->SetOrder(-1);
		MyRenderer_->ChangeAnimation("IG_PLAYER_LIGHT");
	}

	else if (true == MyRenderer_->IsEndAnimation()
		&& true == MyRenderer_->IsAnimationName("IG_ENEMY_LIGHT_EXPLOSION"))
	{
		MyRenderer_->SetOrder(-1);
		MyRenderer_->ChangeAnimation("IG_ENEMY_LIGHT");
	}
}
