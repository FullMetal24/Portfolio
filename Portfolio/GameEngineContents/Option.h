#pragma once
#include <GameEngine/GameEngineLevel.h>

class Option : public GameEngineLevel
{
public:
	Option();
	~Option();

	Option(const Option& _Other) = delete;
	Option(Option&& _Other) noexcept = delete;
	Option& operator=(const Option& _Other) = delete;
	Option& operator=(Option&& _Other) noexcept = delete;

	void Loading() override;
	void Update() override;

protected:

private:

};

