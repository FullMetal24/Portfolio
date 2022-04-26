#include "Player.h"
#include "GameEngineBase/GameEngineInput.h"
#include "HindrancePuyo.h"
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineImageManager.h>
#include "Fire.h"

Player::Player()
	: PlayerMap_{ nullptr }
	, PlayerState_(PlayerState::NewPuyo)
	, AutoDownTime_(1.0f)
	, InputDownTime_(0.f)
	, Score_(0)
{
}

Player::~Player() 
{
}

void Player::Start()
{
	if (false == GameEngineInput::GetInst()->IsKey("Right"))
	{
		GameEngineInput::GetInst()->CreateKey("Right", VK_RIGHT);
		GameEngineInput::GetInst()->CreateKey("Left", VK_LEFT);
		GameEngineInput::GetInst()->CreateKey("Down", VK_DOWN);
		GameEngineInput::GetInst()->CreateKey("Rotate", VK_SPACE);
	}

	InitNextPair();
	ScoreInit();

	GameEngineImage* LightImage = GameEngineImageManager::GetInst()->Find("IG_PLAYER_LIGHT.bmp");
	LightImage->CutCount(4, 1);

	GameEngineImage* LightImage1 = GameEngineImageManager::GetInst()->Find("IG_PLAYER_LIGHT_EXPLOSION.bmp");
	LightImage1->CutCount(4, 1);

	EnemeyPoint_ = GameEngineWindow::GetScale().Half() + float4{ 400, -400 };

	Fire_ = GetLevel()->CreateActor<Fire>();
	Fire_->SetFireOwner(FireOwner::Player);

}

void Player::Update()
{
	switch (PlayerState_)
	{
	case PlayerState::NewPuyo:
		NewPuyoPair();
		break;
	case PlayerState::MovePuyo:
		InputPuyoMove();
		AutoDown();
		LandCheck();
		OtherPuyoLandCheck();
		break;
	case PlayerState::PuyoCheck:
		SearchPuyo();
		break;
	case PlayerState::PuyoDestroy:
		DestroyPuyo();
		break;
	case PlayerState::PuyoDestroyEnd:
		DestroyEndPuyo();
		break;
	case PlayerState::LandPuyo:
		LandPuyo();
		break;
	case PlayerState::PuyoLandEnd:
		LandEndPuyo();
		break;
	case PlayerState::HindranceCheck:
		HindrancePuyoCheck();
		break;
	case PlayerState::Win:
		break;
	case PlayerState::Lose:
		break;
	}

	DigitScore(Score_);
	RenderToScore();
}

void Player::NewPuyoPair() 
{
	SecondPuyo_ = CreatePuyo(2, 14, NextSecondPuyo_->GetColor());
	CenterPuyo_ = CreatePuyo(2, 13, NextCenterPuyo_->GetColor());

	NextSecondPuyo_->SetColor(NextNextSecondPuyo_->GetColor());
	NextCenterPuyo_->SetColor(NextNextCenterPuyo_->GetColor());

	int Color = Random_.RandomInt(0, 4);
	NextNextCenterPuyo_->SetColor(static_cast<PuyoColor>(Color));
	Color = Random_.RandomInt(0, 4);
	NextNextSecondPuyo_->SetColor(static_cast<PuyoColor>(Color));

	PlayerState_ = PlayerState::MovePuyo;
}

void Player::InitNextPair()
{
	int Color = Random_.RandomInt(0, 4);

	NextNextCenterPuyo_ = GetLevel()->CreateActor<Puyo>(1);
	NextNextCenterPuyo_->InitAnimation(static_cast<PuyoColor>(Color));
	NextNextCenterPuyo_->SetColor(static_cast<PuyoColor>(Color));

	Color = Random_.RandomInt(0, 4);

	NextNextSecondPuyo_ = GetLevel()->CreateActor<Puyo>(1);
	NextNextSecondPuyo_->InitAnimation(static_cast<PuyoColor>(Color));
	NextNextSecondPuyo_->SetColor(static_cast<PuyoColor>(Color));

	Color = Random_.RandomInt(0, 4);

	NextCenterPuyo_ = GetLevel()->CreateActor<Puyo>(1);
	NextCenterPuyo_->InitAnimation(static_cast<PuyoColor>(Color));
	NextCenterPuyo_->SetColor(static_cast<PuyoColor>(Color));

	Color = Random_.RandomInt(0, 4);

	NextSecondPuyo_ = GetLevel()->CreateActor<Puyo>(1);
	NextSecondPuyo_->InitAnimation(static_cast<PuyoColor>(Color));
	NextSecondPuyo_->SetColor(static_cast<PuyoColor>(Color));

	NextNextCenterPuyo_->SetPosition({ 605.f, 330.f });
	NextNextSecondPuyo_->SetPosition({ 605.f, 270.f });

	NextCenterPuyo_->SetPosition({ 540.f, 270.f });
	NextSecondPuyo_->SetPosition({ 540.f, 210.f });
}

