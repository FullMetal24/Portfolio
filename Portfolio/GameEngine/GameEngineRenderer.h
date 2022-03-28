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

	void SetImageScale();

	inline void SetScale(const float4& _Scale)
	{
		ScaleMode_ = RenderScaleMode::User;
		RenderScale_ = _Scale; 
	}

	void SetIndex(size_t _Index, float4 _Scale = {-1.0f, -1.0f });

protected:
	void Render();

private:
	GameEngineImage* Image_;
	RenderPivot PivotType_;
	RenderScaleMode ScaleMode_;

	float4 RenderPivot_;
	float4 RenderScale_; //화면 상에 그려낼 크기

	float4 RenderImagePivot_; //이미지에서 잘라내는 크기
	float4 RenderImageScale_;

	unsigned int TransColor_;
};

