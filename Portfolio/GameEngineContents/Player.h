#pragma once
#include "GameEngine/GameEngineActor.h"
#include <list>
#include "Puyo.h"

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

	void PuyoInput();
	bool IsLanding();

	void AddPuyo();

	//뿌요들 리스트, 벡터?로 관리?
	//게임 끝나면 전부 삭제

protected:

private:

	//std::list<std::list<Puyo*>> PlayerMap_; //생성되는 건 뿌요페어지만 저장은 두 뿌요로 나누어 저장한다.
	GameEngineActor* MyProfile_;
	Puyo* PlayerMap_[6][13];
	
	PuyoPair* CurrnetPair_;
	PuyoPair* NextPair_;
	PuyoPair* NextNextPair_;

	Puyo* Visited_;
	
	int RotationCount;
	int Score_;

	bool CreatePuyo_;
};

