#pragma once
#include <GameEngine/GameEngineLevel.h>
#include <GameEngineBase/GameEngineSound.h>

class FadeInOutBackground;
class BestRecordsActor;
class EnemyProfile;
class BestRecords : public GameEngineLevel
{
public:
	BestRecords();
	~BestRecords();

	BestRecords(const BestRecords& _Other) = delete;
	BestRecords(BestRecords&& _Other) noexcept = delete;
	BestRecords& operator=(const BestRecords& _Other) = delete;
	BestRecords& operator=(BestRecords&& _Other) noexcept = delete;

	inline void SetEnemyProfile(EnemyProfile* _Enemy)
	{
		EnemyProfile_ = _Enemy;
	}

protected:
	void Loading() override;
	void Update() override;

	void LevelChangeStart(GameEngineLevel* _PrevLevel) override;
	void LevelChangeEnd(GameEngineLevel* _NextLevel) override;

private:
	GameEngineSoundPlayer MainMenuBgm_;
	FadeInOutBackground* FadeInOutBackground_;

	EnemyProfile* EnemyProfile_;

	float Time_;


};

