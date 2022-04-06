#pragma once
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineImage.h>
#include <GameEngine/GameEngineActor.h>

class EnemyRoulette : public GameEngineActor
{
public:
	EnemyRoulette();
	~EnemyRoulette();

	EnemyRoulette(const EnemyRoulette& _Other) = delete;
	EnemyRoulette(EnemyRoulette&& _Other) noexcept = delete;
	EnemyRoulette& operator=(const EnemyRoulette& _Other) = delete;
	EnemyRoulette& operator=(EnemyRoulette&& _Other) noexcept = delete;

	inline void SetCurrentProfile(GameEngineRenderer* _Profile)
	{
		CurrentProfile_->SetImage(_Profile->GetImage()->GetNameCopy());
	}

	inline void SetCurrentIcon(GameEngineRenderer* _Icon)
	{
		CurrentProfile_->SetImage(_Icon->GetImage()->GetNameCopy());
	}

	inline GameEngineRenderer* GetCurrentprofile()
	{
		return CurrentProfile_;
	}

	inline GameEngineRenderer* GetCurrentIncon()
	{
		return CurrentIcon_;
	}

protected:
	void Start() override;
	void Update() override;
	void Render() override;

private:
	GameEngineRenderer* CurrentProfile_;
	GameEngineRenderer* CurrentIcon_;
};

