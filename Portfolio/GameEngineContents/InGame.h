#pragma once
#include "GameEngine/GameEngineLevel.h"
#include "GameEngine/GameEngineActor.h"
#include "GameEngine/GameEngineRenderer.h"
#include "Stage.h"
#include "Player.h"
#include <vector>

class Enemy;
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

	void SetEnemy(Enemy* _Enemy)
	{
		CurrentEnemy_ = _Enemy;
	}

	PuyoPair* CreatePuyoPair();

protected:

private:

	//13 * 6
	//부모 뿌요를 넣고 자식(레드 블루) 뿌요들을 삭제 관리
	//std::vector<Stage*> Stages;
	Stage* Stages_[3]; //굳이 스테이지 말고 렌더러여도 된다.
		
	//Plyer와 선택한 Enemy를 동적할당(Enemy 타입, 이미지 넘겨주기?)

	Player*	Player_;
	Enemy* CurrentEnemy_;

	GameEngineRenderer* StageName_; //스테이지 이미지 (렌더러가 나을듯함

	int StageClear_;
};
	
//스테이지 
//스테이지 내부 멤버에 렌더러를 여러 개 두고 따로 로딩하는 형식이 좋을까?
//렌더러를 인게임에 두고 하는 방법은 어떨까


