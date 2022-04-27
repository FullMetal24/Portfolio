#include "EnemyFSM.h"
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineImageManager.h>
#include "Puyo.h"
#include "HindrancePuyo.h"
#include "Fire.h"
#include "Player.h"

EnemyFSM::EnemyFSM()
{
}

EnemyFSM::~EnemyFSM()
{
}

void EnemyFSM::Start()
{
	InitNextPair();

	for (int i = 0; i < 9; ++i)
	{
		ScoreRenderers_[i] = CreateRenderer("IG_ENEMY_NUMBER_0.bmp");
		ScoreRenderers_[i]->SetOrder(-1);
		ScoreRenderers_[i]->SetPivot({ -80.f + (-33.f * i) , 0.f });
	}

	GameEngineImage* LightImage = GameEngineImageManager::GetInst()->Find("IG_ENEMY_LIGHT.bmp");
	LightImage->CutCount(4, 1);

	GameEngineImage* LightImage1 = GameEngineImageManager::GetInst()->Find("IG_ENEMY_LIGHT_EXPLOSION.bmp");
	LightImage1->CutCount(4, 1);

	PlayerPoint_ = GameEngineWindow::GetScale().Half() + float4{ -400 , -400 };

	Fire_ = GetLevel()->CreateActor<Fire>();
	Fire_->SetFireOwner(FireOwner::Player);
}

void EnemyFSM::Update()
{
	switch (EnemyState_)
	{
	case EnemyState::NewPuyo:
		NewPuyoPair();
		break;
	case EnemyState::MovePuyo:
		GreedyPuyoMove();
		AutoDown();
		LandCheck();
		OtherPuyoLandCheck();
		break;
	case EnemyState::PuyoCheck:
		CheckTime_ += GameEngineTime::GetDeltaTime();
		if (0.7f < CheckTime_)
		{
			CheckTime_ = 0.f;
			SearchPuyo();
		}
		break;
	case EnemyState::PuyoDestroy:
		DestroyPuyo();
		break;
	case EnemyState::LandPuyo:
		LandTime_ += GameEngineTime::GetDeltaTime();
		if (0.7f < LandTime_)
		{
			LandTime_ = 0.f;
			LandPuyo();
		}
		break;
	case EnemyState::HindranceCheck:
		HindrancePuyoCheck();
		break;
	case EnemyState::Win:
		break;
	case EnemyState::Lose:
		break;
	}

	DigitScore(Score_);
	RenderToScore();
}

void EnemyFSM::NewPuyoPair()
{
	SecondPuyo_ = CreatePuyo(2, 14, NextSecondPuyo_->GetColor());
	CenterPuyo_ = CreatePuyo(2, 13, NextCenterPuyo_->GetColor());

	NextSecondPuyo_->SetColor(NextNextSecondPuyo_->GetColor());
	NextCenterPuyo_->SetColor(NextNextCenterPuyo_->GetColor());

	NextCenterPuyo_->SetColorImage(NextCenterPuyo_->GetColor());
	NextSecondPuyo_->SetColorImage(NextSecondPuyo_->GetColor());

	int Color = Random_.RandomInt(0, 4);
	NextNextCenterPuyo_->SetColor(static_cast<PuyoColor>(Color));
	NextNextCenterPuyo_->SetColorImage(static_cast<PuyoColor>(Color));

	Color = Random_.RandomInt(0, 4);
	NextNextSecondPuyo_->SetColor(static_cast<PuyoColor>(Color));
	NextNextSecondPuyo_->SetColorImage(static_cast<PuyoColor>(Color));

	if (nullptr == CenterPuyo_)
	{
		EnemyState_ = EnemyState::Lose;
		return;
	}

	RenderToCenterPuyo();
	EnemyState_ = EnemyState::MovePuyo;
}

