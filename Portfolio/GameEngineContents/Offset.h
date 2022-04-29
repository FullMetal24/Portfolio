#pragma once
#include <GameEngine/GameEngineActor.h>

class GameEngineRenderer;
class Offset : public GameEngineActor
{
public:
	// constrcuter destructer
	Offset();
	~Offset();

	// delete Function
	Offset(const Offset& _Other) = delete;
	Offset(Offset&& _Other) noexcept = delete;
	Offset& operator=(const Offset& _Other) = delete;
	Offset& operator=(Offset&& _Other) noexcept = delete;

	void Start() override;
	void Update() override;

	inline void SetStartPos(float4 _StartPos)
	{
		StartPos_ = _StartPos;
		SetPosition(StartPos_);
	}

	inline void SetMyRenderer(GameEngineRenderer* _Renderer)
	{
		MyRenderer_ = _Renderer;
	}

	inline GameEngineRenderer* GetMyRenderer()
	{
		return MyRenderer_;
	}

	inline void SetUpdate(bool _Update)
	{
		IsUpdate_ = _Update;
	}

protected:

private:
	GameEngineRenderer* MyRenderer_;

	float4 StartPos_;
	bool IsUpdate_;

};

