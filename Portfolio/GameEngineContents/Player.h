#pragma once
#include "GameEngine/GameEngineActor.h"
#include "Puyo.h"
#include "ContentsEnum.h"
#include "GameEngineBase/GameEngineRandom.h"
#include <set>

class Fire;
class HindrancePuyo;
class Player : public GameEngineActor
{
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
	Puyo* CreatePuyo(int x, int y, PuyoColor _Color);

	//MovePuyo 관련 함수
	void InputPuyoMove();
	void AutoDown();
	void InputDown();
	void LandCheck();
	void OtherPuyoLandCheck();

	//PuyoCheck 관련 함수
	void SearchPuyo();
	void OnePuyoSearch(Puyo* _Puyo, std::vector<Puyo*>& _Out);

	//PuyoDestroy 관련 함수
	void DestroyPuyo();

	//PuyoDestroyEnd 관련 함수
	void DestroyEndPuyo();

	//PuyoLand 관련 함수
	void LandPuyo();

	//PuyoLandEnd 관련 함수
	void LandEndPuyo();

	void PlayerToEnemyAttack(float4 _FromPos);
	void CreateHindrancePuyo(int _Count);
	void HindrancePuyoCheck();
	void FallHindrancePuyo();


protected:
	void Start() override;
	void Update() override;

private:
	Puyo* PlayerMap_[15][6];

	PlayerState PlayerState_;

	std::vector<std::vector<Puyo*>> AllDestroyPuyo_;
	std::set<Puyo*> FindAllDestroy_;

	std::vector<Puyo*> Destroys_;
	std::vector<Puyo*> Falls_;

	std::vector<HindrancePuyo*> Hindrances_;

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
};

