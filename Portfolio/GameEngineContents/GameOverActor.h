#pragma once
#include <GameEngine/GameEngineActor.h>

class GameEngineRenderer;
class GameOverActor : public GameEngineActor
{
public:
	GameOverActor();
	~GameOverActor();

	GameOverActor(const GameOverActor& _Other) = delete;
	GameOverActor(GameOverActor&& _Other) noexcept = delete;
	GameOverActor& operator=(const GameOverActor& _Other) = delete;
	GameOverActor& operator=(GameOverActor&& _Other) noexcept = delete;

	void Start() override;
	void Update() override;
	void Render() override;


	inline GameEngineRenderer* GetMyRenderer()
	{
		return MyRenderer_;
	}

	inline void SetMyRenderer(GameEngineRenderer* _Renderer)
	{
		MyRenderer_ = _Renderer;
	}

	inline GameEngineRenderer* CreateRenderer(const std::string& _Name)
	{
		MyRenderer_ = CreateRenderer(_Name);

		if (nullptr == MyRenderer_)
		{
			return nullptr;
		}

		return MyRenderer_;
	}

protected:

private:
	GameEngineRenderer* MyRenderer_;

};