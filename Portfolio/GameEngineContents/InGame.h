#pragma once
#include "GameEngine/GameEngineLevel.h"
#include "Stage.h"

class Enemy;
class PuyoPair;
class InGame : public GameEngineLevel
{
public:
	InGame();
	~InGame();
	
	InGame(const InGame& _Other) = delete;
	InGame(InGame&& _Other) noexcept = delete;
	InGame& operator=(const InGame& _Other) = delete;
	InGame& operator=(InGame&& _Other) noexcept = delete;

	void Loading() override;
	void Update()  override;

	void SetEnemy(Enemy* _Enemy)
	{
		CurrentEnemy_ = _Enemy;
	}

	PuyoPair* CreatePuyoPair();

protected:

private:

	//13 * 6
	//�θ� �ѿ並 �ְ� �ڽ�(���� ���) �ѿ���� ���� ����
	//std::vector<Stage> Stages;
		
	//Plyer�� ������ Enemy�� �����Ҵ�(Enemy Ÿ��, �̹��� �Ѱ��ֱ�?)
	Enemy* CurrentEnemy_;
	GameEngineActor* StageName_; //�������� �̹���
};

