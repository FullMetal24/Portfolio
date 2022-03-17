#pragma once
#include "GameEngine/GameEngineLevel.h"

class GameOver : public GameEngineLevel
{
public:
	// constrcuter destructer
	GameOver();
	~GameOver();

	// delete Function
	GameOver(const GameOver& _Other) = delete;
	GameOver(GameOver&& _Other) noexcept = delete;
	GameOver& operator=(const GameOver& _Other) = delete;
	GameOver& operator=(GameOver&& _Other) noexcept = delete;

	void Loading() override;
	void Update()  override;

protected:

private:

};

