#include "FSM.h"
#include "PuyoPair.h"
#include "Puyo.h"

FSM::FSM() 
{
}

FSM::~FSM() 
{
}

void FSM::Start()
{
}

void FSM::Update()
{
}

void FSM::Render()
{
}

void FSM::AddPuyoPair(PuyoPair* _Pair)
{
	CurrentPair_ = _Pair;

	Puyo* CenterPuyo = _Pair->GetCenterPuyo();
	Puyo* SecondPuyo = _Pair->GetSecondPuyo();

	CurrentPair_->SetCenterPuyo(CenterPuyo);
	CurrentPair_->SetSecondPuyo(SecondPuyo);

	PlayerMap_[1][2] = CurrentPair_->GetCenterPuyo();
	PlayerMap_[0][2] = CurrentPair_->GetSecondPuyo();

	CurrentPair_->GetCenterPuyo()->SetY(1);
	CurrentPair_->GetCenterPuyo()->SetX(2);

	CenterX_ = CurrentPair_->GetCenterPuyo()->GetX();
	CenterY_ = CurrentPair_->GetCenterPuyo()->GetY();

	CurrentPair_->GetSecondPuyo()->SetY(0);
	CurrentPair_->GetSecondPuyo()->SetX(2);

	SecondX_ = CurrentPair_->GetSecondPuyo()->GetX();
	SecondY_ = CurrentPair_->GetSecondPuyo()->GetY();
}
