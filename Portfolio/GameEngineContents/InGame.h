#pragma once
#include "GameEngine/GameEngineLevel.h"
#include "GameEngine/GameEngineActor.h"
#include "GameEngine/GameEngineRenderer.h"
#include "Stage.h"
#include "Player.h"
#include <vector>

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
	void LevelChangeStart() override;
	void LevelChangeEnd() override;

	void SetEnemy(Enemy* _Enemy)
	{
		CurrentEnemy_ = _Enemy;
	}

	PuyoPair* CreatePuyoPair();

protected:

private:

	//13 * 6
	//�θ� �ѿ並 �ְ� �ڽ�(���� ���) �ѿ���� ���� ����
	//std::vector<Stage*> Stages;
	Stage* Stages_[3]; //���� �������� ���� ���������� �ȴ�.
		
	//Plyer�� ������ Enemy�� �����Ҵ�(Enemy Ÿ��, �̹��� �Ѱ��ֱ�?)

	Player*	Player_;
	Enemy* CurrentEnemy_;

	GameEngineRenderer* StageName_; //�������� �̹��� (�������� ��������

	int StageClear_;
};
	
//�������� 
//�������� ���� ����� �������� ���� �� �ΰ� ���� �ε��ϴ� ������ ������?
//�������� �ΰ��ӿ� �ΰ� �ϴ� ����� ���


