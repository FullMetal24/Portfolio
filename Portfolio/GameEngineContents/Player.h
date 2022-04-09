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

	void CurrentPairInit();
	void AddPuyoPair(PuyoPair* _Pair);

	void LandCheck();

	inline void SetCurrentPair(PuyoPair* _Current)
	{
		CurrentPair_ = _Current;
	}

	inline void SetNextPair(PuyoPair* _Next)
	{
		NextPair_ = _Next;
	}

	inline void SetNextNextPair(PuyoPair* _NextNext)
	{
		NextNextPair_ = _NextNext;
	}

	inline bool GetAllLanding()
	{
		return IsAllLanding_;
	}

protected:

private:
	Puyo* PlayerMap_[30][6];

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

	float DownTime;
	float JedgementTime_; //판정 시간

	bool IsStart_;
	bool IsAllLanding_;
	bool IsLose_;
};

