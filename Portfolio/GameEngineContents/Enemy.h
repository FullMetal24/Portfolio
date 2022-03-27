#pragma once
#include "GameEngine/GameEngineActor.h"
#include <list>

class Puyo;
class Enemy : public GameEngineActor //AI
{
public:
	// constrcuter destructer
	Enemy();
	~Enemy();

	// delete Function
	Enemy(const Enemy& _Other) = delete;
	Enemy(Enemy&& _Other) noexcept = delete;
	Enemy& operator=(const Enemy& _Other) = delete;
	Enemy& operator=(Enemy&& _Other) noexcept = delete;

	void Start() override;
	void Update() override;
	void Render() override;

protected:

private:

	std::list<std::list<Puyo*>> EnemyMap_;

};