void EnemyFSM::InitNextPair()
{
	int Color = Random_.RandomInt(0, 4);

	NextNextCenterPuyo_ = GetLevel()->CreateActor<Puyo>(1);
	NextNextCenterPuyo_->InitAllAnimation();
	NextNextCenterPuyo_->SetColorImage(static_cast<PuyoColor>(Color));

	Color = Random_.RandomInt(0, 4);

	NextNextSecondPuyo_ = GetLevel()->CreateActor<Puyo>(1);
	NextNextSecondPuyo_->InitAllAnimation();
	NextNextSecondPuyo_->SetColorImage(static_cast<PuyoColor>(Color));

	Color = Random_.RandomInt(0, 4);

	NextCenterPuyo_ = GetLevel()->CreateActor<Puyo>(1);
	NextCenterPuyo_->InitAllAnimation();
	NextCenterPuyo_->SetColorImage(static_cast<PuyoColor>(Color));

	Color = Random_.RandomInt(0, 4);

	NextSecondPuyo_ = GetLevel()->CreateActor<Puyo>(1);
	NextSecondPuyo_->InitAllAnimation();
	NextSecondPuyo_->SetColorImage(static_cast<PuyoColor>(Color));

	NextNextCenterPuyo_->SetPosition({ 675.f, 330.f });
	NextNextSecondPuyo_->SetPosition({ 675.f, 270.f });

	NextCenterPuyo_->SetPosition({ 735.f, 270.f });
	NextSecondPuyo_->SetPosition({ 735.f, 210.f });
}

Puyo* EnemyFSM::CreatePuyo(int _X, int _Y, PuyoColor _Color)
{
	if (0 > _X || 5 < _X)
	{
		return nullptr;
	}

	if (0 > _Y || 14 < _Y)
	{
		return nullptr;
	}

	if (nullptr != EnemyMap_[_Y][_X])
	{
		return nullptr;
	}

	Puyo* NewPuyo_ = GetLevel()->CreateActor<Puyo>(0);
	EnemyMap_[_Y][_X] = NewPuyo_;

	NewPuyo_->Init(this, _X, _Y, _Color);

	return NewPuyo_;
}

void EnemyFSM::RenderToCenterPuyo()
{
	switch (CenterPuyo_->GetColor())
	{
	case PuyoColor::RED:
	{
		CenterPuyo_->GetMyRenderer()->ChangeAnimation("IG_RED_CENTER");
	}
	break;

	case PuyoColor::BLUE:
	{
		CenterPuyo_->GetMyRenderer()->ChangeAnimation("IG_BLUE_CENTER");
	}
	break;

	case PuyoColor::GREEN:
	{
		CenterPuyo_->GetMyRenderer()->ChangeAnimation("IG_GREEN_CENTER");
	}
	break;
	case PuyoColor::YELLOW:
	{
		CenterPuyo_->GetMyRenderer()->ChangeAnimation("IG_YELLOW_CENTER");
	}
	break;
	case PuyoColor::PURPLE:
	{
		CenterPuyo_->GetMyRenderer()->ChangeAnimation("IG_PURPLE_CENTER");
	}
	break;
	}
}

void EnemyFSM::RenderToLinkedPuyo()
{
	for (int Y = 0; Y <= 14; ++Y)
	{
		for (int X = 0; X < 6; ++X)
		{
			if (nullptr != EnemyMap_[Y][X])
			{
				EnemyMap_[Y][X]->LinkedPuyoAnimtaion(EnemyMap_);
			}
		}
	}
}

void EnemyFSM::ResetLinkedPuyo()
{
	for (int Y = 0; Y <= 14; ++Y)
	{
		for (int X = 0; X < 6; ++X)
		{
			if (nullptr != EnemyMap_[Y][X])
			{
				EnemyMap_[Y][X]->ResetConnect();
			}
		}
	}
}

float Time_;

