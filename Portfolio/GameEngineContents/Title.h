#pragma once
#include "GameEngine/GameEngineLevel.h"

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
	void LevelChangeStart() override;
	void LevelChangeEnd() override;

	void BackgroundInit();
	void ChangeBackground();

protected:

private:
	GameEngineActor* TitleActors_[17];
	GameEngineRenderer* TitleRenderers_[17];


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

	GameEngineRenderer* BackRenderer_;

	int TransCount_;
	float TransTime_;
	
	bool EyeMove_;

	int TitleShow_;
};

//열겨형으로 해서 벡터에 접근?
//[]
