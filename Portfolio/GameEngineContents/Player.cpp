#include "Player.h"
#include "GameEngineBase/GameEngineInput.h"
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineImageManager.h>
#include "Fire.h"
#include "EnemyFSM.h"
#include "Puyo.h"

Player::Player()
	: PlayerMap_{ nullptr }
	, PlayerState_(PlayerState::NewPuyo)
	, AutoDownTime_(1.0f)
	, InputDownTime_(0.f)
	, InputDownAcc_(0.f)
	, CheckTime_(0.f)
	, LandTime_(0.f)
	, Score_(0)
	, Chain_(0)
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
		CheckTime_ += GameEngineTime::GetDeltaTime();
		if (0.7f < CheckTime_)
		{
			CheckTime_ = 0.f;
			SearchPuyo();
		}
		break;
	case PlayerState::PuyoDestroy:
		DestroyPuyo();
		break;
	case PlayerState::LandPuyo:
		LandTime_ += GameEngineTime::GetDeltaTime();
		if (0.7f < LandTime_)
		{
			LandTime_ = 0.f;
			LandPuyo();
		}
		break;
	case PlayerState::HindranceCheck:
		Chain_ = 0;
		HindrancePuyoCheck();
		break;
	case PlayerState::Win:
		break;
	case PlayerState::Lose:
		Lose();
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
		PlayerState_ = PlayerState::Lose;
		return;
	}

	RenderToCenterPuyo();
	PlayerState_ = PlayerState::MovePuyo;
}

void Player::InitNextPair()
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

	NextNextCenterPuyo_->SetPosition({ 605.f, 330.f });
	NextNextSecondPuyo_->SetPosition({ 605.f, 270.f });

	NextCenterPuyo_->SetPosition({ 540.f, 270.f });
	NextSecondPuyo_->SetPosition({ 540.f, 210.f });
}

Puyo* Player::CreatePuyo(int _X, int _Y, PuyoColor _Color)
{
	if (0 > _X || 5 < _X)
	{
		return nullptr;
	}

	if (0 > _Y || 14 < _Y)
	{
		return nullptr;
	}

	if (nullptr != PlayerMap_[_Y][_X])
	{
		return nullptr;
	}

	Puyo* NewPuyo_ = GetLevel()->CreateActor<Puyo>(0);
	PlayerMap_[_Y][_X] = NewPuyo_;

	NewPuyo_->Init(this, _X, _Y, _Color);

	return NewPuyo_;
}

void Player::RenderToCenterPuyo()
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

		else if (CenterPuyo_->GetX() <= SecondPuyo_->GetX())
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
		InputDownAcc_ += GameEngineTime::GetDeltaTime() * 2.0f;
		InputDownTime_ += InputDownAcc_;

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
		++Score_;
		Puyo* DownPuyo = CenterPuyo_->DownPuyo(PlayerMap_, SecondPuyo_);
		Puyo* DownPuyo1 = SecondPuyo_->DownPuyo(PlayerMap_, CenterPuyo_);
	}

	else if(AutoDownTime_ <= 0.2f
		&& CenterPuyo_->GetY() >= SecondPuyo_->GetY())
	{
		AutoDownTime_ = 1.0f;
		++Score_;
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
	InputDownAcc_ = 0.f;

	CenterPuyo_->LandPuyo(PlayerMap_, SecondPuyo_);
	SecondPuyo_->LandPuyo(PlayerMap_, CenterPuyo_);

	if (true == CenterPuyo_->GetLand()
		&& true == SecondPuyo_->GetLand())
	{
		CenterPuyo_->ChangeState(PuyoState::Land);
		SecondPuyo_->ChangeState(PuyoState::Land);
		PlayerState_ = PlayerState::PuyoCheck;
	}
}

