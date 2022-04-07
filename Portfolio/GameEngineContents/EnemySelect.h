#pragma once
#include "GameEngine/GameEngineLevel.h"
#include "EnemyRoulette.h"

class Enemy;
class GameEngineRenderer;
class EnemyRoulette;
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
	void FrameInit();

	void PlayRoulette();

protected:


private:
	Enemy* Enemys_[8];
	//Enemy* EnemyRenderers_[8];
	Enemy* MyEnemy_;
	//EnemyRoulette* EnemyRoulette_;

	float RouletteSpeed_;
	float SpeedLimit_;
	float LevelChangeCount_;

	int RouletteIndex_;
	int LimitForce_;

	bool IsSelect_;
	bool IsKeyDown_;

	GameEngineActor* Top_[6];
	GameEngineRenderer* TopRenderer_[6];
	//�� ĳ���͸� PlayGame�� �����ؾ���


};

