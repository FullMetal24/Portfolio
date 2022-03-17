#pragma once
#include "GameEngineBase/GameEngineNameObject.h"
#include "GameEngineBase/GameEngineMath.h"

class GameEngineLevel;
class GameEngineActor : public GameEngineNameObject
{
public:
	friend GameEngineLevel;

	GameEngineActor();
	~GameEngineActor();

	GameEngineActor(const GameEngineActor& _Other) = delete;
	GameEngineActor(GameEngineActor&& _Other) noexcept = delete;
	GameEngineActor& operator=(const GameEngineActor& _Other) = delete;
	GameEngineActor& operator=(GameEngineActor&& _Other) noexcept = delete;

protected:
	virtual void Start() = 0; //생성자에서 못할 부분을 대신함
	virtual void Update() {};
	virtual void Render() {};

	void DebugRectRender();

	inline float4 GetPosition()
	{
		return Position_;
	}

	inline float4 GetScale()
	{
		return Scale_;
	}

	inline void SetPosition(float4 _Value)
	{
		Position_ = _Value;
	}

	inline void SetScale(float4 _Value)
	{
		Scale_ = _Value;
	}

private:
	float4	Position_;
	float4	Scale_;
	GameEngineLevel* Level_; //자신이 존재하는 레벨

	inline void SetLevel(GameEngineLevel* _Level)
	{
		Level_ = _Level;
	}

};

