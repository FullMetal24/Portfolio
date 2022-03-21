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
	//Plyer와 선택한 Enemy를 동적할당(Enemy 타입, 이미지 넘겨주기?)
};

