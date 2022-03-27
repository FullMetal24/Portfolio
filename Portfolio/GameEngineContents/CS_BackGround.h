#pragma once
#include "GameEngine/GameEngineActor.h"

class CS_BackGround : public GameEngineActor
{
public:
	// constrcuter destructer
	CS_BackGround();
	~CS_BackGround();

	// delete Function
	CS_BackGround(const CS_BackGround& _Other) = delete;
	CS_BackGround(CS_BackGround&& _Other) noexcept = delete;
	CS_BackGround& operator=(const CS_BackGround& _Other) = delete;
	CS_BackGround& operator=(CS_BackGround&& _Other) noexcept = delete;

	void Start() override;
	void Update() override;
	void Render() override;

protected:

private:

};

