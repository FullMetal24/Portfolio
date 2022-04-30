#pragma once
#include <GameEngine/GameEngineActor.h>

// Ό³Έν :
class OffsetStar : public GameEngineActor
{
public:
	// constrcuter destructer
	OffsetStar();
	~OffsetStar();

	// delete Function
	OffsetStar(const OffsetStar& _Other) = delete;
	OffsetStar(OffsetStar&& _Other) noexcept = delete;
	OffsetStar& operator=(const OffsetStar& _Other) = delete;
	OffsetStar& operator=(OffsetStar&& _Other) noexcept = delete;

	void Start() override;
	void Update() override;

	inline void SetStartPos(float4 _StartPos)
	{
		StartPos_ = _StartPos;
		SetPosition(StartPos_);
	}

	inline GameEngineRenderer* GetMyAnimation()
	{
		return MyAnimation_;
	}

	inline void SetUpdate(bool _Update)
	{
		IsUpdate_ = _Update;
	}

	inline void SetDirection(float4 _Dir)
	{
		Dir_ = _Dir;
	}

protected:

private:
	GameEngineRenderer* MyAnimation_;

	float4 StartPos_;
	float4 Dir_;
	bool IsUpdate_;

};

