#pragma once
#include "GameEngineBase/GameEngineNameObject.h"
#include "GameEngineBase/GameEngineMath.h"
#include "GameEngineEnum.h"
#include <list>

class GameEngineLevel;
class GameEngineRenderer;
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

protected:
	virtual void Start() = 0; //�����ڿ��� ���� �κ��� �����
	virtual void Update() {};
	virtual void Render() {};

	void DebugRectRender();

private:
	float4	Position_;
	float4	Scale_;
	GameEngineLevel* Level_; //�ڽ��� �����ϴ� ����

	inline void SetLevel(GameEngineLevel* _Level)
	{
		Level_ = _Level;
	}

	void Rendering();

public:
	GameEngineRenderer* CreateRenderer(const std::string& _Image, RenderPivot _PivotType = RenderPivot::CENTER, const float4& _PivotPos = {0,0});

private:
	std::list<GameEngineRenderer*> RenderList_;
	std::list<GameEngineRenderer*>::iterator StartRenderIter;
	std::list<GameEngineRenderer*>::iterator EndRenderIter;
};

