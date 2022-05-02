#include "EnemyFSM.h"
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineImageManager.h>
#include "Puyo.h"
#include <GameEngineBase/GameEngineInput.h>
#include "Fire.h"
#include "Player.h"
#include "EnemyProfile.h"
#include "Offset.h"
#include "OffsetStar.h"
#include "WarningPuyo.h"

EnemyFSM::EnemyFSM()
	: EnemyMap_{ nullptr }
	, EnemyState_(EnemyState::NewPuyo)
	, MoveTime_(0.f)
	, RotateTime_(0.f)
	, AutoDownTime_(1.0f)
	, InputDownTime_(0.f)
	, CheckTime_(0.f)
	, LandTime_(0.f)
	, Score_(0)
	, Chain_(0)
	, ActionIndex_(0)
	, IsDanger_(false)
{
}

EnemyFSM::~EnemyFSM()
{
}

void EnemyFSM::Start()
{
	InitNextPair();
	InitBubble();

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
	Fire_->SetFireOwner(FireOwner::Enemy);

	if (false == GameEngineInput::GetInst()->IsKey("Hindrance"))
	{
		GameEngineInput::GetInst()->CreateKey("Hindrance", VK_LSHIFT);
		GameEngineInput::GetInst()->CreateKey("LoseEnemy", 'b');
	}

	EnemyActors_ = GetLevel()->CreateActor<InGameActor>();
	EnemyActors_->SetPosition({ GameEngineWindow::GetScale().Half() + float4{0, 75} });
}

