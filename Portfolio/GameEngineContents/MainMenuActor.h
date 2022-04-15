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