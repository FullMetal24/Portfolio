#pragma once
#include "GameEngine/GameEngineActor.h"

class KnockdownPlayer : public GameEngineActor
{
public:
	KnockdownPlayer();
	~KnockdownPlayer();

	KnockdownPlayer(const KnockdownPlayer& _Other) = delete;
	KnockdownPlayer(KnockdownPlayer&& _Other) noexcept = delete;
	KnockdownPlayer& operator=(const KnockdownPlayer& _Other) = delete;
	KnockdownPlayer& operator=(KnockdownPlayer&& _Other) noexcept = delete;

	void Start() override;
	void Update() override;
	void Render() override;


protected:

private:

};

