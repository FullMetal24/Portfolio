#pragma once
#include "GameEngine/GameEngineActor.h"

class MM_BackGround : public GameEngineActor
{
public:
	MM_BackGround();
	~MM_BackGround();

	MM_BackGround(const MM_BackGround& _Other) = delete;
	MM_BackGround(MM_BackGround&& _Other) noexcept = delete;
	MM_BackGround& operator=(const MM_BackGround& _Other) = delete;
	MM_BackGround& operator=(MM_BackGround&& _Other) noexcept = delete;

	void Start() override;
	void Update() override;
	void Render() override;

protected:

private:

};

