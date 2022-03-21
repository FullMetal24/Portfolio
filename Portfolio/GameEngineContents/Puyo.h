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

	//밑에 아무것도 없으면 낙하 함수(첫 도스게임 좌표랑 비슷할듯)(정해진 픽셀씩 움직여야함)
	//닿으면 true를 반환하는 함수(페어가 확인하고 다음 페어 꺼냄
	//떨어진 후 주위에 같은 색 있는지 탐색
	//4개 이상인 걸 어떻게 알 지가 문제...

protected:

private:
	//색
	//뿌요페어를 알아선 안됨
};

