#pragma once

// Ό³Έν :
class GameName
{
public:
	// constrcuter destructer
	GameName();
	~GameName();

	// delete Function
	GameName(const GameName& _Other) = delete;
	GameName(GameName&& _Other) noexcept = delete;
	GameName& operator=(const GameName& _Other) = delete;
	GameName& operator=(GameName&& _Other) noexcept = delete;

protected:

private:

};

