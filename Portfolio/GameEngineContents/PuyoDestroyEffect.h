#pragma once
#include <GameEngine/GameEngineActor.h>
#include "ContentsEnum.h"

class InGameActor;
class GameEngineRenderer;
class PuyoDestroyEffect : public GameEngineActor
{
public:
	PuyoDestroyEffect();
	~PuyoDestroyEffect();

	PuyoDestroyEffect(const PuyoDestroyEffect& _Other) = delete;
	PuyoDestroyEffect(PuyoDestroyEffect&& _Other) noexcept = delete;
	PuyoDestroyEffect& operator=(const PuyoDestroyEffect& _Other) = delete;
	PuyoDestroyEffect& operator=(PuyoDestroyEffect&& _Other) noexcept = delete;

	void Start() override;
	void Update() override;

	inline void SetColor(PuyoColor _Color)
	{
		IsSetColor_ = true;
		MyColor_ = _Color;
	}

	inline void SetPlay(bool _Play)
	{
		IsPlay_ = _Play;
	}

	void CreateEffect();
	void PlayEffect();
	void EndEffect();

protected:

private:
	InGameActor* Effects_[4];
	PuyoColor MyColor_;

	int Count_;

	float Speed_;
	float DirForce_;
	float Gravity_;

	bool IsPlay_;
	bool IsSetColor_;
};

