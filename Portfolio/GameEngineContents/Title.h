#pragma once
#include "GameEngine/GameEngineLevel.h"
#include <GameEngineBase/GameEngineSound.h>
#include "FadeInOutBackground.h"

class Title : public GameEngineLevel
{
public:
	Title();
	~Title();

	Title(const Title& _Other) = delete;
	Title(Title&& _Other) noexcept = delete;
	Title& operator=(const Title& _Other) = delete;
	Title& operator=(Title&& _Other) noexcept = delete;

	void Loading() override;
	void Update()  override;
	void LevelChangeStart(GameEngineLevel* _PrevLevel) override;
	void LevelChangeEnd(GameEngineLevel* _NextLevel) override;

	void BackgroundInit();
	void ChangeBackground();
	void FadeBackground();

protected:

private:
	GameEngineActor* TitleActors_[20];
	GameEngineRenderer* TitleRenderers_[20];

	//마지막 타이틀 이미지들
	GameEngineActor* NameActor_[4];
	GameEngineRenderer* NameRenderer_[4];

	GameEngineRenderer* CoinRenderer_;

	GameEngineActor* ChineseChracter_;
	GameEngineRenderer* ChineseChracterRenderer_;

	GameEngineActor* RedPuyo_;
	GameEngineRenderer* RedRenderer_;
	GameEngineRenderer* RedRenderer1_;
	GameEngineActor* GreenPuyo_;
	GameEngineRenderer* GreenRenderer_;

	FadeInOutBackground* FadeInOutBackground_;
	FadeInOutBackground* LevelChangeBackground_;

	GameEngineActor* Stars_;

	GameEngineSoundPlayer TitleBgm_;
	GameEngineSound EffectSound_;

	int TransCount_;
	float TransTime_;
	
	bool EyeMove_;
};
