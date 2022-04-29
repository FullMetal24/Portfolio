#pragma once
#include <GameEngine/GameEngineActor.h>
#include <GameEngineBase/GameEngineSound.h>
#include "ContentsEnum.h"
#include "InGameActor.h"

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
	void PlayerRenderChain(int _Count, float4 _From);
	void EnemyRenderChain(int _Count, float4 _From);

	float4 LerpMove(float4 A, float4 B, float Alpha);


private:
	void PlayerFire();
	void EnemyFire();

protected:
	void Start() override;
	void Update() override;

private:
	float4 TargetPos_;
	GameEngineRenderer* MyRenderer_;

	GameEngineSound PlayerSound_;

	InGameActor* ChainActor_;

	float4 StartPos_;
	float4 EndPos_;
	float Alpha_;

	FireOwner FireOwner_;

	float Acc_;

	bool IsAttack_;
	bool IsChainUp_;

	bool IsPlayerFireSoundPlay_;

};

