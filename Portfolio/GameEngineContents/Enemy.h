#pragma once
#include "GameEngine/GameEngineActor.h"
#include <list>

class Puyo;
class PuyoPair;
class Enemy : public GameEngineActor //AI
{
public:
	Enemy();
	~Enemy();

	Enemy(const Enemy& _Other) = delete;
	Enemy(Enemy&& _Other) noexcept = delete;
	Enemy& operator=(const Enemy& _Other) = delete;
	Enemy& operator=(Enemy&& _Other) noexcept = delete;

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

