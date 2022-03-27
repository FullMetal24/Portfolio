#pragma once
#include "GameEngineBase/GameEngineNameObject.h"
#include <map>
#include <list>

class GameEngine;
class GameEngineActor;
class GameEngineLevel : public GameEngineNameObject
{
	friend GameEngine;

public:
	GameEngineLevel();
	virtual ~GameEngineLevel();

	GameEngineLevel(const GameEngineLevel& _Other) = delete;
	GameEngineLevel(GameEngineLevel&& _Other) noexcept = delete;
	GameEngineLevel& operator=(const GameEngineLevel& _Other) = delete;
	GameEngineLevel& operator=(GameEngineLevel&& _Other) noexcept = delete;

	template<typename ActorType>
	ActorType* CreateActor(int _Order = 0, const std::string& _Name = "")
	{
		ActorType* NewActor = new ActorType();
		GameEngineActor* StartActor = NewActor;
		NewActor->SetName(_Name);
		NewActor->SetLevel(this);
		StartActor->Start();

		// insert�� find�� ���ÿ� �Ѵ�.

		std::list<GameEngineActor*>& Group = AllActor_[_Order]; 
		Group.push_back(NewActor);

		return NewActor;
	}

protected:
	virtual void Loading() = 0; //��������鼭 ���ҽ��� ���͸� ���� ��
	virtual void Update() = 0; //���� ������ ������Ʈ

	//���� ������ ���� ������ �Ǹ鼭 ���� ������ ȣ��
	virtual void LevelChangeStart() {};
	//���� ������ ���� ������ �Ǹ鼭 ���� ������ ȣ��
	virtual void LevelChangeEnd() {};

private:
	std::map<int, std::list<GameEngineActor*>> AllActor_;
	//std::map<std::string, std::list<GameEngineActor*>> AllActor_;

	void ActorUpdate();
	void ActorRender();
	void ActorRealse();
};

//�� ���͵��� ����Ʈ�� �����ϴ� �ɱ�?
//��Ʈ���� �̸����� ã�� ���ؼ� ���. ������ �־��� ��. ã�� �� �ּҷ� �񱳵ȴ�?