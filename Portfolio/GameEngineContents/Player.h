#pragma once
#include "GameEngine/GameEngineActor.h"
#include <list>
#include "Puyo.h"
#include "ContentsEnum.h"

class Puyo;
class PuyoPair;
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

	void MoveLeft();
	void MoveRight();
	void MoveDown();
	void Rotate();

	void AddPuyo(Puyo* _Puyo);
	void AddPuyoPair(PuyoPair* _Pair);

protected:

private:
	Puyo* PlayerMap_[15][6];

	PuyoPair* CurrentPair_;
	PuyoPair* NextPair_;
	PuyoPair* NextNextPair_;

	PuyoDir PuyoDir_;

	int CenterX_;
	int CenterY_;

	int SecondX_;
	int SecondY_;

	float DownMoveDis_;
	float SideMoveDis_;
};

