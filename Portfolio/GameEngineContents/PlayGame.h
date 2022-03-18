#pragma once
#include "GameEngine/GameEngineLevel.h"

class PlayGame : public GameEngineLevel
{
public:
	PlayGame();
	~PlayGame();
	
	PlayGame(const PlayGame& _Other) = delete;
	PlayGame(PlayGame&& _Other) noexcept = delete;
	PlayGame& operator=(const PlayGame& _Other) = delete;
	PlayGame& operator=(PlayGame&& _Other) noexcept = delete;

	void Loading() override;
	void Update()  override;

protected:

private:

};

