#pragma once
#include <GameEngine/GameEngine.h>


class PuyoPuyo: public GameEngine
{

public:
	PuyoPuyo();
	~PuyoPuyo();

	PuyoPuyo(const PuyoPuyo& _Other) = delete;
	PuyoPuyo(PuyoPuyo&& _Other) noexcept = delete;
	PuyoPuyo& operator=(const PuyoPuyo& _Other) = delete;
	PuyoPuyo& operator=(PuyoPuyo&& _Other) noexcept = delete;

	void GameLoop();
	void GameEnd();
	void GameInit();

protected:

private:

};