void EnemyFSM::Update()
{
	if (GameEngineInput::GetInst()->IsDown("LoseEnemy"))
	{
		EnemyState_ = EnemyState::Lose;
	}

	if (true == Player_->GetDanger())
	{
		IsDanger_ = false;
		ExcitedAnimation();
	}
	
	switch (EnemyState_)
	{
	case EnemyState::NewPuyo:
		Chain_ = 0;
		ActionIndex_ = 0;
		IsAction_ = false;
		NewPuyoPair();
		break;
	case EnemyState::MovePuyo: 
		GreedyPuyoMove();
		RandomRotate();
		RandomDown();
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
		WinAnimation();
		IsDanger_ = false;
		break;
	case EnemyState::Lose:
		Lose();
		LoseAnimation();
		IsDanger_ = false;
		break;
	}

	if (true == GameEngineInput::GetInst()->IsDown("Hindrance"))
	{
		Chain_ += 1;
		//OffsetEffect();
		EnemyToPlayerAttack({ GameEngineWindow::GetScale().Half() });
	}
	
	DigitScore(Score_);
	RenderToScore();
	DisappearBubble();
	VomitBubble();
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

	--Color;

	if (0 > Color)
	{
		Color = 4;
	}

	NextNextCenterPuyo_->SetColor(static_cast<PuyoColor>(Color));
	NextNextCenterPuyo_->SetColorImage(static_cast<PuyoColor>(Color));

	Color = Random_.RandomInt(0, 4);

	--Color;

	if (0 > Color)
	{
		Color = 4;
	}

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

	--Color;

	if (0 > Color)
	{
		Color = 4;
	}

	NextNextCenterPuyo_ = GetLevel()->CreateActor<Puyo>(1);
	NextNextCenterPuyo_->InitAllAnimation();
	NextNextCenterPuyo_->SetColorImage(static_cast<PuyoColor>(Color));

	Color = Random_.RandomInt(0, 4);

	--Color;

	if (0 > Color)
	{
		Color = 4;
	}

	NextNextSecondPuyo_ = GetLevel()->CreateActor<Puyo>(1);
	NextNextSecondPuyo_->InitAllAnimation();
	NextNextSecondPuyo_->SetColorImage(static_cast<PuyoColor>(Color));

	Color = Random_.RandomInt(0, 4);

	--Color;

	if (0 > Color)
	{
		Color = 4;
	}

	NextCenterPuyo_ = GetLevel()->CreateActor<Puyo>(1);
	NextCenterPuyo_->InitAllAnimation();
	NextCenterPuyo_->SetColorImage(static_cast<PuyoColor>(Color));

	Color = Random_.RandomInt(0, 4);

	--Color;

	if (0 > Color)
	{
		Color = 4;
	}

	NextSecondPuyo_ = GetLevel()->CreateActor<Puyo>(1);
	NextSecondPuyo_->InitAllAnimation();
	NextSecondPuyo_->SetColorImage(static_cast<PuyoColor>(Color));

	NextNextCenterPuyo_->SetPosition({ 673.f, 330.f });
	NextNextSecondPuyo_->SetPosition({ 673.f, 270.f });

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

void EnemyFSM::GreedyPuyoMove()
{
	MoveTime_ += GameEngineTime::GetDeltaTime();

	if (2.f < MoveTime_)
	{
		MoveTime_ = 0.f;
		int Distance[6] = { 0 };

		if (false == IsAction_)
		{
			IsAction_ = true;

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
		}


		if (CenterPuyo_->GetX() == ActionIndex_)
		{
			return;
		}
 
		else if (CenterPuyo_->GetX() > ActionIndex_)
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


		else if (CenterPuyo_->GetX() < ActionIndex_)
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

void EnemyFSM::RandomRotate()
{
	RotateTime_ += GameEngineTime::GetDeltaTime();

	if (4.5f <= RotateTime_)
	{
		RotateTime_ = 0.f;
		int Count = Random_.RandomInt(0, 3);

		CenterPuyo_->SetDir(static_cast<PuyoDir>(Count));
		SecondPuyo_->RotatePuyo(EnemyMap_, CenterPuyo_);
	}
}

void EnemyFSM::RandomDown()
{
	DownTime_ += GameEngineTime::GetDeltaTime();

	if (1.0f <= DownTime_)
	{
		DownTime_ = 0.f;

		if (CenterPuyo_->GetY() <= SecondPuyo_->GetY())
		{
			++Score_;
			Puyo* DownPuyo = CenterPuyo_->DownPuyo(EnemyMap_, SecondPuyo_);
			Puyo* DownPuyo1 = SecondPuyo_->DownPuyo(EnemyMap_, CenterPuyo_);
		}

		else if ( CenterPuyo_->GetY() >= SecondPuyo_->GetY())
		{
			++Score_;
			Puyo* DownPuyo1 = SecondPuyo_->DownPuyo(EnemyMap_, CenterPuyo_);
			Puyo* DownPuyo = CenterPuyo_->DownPuyo(EnemyMap_, SecondPuyo_);
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
		DangerCheck();

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

	++Chain_;

	for (StartIter; StartIter != EndIter; ++StartIter)
	{
		std::vector<Puyo*> PuyoVector = (*StartIter);

		std::vector<Puyo*>::iterator PuyoStartIter = PuyoVector.begin();
		std::vector<Puyo*>::iterator PuyoEndIter = PuyoVector.end();

		if (PuyoVector.size() > 0)
		{
			size_t CenterActor = PuyoVector.size() / 2;
			EnemyToPlayerAttack(PuyoVector[CenterActor]->GetPosition());
			Fire_->EnemyRenderChain(Chain_, PuyoVector[CenterActor]->GetPosition());
		}

		for (; PuyoStartIter != PuyoEndIter; ++PuyoStartIter)
		{
			if (nullptr != (*PuyoStartIter))
			{
				(*PuyoStartIter)->ChangeState(PuyoState::Destroy);
				(*PuyoStartIter)->DestroyHindracePuyo(EnemyMap_);
				EnemyMap_[(*PuyoStartIter)->GetY()][(*PuyoStartIter)->GetX()] = nullptr;

				Score_ += PuyoVector.size() * Chain_ * 10;
			}
		}
	}

	for (int Y = 0; Y < 15; ++Y)
	{
		for (int X = 0; X < 6; ++X)
		{
			if (nullptr != EnemyMap_[Y][X]
				&& PuyoColor::Hindrance == EnemyMap_[Y][X]->GetColor())
			{
				EnemyMap_[Y][X]->DestroyHindracePuyo(EnemyMap_);
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

	EnemyState_ = EnemyState::PuyoCheck;
}

void EnemyFSM::EnemyToPlayerAttack(float4 _FromPos)
{
	if (0 < Hindrances_.size()) //»ó¼â
	{
		OffsetEffect();

		CountPopWarningPuyo(Chain_);

		for (int i = 0; i < Chain_; i++)
		{
			if (0 == Hindrances_.size())
			{
				break;
			}

			--Chain_;
			Hindrances_.pop_back();
		}

		Fire_->SetFirePosition(_FromPos);
		Fire_->GetTargetPos(GameEngineWindow::GetScale().Half() + float4{ 400, -400 });
		Fire_->SetIsAttack(true);
	}

	else
	{
		Fire_->SetFirePosition(_FromPos);
		Fire_->GetTargetPos(PlayerPoint_);
		Fire_->SetIsAttack(true);
	}

	Player_->CreateHindrancePuyo(Chain_);
}

void EnemyFSM::CreateHindrancePuyo(int _Count)
{
	for (int i = 0; i < _Count; ++i)
	{
		Puyo* NewPuyo = GetLevel()->CreateActor<Puyo>();
		NewPuyo->SetColor(PuyoColor::Hindrance);
		NewPuyo->InitAnimation(PuyoColor::Hindrance);
		Hindrances_.push_back(NewPuyo);
	}

	AddWarningPuyo(_Count);
}

void EnemyFSM::HindrancePuyoCheck()
{
	if (0 < Hindrances_.size())
	{
		FallHindrancePuyo();
		PopWarningPuyo();
	}

	else
	{
		EnemyState_ = EnemyState::NewPuyo;
	}
}

void EnemyFSM::FallHindrancePuyo()
{
	std::vector<Puyo*>::iterator StartIter = Hindrances_.begin();
	std::vector<Puyo*>::iterator EndIter = Hindrances_.end();

	for (; StartIter != EndIter; ++StartIter)
	{
		int X = Random_.RandomInt(0, 5);
		int Y = 0;

		for (int i = 14; i >= 0; --i)
		{
			if (EnemyMap_[i][X] == nullptr)
			{
				Y = i;
			}
		}

		(*StartIter)->SetIndex(X, Y);
		(*StartIter)->SetPosition((*StartIter)->CoordinatePos(this, X, 15));
		(*StartIter)->FallPuyo(EnemyMap_, this);
		EnemyMap_[Y][X] = (*StartIter);
	}

	Hindrances_.clear();
	EnemyState_ = EnemyState::NewPuyo;
}


void EnemyFSM::AddWarningPuyo(int _Count)
{
	for (int i = 0; i < _Count; ++i)
	{
		WarningPuyo* NewPuyo = GetLevel()->CreateActor<WarningPuyo>(10);
		NewPuyo->SetStartPos({ 1000.f, 35.f });
		NewPuyo->SetEndPos({ 850.f + WarningPuyos_.size() * 35.f, 35.f });
		NewPuyo->MoveLeft();

		WarningPuyos_.push_back(NewPuyo);
	}
}

void EnemyFSM::PopWarningPuyo()
{
	std::vector<WarningPuyo*>::iterator StartIter = WarningPuyos_.begin();
	std::vector<WarningPuyo*>::iterator EndIter = WarningPuyos_.end();

	for (; StartIter != EndIter; ++StartIter)
	{
		if (nullptr != (*StartIter))
		{
			(*StartIter)->MoveRight();
		}
	}

	WarningPuyos_.clear();
}

void EnemyFSM::CountPopWarningPuyo(int _Count)
{
	for (int i = 0; i < _Count; i++)
	{
		if (0 == WarningPuyos_.size())
		{
			return;
		}

		WarningPuyo* NewPuyo = WarningPuyos_.back();

		if (nullptr != NewPuyo)
		{
			NewPuyo->MoveRight();
			WarningPuyos_.pop_back();
		}
	}
}

void EnemyFSM::OffsetEffect()
{
	for (int i = 0; i < 7; i++)
	{
		OffsetStar* OffsetStars_ = GetLevel()->CreateActor<OffsetStar>();
		OffsetStars_->SetStartPos({ 1000.f, 80.f });
		float4 Dir = float4::DegreeToDirectionFloat4((i + 1) * 20);
		OffsetStars_->SetDirection(Dir);

		OffsetStars_->SetUpdate(true);
		OffsetStars_->GetMyAnimation()->SetOrder(20);
	}

	Offset* OffsetRenderer_ = GetLevel()->CreateActor<Offset>();
	OffsetRenderer_->SetStartPos({ 950, 80 });
	float4 Dir = float4::DegreeToDirectionFloat4(60.0f);
	OffsetRenderer_->SetDirection(Dir);

	OffsetRenderer_->SetUpdate(true);
	OffsetRenderer_->GetMyRenderer()->SetOrder(20);
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


void EnemyFSM::DangerCheck()
{
	int Count = 0;

	for (int Y = 14; Y >= 0; --Y)
	{
		for (int X = 0; X < 6; ++X)
		{
			if (nullptr != EnemyMap_[Y][X])
			{
				++Count;
			}
		}
	}

	if (Count >= 10)
	{
		IsDanger_ = true;
		//DangerAnimation();
	}

	else if (Count < 10)
	{
		IsDanger_ = false;
		//IdleAnimation();
	}
}

void EnemyFSM::InitBubble()
{
	GameEngineImage* Image = GameEngineImageManager::GetInst()->Find("IG_BUBBLE.bmp");
	Image->CutCount(3, 1);

	for (int i = 0; i < 10; ++i)
	{
		Bubbles_[i] = GetLevel()->CreateActor<InGameActor>(5);
		Bubbles_[i]->SetMyRenderer(Bubbles_[i]->CreateRenderer());
		Bubbles_[i]->GetMyRenderer()->CreateAnimation("IG_BUBBLE.bmp", "IG_BUBBLE", 0, 2, 0.1f, true);
		Bubbles_[i]->GetMyRenderer()->ChangeAnimation("IG_BUBBLE");
		Bubbles_[i]->GetMyRenderer()->PauseOn();
		Bubbles_[i]->GetMyRenderer()->SetOrder(0);

		float RanRadian = Random_.RandomFloat(0, 3.14256f);
		BubbleDir_[i] = float4::RadianToDirectionFloat4(RanRadian * -1.f);

		int RanSpeed = Random_.RandomInt(100, 150);
		BubbleSpeed_[i] = RanSpeed;

		Bubbles_[i]->SetPosition(GameEngineWindow::GetScale().Half() + float4{0.f, 50.f + (10 * (i * -1.f)) });
	}
}

void EnemyFSM::VomitBubble()
{
	if (true == IsDanger_)
	{
		int RanCreate = Random_.RandomInt(0, 15);

		for (int i = 0; i < 10; ++i)
		{
			if (i == RanCreate)
			{
				continue;
			}

			if (false == Bubbles_[i]->IsUpdate())
			{
				Bubbles_[i]->GetMyRenderer()->PauseOff();
				Bubbles_[i]->SetPosition(GameEngineWindow::GetScale().Half() + float4{0.f, 50.f + (10 * (i * -1.f)) });
				Bubbles_[i]->GetMyRenderer()->SetOrder(5);
				Bubbles_[i]->On();
			}

			Bubbles_[i]->SetMove(BubbleDir_[i] * BubbleSpeed_[i] * GameEngineTime::GetDeltaTime());
		}

		for (int i = 0; i < 10; ++i)
		{
			float4 Dis = GameEngineWindow::GetScale().Half() - Bubbles_[i]->GetPosition();

			if (Dis.x > 200.f || Dis.x < -200.f
				|| Dis.y > 200.f || Dis.y < -200.f)
			{
				Bubbles_[i]->GetMyRenderer()->PauseOn();
				Bubbles_[i]->GetMyRenderer()->SetOrder(0);
				Bubbles_[i]->Off();
			}
		}

		RanCreate = Random_.RandomInt(0, 15);

		for (int i = 0; i < 10; ++i)
		{
			if (i == RanCreate)
			{
				continue;
			}

			if (false == Bubbles_[i]->IsUpdate())
			{
				Bubbles_[i]->GetMyRenderer()->PauseOff();
				Bubbles_[i]->SetPosition(GameEngineWindow::GetScale().Half() + float4{ 0.f, 50.f + (10 * (i * -1.f)) });
				Bubbles_[i]->GetMyRenderer()->SetOrder(5);
				Bubbles_[i]->On();
			}

			Bubbles_[i]->SetMove(BubbleDir_[i] * BubbleSpeed_[i] * GameEngineTime::GetDeltaTime());
		}

		for (int i = 0; i < 10; ++i)
		{
			float4 Dis = GameEngineWindow::GetScale().Half() - Bubbles_[i]->GetPosition();

			if (Dis.x > 250.f || Dis.x < -250.f
				|| Dis.y > 250.f || Dis.y < -250.f)
			{
				Bubbles_[i]->GetMyRenderer()->PauseOn();
				Bubbles_[i]->GetMyRenderer()->SetOrder(0);
				Bubbles_[i]->Off();
			}
		}
	}
}

void EnemyFSM::DisappearBubble()
{
	if (false == IsDanger_)
	{
		for (int i = 0; i < 10; ++i)
		{
			if (true == Bubbles_[i]->GetMyRenderer()->IsEndAnimation())
			{
				Bubbles_[i]->GetMyRenderer()->Off();
				Bubbles_[i]->GetMyRenderer()->SetOrder(0);
			}
		}
	}
}

void EnemyFSM::SetMyProfile(EnemyProfile* _Porifle)
{
	MyPorifle_ = _Porifle;

	if (nullptr != MyPorifle_)
	{
		float XPos = 95.f;
		float YPos = 365.f;

		switch (MyPorifle_->GetMyLevel())
		{
		case 1:
			EnemyAnimations_[0] = EnemyActors_->CreateRenderer();
			EnemyAnimations_[0]->SetOrder(2);
			EnemyAnimations_[0]->CreateAnimation("IG_LV1_IDLE.bmp", "IG_LV1_IDLE", 0, 3, 0.2f, true);
			EnemyAnimations_[0]->CreateAnimation("IG_LV1_LOSE.bmp", "IG_LV1_LOSE", 0, 3, 0.2f, false);
			EnemyAnimations_[0]->CreateAnimation("IG_LV1_WIN.bmp", "IG_LV1_WIN", 0, 0, 0.0f, false);
			EnemyAnimations_[0]->CreateAnimation("IG_LV1_EXCITED.bmp", "IG_LV1_EXCITED", 0, 5, 0.2f, true);
			EnemyAnimations_[0]->CreateAnimation("IG_LV1_DANGER.bmp", "IG_LV1_DANGER", 0, 3, 0.1f, true);
			EnemyAnimations_[0]->ChangeAnimation("IG_LV1_IDLE");

			EnemyNames_[0] = EnemyActors_->CreateRenderer();
			EnemyNames_[0]->SetOrder(2);
			EnemyNames_[0]->SetPivot({ XPos, -YPos });
			EnemyNames_[0]->SetImage("IG_NAME_SKEL.bmp");
			break;

		case 2:
			EnemyAnimations_[1] = EnemyActors_->CreateRenderer();
			EnemyAnimations_[1]->SetOrder(2);
			EnemyAnimations_[1]->CreateAnimation("IG_LV2_IDLE.bmp", "IG_LV2_IDLE", 0, 0, 0.0f, false);
			EnemyAnimations_[1]->CreateAnimation("IG_LV2_LOSE.bmp", "IG_LV2_LOSE", 0, 3, 0.2f,true);
			EnemyAnimations_[1]->CreateAnimation("IG_LV2_WIN.bmp", "IG_LV2_WIN", 0, 0, 0.0f, false);
			EnemyAnimations_[1]->CreateAnimation("IG_LV2_EXCITED.bmp", "IG_LV2_EXCITED", 0, 0, 0.0f, false);
			EnemyAnimations_[1]->CreateAnimation("IG_LV2_DANGER.bmp", "IG_LV2_DANGER", 0, 0, 0.0f, false);
			EnemyAnimations_[1]->ChangeAnimation("IG_LV2_IDLE");

			EnemyNames_[1] = EnemyActors_->CreateRenderer();
			EnemyNames_[1]->SetOrder(2);
			EnemyNames_[1]->SetPivot({ XPos, -YPos });
			EnemyNames_[1]->SetImage("IG_NAME_WISP.bmp");
			break;

		case 3:
			EnemyAnimations_[2] = EnemyActors_->CreateRenderer();
			EnemyAnimations_[2]->SetOrder(2);
			EnemyAnimations_[2]->CreateAnimation("IG_LV3_IDLE.bmp", "IG_LV3_IDLE", 0, 3, 0.2f, true);
			EnemyAnimations_[2]->CreateAnimation("IG_LV3_LOSE.bmp", "IG_LV3_LOSE", 0, 3, 0.2f, true);
			EnemyAnimations_[2]->CreateAnimation("IG_LV3_WIN.bmp", "IG_LV3_WIN", 0, 1, 0.2f, true);
			EnemyAnimations_[2]->CreateAnimation("IG_LV3_EXCITED.bmp", "IG_LV3_EXCITED", 0, 3, 0.2f, true);
			EnemyAnimations_[2]->CreateAnimation("IG_LV3_DANGER.bmp", "IG_LV3_DANGER", 0, 3, 0.1f, true);
			EnemyAnimations_[2]->ChangeAnimation("IG_LV3_IDLE");

			EnemyNames_[2] = EnemyActors_->CreateRenderer();
			EnemyNames_[2]->SetOrder(2);
			EnemyNames_[2]->SetPivot({ XPos, -YPos });
			EnemyNames_[2]->SetImage("IG_NAME_PODE.bmp");
			break;

		case 4:
			EnemyAnimations_[3] = EnemyActors_->CreateRenderer();
			EnemyAnimations_[3]->SetOrder(2);
			EnemyAnimations_[3]->CreateAnimation("IG_LV4_IDLE.bmp", "IG_LV4_IDLE", 0, 3, 0.2f, true);
			EnemyAnimations_[3]->CreateAnimation("IG_LV4_EXCITED.bmp", "IG_LV4_EXCITED", 0, 3, 0.2f, true);
			EnemyAnimations_[3]->CreateAnimation("IG_LV4_LOSE.bmp", "IG_LV4_LOSE", 0, 3, 0.2f, true);
			EnemyAnimations_[3]->CreateAnimation("IG_LV4_WIN.bmp", "IG_LV4_WIN", 0, 0, 0.0f, false);
			EnemyAnimations_[3]->CreateAnimation("IG_LV4_DANGER.bmp", "IG_LV4_DANGER", 0, 3, 0.2f, true);
			EnemyAnimations_[3]->ChangeAnimation("IG_LV4_IDLE");

			EnemyNames_[3] = EnemyActors_->CreateRenderer();
			EnemyNames_[3]->SetOrder(2);
			EnemyNames_[3]->SetPivot({ XPos, -YPos });
			EnemyNames_[3]->SetImage("IG_NAME_BANS.bmp");
			break;

		case 5:
			EnemyAnimations_[4] = EnemyActors_->CreateRenderer();
			EnemyAnimations_[4]->SetOrder(2);
			EnemyAnimations_[4]->CreateAnimation("IG_LV5_IDLE.bmp", "IG_LV5_IDLE", 0, 3, 0.2f, true);
			EnemyAnimations_[4]->CreateAnimation("IG_LV5_LOSE.bmp", "IG_LV5_LOSE", 0, 3, 0.2f, true);
			EnemyAnimations_[4]->CreateAnimation("IG_LV5_WIN.bmp", "IG_LV5_WIN", 0, 6, 0.2f, true);
			EnemyAnimations_[4]->CreateAnimation("IG_LV5_EXCITED.bmp", "IG_LV5_EXCITED", 0, 4, 0.2f, true);
			EnemyAnimations_[4]->CreateAnimation("IG_LV5_DANGER.bmp", "IG_LV5_DANGER", 0, 3, 0.2f, true);
			EnemyAnimations_[4]->ChangeAnimation("IG_LV5_IDLE");

			EnemyNames_[4] = EnemyActors_->CreateRenderer();
			EnemyNames_[4]->SetOrder(2);
			EnemyNames_[4]->SetPivot({ XPos, -YPos });
			EnemyNames_[4]->SetImage("IG_NAME_SATA.bmp");
			break;

		case 6:
			EnemyAnimations_[5] = EnemyActors_->CreateRenderer();
			EnemyAnimations_[5]->SetOrder(2);
			EnemyAnimations_[5]->CreateAnimation("IG_LV6_IDLE.bmp", "IG_LV6_IDLE", 0, 2, 0.2f, true);
			EnemyAnimations_[5]->CreateAnimation("IG_LV6_LOSE.bmp", "IG_LV6_LOSE", 0, 2, 0.2f, true);
			EnemyAnimations_[5]->CreateAnimation("IG_LV6_WIN.bmp", "IG_LV6_WIN", 0, 2, 0.2f, true);
			EnemyAnimations_[5]->CreateAnimation("IG_LV6_EXCITED.bmp", "IG_LV6_EXCITED", 0, 3, 0.2f, true);
			EnemyAnimations_[5]->CreateAnimation("IG_LV6_DANGER.bmp", "IG_LV6_DANGER", 0, 3, 0.2f, true);
			EnemyAnimations_[5]->ChangeAnimation("IG_LV6_IDLE");

			EnemyNames_[5] = EnemyActors_->CreateRenderer();
			EnemyNames_[5]->SetOrder(2);
			EnemyNames_[5]->SetPivot({ XPos, -YPos });
			EnemyNames_[5]->SetImage("IG_NAME_MOMO.bmp");
			break;
			 
		case 7:
			EnemyAnimations_[6] = EnemyActors_->CreateRenderer();
			EnemyAnimations_[6]->SetOrder (2);
			EnemyAnimations_[6]->CreateAnimation("IG_LV7_IDLE.bmp", "IG_LV7_IDLE", 0, 4, 0.2f, true);
			EnemyAnimations_[6]->CreateAnimation("IG_LV7_LOSE.bmp", "IG_LV7_LOSE", 0, 0, 0.0f, false);
			EnemyAnimations_[6]->CreateAnimation("IG_LV7_WIN.bmp", "IG_LV7_WIN", 0, 2, 0.2f, true);
			EnemyAnimations_[6]->CreateAnimation("IG_LV7_DANGER.bmp", "IG_LV7_DANGER", 0, 3, 0.2f, true);
			EnemyAnimations_[6]->CreateAnimation("IG_LV7_EXCITED.bmp", "IG_LV7_EXCITED", 0, 3, 0.2f, true);
			EnemyAnimations_[6]->ChangeAnimation("IG_LV7_IDLE");

			EnemyNames_[6] = EnemyActors_->CreateRenderer();
			EnemyNames_[6]->SetOrder(2);
			EnemyNames_[6]->SetPivot({ XPos, -YPos });
			EnemyNames_[6]->SetImage("IG_NAME_BARO.bmp");
			break;

		case 8:
			EnemyAnimations_[7] = EnemyActors_->CreateRenderer();
			EnemyAnimations_[7]->SetOrder(2);
			EnemyAnimations_[7]->CreateAnimation("IG_LV8_IDLE.bmp", "IG_LV8_IDLE", 0, 3, 0.2f, true);
			EnemyAnimations_[7]->CreateAnimation("IG_LV8_LOSE.bmp", "IG_LV8_LOSE", 0, 3, 0.2f, true);
			EnemyAnimations_[7]->CreateAnimation("IG_LV8_WIN.bmp", "IG_LV8_WIN", 0, 2, 0.2f, true);
			EnemyAnimations_[7]->CreateAnimation("IG_LV8_EXCITED.bmp", "IG_LV8_EXCITED", 0, 2, 0.2f, true);
			EnemyAnimations_[7]->CreateAnimation("IG_LV8_DANGER.bmp", "IG_LV8_DANGER", 0, 3, 0.2f, true);
			EnemyAnimations_[7]->ChangeAnimation("IG_LV8_IDLE");

			EnemyNames_[7] = EnemyActors_->CreateRenderer();
			EnemyNames_[7]->SetOrder(2);
			EnemyNames_[7]->SetPivot({ XPos, -YPos });
			EnemyNames_[7]->SetImage("IG_NAME_MINI.bmp");
			break;
		}
	}
}


void EnemyFSM::Lose()
{
	for (int Y = 14; Y >= 0; --Y)
	{
		for (int X = 0; X < 6; ++X)
		{
			if (nullptr != EnemyMap_[Y][X])
			{
				EnemyMap_[Y][X]->LoseFall();
			}
		}
	}
}

void EnemyFSM::IdleAnimation()
{
	if (nullptr == MyPorifle_)
	{
		return;
	}

	switch (MyPorifle_->GetMyLevel())
	{
	case 1:
		EnemyAnimations_[0]->ChangeAnimation("IG_LV1_IDLE");
		break;

	case 2:
		EnemyAnimations_[1]->ChangeAnimation("IG_LV2_IDLE");
		break;

	case 3:
		EnemyAnimations_[2]->ChangeAnimation("IG_LV3_IDLE");
		break;

	case 4:
		EnemyAnimations_[3]->ChangeAnimation("IG_LV4_IDLE");
		break;

	case 5:
		EnemyAnimations_[4]->ChangeAnimation("IG_LV5_IDLE");
		break;

	case 6:
		EnemyAnimations_[5]->ChangeAnimation("IG_LV6_IDLE");
		break;

	case 7:
		EnemyAnimations_[6]->ChangeAnimation("IG_LV7_IDLE");
		break;

	case 8:
		EnemyAnimations_[7]->ChangeAnimation("IG_LV8_IDLE");
		break;
	}
}

void EnemyFSM::ExcitedAnimation()
{
	if (nullptr == MyPorifle_)
	{
		return;
	}

	switch (MyPorifle_->GetMyLevel())
	{
	case 1:
		EnemyAnimations_[0]->ChangeAnimation("IG_LV1_EXCITED");
		break;

	case 2:
		EnemyAnimations_[1]->ChangeAnimation("IG_LV2_EXCITED");
		break;

	case 3:
		EnemyAnimations_[2]->ChangeAnimation("IG_LV3_EXCITED");
		break;

	case 4:
		EnemyAnimations_[3]->ChangeAnimation("IG_LV4_EXCITED");
		break;

	case 5:
		EnemyAnimations_[4]->ChangeAnimation("IG_LV5_EXCITED");
		break;

	case 6:
		EnemyAnimations_[5]->ChangeAnimation("IG_LV6_EXCITED");
		break;

	case 7:
		EnemyAnimations_[6]->ChangeAnimation("IG_LV7_EXCITED");
		break;

	case 8:
		EnemyAnimations_[7]->ChangeAnimation("IG_LV8_EXCITED");
		break;
	}
}

void EnemyFSM::DangerAnimation()
{
	if (nullptr == MyPorifle_)
	{
		return;
	}

	switch (MyPorifle_->GetMyLevel())
	{
	case 1:
		EnemyAnimations_[0]->ChangeAnimation("IG_LV1_DANGER");
		break;

	case 2:
		EnemyAnimations_[1]->ChangeAnimation("IG_LV2_DANGER");
		break;

	case 3:
		EnemyAnimations_[2]->ChangeAnimation("IG_LV3_DANGER");
		break;

	case 4:
		EnemyAnimations_[3]->ChangeAnimation("IG_LV4_DANGER");
		break;

	case 5:
		EnemyAnimations_[4]->ChangeAnimation("IG_LV5_DANGER");
		break;

	case 6:
		EnemyAnimations_[5]->ChangeAnimation("IG_LV6_DANGER");
		break;

	case 7:
		EnemyAnimations_[6]->ChangeAnimation("IG_LV7_DANGER");
		break;

	case 8:
		EnemyAnimations_[7]->ChangeAnimation("IG_LV8_DANGER");
		break;
	}
}

void EnemyFSM::LoseAnimation()
{
	if (nullptr == MyPorifle_)
	{
		return;
	}

	switch (MyPorifle_->GetMyLevel())
	{
	case 1:
		EnemyAnimations_[0]->ChangeAnimation("IG_LV1_LOSE");
		break;

	case 2:
		EnemyAnimations_[1]->ChangeAnimation("IG_LV2_LOSE");
		break;

	case 3:
		EnemyAnimations_[2]->ChangeAnimation("IG_LV3_LOSE");
		break;

	case 4:
		EnemyAnimations_[3]->ChangeAnimation("IG_LV4_LOSE");
		break;

	case 5:
		EnemyAnimations_[4]->ChangeAnimation("IG_LV5_LOSE");
		break;

	case 6:
		EnemyAnimations_[5]->ChangeAnimation("IG_LV6_LOSE");
		break;

	case 7:
		EnemyAnimations_[6]->ChangeAnimation("IG_LV7_LOSE");
		break;

	case 8:
		EnemyAnimations_[7]->ChangeAnimation("IG_LV8_LOSE");
		break;
	}
}

void EnemyFSM::WinAnimation()
{
	if (nullptr == MyPorifle_)
	{
		return;
	}

	switch (MyPorifle_->GetMyLevel())
	{
	case 1:
		EnemyAnimations_[0]->ChangeAnimation("IG_LV1_WIN");
		break;

	case 2:
		EnemyAnimations_[1]->ChangeAnimation("IG_LV2_WIN");
		break;

	case 3:
		EnemyAnimations_[2]->ChangeAnimation("IG_LV3_WIN");
		break;

	case 4:
		EnemyAnimations_[3]->ChangeAnimation("IG_LV4_WIN");
		break;

	case 5:
		EnemyAnimations_[4]->ChangeAnimation("IG_LV5_WIN");
		break;

	case 6:
		EnemyAnimations_[5]->ChangeAnimation("IG_LV6_WIN");
		break;

	case 7:
		EnemyAnimations_[6]->ChangeAnimation("IG_LV7_WIN");
		break;

	case 8:
		EnemyAnimations_[7]->ChangeAnimation("IG_LV8_WIN");
		break;
	}
}