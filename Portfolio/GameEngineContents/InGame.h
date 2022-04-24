#pragma once
#include <GameEngineBase/GameEngineRandom.h>
#include <GameEngineBase/GameEngineSound.h>
#include <GameEngine/GameEngineLevel.h>
#include <GameEngine/GameEngineActor.h>
#include <GameEngine/GameEngineRenderer.h>
#include "FadeInOutBackground.h"
#include "Stage.h"
#include "Player.h"
#include <vector>

class FSM;
class PuyoPair;
class InGameActor;
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

	inline void SetEnemy(GameEngineRenderer* _Enemy)
	{
		EnemyProfile_ = _Enemy;
	}

	void PuyoAnimationInit();
	void CarbuncleAnimationInit();

	void CarbuncleUpdate();
	void SpewStar();

	void VomitBubble();

protected:

private:
	Stage* Stages_[3];
	Player*	Player_; 
	FSM* FSM_;

	InGameActor* Carbuncle_;
	InGameActor* Stars_[36];
	  
	GameEngineRenderer* EnemyProfile_;
	GameEngineRenderer* Stage_; //스테이지 이미지 (렌더러가 나을듯함


	FadeInOutBackground* FadeBackground_;

	GameEngineSoundPlayer InGameBgm_;

	GameEngineRandom Random_;
	InGameActor* Bubbles_[15 ];
	float4 BubbleDir_[15];
	int BubbleSpeed_[15];

	int StageClear_;
	float ChangeCount_;

	bool IsStart_;
	bool IsEnemyFlap_;
};
	

 //스테이지 
//스테이지 내부 멤버에 렌더러를 여러 개 두고 따로 로딩하는 형식이 좋을까?
//렌더러를 인게임에 두고 하는 방법은 어떨까


