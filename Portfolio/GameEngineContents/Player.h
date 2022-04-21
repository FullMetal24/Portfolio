#pragma once
#include "GameEngine/GameEngineActor.h"
#include <list>
#include "Puyo.h"
#include "ContentsEnum.h"

class Puyo;
class PuyoPair;
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
	void Render() override;

	void MoveLeft();
	void MoveRight();
	void MoveDown();
	void Rotate();

	void BfsPuyo(Puyo* _Puyo);
	void DestroyPuyo();

	void CurrentPairInit();
	void AddPuyoPair(PuyoPair* _Pair);

	void LandCheck();
	void FallPuyo(); //»Ñ¿ä È¥ÀÚ °¡¼Ó ³«ÇÏ
	void FallAfterLanding();

	int GradePuyoAnimation(int _Dx, int _Dy, Puyo* _Puyo);
	void ConvertPuyoAnimtion(int _Dx, int _Dy, Puyo* _Puyo);

	void DigitScore(int _Score);
	void RenderToScore();

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

	inline bool GetAllLanding()
	{
		return IsAllLanding_;
	}

	inline bool GetLose()
	{
		return IsLose_;
	}

protected:

private:
	Puyo* PlayerMap_[30][6];
	std::list<Puyo*> Visited_;

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
	int DestroyFallTime_;

	bool IsStart_;
	bool IsAllLanding_;
	bool IsLose_;
};
