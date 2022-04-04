#pragma once
#include "GameEngine/GameEngineLevel.h"

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

	void Loading() override; //캐릭터 이미지 생성
	void Update() override; //상대 캐릭터 고르기
	void LevelChangeStart() override;
	void LevelChangeEnd() override;

	void TopPositionInit();
	void SelectEnemy();

protected:


private:
	GameEngineActor* Top[6];

	GameEngineRenderer* TopRenderer[6];
	//고른 캐릭터를 PlayGame에 전달해야함
};

