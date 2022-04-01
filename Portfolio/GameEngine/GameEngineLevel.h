#pragma once
#include <list>
#include <map>
#include <GameEngineBase/GameEngineNameObject.h>
#include <GameEngineBase/GameEngineMath.h>

class GameEngine;
class GameEngineActor;
class GameEngineLevel : public GameEngineNameObject
{
	friend GameEngine;
public:
	// constrcuter destructer
	GameEngineLevel();

	// 소멸자 virtual 중요
	virtual ~GameEngineLevel();

	// delete Function
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
		std::list<GameEngineActor*>& Group = AllActor_[_Order];
		Group.push_back(NewActor);

		//// _Order 액터들이 돌아가는 순서를 의미하게 된다.
		//// insert와 find를 동시에
		//std::map<int, std::list<GameEngineActor*>>::iterator FindGroup
		//	= AllActor_.find(_Order);

		//if (FindGroup == AllActor_.end())
		//{

		//	// AllActor_.insert(std::make_pair(_Order, std::list<GameEngineActor*>()));
		//	// 이게더 빠름
		//	AllActor_.insert(
		//		std::map<int, std::list<GameEngineActor*>>::value_type(_Order, std::list<GameEngineActor*>())
		//	);
		//	FindGroup = AllActor_.find(_Order);
		//}

		return NewActor;
	}

	inline float4 GetCameraPos() 
	{
		return CameraPos_;
	}

	inline void MoveCameraPos(const float4& _Value)
	{
		CameraPos_ += _Value;
	}

	inline void SetCameraPos(const float4& _Value )
	{
		CameraPos_  = _Value;
	}


protected:
	// 시점함수
	// 만들어지면서 리소스나 액터를 만들때 써라
	virtual void Loading() = 0;
	// 이 레벨이 현재 레벨일때 해야할일을 실행한다.
	virtual void Update() = 0;
	// Current레벨 => Next레벨로 이전할때 현재레벨이 실행하는 함수.
	virtual void LevelChangeStart() {}
	// Current레벨 => Next레벨로 이전할때 이전레벨이 실행하는 함수.
	virtual void LevelChangeEnd() {}

private:
	// std::vector로 관리하는게 더 좋다고 생각..
	std::map<int, std::list<GameEngineActor*>> AllActor_;

	float4 CameraPos_;

	void ActorUpdate();
	void ActorRender();
	void ActorRelease();
};
