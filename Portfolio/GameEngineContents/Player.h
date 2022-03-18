#pragma once
#include "GameEngine/GameEngineActor.h"
#include "PuyoPair.h"

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

	//�ѿ�� ����Ʈ, ����?�� ����?
	//���� ������ ���� ����

protected:

private:
};

