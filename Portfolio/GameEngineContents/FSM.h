#pragma once
#include <GameEngine/GameEngineActor.h>
#include "ContentsEnum.h"

class Puyo;
class PuyoPair;
class FSM : public GameEngineActor
{

public:
	FSM();
	~FSM();

	FSM(const FSM& _Other) = delete;
	FSM(FSM&& _Other) noexcept = delete;
	FSM& operator=(const FSM& _Other) = delete;
	FSM& operator=(FSM&& _Other) noexcept = delete;

	void Start() override;
	void Update() override;
	void Render() override;

	void AddPuyoPair(PuyoPair* _Pair);

	inline bool GetLose()
	{
		return IsLose_;
	}
	
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

	bool IsLose_;
};


