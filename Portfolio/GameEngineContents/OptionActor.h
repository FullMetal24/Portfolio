#pragma once
#include <GameEngine/GameEngineActor.h>

class GameEngineRenderer;
class OptionActor : public GameEngineActor
{
public:
	OptionActor();
	~OptionActor();

	OptionActor(const OptionActor& _Other) = delete;
	OptionActor(OptionActor&& _Other) noexcept = delete;
	OptionActor& operator=(const OptionActor& _Other) = delete;
	OptionActor& operator=(OptionActor&& _Other) noexcept = delete;

	void Start() override;
	void Update() override;

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

};

