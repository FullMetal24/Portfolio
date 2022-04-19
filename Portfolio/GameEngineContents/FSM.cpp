#include "FSM.h"
#include "PuyoPair.h"
#include <GameEngine/GameEngineRenderer.h>
#include "Puyo.h"

FSM::FSM() 
{
}

FSM::~FSM() 
{
}

void FSM::Start()
{
	for (int i = 0; i < 9; ++i)
	{
		ScoreRenderers_[i] = CreateRenderer("IG_ENEMY_NUMBER_0.bmp");
		ScoreRenderers_[i]->SetOrder(-1);
		ScoreRenderers_[i]->SetPivot({ GameEngineWindow::GetScale().Half().x + 140.f - (33.f * i), GameEngineWindow::GetScale().Half().y + 300.f });
	}
}

void FSM::Update()
{
	DigitScore(0);
	RenderToScore();
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

	FSMMap_[1][2] = CurrentPair_->GetCenterPuyo();
	FSMMap_[0][2] = CurrentPair_->GetSecondPuyo();

	CurrentPair_->GetCenterPuyo()->SetY(1);
	CurrentPair_->GetCenterPuyo()->SetX(2);

	CenterX_ = CurrentPair_->GetCenterPuyo()->GetX();
	CenterY_ = CurrentPair_->GetCenterPuyo()->GetY();

	CurrentPair_->GetSecondPuyo()->SetY(0);
	CurrentPair_->GetSecondPuyo()->SetX(2);

	SecondX_ = CurrentPair_->GetSecondPuyo()->GetX();
	SecondY_ = CurrentPair_->GetSecondPuyo()->GetY();
}


void FSM::DigitScore(int _Score)
{
	if (0 >= _Score)
	{
		DigitSize_ = 0;
	}

	int Index = 0;
	int Temp = _Score;

	while (Temp > 0)
	{
		ScoreDigits_[Index] = Temp % 10;
		Temp /= 10;
		++Index;
	}

	DigitSize_ = Index;
}

void FSM::RenderToScore()
{
	for (int i = 0; i < DigitSize_; ++i)
	{
		switch (ScoreDigits_[i])
		{
		case 0:
			ScoreRenderers_[i]->SetOrder(10);
			ScoreRenderers_[i]->SetImage("IG_ENEMY_NUMBER_0.bmp");
			break;
		case 1:
			ScoreRenderers_[i]->SetOrder(10);
			ScoreRenderers_[i]->SetImage("IG_ENEMY_NUMBER_1.bmp");
			break;
		case 2:
			ScoreRenderers_[i]->SetOrder(10);
			ScoreRenderers_[i]->SetImage("IG_ENEMY_NUMBER_2.bmp");
			break;
		case 3:
			ScoreRenderers_[i]->SetOrder(10);
			ScoreRenderers_[i]->SetImage("IG_ENEMY_NUMBER_3.bmp");
			break;
		case 4:
			ScoreRenderers_[i]->SetOrder(10);
			ScoreRenderers_[i]->SetImage("IG_ENEMY_NUMBER_4.bmp");
			break;
		case 5:
			ScoreRenderers_[i]->SetOrder(10);
			ScoreRenderers_[i]->SetImage("IG_ENEMY_NUMBER_5.bmp");
			break;
		case 6:
			ScoreRenderers_[i]->SetOrder(10);
			ScoreRenderers_[i]->SetImage("IG_ENEMY_NUMBER_6.bmp");
			break;
		case 7:
			ScoreRenderers_[i]->SetOrder(10);
			ScoreRenderers_[i]->SetImage("IG_ENEMY_NUMBER_7.bmp");
			break;
		case 8:
			ScoreRenderers_[i]->SetOrder(10);
			ScoreRenderers_[i]->SetImage("IG_ENEMY_NUMBER_8.bmp");
			break;
		case 9:
			ScoreRenderers_[i]->SetOrder(10);
			ScoreRenderers_[i]->SetImage("IG_ENEMY_NUMBER_9.bmp");
			break;
		}
	}

	if (0 == DigitSize_)
	{
		ScoreRenderers_[0]->SetOrder(10);
		ScoreRenderers_[0]->SetImage("IG_ENEMY_NUMBER_0.bmp");
	}
}