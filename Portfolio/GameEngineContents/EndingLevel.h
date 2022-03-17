#pragma once
#include <GameEngine/GameEngineLevel.h>

class EndingLevel : public GameEngineLevel
{
public:
	EndingLevel();
	~EndingLevel();

	EndingLevel(const EndingLevel& _Other) = delete;
	EndingLevel(EndingLevel&& _Other) noexcept = delete;
	EndingLevel& operator=(const EndingLevel& _Other) = delete;
	EndingLevel& operator=(EndingLevel&& _Other) noexcept = delete;

	void Loading() override;
	void Update() override;

protected:

private:

};

