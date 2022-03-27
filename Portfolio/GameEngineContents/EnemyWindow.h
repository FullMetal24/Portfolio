#pragma once

// Ό³Έν :
class EnemyWindow
{
public:
	// constrcuter destructer
	EnemyWindow();
	~EnemyWindow();

	// delete Function
	EnemyWindow(const EnemyWindow& _Other) = delete;
	EnemyWindow(EnemyWindow&& _Other) noexcept = delete;
	EnemyWindow& operator=(const EnemyWindow& _Other) = delete;
	EnemyWindow& operator=(EnemyWindow&& _Other) noexcept = delete;

protected:

private:

};

