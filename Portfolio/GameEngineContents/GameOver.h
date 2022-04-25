#pragma once
#include "FadeInOutBackground.h"
#include "GameEngine/GameEngineLevel.h"
#include <GameEngineBase/GameEngineSound.h>

class GameOverActor;
class GameEngineRenderer;
class EnemyProfile;
class GameOver : public GameEngineLevel
{
public:
	GameOver();
	~GameOver();

	GameOver(const GameOver& _Other) = delete;
	GameOver(GameOver&& _Other) noexcept = delete;
	GameOver& operator=(const GameOver& _Other) = delete;
	GameOver& operator=(GameOver&& _Other) noexcept = delete;

	void Loading() override; 
	void Update()  override; //재시작 키 입력 감지(PlayGame or mainmenu)
	void LevelChangeStart(GameEngineLevel* _PrevLevel) override;
	void LevelChangeEnd(GameEngineLevel* _NextLevel) override;

	inline void SetEnemy(EnemyProfile* _Enemy)
	{
		EnemyProfile_ = _Enemy;
	}


protected:

private:
	GameOverActor* Background_;
	GameEngineRenderer* BackRenderer_;

	FadeInOutBackground* FadeBack_;
	EnemyProfile* EnemyProfile_;

	int Count_;
	float Time_;

	bool IsLevelStart_;

};

