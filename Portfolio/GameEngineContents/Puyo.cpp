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
	//�ѿ�� �������� ���� �� ����

	//�������� ���� �����ϰ� �װɷ� �����س��� �ѿ並 ���ָ� ���� ������?
	//������ ���� �����ؼ� �÷� ����

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