void Player::OtherPuyoLandCheck()
{
	if (true == CenterPuyo_->GetLand())
	{
		SecondPuyo_->SetFall(true);
		SecondPuyo_->AloneFallPuyo(PlayerMap_);
	}

	if (true == SecondPuyo_->GetLand())
	{
		CenterPuyo_->SetFall(true);
		CenterPuyo_->AloneFallPuyo(PlayerMap_);
	}
}

void Player::DestroyPuyo()
{
	std::vector<std::vector<Puyo*>>::iterator StartIter = AllDestroyPuyo_.begin();
	std::vector<std::vector<Puyo*>>::iterator EndIter = AllDestroyPuyo_.end();

	if (0 == AllDestroyPuyo_.size())
	{
		PlayerState_ = PlayerState::HindranceCheck;
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
			PlayerToEnemyAttack(PuyoVector[CenterActor]->GetPosition());
			Fire_->PlayerRenderChain(Chain_, PuyoVector[CenterActor]->GetPosition());
		}


		for (; PuyoStartIter != PuyoEndIter; ++PuyoStartIter)
		{
			if (nullptr != (*PuyoStartIter))
			{
				(*PuyoStartIter)->ChangeState(PuyoState::Destroy);
				(*PuyoStartIter)->DestroyHindracePuyo(PlayerMap_);
				PlayerMap_[(*PuyoStartIter)->GetY()][(*PuyoStartIter)->GetX()] = nullptr;

				Score_ += static_cast<int>(GameEngineTime::GetDeltaTime() * 100);
			}
		}
	}

	AllDestroyPuyo_.clear();
	PlayerState_ = PlayerState::LandPuyo;
}

void Player::LandPuyo()
{
	for (int Y = 0; Y < 15; ++Y)
	{
		for (int X = 0; X < 6; ++X)
		{
			if (nullptr != PlayerMap_[Y][X])
			{
				Puyo* FallPuyo = PlayerMap_[Y][X];
				FallPuyo->FallPuyo(PlayerMap_, this);
			}
		}
	}

	for (int Y = 0; Y < 15; ++Y)
	{
		for (int X = 0; X < 6; ++X)
		{
			if (nullptr != PlayerMap_[Y][X])
			{
				Puyo* LandPuyo = PlayerMap_[Y][X];
				LandPuyo->LinkedPuyoAnimtaion(PlayerMap_);
			}
		}
	}

	PlayerState_ = PlayerState::PuyoCheck;
}

void Player::PlayerToEnemyAttack(float4 _FromPos)
{
	Fire_->SetFirePosition(_FromPos);
	Fire_->GetTargetPos(EnemeyPoint_);
	Fire_->SetIsAttack(true);

	Enemy_->CreateHindrancePuyo();
}

void Player::CreateHindrancePuyo()
{
	Puyo* NewPuyo = GetLevel()->CreateActor<Puyo>();
	NewPuyo->SetColor(PuyoColor::Hindrance);
	NewPuyo->InitAnimation(PuyoColor::Hindrance);
	Hindrances_.push_back(NewPuyo);
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
	std::vector<Puyo*>::iterator StartIter = Hindrances_.begin();
	std::vector<Puyo*>::iterator EndIter = Hindrances_.end();

	for (; StartIter != EndIter; ++StartIter)
	{
		int X = Random_.RandomInt(0, 5);
		int Y = 0;

		for  (int i = 14; i >= 0; --i)
		{
			if (PlayerMap_[i][X] == nullptr)
			{
				Y = i;
			}
		 } 

		(*StartIter)->SetIndex(X, Y);
		(*StartIter)->SetPosition((*StartIter)->CoordinatePos(this, X, 15));
		(*StartIter)->FallPuyo(PlayerMap_, this);
 		PlayerMap_[Y][X] = (*StartIter);
	}

	Hindrances_.clear();
	PlayerState_ = PlayerState::NewPuyo;
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

void Player::Lose()
{
	for (int Y = 14; Y >= 0; --Y)
	{
		for (int X = 0; X < 6; ++X)
		{
			if (nullptr != PlayerMap_[Y][X])
			{
				
			}
		}
	}

}
