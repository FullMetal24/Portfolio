#pragma once
#include "GameEngineActorSubObject.h"
#include "GameEngineEnum.h"

class GameEngineImage;
class GameEngineRenderer: public GameEngineActorSubObject
{
	friend GameEngineActor;

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

	inline void SetPivot(const float4& _Pos)
	{
		RenderPivot_ = _Pos;
	}

	inline void SetColor(const int& _Color)
	{
		TransColor_ = _Color;
	}

	inline void SetScaleMode(const RenderScaleMode& _Mode)
	{
		ScaleMode_ = _Mode;
	}


protected:
	void Render();

private:
	GameEngineImage* Image_;
	RenderPivot PivotType_;
	RenderScaleMode ScaleMode_;
	float4 RenderPivot_;
	float4 RenderScale_;
	unsigned int TransColor_;
};

