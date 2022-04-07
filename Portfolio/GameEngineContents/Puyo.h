#pragma once
#include <GameEngine/GameEngineActor.h>
#include "GlobalEnum.h"


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
	bool IsLaunding();

	//inline bool GetLaundiung()
	//{
	//	return IsLanding_;
	//}

	inline int GetX()
	{
		return X_;
	}

	inline int GetY()
	{
		return Y_;
	}

	inline void SetX(int _X)
	{
		X_ = _X;
	}

	inline void SetY(int _Y)
	{
		Y_ = _Y;
	}

	//��¥ �������� SetMove���� 

	inline GameEngineActor* GetMyActor_()
	{
		return MyActor_;
	}

	inline void SetMyActor_(GameEngineActor* _Actor)
	{
		MyActor_ = _Actor;
	}

protected:

private:
	GameEngineActor* MyActor_;

	Color PuyoColor_;
	bool IsVisited_;
	int X_;
	int Y_;

	bool IsLaunding_;

	//��
	//�ѿ��� �˾Ƽ� �ȵ�
	//������ �ѿ交�ʹ� �˾ƾ� �Ѵ�.

};

