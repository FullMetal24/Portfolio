#pragma once
#include <GameEngine/GameEngineActor.h>
#include "ContentsEnum.h"

class GameEngineRenderer;
class Fire : public GameEngineActor
{
public:
	Fire();
	~Fire();

	Fire(const Fire& _Other) = delete;
	Fire(Fire&& _Other) noexcept = delete;
	Fire& operator=(const Fire& _Other) = delete;
	Fire& operator=(Fire&& _Other) noexcept = delete;

	void SetIsAttack(bool _IsAttack)
	{
		IsAttack_ = _IsAttack;
	}

	void SetFirePosition(float4 _Pos)
	{
		SetPosition(_Pos);
	}

	void GetTargetPos(float4 _Pos)
	{
		TargetPos_ = _Pos;
	}

	void SetFireOwner(FireOwner _Owner)
	{
		FireOwner_ = _Owner;
	}

	void ExplosionCheck();

protected:
	void Start() override;
	void Update() override;
private:
	float4 TargetPos_;
	GameEngineRenderer* MyRenderer_;

	FireOwner FireOwner_;

	float Acc_;

	bool IsAttack_;

	void PlayerFire();
	void EnemyFire();
};