void EnemyFSM::GreedyPuyoMove()
{
	Time_ += GameEngineTime::GetDeltaTime();

	if (2.f < Time_)
	{
		Time_ = 0.f;
		int Distance[6] = { 0 };

		if (12 < CenterPuyo_->GetY())
		{
			return;
		}

		for (int X = 0; X < 6; ++X)
		{
			for (int Y = 0; Y < 14; ++Y)
			{
				if (nullptr != EnemyMap_[Y][X]
					&& CenterPuyo_ != EnemyMap_[Y][X]
					&& SecondPuyo_ != EnemyMap_[Y][X])
				{
					++Distance[X];
				}
			}
		}

		for (int i = 0; i < 6; ++i)
		{
			int Temp;

			int CurIndex = i;
			int NextIndex = i + 1;

			if (6 <= NextIndex)
			{
				NextIndex = 0;
			}

			if (Distance[CurIndex] < Distance[NextIndex])
			{
				Temp = Distance[NextIndex];
				Distance[NextIndex] = Distance[CurIndex];
				Distance[CurIndex] = Temp;
			}
		}

		if (CenterPuyo_->GetX() < Distance[0])
		{
			if (CenterPuyo_->GetX() >= SecondPuyo_->GetX())
			{
				SecondPuyo_->LeftPuyo(EnemyMap_, CenterPuyo_);
				CenterPuyo_->LeftPuyo(EnemyMap_, SecondPuyo_);
			}

			else if (CenterPuyo_->GetX() <= SecondPuyo_->GetX())
			{
				CenterPuyo_->LeftPuyo(EnemyMap_, SecondPuyo_);
				SecondPuyo_->LeftPuyo(EnemyMap_, CenterPuyo_);
			}
		}


		else
		{
			if (CenterPuyo_->GetX() >= SecondPuyo_->GetX())
			{
				CenterPuyo_->RightPuyo(EnemyMap_, SecondPuyo_);
				SecondPuyo_->RightPuyo(EnemyMap_, CenterPuyo_);
			}

			else if (CenterPuyo_->GetX() <= SecondPuyo_->GetX())
			{
				SecondPuyo_->RightPuyo(EnemyMap_, CenterPuyo_);
				CenterPuyo_->RightPuyo(EnemyMap_, SecondPuyo_);
			}
		}
	}
}

void EnemyFSM::AutoDown()
{
	AutoDownTime_ -= GameEngineTime::GetDeltaTime();

	if (AutoDownTime_ <= 0.2f
		&& CenterPuyo_->GetY() <= SecondPuyo_->GetY())
	{
		++Score_;
		AutoDownTime_ = 1.0f;
		Puyo* DownPuyo = CenterPuyo_->DownPuyo(EnemyMap_, SecondPuyo_);
		Puyo* DownPuyo1 = SecondPuyo_->DownPuyo(EnemyMap_, CenterPuyo_);
	}

	else if (AutoDownTime_ <= 0.2f
		&& CenterPuyo_->GetY() >= SecondPuyo_->GetY())
	{
		++Score_;
		AutoDownTime_ = 1.0f;
		Puyo* DownPuyo1 = SecondPuyo_->DownPuyo(EnemyMap_, CenterPuyo_);
		Puyo* DownPuyo = CenterPuyo_->DownPuyo(EnemyMap_, SecondPuyo_);
	}
}

void EnemyFSM::LandCheck()
{
	CenterPuyo_->LandPuyo(EnemyMap_, SecondPuyo_);
	SecondPuyo_->LandPuyo(EnemyMap_, CenterPuyo_);

	if (true == CenterPuyo_->GetLand()
		&& true == SecondPuyo_->GetLand())
	{
		RenderToLinkedPuyo();
		CenterPuyo_->ChangeState(PuyoState::Land);
		SecondPuyo_->ChangeState(PuyoState::Land);
		EnemyState_ = EnemyState::PuyoCheck;
	}
}

