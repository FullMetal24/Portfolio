#pragma once
#include <GameEngine/GameEngineActor.h>

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

	inline bool GetIsOn()
	{
		return IsOn_;
	}

	inline bool GetIsOff()
	{
		return IsOff_;
	}

protected:

private:
	GameEngineRenderer* Background_;

	int FadeValue_;

	bool IsOn_;
	bool IsOff_;
};

