#pragma once
#include "GameEngine/GameEngineActor.h"
#include "Puyo.h"
#include "ContentsEnum.h"

class Player : public GameEngineActor
{
public:
	Player();
	~Player();

	Player(const Player& _Other) = delete;
	Player(Player&& _Other) noexcept = delete;
	Player& operator=(const Player& _Other) = delete;
	Player& operator=(Player&& _Other) noexcept = delete;

	Puyo* CreatePuyo(int x, int y, PuyoColor _Color);

	void NewPuyoPair();
	void InputCreatePuyo();

	void InputPuyoMove();
	void AutoDown();

protected:
	void Start() override;
	void Update() override;

private:
	Puyo* PlayerMap_[15][6];

	PlayerState PlayerState_;

	Puyo* CenterPuyo_;
	Puyo* SecondPuyo_;

	float DownTime;
};

