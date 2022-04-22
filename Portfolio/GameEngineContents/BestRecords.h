#pragma once
#include <GameEngine/GameEngineLevel.h>
#include <GameEngineBase/GameEngineSound.h>

class FadeInOutBackground;
class BestRecordsActor;
class BestRecords : public GameEngineLevel
{
public:
	// constrcuter destructer
	BestRecords();
	~BestRecords();

	// delete Function
	BestRecords(const BestRecords& _Other) = delete;
	BestRecords(BestRecords&& _Other) noexcept = delete;
	BestRecords& operator=(const BestRecords& _Other) = delete;
	BestRecords& operator=(BestRecords&& _Other) noexcept = delete;

protected:
	void Loading() override;
	void Update() override;

	void LevelChangeStart(GameEngineLevel* _PrevLevel) override;
	void LevelChangeEnd(GameEngineLevel* _NextLevel) override;

private:
	GameEngineSoundPlayer MainMenuBgm_;
	FadeInOutBackground* FadeInOutBackground_;

	BestRecordsActor* Enemy_;

	float Time_;


};

