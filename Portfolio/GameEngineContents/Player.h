#pragma once
#include "GameEngine/GameEngineActor.h"
#include <list>
#include <set>
#include "Puyo.h"
#include "ContentsEnum.h"
#include "InGameActor.h"
#include <GameEngineBase/GameEngineRandom.h>

class Puyo;
class PuyoPair;
class HindrancePuyo;
class Fire;
class FSM;
class Player : public GameEngineActor
{
public:
	Player();
	~Player();

	Player(const Player& _Other) = delete;
	Player(Player&& _Other) noexcept = delete;
	Player& operator=(const Player& _Other) = delete;
	Player& operator=(Player&& _Other) noexcept = delete;

	void Start() override;
	void Update() override;
	
	void PlayerInput();

	void MoveLeft();
	void MoveRight();
	void MoveDown();
	void Rotate();

	void AddPuyoPair(PuyoPair* _Pair);
	void CurrentPairInit();

	void CurrentPuyoLandCheck();

	void AutoFall();
	void FallAlonePuyo();

	int GradePuyoAnimation(int _Dx, int _Dy, Puyo* _Puyo);
	void ConvertPuyoAnimtion(int _Dx, int _Dy, Puyo* _Puyo);

	void DigitScore(int _Score);
	void RenderToScore();

	void SearchPuyo(); 
	void DestroyPuyo();
	void DestroyEndPuyo();
	void LandPuyo();
	void LandEndPuyo();
	void NewPuyoCreate();
	PuyoPair* CreatePuyoPair();

	inline FSM* GetEnemy(FSM* _Enemy)
	{
		Enemy_ = _Enemy;
	}

	inline void SetCurrentPair(PuyoPair* _Current)
	{
		CurrentPair_ = _Current;
	}

	inline void SetNextPair(PuyoPair* _Next)
	{
		NextPair_ = _Next;
	}

	inline void SetNextNextPair(PuyoPair* _NextNext)
	{
		NextNextPair_ = _NextNext;
	}

	inline PlayerState GetState()
	{
		return PlayerState_;
	}

	void OnePuyoSearch(Puyo* _Puyo, std::vector<Puyo*>& _Out);

	void PlayerToEnemyAttack(float4 _FromPos);
	void CreateHindrancePuyo(int _Count);
	void HindrancePuyoCheck();
	void FallHindrancePuyo();

protected:

private:
	PlayerState PlayerState_;
	FSM* Enemy_;

	Puyo* PlayerMap_[30][6];

	std::vector<Puyo*> Destroys_;
	std::vector<Puyo*> Falls_;

	std::vector<std::vector<Puyo*>> AllDestroyPuyo_; 
	std::set<Puyo*> FindAllDestroy_;

	std::vector<HindrancePuyo*> HindrancePuyos_;

	float4 EnemeyPoint_;
	Fire* Fire_;

	PuyoPair* CurrentPair_;
	PuyoPair* NextPair_;
	PuyoPair* NextNextPair_;

	PuyoDir PuyoDir_;

	unsigned int Score_;
	unsigned int ScoreDigits_[10];
	unsigned int DigitSize_;
	GameEngineRenderer* ScoreRenderers_[10];

	GameEngineRandom RandomColor_;

	int CenterX_;
	int CenterY_;

	int SecondX_;
	int SecondY_;

	unsigned int Chain_;

	float DownMoveDis_;
	float SideMoveDis_;

	float AutoDownTime_;
	float DestroyDownTime_;
	int LimitTime_;
	int FallTime_;

	bool IsWin_;
	bool IsLose_;

};

