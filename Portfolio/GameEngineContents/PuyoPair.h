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

	//start(�ѿ� ���� ��ġ, �ѿ� ���� startȣ��)
	void Start();
	void Update();
	// update(Ű�Է� ����, �ѿ� ������Ʈ ȣ��)
	//render(�ѿ� ���� ȣ��)

	//���� ��ȯ(������ �ѿ丸 ������ȯ.
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

