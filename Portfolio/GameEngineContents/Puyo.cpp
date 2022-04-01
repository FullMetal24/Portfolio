#include "Puyo.h"
#include "GameEngineBase/GameEngineWindow.h"
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngine.h>
#include <GameEngineBase/GameEngineTime.h>

Puyo::Puyo() 
{
}

Puyo::~Puyo() 
{
}

void Puyo::Start()
{
	SetPosition(GameEngineWindow::GetScale().Half());
	SetScale({ 100, 100 });

	//랜덤으로 색을 지정하고 그걸로 구별해내서 뿌요를 없애면 되지 않을까?
	//위에서 난수 생성해서 컬러 지정
	switch (PuyoColor_)
	{
	case Color::RED:
		CreateRenderer("Puyo.bmp");
		break;
	case Color::BLUE:
		CreateRenderer("Puyo.bmp");
		break;
	case Color::GREEN:
		CreateRenderer("Puyo.bmp");
		break;
	case Color::YELLO:
		CreateRenderer("Puyo.bmp");

		break;
	case Color::PURPLE:
		CreateRenderer("Puyo.bmp");
		break;
	}
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



bool Puyo::IsLaunding() //매 프레임 호출? 일단 보류(다운 라이트 등에 넣어도 될듯
{
	//근데 여기서 확인하려면 Player를 알아야 한다.....
	//얘가 플레이어를 알아도 될까?
	//여기서 만들지 않을 거면 플레이어에서 두 개 만들어야 한다.


	return false;
}
