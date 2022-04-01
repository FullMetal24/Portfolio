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

	//�������� ���� �����ϰ� �װɷ� �����س��� �ѿ並 ���ָ� ���� ������?
	//������ ���� �����ؼ� �÷� ����
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
	//��ǥ Ȯ��
	SetPosition(GetPosition() + /* OffSet_ + */(float4::DOWN * GameEngineTime::GetDeltaTime()));
}

void Puyo::Left()
{
	SetPosition(GetPosition() - (float4::LEFT * GameEngineTime::GetDeltaTime())); //�ð������� ���̴� ��?

}

void Puyo::Right()
{
	SetPosition(GetPosition() + (float4::RIGHT * GameEngineTime::GetDeltaTime()));
}



bool Puyo::IsLaunding() //�� ������ ȣ��? �ϴ� ����(�ٿ� ����Ʈ � �־ �ɵ�
{
	//�ٵ� ���⼭ Ȯ���Ϸ��� Player�� �˾ƾ� �Ѵ�.....
	//�갡 �÷��̾ �˾Ƶ� �ɱ�?
	//���⼭ ������ ���� �Ÿ� �÷��̾�� �� �� ������ �Ѵ�.


	return false;
}
