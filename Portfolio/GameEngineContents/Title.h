#pragma once
#include "GameEngine/GameEngineLevel.h"

// Ό³Έν :
class Title : public GameEngineLevel
{
public:
	// constrcuter destructer
	Title();
	~Title();

	// delete Function
	Title(const Title& _Other) = delete;
	Title(Title&& _Other) noexcept = delete;
	Title& operator=(const Title& _Other) = delete;
	Title& operator=(Title&& _Other) noexcept = delete;

	void Loading() override;
	void Update()  override;

protected:

private:

};

