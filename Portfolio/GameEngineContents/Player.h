#pragma once
#include "GameEngine/GameEngineActor.h"
#include "Puyo.h"
#include "ContentsEnum.h"
#include "GameEngineBase/GameEngineRandom.h"

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
	void InitNextPair();
	void InputCreatePuyo();

	void InputPuyoMove();
	void AutoDown();

protected:
	void Start() override;
	void Update() override;

private:
	Puyo* PlayerMap_[15][6];

	PlayerState PlayerState_;

	GameEngineRandom Random_;

	Puyo* CenterPuyo_;
	Puyo* SecondPuyo_;

	Puyo* NextCenterPuyo_;
	Puyo* NextSecondPuyo_;

	Puyo* NextNextCenterPuyo_;
	Puyo* NextNextSecondPuyo_;

	float DownTime;
};

