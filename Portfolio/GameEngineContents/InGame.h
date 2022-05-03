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

	void ActorsInit();

	void TwinklePlayerWin();
	void TwinklePlayerGameOver();
	void ResultScore();
	void PlayerLose();

	void RenderTime();
	void RenderBonus(int _Value);
	void RenderStagePoint(int _Value);
	void RenderRestPoint(int _Value);

protected:

private:
	Stage* Stages_[3];
	InGameActor* StageRenderer_;
	InGameActor* StateBottoms_[2];

	float GameTime_;
	float Alpha_;

	float4 StageRenderStartPos_;
	float4 StageRenderEndPos_;

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
	int ResultCount_;

	InGameActor* PlayerGameOver_;
	InGameActor* PlayerWin_;
	InGameActor* SDPlayer_;

	float4 GameOverStartPos_;
	float4 GameOverEndPos_;

	float GameOverAlpha_;

	float TwinkleTime_;
	float WinWaitTime_;

	bool IsStart_;
	bool IsSpewStar_;
	bool IsStarUpdate_;
	bool IsTwinkleOn_;
};
	