Puyo* Player::CreatePuyo(int x, int y, PuyoColor _Color)
{
	if (0 > x || 5 < x)
	{
		return nullptr;
	}

	if (0 > y || 14 < y)
	{
		return nullptr;
	}

	if (nullptr != PlayerMap_[y][x])
	{
		return nullptr;
	}

	Puyo* NewPuyo_ = GetLevel()->CreateActor<Puyo>(0);
	PlayerMap_[y][x] = NewPuyo_;

	NewPuyo_->Init(this, x, y, _Color);

	return NewPuyo_;
}

void Player::InputPuyoMove()
{
	InputDownTime_ += GameEngineTime::GetDeltaTime();

	if (true == CenterPuyo_->GetFall() || true == CenterPuyo_->GetLand()
		|| true == SecondPuyo_->GetFall() || true == SecondPuyo_->GetLand())
	{
		return;
	}

	if (GameEngineInput::GetInst()->IsDown("Left"))
	{
		if (CenterPuyo_->GetX() >= SecondPuyo_->GetX())
		{
			SecondPuyo_->LeftPuyo(PlayerMap_, CenterPuyo_);
			CenterPuyo_->LeftPuyo(PlayerMap_, SecondPuyo_);
		}

		else if (CenterPuyo_->GetX() <= SecondPuyo_->GetX())
		{
			CenterPuyo_->LeftPuyo(PlayerMap_, SecondPuyo_);
			SecondPuyo_->LeftPuyo(PlayerMap_, CenterPuyo_);
		}
	}

	if (GameEngineInput::GetInst()->IsDown("Right"))
	{
		if (CenterPuyo_->GetX() >= SecondPuyo_->GetX())
		{
			CenterPuyo_->RightPuyo(PlayerMap_, SecondPuyo_);
			SecondPuyo_->RightPuyo(PlayerMap_, CenterPuyo_);
		}

		if (CenterPuyo_->GetX() <= SecondPuyo_->GetX())
		{
			SecondPuyo_->RightPuyo(PlayerMap_, CenterPuyo_);
			CenterPuyo_->RightPuyo(PlayerMap_, SecondPuyo_);
		}
	}

	if (GameEngineInput::GetInst()->IsDown("Rotate"))
	{
		SecondPuyo_->RotatePuyo(PlayerMap_, CenterPuyo_);
	}

	if (GameEngineInput::GetInst()->IsDown("Down"))
	{
		InputDown();
	}

	if (GameEngineInput::GetInst()->IsPress("Down"))
	{
		if (0.15f <= InputDownTime_)
		{
			InputDownTime_ = 0.f;
			InputDown();
		}
	}
}

void Player::AutoDown()
{
	AutoDownTime_ -= GameEngineTime::GetDeltaTime();

	if (AutoDownTime_ <= 0.2f 
		&& CenterPuyo_->GetY() <= SecondPuyo_->GetY())
	{
		AutoDownTime_ = 1.0f;
		Puyo* DownPuyo = CenterPuyo_->DownPuyo(PlayerMap_, SecondPuyo_);
		Puyo* DownPuyo1 = SecondPuyo_->DownPuyo(PlayerMap_, CenterPuyo_);
	}

	else if(AutoDownTime_ <= 0.2f
		&& CenterPuyo_->GetY() >= SecondPuyo_->GetY())
	{
		AutoDownTime_ = 1.0f;
		Puyo* DownPuyo1 = SecondPuyo_->DownPuyo(PlayerMap_, CenterPuyo_);
		Puyo* DownPuyo = CenterPuyo_->DownPuyo(PlayerMap_, SecondPuyo_);
	}
}

