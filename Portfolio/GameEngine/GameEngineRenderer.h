#pragma once
#include "GameEngineImage.h"
#include "GameEngineEnum.h"

class GameEngineRenderer
{
public:
	GameEngineRenderer();
	~GameEngineRenderer();

	GameEngineRenderer(const GameEngineRenderer& _Other) = delete;
	GameEngineRenderer(GameEngineRenderer&& _Other) noexcept = delete;
	GameEngineRenderer& operator=(const GameEngineRenderer& _Other) = delete;
	GameEngineRenderer& operator=(GameEngineRenderer&& _Other) noexcept = delete;

	void SetImage(const std::string& _Name);
	inline void SetType(const RenderPivot& _Type)
	{
		PivotType_ = _Type;
	}

protected:
	void Render();

private:
	GameEngineImage* Image_;
	RenderPivot PivotType_;
};

