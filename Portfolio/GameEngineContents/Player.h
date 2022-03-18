#pragma once
#include "GameEngine/GameEngineActor.h"
#include "PuyoPair.h"

class Player : public GameEngineActor
{
public:
	Player();
	~Player();

	Player(const Player& _Other) = delete;
	Player(Player&& _Other) noexcept = delete;
	Player& operator=(const Player& _Other) = delete;
	Player& operator=(Player&& _Other) noexcept = delete;

	void Start() override;
	void Update() override;
	void Render() override;

	//뿌요들 리스트, 벡터?로 관리?
	//게임 끝나면 전부 삭제

protected:

private:
};

