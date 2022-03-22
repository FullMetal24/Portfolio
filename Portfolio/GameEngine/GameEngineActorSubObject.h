#pragma once
#include "GameEngineActor.h"

//렌더러에게 엑터를 알려주기 위한 클래스
class GameEngineActorSubObject
{
	friend GameEngineActor;

public:
	GameEngineActorSubObject();
	~GameEngineActorSubObject();

	GameEngineActorSubObject(const GameEngineActorSubObject& _Other) = delete;
	GameEngineActorSubObject(GameEngineActorSubObject&& _Other) noexcept = delete;
	GameEngineActorSubObject& operator=(const GameEngineActorSubObject& _Other) = delete;
	GameEngineActorSubObject& operator=(GameEngineActorSubObject&& _Other) noexcept = delete;
	
	inline GameEngineActor* GetActor()
	{
		return Actor_;
	}

protected:
	inline void SetActor(GameEngineActor* _Actor)
	{
		Actor_ = _Actor;
	}


private:
	GameEngineActor* Actor_;

};

