#pragma once
#include "GameEngine/GameEngineActor.h"

enum class Color
{
	RED,
	BLUE,
	GREEN,
	YELLO,
	PURPLE
};


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
	//4�� �̻��� �� ��� �� ���� ����... Ʈ��ŷ�ؾ���

	void Down();
	void Left();
	void Right();
	void CheckSearch();

	//inline bool GetLaundiung()
	//{
	//	return IsLanding_;
	//}

protected:

private:
	Color PuyoColor_;
	bool IsLaunding_;
	//��
	//�ѿ��� �˾Ƽ� �ȵ�
	//������ �ѿ交�ʹ� �˾ƾ� �Ѵ�.
};

