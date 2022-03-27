#pragma once
#include "GameEngine/GameEngineActor.h"
#include <list>
#include "Puyo.h"


class PuyoPair;
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

	void Start() override;
	void Update() override;
	void Render() override;

	void AddPuyo();

	//�ѿ�� ����Ʈ, ����?�� ����?
	//���� ������ ���� ����

protected:

private:

	//std::list<std::list<Puyo*>> PlayerMap_; //�����Ǵ� �� �ѿ�������� ������ �� �ѿ�� ������ �����Ѵ�.

	Puyo* PlayerMap_[6][13];
	
	PuyoPair* CurrnetPair_;
	PuyoPair* NextPair_;
	PuyoPair* NextNextPair_;

	Puyo* Visited_[];

};

