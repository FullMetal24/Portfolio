#pragma once
#include "Puyo.h"
#include <GameEngine/GameEngineRenderer.h>

class HindrancePuyo : public Puyo
{
public:
	HindrancePuyo();
	~HindrancePuyo();

	HindrancePuyo(const HindrancePuyo& _Other) = delete;
	HindrancePuyo(HindrancePuyo&& _Other) noexcept = delete;
	HindrancePuyo& operator=(const HindrancePuyo& _Other) = delete;
	HindrancePuyo& operator=(HindrancePuyo&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update() override;


private:


};

