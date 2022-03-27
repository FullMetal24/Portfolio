#pragma once
#include "GameEngine/GameEngineLevel.h"
#include "Stage.h"

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

	void SetEnemy(Enemy* _Enemy)
	{
		CurrentEnemy_ = _Enemy;
	}

	PuyoPair* CreatePuyoPair();

protected:

private:

	//13 * 6
	//부모 뿌요를 넣고 자식(레드 블루) 뿌요들을 삭제 관리
	//std::vector<Stage> Stages;
		
	//Plyer와 선택한 Enemy를 동적할당(Enemy 타입, 이미지 넘겨주기?)
	Enemy* CurrentEnemy_;
	GameEngineActor* StageName_; //스테이지 이미지
};

