#pragma once
#include "ContentsEnum.h"
#include "InGameActor.h"
#include "GameEngineBase/GameEngineRandom.h"
#include <set>

class Puyo;
class EnemyFSM;
class Fire;
class Player : public GameEngineActor
{
	friend Puyo;

public:
	Player();
	~Player();

	Player(const Player& _Other) = delete;
	Player(Player&& _Other) noexcept = delete;
	Player& operator=(const Player& _Other) = delete;
	Player& operator=(Player&& _Other) noexcept = delete;

	//NewPuyo 관련 함수
	void NewPuyoPair();
	void InitNextPair();
	Puyo* CreatePuyo(int _X, int _Y, PuyoColor _Color);
	void RenderToCenterPuyo();
	
	//MovePuyo 관련 함수
	void InputPuyoMove();
	void AutoDown();
	void InputDown();
	void LandCheck();
	void OtherPuyoLandCheck();

	//PuyoCheck 관련 함수
	void SearchPuyo();
	void OnePuyoSearch(Puyo* _Puyo, std::vector<Puyo*>& _Out);
	bool IsOver(float4 _Index);
	//PuyoDestroy 관련 함수
	void DestroyPuyo();

	//PuyoLand 관련 함수
	void LandPuyo();

	//HindrancePuyo 관련 함수
	void PlayerToEnemyAttack(float4 _FromPos);
	void CreateHindrancePuyo();
	void HindrancePuyoCheck();
	void FallHindrancePuyo();

	//스코어 관련 함수
	void ScoreInit();
	void DigitScore(int _Score);
	void RenderToScore();

	void Lose();

	inline void SetEnemyFSM(EnemyFSM* _Enemy)
	{
		Enemy_ = _Enemy;
	}

	inline PlayerState GetState()
	{
		return PlayerState_;
	}

	inline int GetRandomInt(int _At, int _Untill)
	{
		int Value = Random_.RandomInt(_At, _Untill);
		return Value;
	}

	inline float GetRandomFloat(float _At, float _Untill)
	{
		float Value = Random_.RandomFloat(_At, _Untill);
		return Value;
	}

protected:
	void Start() override;
	void Update() override;

private:
	Puyo* PlayerMap_[15][6];

	PlayerState PlayerState_;

	EnemyFSM* Enemy_;

	std::vector<std::vector<Puyo*>> AllDestroyPuyo_;
	std::set<Puyo*> FindAllDestroy_;

	std::vector<Puyo*> Hindrances_;

	GameEngineRandom Random_;

	Fire* Fire_;
	float4 EnemeyPoint_;

	Puyo* CenterPuyo_;
	Puyo* SecondPuyo_;
	Puyo* NextCenterPuyo_;
	Puyo* NextSecondPuyo_;
	Puyo* NextNextCenterPuyo_;
	Puyo* NextNextSecondPuyo_;

	float AutoDownTime_;
	float InputDownTime_;
	float InputDownAcc_;
	float CheckTime_;
	float LandTime_;

	unsigned int Score_;
	unsigned int ScoreDigits_[10];
	unsigned int DigitSize_;
	GameEngineRenderer* ScoreRenderers_[10];

	unsigned int Chain_;
};

