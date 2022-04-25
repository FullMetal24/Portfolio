#pragma once
#include "GameEngine/GameEngineActor.h"
#include <list>

class Puyo;
class PuyoPair;
class GameEngineRenderer;
class EnemyProfile : public GameEngineActor //AI
{
public:
	EnemyProfile();
	~EnemyProfile();

	EnemyProfile(const EnemyProfile& _Other) = delete;
	EnemyProfile(EnemyProfile&& _Other) noexcept = delete;
	EnemyProfile& operator=(const EnemyProfile& _Other) = delete;
	EnemyProfile& operator=(EnemyProfile&& _Other) noexcept = delete;

	void Start() override;
	void Update() override;
	void Render() override;

	GameEngineRenderer* GetProfile()
	{
   		return MyProfile_;
	}

	GameEngineRenderer* GetIcon()
	{
		return MyIcon_;
	}
	

	GameEngineRenderer* GetRenderName()
	{
		return MyName_;
	}

	void SetProfile(GameEngineRenderer* _Profile)
	{
		MyProfile_ = _Profile;
	}

	void SetMyAnimation(GameEngineRenderer* _Renderer)
	{
		MyAnimation_ = _Renderer;
	}

	GameEngineRenderer* GetMyAnimation()
	{
		return MyAnimation_;
	}

	void SetIcon(GameEngineRenderer* _Icon)
	{
		MyIcon_ = _Icon;
	}

	void SetRenderName(GameEngineRenderer* _Name)
	{
		MyName_ = _Name;
	}

	void SetSD(GameEngineRenderer* _SD)
	{
		MySD_ = _SD;
	}

protected:

private:
	GameEngineRenderer* MyProfile_; //에네미 셀렉트 레벨 프로필
	GameEngineRenderer* MyAnimation_; //인게임 레벨 애니메이션(다 애니메이션으로 만들어야 함)
	GameEngineRenderer* MyIcon_; 
	GameEngineRenderer* MyName_; 
	GameEngineRenderer* MySD_;


};

