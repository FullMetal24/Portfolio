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

	inline void FadeOn()
	{
		IsOn_ = true;
	}

	//�ϳ��� ������� ���� �� ��� ���� ���� �ѹ� ����
	inline void Reset()
	{
		AlphaValue_ = 0;
		IsOn_ = false;
		FadeSpeed_ = 0.f;
		MyRenderer_->SetOrder(0);
		MyRenderer_->SetAlpha(0);
	}

	inline bool GetIsOn()
	{
		return IsOn_;
	}

	inline void SetFadeSpeed(float _Speed)
	{
		FadeSpeed_ = _Speed;
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

	bool IsOn_;
};

