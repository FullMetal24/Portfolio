#pragma once
#include "GameEngine/GameEngineLevel.h"
#include <GameEngineBase/GameEngineSound.h>
#include "FadeInOutBackground.h"
#include "EnemyRoulette.h"

class EnemyProfile;
class GameEngineRenderer;
class EnemyRoulette;
class EnemySelectActor;
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
	void LevelChangeStart(GameEngineLevel* _PrevLevel) override;
	void LevelChangeEnd(GameEngineLevel* _NextLevel) override;

	//void BackgroundInit();
	void TopPositionInit();
	void EnemyInit();
	void FrameInit();

	void PlayRoulette();
	void TwinkleEnemyIcon();

protected:


private:
	EnemyProfile* Enemys_[8];
	EnemyProfile* MyEnemy_;

	std::vector<EnemySelectActor*> MidLine_;
	std::vector<std::vector<EnemySelectActor*>> Backgrounds_;

	float RouletteSpeed_;
	float SpeedLimit_;
	float LevelChangeCount_;

	float TwinkleTime_;

	int RouletteIndex_;
	int LimitForce_;

	bool IsSelect_;
	bool IsKeyDown_;

	GameEngineActor* Top_[6];
	GameEngineRenderer* TopRenderer_[6];
	//�� ĳ���͸� PlayGame�� �����ؾ���

	FadeInOutBackground* FadeBackground_;

	GameEngineSoundPlayer EnemySelectBgm_;
};

