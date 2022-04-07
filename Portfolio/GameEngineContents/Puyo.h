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

	//밑에 아무것도 없으면 낙하 함수(첫 도스게임 좌표랑 비슷할듯)(정해진 픽셀씩 움직여야함)
	//닿으면 true를 반환하는 함수(페어가 확인하고 다음 페어 꺼냄
	//떨어진 후 주위에 같은 색 있는지 탐색
	//4개 이상인 걸 어떻게 알 지가 문제... 트래킹해야지

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

	//진짜 움직임은 SetMove에서 

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

	//색
	//뿌요페어를 알아선 안됨
	//하지만 뿌요벡터는 알아야 한다.

};

