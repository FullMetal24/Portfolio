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

	//���� ��ȯ
	//

protected:

private:
	Puyo  CenterPuyo_;
	Puyo  SecondPuyo_;
	
};

