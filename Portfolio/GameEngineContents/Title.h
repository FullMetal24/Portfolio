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

	void ChangeBackground();

protected:

private:
	GameEngineActor* CompanyLogo_;
	GameEngineActor* Puyo_;
	GameEngineActor* Background_;
	GameEngineActor* Carbuncle_;
	GameEngineActor* Roll_;
	GameEngineActor* Background1_;
	GameEngineActor* Roll1_;
	GameEngineActor* AREL_;
	GameEngineActor* Finger_;
	GameEngineActor* Roll2_;

	int TransCount_;

	float TransTime;
};

//열겨형으로 해서 벡터에 접근?
//[]
