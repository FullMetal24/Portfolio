#include "Fire.h"
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngineBase/GameEngineInput.h>

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

	ChainActor_ = GetLevel()->CreateActor<InGameActor>();
	ChainActor_->SetMyRenderer(ChainActor_->CreateRenderer("IG_CHAIN.bmp"));
	ChainActor_->GetMyRenderer()->SetOrder(0);

	if (false == GameEngineInput::GetInst()->IsKey("Fire"))
	{
		GameEngineInput::GetInst()->CreateKey("Fire", VK_SPACE); 
	}
}

void Fire::Update()
{
	PlayerFire();
	EnemyFire();

	ExplosionCheck();

	//if (true == GameEngineInput::GetInst()->IsDown("Fire"))
	//{
	//	PlayerRenderChain(1, GameEngineWindow::GetScale().Half());
	//}

	 
	if (true == IsChainUp_)
	{
		Alpha_ += GameEngineTime::GetDeltaTime() * 1.5f;

		if (1.f <= Alpha_)
		{
			Alpha_ = 1.f;
		}

		ChainActor_->SetPosition(LerpMove(StartPos_, EndPos_, Alpha_));

		if (1.f <= Alpha_)
		{
			IsChainUp_ = false;
			ChainActor_->SetPosition(GetPosition());
  			ChainActor_->GetMyRenderer()->SetOrder(-1);
		}
	}
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
		&& true == MyRenderer_->IsAnimationName("IG_PLAYER_LIGHT_EXPLOSION"))
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


void Fire::PlayerRenderChain(int _Count, float4 _From)
{
	Alpha_ = 0.f;
	IsChainUp_ = true;
	StartPos_ = _From;
	EndPos_ = StartPos_ + float4{ 0, -200.f };

	switch (_Count)
	{
	case 1:
		ChainActor_->GetMyRenderer()->SetImage("IG_CHAIN_1.bmp");
		break;
	case 2:
		ChainActor_->GetMyRenderer()->SetImage("IG_CHAIN_2.bmp");
		break;
	case 3:
		ChainActor_->GetMyRenderer()->SetImage("IG_CHAIN_3.bmp");
		break;
	}

 	ChainActor_->GetMyRenderer()->SetOrder(10);
}

void Fire::EnemyRenderChain(int _Count, float4 _From)
{
	Alpha_ = 0.f;   
	IsChainUp_ = true;
	StartPos_ = _From;
	EndPos_ = StartPos_ + float4{ 0, -200.f };

	switch (_Count)
	{
	case 1:
		ChainActor_->GetMyRenderer()->SetImage("IG_CHAIN_1.bmp");
		break;
	case 2:
		ChainActor_->GetMyRenderer()->SetImage("IG_CHAIN_2.bmp");
		break;
	case 3:
		ChainActor_->GetMyRenderer()->SetImage("IG_CHAIN_3.bmp");
		break;
	}

	ChainActor_->GetMyRenderer()->SetOrder(10);
}


float4 Fire::LerpMove(float4 A, float4 B, float Alpha)
{
	return A * (1 - Alpha) + B * Alpha;

}
