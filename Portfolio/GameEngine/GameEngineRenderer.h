#pragma once
#include "GameEngineActorSubObject.h"
#include "GameEngineEnum.h"
#include <map>

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

	inline GameEngineImage* GetImage()
	{
		return Image_;
	}

protected:
	void Render();

private:
	friend class FrameAnimation;

private:
	GameEngineImage* Image_; //그려낼 이미지
	RenderPivot PivotType_;
	RenderScaleMode ScaleMode_;

	float4 RenderPivot_;
	float4 RenderScale_; //화면 상에 그려낼 크기

	float4 RenderImagePivot_; //이미지에서 잘라내는 크기
	float4 RenderImageScale_;

	unsigned int TransColor_;


private:
	class FrameAnimation
	{
	public:
		GameEngineRenderer* Renderer;
		GameEngineImage* _Image;
		int CurrentFrame_;
		int StartFrame_;
		int EndFrame_;
		float CurrentInterTime_;
		float InterTime_;
		bool Loop_;

	public:
		FrameAnimation()
			: _Image(nullptr)
			, CurrentFrame_(-1)
			, StartFrame_(-1)
			, EndFrame_(-1)
			, CurrentInterTime_(0.1f)
			, InterTime_(0.1f)
			, Loop_(true)
		{

		}

	public:
		void Reset()
		{
			CurrentFrame_ = StartFrame_;
			CurrentInterTime_ = InterTime_;
		}

		void Update();
	};

public:
	void CreateAnimation(const std::string& _Image, const std::string& _Name, int _StartIndex, int _EndIndex, float _InterTime, bool Loop = true);

	void ChangeAnimation(const std::string& _Name);

private:
	std::map<std::string, FrameAnimation> Animations_;
	FrameAnimation* CurrentAnimation_;

};

