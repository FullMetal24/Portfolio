#pragma once
#include <GameEngine/GameEngineActor.h>

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

	void AddPuyo();

protected:

private:

	Puyo* EnemyMap_[6][13];

	PuyoPair* CurrnetPair_;
	PuyoPair* NextPair_;
	PuyoPair* NextNextPair_;

	Puyo* Visited_;

	int RotationCount;
	int Score_;

	bool CreatePuyo_;


};


