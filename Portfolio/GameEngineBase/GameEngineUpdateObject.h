#pragma once
#include "GameEngineTime.h"

class GameEngineUpdateObject
{
public:
	GameEngineUpdateObject();
	virtual ~GameEngineUpdateObject();

	GameEngineUpdateObject(const GameEngineUpdateObject& _Other) = delete;
	GameEngineUpdateObject(GameEngineUpdateObject&& _Other) noexcept = delete;
	GameEngineUpdateObject& operator=(const GameEngineUpdateObject& _Other) = delete;
	GameEngineUpdateObject& operator=(GameEngineUpdateObject&& _Other) noexcept = delete;

	inline void On()
	{
		IsUpdate_ = true;
	}

	inline void Off()
	{
		IsUpdate_ = false;
	}

	virtual bool IsUpdate()
	{
		return IsUpdate_ && false == IsDeath_;
	}

	inline void Death()
	{
		IsDeath_ = true;
	}

	void ReleaseUpdate()
	{
		if (false == IsReleaseUpdate_)
		{
			return;
		}

		DeathTime_ = GameEngineTime::GetDeltaTime();

		if (0.0f >= DeathTime_)
		{
			DeathTime_ = true;
		}
	}

	inline void Death(float _Time)
	{
		DeathTime_ = _Time;
		IsReleaseUpdate_ = true;
	}
	
	inline bool IsDeath()
	{
		return IsDeath_;
	}

protected:

private:
	bool IsReleaseUpdate_;
	float DeathTime_;

	bool IsUpdate_;
	bool IsDeath_;
};

