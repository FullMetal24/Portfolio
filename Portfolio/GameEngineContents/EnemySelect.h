#pragma once
#include "GameEngine/GameEngineLevel.h"

class Enemy;
class GameEngineRenderer;
class EnemySelect : public GameEngineLevel
{
public:
	EnemySelect();
	~EnemySelect();

	EnemySelect(const EnemySelect& _Other) = delete;
	EnemySelect(EnemySelect&& _Other) noexcept = delete;
	EnemySelect& operator=(const EnemySelect& _Other) = delete;
	EnemySelect& operator=(EnemySelect&& _Other) noexcept = delete;

	void Loading() override; //ĳ���� �̹��� ����
	void Update() override; //��� ĳ���� ����
	void LevelChangeStart() override;
	void LevelChangeEnd() override;

	void TopPositionInit();
	void EnemyInit();
	void SelectEnemy();

protected:


private:
	Enemy* Enemys_[8];

	float RouletteSpeed;

	GameEngineActor* Top_[6];
	GameEngineRenderer* TopRenderer_[6];
	//�� ĳ���͸� PlayGame�� �����ؾ���
};

