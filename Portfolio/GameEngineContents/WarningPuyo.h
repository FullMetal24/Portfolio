#pragma once
#include <GameEngine/GameEngineActor.h>

class GameEngineRenderer;
class WarningPuyo : public GameEngineActor
{
public:
	// constrcuter destructer
	WarningPuyo();
	~WarningPuyo();

	// delete Function
	WarningPuyo(const WarningPuyo& _Other) = delete;
	WarningPuyo(WarningPuyo&& _Other) noexcept = delete;
	WarningPuyo& operator=(const WarningPuyo& _Other) = delete;
	WarningPuyo& operator=(WarningPuyo&& _Other) noexcept = delete;

	void Start() override;
	void Update() override;

	void MoveLeftPuyo();
	void MoveRightPuyo();

	inline void SetStartPos(float4 _StartPos)
	{
		StartPos_ = _StartPos;
		SetPosition(StartPos_);
	}

	inline void SetEndPos(float4 _EndPos)
	{
		EndPos_ = _EndPos;
	}

	inline GameEngineRenderer* GetMyRenderer()
	{
		return MyRenderer_;
	}

	inline void SetMyRenderer(GameEngineRenderer* _Renderer)
	{
		MyRenderer_ = _Renderer;
	}

	inline void MoveLeft()
	{
		MoveLeft_ = true;
	}

	inline void MoveRight()
	{
		MoveRight_ = true;
	}

protected:

private:
	GameEngineRenderer* MyRenderer_;

	float4 StartPos_;
	float4 EndPos_;
	float Alpha_;

	bool MoveLeft_;
	bool MoveRight_;
};

