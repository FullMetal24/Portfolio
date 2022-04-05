#pragma once
#include "GameEngine/GameEngineActor.h"
#include <list>
#include "Puyo.h"

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

	void PuyoInput();
	bool IsLanding();

	void AddPuyo();

	//�ѿ�� ����Ʈ, ����?�� ����?
	//���� ������ ���� ����

protected:

private:

	//std::list<std::list<Puyo*>> PlayerMap_; //�����Ǵ� �� �ѿ�������� ������ �� �ѿ�� ������ �����Ѵ�.
	GameEngineActor* MyProfile_;
	Puyo* PlayerMap_[6][13];
	
	PuyoPair* CurrnetPair_;
	PuyoPair* NextPair_;
	PuyoPair* NextNextPair_;

	Puyo* Visited_;
	
	int RotationCount;
	int Score_;

	bool CreatePuyo_;
};