void Player::InputDown()
{
	Score_ += 1;

	if (CenterPuyo_->GetY() <= SecondPuyo_->GetY())
	{
		Puyo* DownPuyo = CenterPuyo_->DownPuyo(PlayerMap_, SecondPuyo_);
		Puyo* DownPuyo1 = SecondPuyo_->DownPuyo(PlayerMap_, CenterPuyo_);
	}

	else if (CenterPuyo_->GetY() >= SecondPuyo_->GetY())
	{
		Puyo* DownPuyo1 = SecondPuyo_->DownPuyo(PlayerMap_, CenterPuyo_);
		Puyo* DownPuyo = CenterPuyo_->DownPuyo(PlayerMap_, SecondPuyo_);
	}
}

void Player::LandCheck()
{
	CenterPuyo_->LandPuyo(PlayerMap_, SecondPuyo_);
	SecondPuyo_->LandPuyo(PlayerMap_, CenterPuyo_);

	if (true == CenterPuyo_->GetLand()
		&& true == SecondPuyo_->GetLand())
	{
		PlayerState_ = PlayerState::PuyoCheck;
	}
}

void Player::OtherPuyoLandCheck()
{
	if (true == CenterPuyo_->GetLand())
	{
		SecondPuyo_->SetFall(true);
		SecondPuyo_->FallPuyo(PlayerMap_);
	}

	if (true == SecondPuyo_->GetLand())
	{
		CenterPuyo_->SetFall(true);
		CenterPuyo_->FallPuyo(PlayerMap_);
	}
}

void Player::DestroyPuyo()
{
	std::vector<std::vector<Puyo*>>::iterator StartIter = AllDestroyPuyo_.begin();
	std::vector<std::vector<Puyo*>>::iterator EndIter = AllDestroyPuyo_.end();

	for (StartIter; StartIter != EndIter; ++StartIter)
	{
		std::vector<Puyo*> PuyoVector = (*StartIter);

		std::vector<Puyo*>::iterator PuyoStartIter = PuyoVector.begin();
		std::vector<Puyo*>::iterator PuyoEndIter = PuyoVector.end();

		if (PuyoVector.size() > 0)
		{
			int CenterActor = PuyoVector.size() / 2;
			PlayerToEnemyAttack(PuyoVector[CenterActor]->GetPosition());
		}

		for (; PuyoStartIter != PuyoEndIter; ++PuyoStartIter)
		{
			if (nullptr != (*PuyoStartIter))
			{
				PlayerMap_[(*PuyoStartIter)->GetY()][(*PuyoStartIter)->GetX()] = nullptr;
				Destroys_.push_back((*PuyoStartIter));
				(*PuyoStartIter)->RenderToDestroy();
			}
		}
	}

	AllDestroyPuyo_.clear();
	PlayerState_ = PlayerState::PuyoDestroyEnd;
}

void Player::DestroyEndPuyo()
{
	std::vector<Puyo*>::iterator StartIter = Destroys_.begin();
	std::vector<Puyo*>::iterator EndIter = Destroys_.end();

	int Index = 0;

	for (StartIter; StartIter != EndIter; ++StartIter)
	{
		if (nullptr != (*StartIter))
		{
			if (true == (*StartIter)->GetDestroyAnimationEnd())
			{
				++Index;
			}
		}
	}

	if (Destroys_.size() <= Index)
	{
		PlayerState_ = PlayerState::LandPuyo;
	}

	Destroys_.clear();
}

void Player::LandPuyo()
{
	for (int Y = 14; Y >= 0; --Y)
	{
		for (int X = 0; X < 6; ++X)
		{
			if (nullptr != PlayerMap_[Y][X])
			{
				Puyo* FallPuyo = PlayerMap_[Y][X];

				if (0 <= FallPuyo->GetY() - 1
					&& nullptr == PlayerMap_[FallPuyo->GetY() - 1][X])
				{
					Falls_.push_back(FallPuyo);
					continue;
				}
			}
		}
	}

	PlayerState_ = PlayerState::PuyoLandEnd;
}


