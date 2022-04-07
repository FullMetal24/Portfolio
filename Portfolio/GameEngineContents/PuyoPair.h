#pragma once
#include <GameEngine/GameEngineActor.h>

class Puyo;
//뿌요페어는 결국 뿌요를 두 개로 묶은 클래스다
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


	inline PuyoPair* GetPuyoPair()
	{
		return this;
	}

	inline Puyo* GetCenterPuyo()
	{
 		return CenterPuyo_;
	};

	inline Puyo* GetSecondPuyo()
	{
		return SecondPuyo_;
	};

	inline void SetCenterPuyo(Puyo* _Puyo)
	{
		CenterPuyo_ = _Puyo;
	};

	inline void SetSecondPuyo(Puyo* _Puyo)
	{
		SecondPuyo_ = _Puyo;
	};


	//inline void SetCenterPuyo(GameEngineActor* _Puyo)
	//{
	//	CenterPuyo_->SetMyActor_(_Puyo);
	//};

	//inline void SetSecondPuyo(GameEngineActor* _Puyo)
	//{
	//	SecondPuyo_->SetMyActor_(_Puyo);
	//};

	//void operator=(const PuyoPair* _Other)
	//{
	//	this->CenterPuyo_ = _Other->CenterPuyo_;
	//	this->SecondPuyo_ = _Other->SecondPuyo_;
	//}

protected:

private:
	Puyo*  CenterPuyo_;
	Puyo*  SecondPuyo_;

};

