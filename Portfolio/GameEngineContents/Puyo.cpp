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
