#pragma once

// Ό³Έν :
class PlayerWindow
{
public:
	// constrcuter destructer
	PlayerWindow();
	~PlayerWindow();

	// delete Function
	PlayerWindow(const PlayerWindow& _Other) = delete;
	PlayerWindow(PlayerWindow&& _Other) noexcept = delete;
	PlayerWindow& operator=(const PlayerWindow& _Other) = delete;
	PlayerWindow& operator=(PlayerWindow&& _Other) noexcept = delete;

protected:

private:

};

