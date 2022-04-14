#pragma once
#include <GameEngine/GameEngineActor.h>

class GameEngineRenderer;
class InGameActor : public GameEngineActor
{
public:
	InGameActor();
	~InGameActor();

	InGameActor(const InGameActor& _Other) = delete;
	InGameActor(InGameActor&& _Other) noexcept = delete;
	InGameActor& operator=(const InGameActor& _Other) = delete;
	InGameActor& operator=(InGameActor&& _Other) noexcept = delete;

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
		return MyRenderer_;
	}

protected:

private:
	GameEngineRenderer* MyRenderer_;

};