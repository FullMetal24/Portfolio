#pragma once
#include "GameEngine/GameEngineActor.h"

class Puyo : public GameEngineActor
{
public:
	Puyo();
	~Puyo();

	Puyo(const Puyo& _Other) = delete;
	Puyo(Puyo&& _Other) noexcept = delete;
	Puyo& operator=(const Puyo& _Other) = delete;
	Puyo& operator=(Puyo&& _Other) noexcept = delete;

	void Start() override;
	void Update() override;
	void Render() override; 

	//�ؿ� �ƹ��͵� ������ ���� �Լ�(ù �������� ��ǥ�� ����ҵ�)(������ �ȼ��� ����������)
	//������ true�� ��ȯ�ϴ� �Լ�(�� Ȯ���ϰ� ���� ��� ����
	//������ �� ������ ���� �� �ִ��� Ž��
	//4�� �̻��� �� ��� �� ���� ����...

protected:

private:
	//��
	//�ѿ��� �˾Ƽ� �ȵ�
};