void Player::LandEndPuyo()
{
	std::vector<Puyo*>::iterator StartIter = Falls_.begin();
	std::vector<Puyo*>::iterator EndIter = Falls_.end();

	int Index = 0;

	for (; StartIter != EndIter; ++StartIter)
	{
		if (nullptr != (*StartIter))
		{
			Puyo* FallPuyo = (*StartIter);

			while (0 <= FallPuyo->GetY() - 1
				&& nullptr == PlayerMap_[FallPuyo->GetY() - 1][FallPuyo->GetX()])
			{
				PlayerMap_[FallPuyo->GetY()][FallPuyo->GetX()] = nullptr;

				FallPuyo->SetY(FallPuyo->GetY() - 1);
				FallPuyo->CoordinateMove(this, FallPuyo->GetX(), FallPuyo->GetY());

				PlayerMap_[FallPuyo->GetY()][FallPuyo->GetX()] = FallPuyo;
			}

			++Index;
		}
	}

	if (Falls_.size() <= Index)
	{
		PlayerState_ = PlayerState::PuyoCheck;
	}

	if (Index <= 0)
	{
		PlayerState_ = PlayerState::HindranceCheck;
	}

	Falls_.clear();
}

void Player::PlayerToEnemyAttack(float4 _FromPos)
{
	Fire_->SetFirePosition(_FromPos);
	Fire_->GetTargetPos(EnemeyPoint_);
	Fire_->SetIsAttack(true);

	//Enemy_->CreateHindrancePuyo(1);
}

void Player::CreateHindrancePuyo(int _Count)
{
	for (int i = 0; i < _Count; i++)
	{
		HindrancePuyo* NewPuyo = GetLevel()->CreateActor<HindrancePuyo>();
		NewPuyo->SetMyRenderer(NewPuyo->CreateRenderer("IG_HINDRANCE_PUYO.bmp"));
		Hindrances_.push_back(NewPuyo);
	}
}

void Player::HindrancePuyoCheck()
{
	if (0 < Hindrances_.size())
	{
		FallHindrancePuyo();
	}

	else
	{
		PlayerState_ = PlayerState::NewPuyo;
	}
}

void Player::FallHindrancePuyo()
{

}


void Player::ScoreInit()
{
	for (int i = 0; i < 9; ++i)
	{
		ScoreRenderers_[i] = CreateRenderer("IG_PLAYER_NUMBER_0.bmp");
		ScoreRenderers_[i]->SetOrder(-1);
		ScoreRenderers_[i]->SetPivot({ 620 - (33.f * i) , -60 });
	}
}

void Player::DigitScore(int _Score)
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

void Player::RenderToScore()
{
	for (int i = 0; i < DigitSize_; ++i)
	{
		switch (ScoreDigits_[i])
		{
		case 0:
			ScoreRenderers_[i]->SetOrder(10);
			ScoreRenderers_[i]->SetImage("IG_PLAYER_NUMBER_0.bmp");
			break;
		case 1:
			ScoreRenderers_[i]->SetOrder(10);
			ScoreRenderers_[i]->SetImage("IG_PLAYER_NUMBER_1.bmp");
			break;
		case 2:
			ScoreRenderers_[i]->SetOrder(10);
			ScoreRenderers_[i]->SetImage("IG_PLAYER_NUMBER_2.bmp");
			break;
		case 3:
			ScoreRenderers_[i]->SetOrder(10);
			ScoreRenderers_[i]->SetImage("IG_PLAYER_NUMBER_3.bmp");
			break;
		case 4:
			ScoreRenderers_[i]->SetOrder(10);
			ScoreRenderers_[i]->SetImage("IG_PLAYER_NUMBER_4.bmp");
			break;
		case 5:
			ScoreRenderers_[i]->SetOrder(10);
			ScoreRenderers_[i]->SetImage("IG_PLAYER_NUMBER_5.bmp");
			break;
		case 6:
			ScoreRenderers_[i]->SetOrder(10);
			ScoreRenderers_[i]->SetImage("IG_PLAYER_NUMBER_6.bmp");
			break;
		case 7:
			ScoreRenderers_[i]->SetOrder(10);
			ScoreRenderers_[i]->SetImage("IG_PLAYER_NUMBER_7.bmp");
			break;
		case 8:
			ScoreRenderers_[i]->SetOrder(10);
			ScoreRenderers_[i]->SetImage("IG_PLAYER_NUMBER_8.bmp");
			break;
		case 9:
			ScoreRenderers_[i]->SetOrder(10);
			ScoreRenderers_[i]->SetImage("IG_PLAYER_NUMBER_9.bmp");
			break;
		}
	}

	if (0 == DigitSize_)
	{
		ScoreRenderers_[0]->SetOrder(10);
		ScoreRenderers_[0]->SetImage("IG_PLAYER_NUMBER_0.bmp");
	}
}
