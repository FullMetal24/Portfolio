#pragma once
#include <GameEngineBase/GameEngineSound.h>
#include <GameEngine/GameEngineLevel.h>
#include <GameEngine/GameEngineActor.h>
#include <GameEngine/GameEngineRenderer.h>
#include "FadeInOutBackground.h"
#include "Stage.h"
#include <vector>

class Player;
class EnemyFSM;
class PuyoPair;
class InGameActor;
class EnemyProfile;
class InGame : public GameEngineLevel
{
public:
	InGame();
	~InGame();
	
	InGame(const InGame& _Other) = delete;
	InGame(InGame&& _Other) noexcept = delete;
	InGame& operator=(const InGame& _Other) = delete;
	InGame& operator=(InGame&& _Other) noexcept = delete;

	void Loading() override;
	void Update()  override;

	void LevelChangeStart(GameEngineLevel* _PrevLevel) override;
	void LevelChangeEnd(GameEngineLevel* _NextLevel) override;
	void UserResetEnd() override;

	inline void SetEnemyProfile(EnemyProfile* _Enemy)
	{
		EnemyProfile_ = _Enemy;
	}
	inline EnemyProfile* GetEnemyProfile()
	{
		return EnemyProfile_;
	}	

	void InitPlayerEndEnemy();

	void PuyoAnimationInit();
	void EnemyAnimatioInit();
	void CarbuncleAnimationInit();

	void GameOverCheck();
	void CarbuncleUpdate();
	void SpewStar();

	void TwinkleWinRenderer();

protected:

private:
	Stage* Stages_[3];
	InGameActor* StageRenderer_;
	InGameActor* StateBottoms_[2];

	float StageAlpha_;

	float4 StageRenderStartPos_;
	float4 StageRenderEndPos_;

	InGameActor* GameOverRenderer_;
	InGameActor* WinRenderer_;

	Player*	Player_; 
	EnemyFSM* EnemyFSM_;

	InGameActor* Carbuncle_;
	InGameActor* Stars_[36];
	  
	EnemyProfile* EnemyProfile_;
	GameEngineRenderer* Stage_; 

	FadeInOutBackground* FadeBackground_;

	GameEngineSoundPlayer InGameBgm_;
	GameEngineSound EffectSound_;

	int StageClear_;
	int TwinkleCount_; //WinRenderer ±ôºýÀÓ
	float ChangeCount_;
	float Alpha_;

	bool IsStart_;
	bool IsEnemyFlap_;
	bool IsStateUp_;

	float4 GameOverStartPos_;
	float4 GameOverEndPos_;
};
	

