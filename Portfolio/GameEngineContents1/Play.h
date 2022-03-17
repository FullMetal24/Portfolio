#pragma once
#include "GameEngine/GameEngineLevel.h"

class Play : public GameEngineLevel
{
public:
	Play();
	~Play();
	
	Play(const Play& _Other) = delete;
	Play(Play&& _Other) noexcept = delete;
	Play& operator=(const Play& _Other) = delete;
	Play& operator=(Play&& _Other) noexcept = delete;

	void Loading() override;
	void Update()  override;

protected:

private:

};

