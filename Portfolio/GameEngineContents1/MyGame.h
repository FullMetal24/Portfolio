#pragma once
#include "GameEngine/GameEngine.h"

class MyGame : public GameEngine
{
public:
	MyGame();
	~MyGame();

	MyGame(const MyGame& _Other) = delete;
	MyGame(MyGame&& _Other) noexcept = delete;
	MyGame& operator=(const MyGame& _Other) = delete;
	MyGame& operator=(MyGame&& _Other) noexcept = delete;

	void GameInit() override;
	void GameLoop() override;
	void GameEnd()  override;

protected:


private:

};

