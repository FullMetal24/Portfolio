#pragma once
#include "InGameActor.h"
#include "ContentsEnum.h"
#include "GameEngineBase/GameEngineRandom.h"
#include <GameEngineBase/GameEngineSound.h>
#include <set>


enum class EnemyAnimationState
{
	Idle,
	Excited,
	Danger,
	Win,
	Lose
};


class InGame;
class Player;
class Fire;
class Puyo;
class EnemyProfile;
class WarningPuyo;
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
	void RandomRotate();
	void RandomDown();
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
	void CreateHindrancePuyo(int _Count);
	void HindrancePuyoCheck();
	void FallHindrancePuyo();
	void AddWarningPuyo(int _Count);
	void PopWarningPuyo();
	void CountPopWarningPuyo(int _Count);
	
	void OffsetEffect();

	void DigitScore(int _Score);
	void RenderToScore();

	//위험 시 거품 이펙트
	void DangerCheck();
	void AnimationStateCheck();
	void InitBubble();
	void VomitBubble();
	void DisappearBubble();

	//에네미 프로필
	void SetMyProfile(EnemyProfile* _Porifle);
	void IdleAnimation();
	void ExcitedAnimation();
	void DangerAnimation();
	void LoseAnimation();
	void WinAnimation();
	
	void Lose();

	inline void SetPlayer(Player* _Player)
	{
		Player_ = _Player;
	}

	inline void SetState(EnemyState _EnemyState)
	{
		EnemyState_ = _EnemyState;
	}

	inline EnemyState GetState()
	{
		return EnemyState_;
	}

protected:

private:
	Puyo* EnemyMap_[15][6];

	EnemyProfile* MyPorifle_;
	EnemyState EnemyState_;
	EnemyAnimationState AnimationState_;

	Player* Player_;

	std::vector<std::vector<Puyo*>> AllDestroyPuyo_;
	std::set<Puyo*> FindAllDestroy_;
	std::vector<Puyo*> Hindrances_;

	std::vector<InGameActor*> HindrancePreview_;
	std::vector<WarningPuyo*> WarningPuyos_;

	Fire* Fire_;
	float4 PlayerPoint_;

	GameEngineSound EffectSound_;

	GameEngineRandom Random_;

	Puyo* CenterPuyo_;
	Puyo* SecondPuyo_;
	Puyo* NextCenterPuyo_;
	Puyo* NextSecondPuyo_;
	Puyo* NextNextCenterPuyo_;
	Puyo* NextNextSecondPuyo_;

	float MoveTime_;
	float RotateTime_;
	float DownTime_;
	float AutoDownTime_;
	float InputDownTime_;
	float CheckTime_;
	float LandTime_;

	unsigned int Score_;
	unsigned int ScoreDigits_[10];
	unsigned int DigitSize_;
	GameEngineRenderer* ScoreRenderers_[10];

	unsigned int Chain_;

	InGameActor* Bubbles_[10];
	float4 BubbleDir_[10];
	int BubbleSpeed_[10];

	InGameActor* EnemyActors_;
	GameEngineRenderer* EnemyAnimations_[8];
	GameEngineRenderer* EnemyNames_[8];

	int ActionIndex_;

	bool IsAction_;
	bool IsDanger_;

	InGame* InGameLevel_;
	bool IsStart_;
	bool IsLosePlay_;
};



