#pragma once
#include <GameEngine/GameEngineActor.h>
#include <GameEngine/GameEngineRenderer.h>

class GameEngineRenderer;
class FadeInOutBackground : public GameEngineActor
{
public:
	FadeInOutBackground();
	~FadeInOutBackground();

	FadeInOutBackground(const FadeInOutBackground& _Other) = delete;
	FadeInOutBackground(FadeInOutBackground&& _Other) noexcept = delete;
	FadeInOutBackground& operator=(const FadeInOutBackground& _Other) = delete;
	FadeInOutBackground& operator=(FadeInOutBackground&& _Other) noexcept = delete;

	void Start() override;
	void Update() override;
	void Render() override;

	inline void FadeInOn()
	{
		IsIn_ = true;
	}


	inline void FadeOutOn()
	{
		IsOut_ = true;
	}

	inline void IsChangeOn()
	{
		IsInChange_ = true;
	}

	//하나의 배경으로 돌려 쓸 경우 쓰고 나서 한번 리셋
	inline void Reset()
	{
		AlphaValue_ = 0;
		IsIn_ = false;
		IsInChange_ = false;
		FadeSpeed_ = 0.f;
		MyRenderer_->SetOrder(0);
		MyRenderer_->SetAlpha(0);
	}

	inline bool GetIsIn()
	{
		return IsIn_;
	}

	inline bool GetIsInChange()
	{
		return IsInChange_;
	}

	inline bool GetIsOutChange()
	{
		return IsOutChange_;
	}

	inline void SetIsChage(bool _Change)
	{
		IsInChange_ = _Change;
	}

	inline void SetFadeSpeed(float _Speed)
	{
		FadeSpeed_ = _Speed;
	}

	inline int GetAlphaValue()
	{
		return AlphaValue_;
	}

	inline void SetAlphaValue(int _Value)
	{
		if (255 < _Value)
		{
			_Value = 255;
		}

		if (0 > _Value)
		{
			_Value = 0;
		}

		AlphaValue_ = _Value;
	}

	inline GameEngineRenderer* GetMyRenderer()
	{
		return MyRenderer_;
	}

	inline void SetMyRenderer(GameEngineRenderer* _Renderer)
	{
		MyRenderer_ = _Renderer;
	}

protected:

private:
	GameEngineRenderer* MyRenderer_;

	int AlphaValue_;

	float FadeSpeed_;

	bool IsIn_;
	bool IsOut_;
	bool IsInChange_;
	bool IsOutChange_;
};

