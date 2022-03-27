#pragma once
#include <GameEngine/GameEngineActor.h>


class Stage : public GameEngineActor
{
public:
	Stage();
	~Stage();

	Stage(const Stage& _Other) = delete;
	Stage(Stage&& _Other) noexcept = delete;
	Stage& operator=(const Stage& _Other) = delete;
	Stage& operator=(Stage&& _Other) noexcept = delete;

	void Start();
	void Update();
	void Render();

protected:

private:

};

