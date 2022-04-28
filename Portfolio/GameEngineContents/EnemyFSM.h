#pragma once
#include "InGameActor.h"
#include "ContentsEnum.h"
#include "GameEngineBase/GameEngineRandom.h"
#include <set>

class Player;
class Fire;
class Puyo;
class EnemyProfile;
class EnemyFSM : public GameEngineActor
{
	friend Puyo;

public:
	EnemyFSM();
	~EnemyFSM();

	EnemyFSM(const EnemyFSM& _Other) = delete;
	EnemyFSM(EnemyFSM&& _Other) noexcept = delete;
	EnemyFSM& operator=(const EnemyFSM& _Other) = delete;
	EnemyFSM& operator=(EnemyFSM&& _Other) noexcept = delete;

	void Start() override;
	void Update() override;

	//NewPuyo 관련 함수
	void NewPuyoPair();
	void InitNextPair();
	Puyo* CreatePuyo(int _X, int _Y, PuyoColor _Color);
	void RenderToCenterPuyo();

	//MovePuyo 관련 함수
	void GreedyPuyoMove();
	void AutoDown();
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
	void EnemyToPlayerAttack(float4 _FromPos);
	void CreateHindrancePuyo();
	void HindrancePuyoCheck();
	void FallHindrancePuyo();

	void DigitScore(int _Score);
	void RenderToScore();

	//위험 시 거품 이펙트
	void DangerCheck();
	void InitBubble();
	void VomitBubble();
	void DisappearBubble();

	//에네미 프로필
	void EnemyAnimatioInit();
	void SetMyProfile(EnemyProfile* _Porifle);

	inline void SetPlayer(Player* _Player)
	{
		Player_ = _Player;
	}

	inline EnemyState GetState()
	{
		return EnemyState_;
	}


protected:

private:
	Puyo* EnemyMap_[15][6];

	EnemyState EnemyState_;

	Player* Player_;

	std::vector<std::vector<Puyo*>> AllDestroyPuyo_;
	std::set<Puyo*> FindAllDestroy_;
	std::vector<Puyo*> Hindrances_;

	Fire* Fire_;
	float4 PlayerPoint_;

	GameEngineRandom Random_;

	Puyo* CenterPuyo_;
	Puyo* SecondPuyo_;
	Puyo* NextCenterPuyo_;
	Puyo* NextSecondPuyo_;
	Puyo* NextNextCenterPuyo_;
	Puyo* NextNextSecondPuyo_;

	float AutoDownTime_;
	float InputDownTime_;
	float CheckTime_;
	float LandTime_;

	unsigned int Score_;
	unsigned int ScoreDigits_[10];
	unsigned int DigitSize_;
	GameEngineRenderer* ScoreRenderers_[10];

	unsigned int Chain_;

	InGameActor* Bubbles_[15];
	float4 BubbleDir_[15];
	int BubbleSpeed_[15];
	bool IsDanger_;

	InGameActor* EnemyActors_;
	GameEngineRenderer* EnemyAnimations_[8];
	GameEngineRenderer* EnemyNames_[8];

};


