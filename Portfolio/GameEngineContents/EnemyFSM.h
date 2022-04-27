#pragma once
#include <GameEngine/GameEngineActor.h>
#include "ContentsEnum.h"
#include "Player.h"

class Puyo;
class PuyoPair;
class EnemyFSM : public GameEngineActor
{
public:
	EnemyFSM();
	~EnemyFSM();

	EnemyFSM(const EnemyFSM& _Other) = delete;
	EnemyFSM(EnemyFSM&& _Other) noexcept = delete;
	EnemyFSM& operator=(const EnemyFSM& _Other) = delete;
	EnemyFSM& operator=(EnemyFSM&& _Other) noexcept = delete;

	void Start() override;
	void Update() override;

	void DigitScore(int _Score);
	void RenderToScore();

	void AddPuyoPair(PuyoPair* _Pair);
	void CurrentPairInit();

	void PlayerInput();

	void MoveLeft();
	void MoveRight();
	void MoveDown();
	void Rotate();

	void CurrentPuyoLandCheck();

	void AutoFall();
	void FallAlonePuyo();

	int GradePuyoAnimation(int _Dx, int _Dy, Puyo* _Puyo);
	void ConvertPuyoAnimtion(int _Dx, int _Dy, Puyo* _Puyo);

	void SearchPuyo();
	void BfsPuyo(Puyo* _Puyo);
	void DestroyPuyo();
	void DestroyEndPuyo();
	void LandPuyo();
	void LandEndPuyo();

	void GreedyCheck();
	void EnemyToPlayerAttack(float4 _FromPos);

	inline EnemyState GetState()
	{
		return EnemyState_;
	}

	inline bool GetLose()
	{
		return IsLose_;
	}
	
protected:

private:
	Puyo* EnemyMap_[30][6];
	EnemyState EnemyState_;

	std::list<Puyo*> Visited_;
	std::vector<Puyo*> Falls_;

	PuyoPair* CurrentPair_;
	PuyoPair* NextPair_;
	PuyoPair* NextNextPair_;

	PuyoDir PuyoDir_;

	unsigned int Score_;
	unsigned int ScoreDigits_[10];
	unsigned int DigitSize_;
	GameEngineRenderer* ScoreRenderers_[10];

	int CenterX_;
	int CenterY_;

	int SecondX_;
	int SecondY_;

	unsigned int Chain_;

	float DownMoveDis_;
	float SideMoveDis_;

	float DownTime_;
	int LimitTime_;
	int FallTime_;

	bool IsWin_;
	bool IsLose_;
};


