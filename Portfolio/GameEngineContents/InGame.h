#pragma once
#include "GameEngine/GameEngineLevel.h"
#include "GameEngine/GameEngineActor.h"
#include "GameEngine/GameEngineRenderer.h"
#include "Stage.h"
#include "Player.h"
#include <vector>

class Player;
class FSM;
class PuyoPair;
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
	void LevelChangeStart() override;
	void LevelChangeEnd() override;

	inline void SetEnemy(GameEngineRenderer* _Enemy)
	{
		EnemyProfile_ = _Enemy;
	}

	void CreatePuyoPair(bool _IsPlayer);

protected:

private:
	Stage* Stages_[3];
	Player*	Player_; 
	FSM* FSM_;


	GameEngineRenderer* EnemyProfile_;
	GameEngineRenderer* Stage_; //스테이지 이미지 (렌더러가 나을듯함

	int StageClear_;

	bool IsStart_;
};
	

//스테이지 
//스테이지 내부 멤버에 렌더러를 여러 개 두고 따로 로딩하는 형식이 좋을까?
//렌더러를 인게임에 두고 하는 방법은 어떨까