void EnemyFSM::OtherPuyoLandCheck()
{
	if (true == CenterPuyo_->GetLand())
	{
		SecondPuyo_->SetFall(true);
		SecondPuyo_->AloneFallPuyo(EnemyMap_);
	}

	if (true == SecondPuyo_->GetLand())
	{
		CenterPuyo_->SetFall(true);
		CenterPuyo_->AloneFallPuyo(EnemyMap_);
	}
}

void EnemyFSM::DestroyPuyo()
{
	std::vector<std::vector<Puyo*>>::iterator StartIter = AllDestroyPuyo_.begin();
	std::vector<std::vector<Puyo*>>::iterator EndIter = AllDestroyPuyo_.end();

	if (0 == AllDestroyPuyo_.size())
	{
		EnemyState_ = EnemyState::HindranceCheck;
		return;
	}

	for (StartIter; StartIter != EndIter; ++StartIter)
	{
		std::vector<Puyo*> PuyoVector = (*StartIter);

		std::vector<Puyo*>::iterator PuyoStartIter = PuyoVector.begin();
		std::vector<Puyo*>::iterator PuyoEndIter = PuyoVector.end();

		if (PuyoVector.size() > 0)
		{
			size_t CenterActor = PuyoVector.size() / 2;
			EnemyToPlayerAttack(PuyoVector[CenterActor]->GetPosition());
		}

		for (; PuyoStartIter != PuyoEndIter; ++PuyoStartIter)
		{
			if (nullptr != (*PuyoStartIter))
			{
				EnemyMap_[(*PuyoStartIter)->GetY()][(*PuyoStartIter)->GetX()] = nullptr;
				(*PuyoStartIter)->ChangeState(PuyoState::Destroy);
			}
		}
	}

	AllDestroyPuyo_.clear();
	EnemyState_ = EnemyState::LandPuyo;
}

void EnemyFSM::LandPuyo()
{
	for (int Y = 0; Y < 15; ++Y)
	{
		for (int X = 0; X < 6; ++X)
		{
			if (nullptr != EnemyMap_[Y][X])
			{
				Puyo* FallPuyo = EnemyMap_[Y][X];
				FallPuyo->FallPuyo(EnemyMap_, this);
			}
		}
	}

	ResetLinkedPuyo();
	EnemyState_ = EnemyState::PuyoCheck;
}

void EnemyFSM::EnemyToPlayerAttack(float4 _FromPos)
{
	Fire_->SetFirePosition(_FromPos);
	Fire_->GetTargetPos(PlayerPoint_);
	Fire_->SetIsAttack(true);

	Player_->CreateHindrancePuyo();
}

void EnemyFSM::CreateHindrancePuyo()
{
	HindrancePuyo* NewPuyo = GetLevel()->CreateActor<HindrancePuyo>(0);
	NewPuyo->SetPosition({-100, -100});
	Hindrances_.push_back(NewPuyo);
}

void EnemyFSM::HindrancePuyoCheck()
{
	if (0 < Hindrances_.size())
	{
		FallHindrancePuyo();
	}

	else
	{
		EnemyState_ = EnemyState::NewPuyo;
	}
}

void EnemyFSM::FallHindrancePuyo()
{
	std::vector<HindrancePuyo*>::iterator StartIter = Hindrances_.begin();
	std::vector<HindrancePuyo*>::iterator EndIter = Hindrances_.end();

	for (; StartIter != EndIter; ++StartIter)
	{
		int X = Random_.RandomInt(0, 5);
		int Y = 0;

		for (int i = 14; i >= 0; --i)
		{
			if (EnemyMap_[i][X] = nullptr)
			{
				Y = i;
			}
		}

		(*StartIter)->SetIndex(X, Y);
		(*StartIter)->SetPosition((*StartIter)->CoordinatePos(this, X, Y));
		EnemyMap_[Y][X] = (*StartIter);
	}

	Hindrances_.clear();
	EnemyState_ = EnemyState::NewPuyo;
}

 

void EnemyFSM::DigitScore(int _Score)
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

void EnemyFSM::RenderToScore()
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
