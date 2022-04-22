#pragma once
#include "FadeInOutBackground.h"
#include "GameEngine/GameEngineLevel.h"
#include <GameEngineBase/GameEngineSound.h>

class GameEngineRenderer;
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
	void Update()  override; //����� Ű �Է� ����(PlayGame or mainmenu)
	void LevelChangeStart(GameEngineLevel* _PrevLevel) override;
	void LevelChangeEnd(GameEngineLevel* _NextLevel) override;

protected:

private:
	GameEngineRenderer* BackRenderer_;
	FadeInOutBackground* Background_;
	GameEngineSoundPlayer GameOverBgm_;

	int Count_;
	float Time_;

};

