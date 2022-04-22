#pragma once
#include <GameEngine/GameEngineActor.h>

class GameEngineRenderer;
class BestRecordsActor : public GameEngineActor
{
public:
	// constrcuter destructer
	BestRecordsActor();
	~BestRecordsActor();

	// delete Function
	BestRecordsActor(const BestRecordsActor& _Other) = delete;
	BestRecordsActor(BestRecordsActor&& _Other) noexcept = delete;
	BestRecordsActor& operator=(const BestRecordsActor& _Other) = delete;
	BestRecordsActor& operator=(BestRecordsActor&& _Other) noexcept = delete;

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

