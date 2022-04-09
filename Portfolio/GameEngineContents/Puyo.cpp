#include "Puyo.h"
#include "GameEngineBase/GameEngineWindow.h"
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngine.h>
#include <GameEngineBase/GameEngineTime.h>

Puyo::Puyo() 
	:  IsLanding_(false)
{
}

Puyo::~Puyo() 
{
}

void Puyo::Start()
{
	//뿌요는 렌더러를 가질 수 없음

	//랜덤으로 색을 지정하고 그걸로 구별해내서 뿌요를 없애면 되지 않을까?
	//위에서 난수 생성해서 컬러 지정

}

void Puyo::Update()
{
}

void Puyo::Render()
{

}

void Puyo::Down()
{
	//좌표 확인
	SetPosition(GetPosition() + /* OffSet_ + */(float4::DOWN * GameEngineTime::GetDeltaTime()));
}

void Puyo::Left()
{
	SetPosition(GetPosition() - (float4::LEFT * GameEngineTime::GetDeltaTime())); //시각적으로 보이는 것?

}

void Puyo::Right()
{
	SetPosition(GetPosition() + (float4::RIGHT * GameEngineTime::GetDeltaTime()));
}
