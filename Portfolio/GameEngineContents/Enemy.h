#pragma once
#include "GameEngine/GameEngineActor.h"

//AI
class Enemy : public GameEngineActor
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

};

