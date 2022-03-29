#pragma once
#include <GameEngine/GameEngineActor.h>

class GO_BackGround : public GameEngineActor
{
public:
	GO_BackGround();
	~GO_BackGround();

	GO_BackGround(const GO_BackGround& _Other) = delete;
	GO_BackGround(GO_BackGround&& _Other) noexcept = delete;
	GO_BackGround& operator=(const GO_BackGround& _Other) = delete;
	GO_BackGround& operator=(GO_BackGround&& _Other) noexcept = delete;

protected:
	void Start();
	void Update();
	void Render();


private:

};

