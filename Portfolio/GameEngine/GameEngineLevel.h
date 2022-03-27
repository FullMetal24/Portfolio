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

		// insert와 find를 동시에 한다.

		std::list<GameEngineActor*>& Group = AllActor_[_Order]; 
		Group.push_back(NewActor);

		return NewActor;
	}

protected:
	virtual void Loading() = 0; //만들어지면서 리소스나 엑터를 만들 때
	virtual void Update() = 0; //레벨 수준의 업데이트

	//이전 레벨이 다음 레벨이 되면서 다음 레벨이 호출
	virtual void LevelChangeStart() {};
	//이전 레벨이 다음 레벨이 되면서 이전 레벨이 호출
	virtual void LevelChangeEnd() {};

private:
	std::map<int, std::list<GameEngineActor*>> AllActor_;
	//std::map<std::string, std::list<GameEngineActor*>> AllActor_;

	void ActorUpdate();
	void ActorRender();
	void ActorRealse();
};

//왜 엑터들을 리스트로 관리하는 걸까?
//스트링은 이름으로 찾기 위해서 사용. 하지만 최악의 수. 찾을 때 주소로 비교된다?