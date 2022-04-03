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

	void InitBackground();
	void ChangeBackground();

protected:

private:
	GameEngineActor* TitleActors_[16];

	int TransCount_;
	float TransTime;
};

//열겨형으로 해서 벡터에 접근?
//[]
