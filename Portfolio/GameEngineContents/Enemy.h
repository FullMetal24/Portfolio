#pragma once
#include "GameEngine/GameEngineActor.h"
#include <list>

class Puyo;
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

protected:

private:

	Puyo* EnemyMap_[6][13];
	int Score_;
};

