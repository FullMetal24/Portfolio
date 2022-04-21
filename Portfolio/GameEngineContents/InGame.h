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

	PuyoPair* CreatePuyoPair();
	Puyo* CreateHindrancePuyo(GameEngineActor* _FromActor, GameEngineActor* _ToActor); //���� �ѿ� ����, �ٿ� ĳ����

	void CreatePuyoAnimation(GameEngineRenderer* _Renderer, PuyoColor _Color);

	void PuyoAnimationInit();
	void CarbuncleAnimationInit();

	void CarbuncleUpdate();
	void SpewStar();

protected:

private:
	Stage* Stages_[3];
	Player*	Player_; 
	FSM* FSM_;

	InGameActor* Carbuncle_;
	InGameActor* Stars_[36];
	  
	GameEngineRenderer* EnemyProfile_;
	GameEngineRenderer* Stage_; //�������� �̹��� (�������� ��������

	GameEngineRandom RandomColor_;

	FadeInOutBackground* FadeBackground_;

	GameEngineSoundPlayer InGameBgm_;

	int StageClear_;
	float LevelCount_;

	bool IsStart_;
};
	

 //�������� 
//�������� ���� ����� �������� ���� �� �ΰ� ���� �ε��ϴ� ������ ������?
//�������� �ΰ��ӿ� �ΰ� �ϴ� ����� ���


