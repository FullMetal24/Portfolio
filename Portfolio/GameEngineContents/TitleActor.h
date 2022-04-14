#pragma once
#include <GameEngine/GameEngineActor.h>

class GameEngineRenderer;
class TitleActor : public GameEngineActor
{
public:
	TitleActor();
	~TitleActor();

	TitleActor(const TitleActor& _Other) = delete;
	TitleActor(TitleActor&& _Other) noexcept = delete;
	TitleActor& operator=(const TitleActor& _Other) = delete;
	TitleActor& operator=(TitleActor&& _Other) noexcept = delete;

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
