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

	//start(�ѿ� ���� ��ġ, �ѿ� ���� startȣ��)
	//update(Ű�Է� ����, �ѿ� ������Ʈ ȣ��)
	//render(�ѿ� ���� ȣ��)

	//���� ��ȯ(������ �ѿ丸 ������ȯ.
	//�����¿� �̵�

protected:

private:
	/*
	Puyo*  CenterPuyo_;
	Puyo*  SecondPuyo_; */
};

