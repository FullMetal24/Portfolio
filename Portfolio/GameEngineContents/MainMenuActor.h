#pragma once
#include <GameEngine/GameEngineActor.h>

class GameEngineRenderer;
class MainMenuActor : public GameEngineActor
{
public:
	MainMenuActor();
	~MainMenuActor();

	MainMenuActor(const MainMenuActor& _Other) = delete;
	MainMenuActor(MainMenuActor&& _Other) noexcept = delete;
	MainMenuActor& operator=(const MainMenuActor& _Other) = delete;
	MainMenuActor& operator=(MainMenuActor&& _Other) noexcept = delete;

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


protected:

private:
	GameEngineRenderer* MyRenderer_;

};