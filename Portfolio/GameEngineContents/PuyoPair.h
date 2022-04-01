#pragma once
#include <GameEngine/GameEngineActor.h>

class Puyo;
class PuyoPair : public GameEngineActor
{
public:
	PuyoPair();
	~PuyoPair();

	PuyoPair(const PuyoPair& _Other) = delete;
	PuyoPair(PuyoPair&& _Other) noexcept = delete;
	PuyoPair& operator=(const PuyoPair& _Other) = delete;
	PuyoPair& operator=(PuyoPair&& _Other) noexcept = delete;

	//start(뿌요 시작 위치, 뿌요 내부 start호출)
	void Start();
	void Update();
	// update(키입력 감지, 뿌요 업데이트 호출)
	//render(뿌요 렌더 호출)

	//방향 변환(세컨드 뿌요만 방향전환.
	void Rotate();

	inline Puyo* GetCenterPuyo()
	{
 		return CenterPuyo_;
	};

	inline Puyo* GetSecondPuyo()
	{
		return SecondPuyo_;
	};



protected:

private:
	Puyo*  CenterPuyo_;
	Puyo*  SecondPuyo_;

};

