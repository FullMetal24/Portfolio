#pragma once
#include <GameEngine/GameEngineActor.h>
#include "ContentsEnum.h"


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

	inline bool GetLandiung()
	{
		return IsLanding_;
	}

	inline void SetLanding(bool _Land)
	{
		IsLanding_ = _Land;
	}


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

	inline GameEngineActor* GetMyActor()
	{
		return MyActor_;
	}

	inline void SetMyActor(GameEngineActor* _Actor)
	{
		MyActor_ = _Actor;
	}

	inline void SetColor(Color _Color)
	{
		PuyoColor_ = _Color;
	}

protected:

private:
	GameEngineActor* MyActor_;

	Color PuyoColor_;
	bool IsVisited_;
	int X_;
	int Y_;

	bool IsLanding_;

	//��
	//�ѿ��� �˾Ƽ� �ȵ�
	//������ �ѿ交�ʹ� �˾ƾ� �Ѵ�.

};

