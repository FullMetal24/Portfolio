#pragma once
#include "Puyo.h"


class PuyoPair
{
public:
	PuyoPair();
	~PuyoPair();

	PuyoPair(const PuyoPair& _Other) = delete;
	PuyoPair(PuyoPair&& _Other) noexcept = delete;
	PuyoPair& operator=(const PuyoPair& _Other) = delete;
	PuyoPair& operator=(PuyoPair&& _Other) noexcept = delete;

	//start(뿌요 시작 위치, 뿌요 내부 start호출)
	//update(키입력 감지, 뿌요 업데이트 호출)
	//render(뿌요 렌더 호출)

	//방향 변환(세컨드 뿌요만 방향전환.
	//상하좌우 이동

protected:

private:
	/*
	Puyo*  CenterPuyo_;
	Puyo*  SecondPuyo_; */
};

