#include "Player.h"
#include "GameEngineBase/GameEngineInput.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineImageManager.h>
#include "ContentsEnum.h"
#include "Puyo.h"
#include "PuyoPair.h"
#include <queue>

Player::Player()
	: PlayerMap_{}
	, PuyoDir_(PuyoDir::UP)
	, Score_(0)
	, CurrentPair_(nullptr)
	, NextPair_(nullptr)
	, NextNextPair_(nullptr)
	, RandomColor_{}
	, CenterX_(0)
	, CenterY_(0)
	, SecondX_(0)
	, SecondY_(0)
	, Chain_(0)
	, DownMoveDis_(30.0f)
	, SideMoveDis_(65.0f)
	, AutoDownTime_(0.5f)
	, DestroyDownTime_(0.f)
	, LimitTime_(0)
	, FallTime_(0)
	, IsLose_(false)
	, IsWin_(false)
{
}

Player::~Player()
{

}

void Player::Start()
{
	for (int Y = 0; Y < 29; Y++)
	{
		for (int X = 0; X < 6; X++)
		{ 
			PlayerMap_[Y][X] = nullptr;
		}
	}

	SetCurrentPair(CreatePuyoPair());
	SetNextPair(CreatePuyoPair());
	SetNextNextPair(CreatePuyoPair());

	if (false == GameEngineInput::GetInst()->IsKey("PuyoLeft"))
	{
		GameEngineInput::GetInst()->CreateKey("PuyoLeft", VK_LEFT);
		GameEngineInput::GetInst()->CreateKey("PuyoRight", VK_RIGHT);
		GameEngineInput::GetInst()->CreateKey("PuyoDown", VK_DOWN);
		GameEngineInput::GetInst()->CreateKey("PuyoRotate", VK_SPACE);
		GameEngineInput::GetInst()->CreateKey("Search", 'S');
		GameEngineInput::GetInst()->CreateKey("Destroy", 'D');
		GameEngineInput::GetInst()->CreateKey("Land", 'L');
	}

	for (int i = 0; i < 9; ++i)
	{
		ScoreRenderers_[i] = CreateRenderer("IG_PLAYER_NUMBER_0.bmp");
		ScoreRenderers_[i]->SetOrder(-1);
		ScoreRenderers_[i]->SetPivot({ GameEngineWindow::GetScale().Half().x + 70.f - (33.f * i), GameEngineWindow::GetScale().Half().y + 240.f });
	}

	GameEngineImage* LightImage = GameEngineImageManager::GetInst()->Find("IG_PLAYER_LIGHT.bmp");
	LightImage->CutCount(4, 1);

	GameEngineImage* LightImage1 = GameEngineImageManager::GetInst()->Find("IG_PLAYER_LIGHT_EXPLOSION.bmp");
	LightImage1->CutCount(4, 1);
}

float ChangeTime_;

bool IsDestroyInput_ = false;
bool IsLandInput_ = false;
bool IsSearchInput_ = false;

void Player::Update()
{ 
	if (true == GameEngineInput::GetInst()->IsDown("Land"))
	{
		IsLandInput_ = true;
	}

	if (true == GameEngineInput::GetInst()->IsDown("Destroy"))
	{
		IsDestroyInput_ = true;
	}

	if (true == GameEngineInput::GetInst()->IsDown("Search"))
	{
		IsSearchInput_ = true;
	}

	ChangeTime_ += GameEngineTime::GetDeltaTime();

	switch (PlayerState_)
	{
	case PlayerState::NewPuyo:
		NewPuyoCreate();
		break;
	case PlayerState::MovePuyo:
		PlayerInput();
		CurrentPuyoLandCheck();
		FallAlonePuyo();
		AutoFall();
		break;
	case PlayerState::LandPuyo:
		if (ChangeTime_ >= 1.f)
		{
			LandPuyo();
			IsLandInput_ = false;
			ChangeTime_ = 0.f;
		}
		break;
	case PlayerState::PuyoLandEnd:
		if (ChangeTime_ >= 0.5f)
		{
			LandEndPuyo();
			ChangeTime_ = 0.f;
		}
		break;
	case PlayerState::PuyoCheck:
		//if (ChangeTime_ >= 1.f)
		{
			SearchPuyo();
			IsSearchInput_ = false;
		}

		break;
	case PlayerState::PuyoDestroy:
		if (ChangeTime_ >= 0.5f)
		{
			DestroyPuyo();
			IsDestroyInput_ = false;
			ChangeTime_ = 0.f;

		}
		break;
	case PlayerState::PuyoDestroyEnd:
		//if (ChangeTime_ >= 1.f)
		{
			DestroyEndPuyo();
		}
		break;
	case PlayerState::Win:
		break;
	case PlayerState::Lose:
		break;
	}

	DigitScore(Score_);
	RenderToScore();
}



void Player::NewPuyoCreate()
{
	AddPuyoPair(CreatePuyoPair());
}

PuyoPair* Player::CreatePuyoPair()
{
	PuyoPair* NewPuyoPair = GetLevel()->CreateActor<PuyoPair>();

	Puyo* CenterPuyo = NewPuyoPair->GetCenterPuyo();
	CenterPuyo = GetLevel()->CreateActor<Puyo>(1);
	NewPuyoPair->SetCenterPuyo(CenterPuyo);

	Puyo* ScecondPuyo = NewPuyoPair->GetSecondPuyo();
	ScecondPuyo = GetLevel()->CreateActor<Puyo>(1);
	NewPuyoPair->SetSecondPuyo(ScecondPuyo);

	int number = RandomColor_.RandomInt(0, 4);

	switch (number)
	{
	case static_cast<int>(PuyoColor::RED):
	{
		CenterPuyo->SetColor(PuyoColor::RED);
		CenterPuyo->InitAnimation(CenterPuyo->GetColor());
	}
	break;
	case static_cast<int>(PuyoColor::BLUE):
	{
		CenterPuyo->SetColor(PuyoColor::BLUE);
		CenterPuyo->InitAnimation(CenterPuyo->GetColor());
	}
	break;
	case static_cast<int>(PuyoColor::GREEN):
	{
		CenterPuyo->SetColor(PuyoColor::GREEN);
		CenterPuyo->InitAnimation(CenterPuyo->GetColor());
	}
	break;
	case static_cast<int>(PuyoColor::YELLOW):
	{
		CenterPuyo->SetColor(PuyoColor::YELLOW);
		CenterPuyo->InitAnimation(CenterPuyo->GetColor());
	}
	break;
	case static_cast<int>(PuyoColor::PURPLE):
	{
		CenterPuyo->SetColor(PuyoColor::PURPLE);
		CenterPuyo->InitAnimation(CenterPuyo->GetColor());
	}
	break;
	}

	number = RandomColor_.RandomInt(0, 4);

	switch (number)
	{
	case static_cast<int>(PuyoColor::RED):
	{
		ScecondPuyo->SetColor(PuyoColor::RED);
		ScecondPuyo->InitAnimation(ScecondPuyo->GetColor());
	}
	break;
	case static_cast<int>(PuyoColor::BLUE):
	{
		ScecondPuyo->SetColor(PuyoColor::BLUE);
		ScecondPuyo->InitAnimation(ScecondPuyo->GetColor());
	}
	break;
	case static_cast<int>(PuyoColor::GREEN):
	{
		ScecondPuyo->SetColor(PuyoColor::GREEN);
		ScecondPuyo->InitAnimation(ScecondPuyo->GetColor());
	}
	break;
	case static_cast<int>(PuyoColor::YELLOW):
	{
		ScecondPuyo->SetColor(PuyoColor::YELLOW);
		ScecondPuyo->InitAnimation(ScecondPuyo->GetColor());
	}
	break;
	case static_cast<int>(PuyoColor::PURPLE):
	{
		ScecondPuyo->SetColor(PuyoColor::PURPLE);
		ScecondPuyo->InitAnimation(ScecondPuyo->GetColor());
	}
	break;
	}

	if (nullptr == NewPuyoPair)
	{
		return nullptr;
	}

	return NewPuyoPair;
}

void Player::AddPuyoPair(PuyoPair* _Pair)
{
	if (nullptr != PlayerMap_[4][2])
	{
		PlayerState_ = PlayerState::Lose;
		return;
	}

	CurrentPair_ = NextPair_;
	NextPair_ = NextNextPair_;
	NextNextPair_ = _Pair;

	PlayerState_ = PlayerState::MovePuyo;
	PuyoDir_ = PuyoDir::UP;

	CurrentPairInit();
}

void Player::CurrentPairInit()
{
	Puyo* SecondPuyo = CurrentPair_->GetSecondPuyo();
	Puyo* CenterPuyo = CurrentPair_->GetCenterPuyo();

	PlayerMap_[0][2] = SecondPuyo;
	PlayerMap_[2][2] = CenterPuyo;

	CenterPuyo->SetY(2);
	CenterPuyo->SetX(2);

	CenterX_ = CenterPuyo->GetX();
	CenterY_ = CenterPuyo->GetY();

	SecondPuyo->SetY(0);
	SecondPuyo->SetX(2);

	SecondX_ = SecondPuyo->GetX();
	SecondY_ = SecondPuyo->GetY();

	SecondPuyo->SetPosition({ 220.f, -90.f });
	CenterPuyo->SetPosition({ 220.f, -30.f });

	NextPair_->GetCenterPuyo()->SetPosition({ 540.f, 270.f });
	NextPair_->GetSecondPuyo()->SetPosition({ 540.f, 210.f });

	NextNextPair_->GetCenterPuyo()->SetPosition({ 605.f, 330.f });
	NextNextPair_->GetSecondPuyo()->SetPosition({ 605.f, 270.f });

	switch (CenterPuyo->GetColor())
	{
	case PuyoColor::RED:
	{
		CenterPuyo->GetMyRenderer()->ChangeAnimation("IG_RED_CENTER");
	}
	break;

	case PuyoColor::BLUE:
	{
		CenterPuyo->GetMyRenderer()->ChangeAnimation("IG_BLUE_CENTER");
	}
	break;

	case PuyoColor::GREEN:
	{
		CenterPuyo->GetMyRenderer()->ChangeAnimation("IG_GREEN_CENTER");
	}
	break;
	case PuyoColor::YELLOW:
	{
		CenterPuyo->GetMyRenderer()->ChangeAnimation("IG_YELLOW_CENTER");
	}
	break;
	case PuyoColor::PURPLE:
	{
		CenterPuyo->GetMyRenderer()->ChangeAnimation("IG_PURPLE_CENTER");
	}
	break;
	}

}



///////////////////////»Ñ¿ä ÀÌµ¿ °ü·Ã
void Player::PlayerInput()
{
	++LimitTime_;

	if (PlayerState_ == PlayerState::MovePuyo)
	{
		if (true == GameEngineInput::GetInst()->IsDown("PuyoLeft"))
		{
			MoveLeft();
		}

		if (true == GameEngineInput::GetInst()->IsDown("PuyoRight"))
		{
			MoveRight();
		}

		if (true == GameEngineInput::GetInst()->IsDown("PuyoDown"))
		{
			MoveDown();
		}

		if (true == GameEngineInput::GetInst()->IsDown("PuyoRotate"))
		{
			Rotate();
		}

		if (true == GameEngineInput::GetInst()->IsPress("PuyoDown") && 0 == 10 / LimitTime_)
		{
			MoveDown();
			Score_ += 1;
			LimitTime_ = 0;
		}
	}
}

void Player::MoveLeft()
{
	if (SecondX_ < CenterX_ || SecondY_ > CenterY_)
	{
		if (0 <= SecondX_ - 1 && nullptr == PlayerMap_[SecondY_][SecondX_ - 1] && nullptr == PlayerMap_[SecondY_ + 1][SecondX_ - 1])
		{
			PlayerMap_[SecondY_][SecondX_ - 1] = CurrentPair_->GetSecondPuyo();
			PlayerMap_[SecondY_][SecondX_] = nullptr;

			CurrentPair_->GetSecondPuyo()->SetMove(float4::LEFT * SideMoveDis_);
			CurrentPair_->GetSecondPuyo()->SetX(SecondX_ - 1);
			SecondX_ = CurrentPair_->GetSecondPuyo()->GetX();
		}

		if (0 <= CenterX_ - 1 && nullptr == PlayerMap_[CenterY_][CenterX_ - 1]
			&& nullptr == PlayerMap_[CenterY_ + 1][CenterX_ - 1]
			&& nullptr == PlayerMap_[CenterY_ + 3][CenterX_ - 1])
		{
			if (nullptr == PlayerMap_[SecondY_ + 2][SecondX_ - 1] || CurrentPair_->GetSecondPuyo() == PlayerMap_[SecondY_ + 2][SecondX_ - 1])
			{
				PlayerMap_[CenterY_][CenterX_ - 1] = CurrentPair_->GetCenterPuyo();
				PlayerMap_[CenterY_][CenterX_] = nullptr;

				CurrentPair_->GetCenterPuyo()->SetMove(float4::LEFT * SideMoveDis_);
				CurrentPair_->GetCenterPuyo()->SetX(CenterX_ - 1);
				CenterX_ = CurrentPair_->GetCenterPuyo()->GetX();
			}
		}
	}

	else if (SecondX_ > CenterX_ || SecondY_ < CenterY_)
	{
		if (0 <= CenterX_ - 1 && nullptr == PlayerMap_[CenterY_][CenterX_ - 1] && nullptr == PlayerMap_[CenterY_ + 1][CenterX_ - 1])
		{
			PlayerMap_[CenterY_][CenterX_ - 1] = CurrentPair_->GetCenterPuyo();
			PlayerMap_[CenterY_][CenterX_] = nullptr;

			CurrentPair_->GetCenterPuyo()->SetMove(float4::LEFT * SideMoveDis_);
			CurrentPair_->GetCenterPuyo()->SetX(CenterX_ - 1);
			CenterX_ = CurrentPair_->GetCenterPuyo()->GetX();
		}

		if (0 <= SecondX_ - 1 && nullptr == PlayerMap_[SecondY_][SecondX_ - 1]
			&& nullptr == PlayerMap_[SecondY_ + 1][SecondX_ - 1]
			&& nullptr == PlayerMap_[SecondY_ + 3][SecondX_ - 1])
		{
			if (nullptr == PlayerMap_[SecondY_ + 2][SecondX_ - 1] || CurrentPair_->GetCenterPuyo() == PlayerMap_[SecondY_ + 2][SecondX_ - 1])
			{
				PlayerMap_[SecondY_][SecondX_ - 1] = CurrentPair_->GetSecondPuyo();
				PlayerMap_[SecondY_][SecondX_] = nullptr;

				CurrentPair_->GetSecondPuyo()->SetMove(float4::LEFT * SideMoveDis_);
				CurrentPair_->GetSecondPuyo()->SetX(SecondX_ - 1);
				SecondX_ = CurrentPair_->GetSecondPuyo()->GetX();
			}
		}
	}

	int a = SecondX_;
	int b = SecondY_;

	{
		int a = CenterX_;
		int b = CenterY_;
	}

	int c = 0;
}

void Player::MoveRight()
{
	if (SecondX_ < CenterX_ || SecondY_ < CenterY_)
	{
		if (5 >= CenterX_ + 1 && nullptr == PlayerMap_[CenterY_][CenterX_ + 1] && nullptr == PlayerMap_[CenterY_ + 1][CenterX_ + 1])
		{
			PlayerMap_[CenterY_][CenterX_ + 1] = CurrentPair_->GetCenterPuyo();
			PlayerMap_[CenterY_][CenterX_] = nullptr;

			CurrentPair_->GetCenterPuyo()->SetMove(float4::RIGHT * SideMoveDis_);
			CurrentPair_->GetCenterPuyo()->SetX(CenterX_ + 1);
			CenterX_ = CurrentPair_->GetCenterPuyo()->GetX();
		}

		if (5 >= SecondX_ + 1 && nullptr == PlayerMap_[SecondY_][SecondX_ + 1]
			&& nullptr == PlayerMap_[SecondY_ + 1][SecondX_ + 1]
			&& nullptr == PlayerMap_[SecondY_ + 3][SecondX_ + 1])
		{
			if (nullptr == PlayerMap_[SecondY_ + 2][SecondX_ + 1] || CurrentPair_->GetCenterPuyo() == PlayerMap_[SecondY_ + 2][SecondX_ + 1])
			{
				PlayerMap_[SecondY_][SecondX_ + 1] = CurrentPair_->GetSecondPuyo();
				PlayerMap_[SecondY_][SecondX_] = nullptr;

				CurrentPair_->GetSecondPuyo()->SetMove(float4::RIGHT * SideMoveDis_);
				CurrentPair_->GetSecondPuyo()->SetX(SecondX_ + 1);
				SecondX_ = CurrentPair_->GetSecondPuyo()->GetX();
			}
		}
	}

	else if (SecondX_ > CenterX_ || SecondY_ > CenterY_)
	{
		if (5 >= SecondX_ + 1 && nullptr == PlayerMap_[SecondY_][SecondX_ + 1] && nullptr == PlayerMap_[SecondY_ + 1][SecondX_ + 1])
		{
			PlayerMap_[SecondY_][SecondX_ + 1] = CurrentPair_->GetSecondPuyo();
			PlayerMap_[SecondY_][SecondX_] = nullptr;

			CurrentPair_->GetSecondPuyo()->SetMove(float4::RIGHT * SideMoveDis_);
			CurrentPair_->GetSecondPuyo()->SetX(SecondX_ + 1);
			SecondX_ = CurrentPair_->GetSecondPuyo()->GetX();
		}

		if (5 >= CenterX_ + 1 && nullptr == PlayerMap_[CenterY_][CenterX_ + 1]
			&& nullptr == PlayerMap_[CenterY_ + 1][CenterX_ + 1]
			&& nullptr == PlayerMap_[CenterY_ + 3][CenterX_ + 1])
		{
			if (nullptr == PlayerMap_[CenterY_ + 2][CenterX_ + 1] || CurrentPair_->GetSecondPuyo() == PlayerMap_[CenterY_ + 2][CenterX_ + 1])
			{
				PlayerMap_[CenterY_][CenterX_ + 1] = CurrentPair_->GetCenterPuyo();
				PlayerMap_[CenterY_][CenterX_] = nullptr;

				CurrentPair_->GetCenterPuyo()->SetMove(float4::RIGHT * SideMoveDis_);
				CurrentPair_->GetCenterPuyo()->SetX(CenterX_ + 1);
				CenterX_ = CurrentPair_->GetCenterPuyo()->GetX();
			}
		}
	}

	int a = SecondX_;
	int b = SecondY_;

	{
		int a = CenterX_;
		int b = CenterY_;
	}

	int c = 0;
}

void Player::MoveDown()
{
	if (SecondY_ > CenterY_)
	{
		if (28 >= SecondY_ + 1 && nullptr == PlayerMap_[SecondY_ + 2][SecondX_])
		{
			PlayerMap_[SecondY_ + 1][SecondX_] = CurrentPair_->GetSecondPuyo();
			PlayerMap_[SecondY_][SecondX_] = nullptr;

			CurrentPair_->GetSecondPuyo()->SetMove(float4::DOWN * DownMoveDis_);
			CurrentPair_->GetSecondPuyo()->SetY(SecondY_ + 1);
			SecondY_ = CurrentPair_->GetSecondPuyo()->GetY();
		}

		if (28 >= CenterY_ + 1 && nullptr == PlayerMap_[CenterY_ + 2][CenterX_])
		{
			PlayerMap_[CenterY_ + 1][CenterX_] = CurrentPair_->GetCenterPuyo();
			PlayerMap_[CenterY_][CenterX_] = nullptr;

			CurrentPair_->GetCenterPuyo()->SetMove(float4::DOWN * DownMoveDis_);
			CurrentPair_->GetCenterPuyo()->SetY(CenterY_ + 1);
			CenterY_ = CurrentPair_->GetCenterPuyo()->GetY();
		}
	}

	else
	{
		if (28 >= CenterY_ + 1 && nullptr == PlayerMap_[CenterY_ + 2][CenterX_])
		{
			PlayerMap_[CenterY_ + 1][CenterX_] = CurrentPair_->GetCenterPuyo();
			PlayerMap_[CenterY_][CenterX_] = nullptr;

			CurrentPair_->GetCenterPuyo()->SetMove(float4::DOWN * DownMoveDis_);
			CurrentPair_->GetCenterPuyo()->SetY(CenterY_ + 1);
			CenterY_ = CurrentPair_->GetCenterPuyo()->GetY();
		}

		if (28 >= SecondY_ + 1 && nullptr == PlayerMap_[SecondY_ + 2][SecondX_])
		{
			PlayerMap_[SecondY_ + 1][SecondX_] = CurrentPair_->GetSecondPuyo();
			PlayerMap_[SecondY_][SecondX_] = nullptr;

			CurrentPair_->GetSecondPuyo()->SetMove(float4::DOWN * DownMoveDis_);
			CurrentPair_->GetSecondPuyo()->SetY(SecondY_ + 1);
			SecondY_ = CurrentPair_->GetSecondPuyo()->GetY();
		}
	}

	int a = SecondX_;
	int b = SecondY_;

	{
		int a = CenterX_;
		int b = CenterY_;
	}
 
	int c = 0;
}

void Player::Rotate()
{
	while (true)
	{
		switch (PuyoDir_)
		{
		case PuyoDir::LEFT:
			if (nullptr == PlayerMap_[CenterY_ + 2][CenterX_] && nullptr == PlayerMap_[CenterY_ + 3][CenterX_])
			{
				PlayerMap_[SecondY_][SecondX_] = nullptr;

				SecondY_ = CenterY_ + 2;
				SecondX_ = CenterX_;

				if (29 <= SecondY_)
				{
					CurrentPair_->GetCenterPuyo()->SetMove(CurrentPair_->GetCenterPuyo()->GetPosition() - float4{ 0.f, 65.0f });
					SecondY_ -= 2;
					CenterY_ -= 2;
				}

				CurrentPair_->GetSecondPuyo()->SetX(SecondX_);
				CurrentPair_->GetSecondPuyo()->SetY(SecondY_);

				CurrentPair_->GetCenterPuyo()->SetX(CenterX_);
				CurrentPair_->GetCenterPuyo()->SetY(CenterY_);

				PlayerMap_[CenterY_ + 2][CenterX_] = CurrentPair_->GetSecondPuyo();
				CurrentPair_->GetSecondPuyo()->SetPosition(CurrentPair_->GetCenterPuyo()->GetPosition() + float4{ 0.f, 65.0f });

				PuyoDir_ = PuyoDir::DOWN;
			}
			else
			{
				PlayerMap_[SecondY_][SecondX_] = nullptr;

				SecondY_ = CenterY_ + 2;
				SecondX_ = CenterX_;

				CurrentPair_->GetCenterPuyo()->SetPosition(CurrentPair_->GetCenterPuyo()->GetPosition() - float4{ 0.f, 65.0f });
				SecondY_ -= 2;
				CenterY_ -= 2;

				CurrentPair_->GetSecondPuyo()->SetX(SecondX_);
				CurrentPair_->GetSecondPuyo()->SetY(SecondY_);

				CurrentPair_->GetCenterPuyo()->SetX(CenterX_);
				CurrentPair_->GetCenterPuyo()->SetY(CenterY_);

				PlayerMap_[CenterY_ + 2][CenterX_] = CurrentPair_->GetSecondPuyo();
				CurrentPair_->GetSecondPuyo()->SetPosition(CurrentPair_->GetCenterPuyo()->GetPosition() + float4{ 0.f, 65.0f });

				PuyoDir_ = PuyoDir::DOWN;
			}
			break;

		case PuyoDir::RIGHT:
			if (nullptr == PlayerMap_[CenterY_ - 2][CenterX_] && nullptr == PlayerMap_[CenterY_ - 3][CenterX_])
			{
				PlayerMap_[SecondY_][SecondX_] = nullptr;

				SecondY_ = CenterY_ - 2;
				SecondX_ = CenterX_;

				if (29 <= SecondY_)
				{
					CurrentPair_->GetCenterPuyo()->SetPosition(CurrentPair_->GetCenterPuyo()->GetPosition() - float4{ 0.f, 65.0f });
					SecondY_ -= 2;
					CenterY_ -= 2;
				}

				CurrentPair_->GetSecondPuyo()->SetX(SecondX_);
				CurrentPair_->GetSecondPuyo()->SetY(SecondY_);

				CurrentPair_->GetCenterPuyo()->SetX(CenterX_);
				CurrentPair_->GetCenterPuyo()->SetY(CenterY_);

				PlayerMap_[CenterY_ - 2][CenterX_] = CurrentPair_->GetSecondPuyo();
				CurrentPair_->GetSecondPuyo()->SetPosition(CurrentPair_->GetCenterPuyo()->GetPosition() + float4{ 0.f, -65.0f });

				PuyoDir_ = PuyoDir::UP;
			}
			else
			{
				PlayerMap_[SecondY_][SecondX_] = nullptr;

				SecondY_ = CenterY_ - 2;
				SecondX_ = CenterX_;

				CurrentPair_->GetCenterPuyo()->SetPosition(CurrentPair_->GetCenterPuyo()->GetPosition() + float4{ 0.f, 65.0f });
				SecondY_ -= 2;
				CenterY_ -= 2;

				CurrentPair_->GetSecondPuyo()->SetX(SecondX_);
				CurrentPair_->GetSecondPuyo()->SetY(SecondY_);

				CurrentPair_->GetCenterPuyo()->SetX(CenterX_);
				CurrentPair_->GetCenterPuyo()->SetY(CenterY_);

				PlayerMap_[CenterY_ - 2][CenterX_] = CurrentPair_->GetSecondPuyo();
				CurrentPair_->GetSecondPuyo()->SetPosition(CurrentPair_->GetCenterPuyo()->GetPosition() + float4{ 0.f, -65.0f });

				PuyoDir_ = PuyoDir::UP;
			}
			break;

		case PuyoDir::DOWN:
			if (nullptr == PlayerMap_[CenterY_][CenterX_ + 1] && nullptr == PlayerMap_[CenterY_ + 1][CenterX_ + 1]
				&& 5 > SecondX_)
			{
				PlayerMap_[SecondY_][SecondX_] = nullptr;

				SecondY_ = CenterY_;
				SecondX_ = CenterX_ + 1;

				CurrentPair_->GetSecondPuyo()->SetX(SecondX_);
				CurrentPair_->GetSecondPuyo()->SetY(SecondY_);

				PlayerMap_[CenterY_][CenterX_ + 1] = CurrentPair_->GetSecondPuyo();
				CurrentPair_->GetSecondPuyo()->SetPosition(CurrentPair_->GetCenterPuyo()->GetPosition() + float4{ 65.0f, 0.0f });

				PuyoDir_ = PuyoDir::RIGHT;
			}

			else
			{
				if (nullptr != PlayerMap_[CenterY_][CenterX_ - 1] || nullptr != PlayerMap_[CenterY_ + 1][CenterX_ - 1]
					|| 0 > SecondX_ - 1 || 0 > CenterX_)
				{
					PuyoDir_ = PuyoDir::RIGHT;
					continue;
				}

				PlayerMap_[SecondY_][SecondX_] = nullptr;

				SecondY_ = CenterY_;
				SecondX_ = CenterX_ + 1;

				CurrentPair_->GetCenterPuyo()->SetPosition(CurrentPair_->GetCenterPuyo()->GetPosition() - float4{ 65.0f, 0.0f });
				SecondX_ -= 1;
				CenterX_ -= 1;

				CurrentPair_->GetSecondPuyo()->SetX(SecondX_);
				CurrentPair_->GetSecondPuyo()->SetY(SecondY_);

				PlayerMap_[CenterY_][CenterX_ + 1] = CurrentPair_->GetSecondPuyo();
				CurrentPair_->GetSecondPuyo()->SetPosition(CurrentPair_->GetCenterPuyo()->GetPosition() + float4{ 65.0f, 0.0f });

				PuyoDir_ = PuyoDir::RIGHT;

			}
			break;

		case PuyoDir::UP:
			if (nullptr == PlayerMap_[CenterY_][CenterX_ - 1] && nullptr == PlayerMap_[CenterY_ + 1][CenterX_ - 1]
				&& 0 <= SecondX_ - 1)
			{
				PlayerMap_[SecondY_][SecondX_] = nullptr;

				SecondY_ = CenterY_;
				SecondX_ = CenterX_ - 1;

				CurrentPair_->GetSecondPuyo()->SetX(SecondX_);
				CurrentPair_->GetSecondPuyo()->SetY(SecondY_);

				PlayerMap_[CenterY_][CenterX_ - 1] = CurrentPair_->GetSecondPuyo();
				CurrentPair_->GetSecondPuyo()->SetPosition(CurrentPair_->GetCenterPuyo()->GetPosition() + float4{ -65.0f, 0.0f });

				PuyoDir_ = PuyoDir::LEFT;
			}

			else
			{
				if (nullptr != PlayerMap_[CenterY_][CenterX_ + 1] || nullptr != PlayerMap_[CenterY_ + 1][CenterX_ + 1]
					|| 5 < SecondX_ || 5 < CenterX_ + 1)
				{
					PuyoDir_ = PuyoDir::LEFT;
					continue;
				}

				PlayerMap_[SecondY_][SecondX_] = nullptr;

				SecondY_ = CenterY_;
				SecondX_ = CenterX_ - 1;

				CurrentPair_->GetCenterPuyo()->SetPosition(CurrentPair_->GetCenterPuyo()->GetPosition() + float4{ 65.0f, 0.0f });
				SecondX_ += 1;
				CenterX_ += 1;

				CurrentPair_->GetSecondPuyo()->SetX(SecondX_);
				CurrentPair_->GetSecondPuyo()->SetY(SecondY_);

				PlayerMap_[CenterY_][CenterX_ - 1] = CurrentPair_->GetSecondPuyo();
				CurrentPair_->GetSecondPuyo()->SetPosition(CurrentPair_->GetCenterPuyo()->GetPosition() + float4{ -65.0f, 0.0f });

				PuyoDir_ = PuyoDir::LEFT;

			}
			break;
		}
		break;
	}
}




////////////////////////»Ñ¿ä ³«ÇÏ °ü·Ã

void Player::CurrentPuyoLandCheck()
{
	if (false == CurrentPair_->GetCenterPuyo()->GetLand())
	{
		if (CenterY_ >= 28)
		{
			CurrentPair_->GetCenterPuyo()->SetLand(true);
		}

		else if (CurrentPair_->GetSecondPuyo() != PlayerMap_[CenterY_ + 2][CenterX_]
			&& nullptr != PlayerMap_[CenterY_ + 2][CenterX_])
		{
			CurrentPair_->GetCenterPuyo()->SetLand(true);
		}

		else if (true == CurrentPair_->GetSecondPuyo()->GetLand()
			&& nullptr != PlayerMap_[CenterY_ + 2][CenterX_])
		{
			CurrentPair_->GetCenterPuyo()->SetLand(true);
		}
	}

	if (false == CurrentPair_->GetSecondPuyo()->GetLand())
	{
		if (SecondY_ >= 28)
		{
			CurrentPair_->GetSecondPuyo()->SetLand(true);
		}

		else if (CurrentPair_->GetCenterPuyo() != PlayerMap_[SecondY_ + 2][SecondX_]
			&& nullptr != PlayerMap_[SecondY_ + 2][SecondX_])
		{
			CurrentPair_->GetSecondPuyo()->SetLand(true);
		}

		else if (true == CurrentPair_->GetCenterPuyo()->GetLand()
			&& nullptr != PlayerMap_[SecondY_ + 2][SecondX_])
		{
			CurrentPair_->GetSecondPuyo()->SetLand(true);
		}
	}

	if (true == CurrentPair_->GetCenterPuyo()->GetLand()
		&& true == CurrentPair_->GetSecondPuyo()->GetLand())
	{
		if (true == CurrentPair_->GetCenterPuyo()->GetLandPlay()
			&& true == CurrentPair_->GetSecondPuyo()->GetLandPlay())
		{
			int a = SecondX_;
			int b = SecondY_;

			{
				int a = CenterX_;
				int b = CenterY_;
			}
 
			PlayerState_ = PlayerState::PuyoCheck; 
    	}   
	 }
}
   
void Player::AutoFall()
{
	AutoDownTime_ -= GameEngineTime::GetDeltaTime();

	if (0.0f >= AutoDownTime_ && false == CurrentPair_->GetCenterPuyo()->GetLand()
		|| 0.0f >= AutoDownTime_ && false == CurrentPair_->GetSecondPuyo()->GetLand())
	{
		MoveDown();
		AutoDownTime_ = 0.5f;
	}
}

void Player::FallAlonePuyo()
{
	++FallTime_;

	if (15 == FallTime_)
	{
		if (false == CurrentPair_->GetCenterPuyo()->GetLand()
			&& true == CurrentPair_->GetSecondPuyo()->GetLand())
		{
			MoveDown();
		}

		else if (false == CurrentPair_->GetSecondPuyo()->GetLand()
			&& true == CurrentPair_->GetCenterPuyo()->GetLand())
		{
			MoveDown();
		}

		FallTime_ = 0;
	}
}



/////////////////////////////»Ñ¿ä ¾Ö´Ï¸ÞÀÌ¼Ç °ü·Ã
int Player::GradePuyoAnimation(int _Dx, int _Dy, Puyo* _Puyo)
{
	int INumber = 0; //½Äº° ¹øÈ£
	bool* ConnectPtr = _Puyo->GetConnect();

	if (1 == _Dx)
	{
		INumber += 10;
		_Puyo->SetConnect(0, true);

		if (true == ConnectPtr[static_cast<int>(PuyoDir::RIGHT)])
		{
			++INumber;

			_Puyo->SetConnect(1, true);
		}

		else if (true == ConnectPtr[static_cast<int>(PuyoDir::DOWN)])
		{
			INumber += 100;

			_Puyo->SetConnect(2, true);
		}

		else if (true == ConnectPtr[static_cast<int>(PuyoDir::UP)])
		{
			INumber += 1000;

			_Puyo->SetConnect(3, true);
		}

		return INumber;
	}

	else if (-1 == _Dx)
	{
		++INumber;
		_Puyo->SetConnect(1, true);

		if (true == ConnectPtr[static_cast<int>(PuyoDir::LEFT)])
		{
			INumber += 10;

			_Puyo->SetConnect(0, true);
		}

		else if (true == ConnectPtr[static_cast<int>(PuyoDir::DOWN)])
		{
			INumber += 100;

			_Puyo->SetConnect(2, true);
		}

		else if (true == ConnectPtr[static_cast<int>(PuyoDir::UP)])
		{
			INumber += 1000;

			_Puyo->SetConnect(3, true);
		}

		return INumber;

	}

	else if (2 == _Dy)
	{
		INumber += 1000;
		_Puyo->SetConnect(3, true);

		if (true == ConnectPtr[static_cast<int>(PuyoDir::RIGHT)])
		{
			++INumber;

			_Puyo->SetConnect(0, true);
		}

		else if (true == ConnectPtr[static_cast<int>(PuyoDir::LEFT)])
		{
			INumber += 10;

			_Puyo->SetConnect(1, true);
		}

		else if (true == ConnectPtr[static_cast<int>(PuyoDir::DOWN)])
		{
			INumber += 100;

			_Puyo->SetConnect(2, true);
		}

		return INumber;
	}

	else if (-2 == _Dy)
	{
		INumber += 100;
		_Puyo->SetConnect(2, true);

		if (true == ConnectPtr[static_cast<int>(PuyoDir::RIGHT)])
		{
			++INumber;

			_Puyo->SetConnect(0, true);
		}

		else if (true == ConnectPtr[static_cast<int>(PuyoDir::LEFT)])
		{
			INumber += 10;

			_Puyo->SetConnect(1, true);
		}

		if (true == ConnectPtr[static_cast<int>(PuyoDir::UP)])
		{
			INumber += 1000;

			_Puyo->SetConnect(3, true);
		}

		return INumber;
	}
}

void Player::ConvertPuyoAnimtion(int _Dx, int _Dy, Puyo* _Puyo)
{
	int Value = GradePuyoAnimation(_Dx, _Dy, _Puyo);

	switch (Value)
	{
		//¿ì
	case 1:
		_Puyo->RenderToRight();
		break;

		//ÁÂ
	case 10:
		_Puyo->RenderToLeft();
		break;

		//ÁÂ¿ì
	case 11:
		_Puyo->RenderToLeftRight();
		break;

		//ÇÏ
	case 100:
		_Puyo->RenderToDown();
		break;

		//ÇÏÁÂ
	case 110:
		_Puyo->RenderToLeftDown();
		break;

		//ÇÏ¿ì
	case 101:
		_Puyo->RenderToRightDown();
		break;

		//ÇÏÁÂ¿ì
	case 111:
		_Puyo->RenderToLeftRightDown();
		break;

		//»ó
	case 1000:
		_Puyo->RenderToUp();
		break;

		//»óÇÏ
	case 1100:
		_Puyo->RenderToUpDown();
		break;

		//»óÇÏÁÂ
	case 1110:
		_Puyo->RenderToLeftUpDown();
		break;

		//»óÇÏ¿ì
	case 1101:
		_Puyo->RenderToRightUpDown();
		break;

		//»óÁÂ
	case 1010:
		_Puyo->RenderToLefttUp();
		break;

		//»ó¿ì
	case 1001:
		_Puyo->RenderToRightUp();
		break;

		//»óÁÂ¿ì
	case 1011:
		_Puyo->RenderToLeftRightUp();
		break;

		//»óÇÏÁÂ¿ì
	case 1111:
		_Puyo->RenderToLeftRightUpDown();
		break;

	}
}



/////////////////////////////½ºÄÚ¾î
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



void Player::DestroyPuyo()
{
	std::vector<std::vector<Puyo*>>::iterator StartIter = AllDestroyPuyo.begin();
	std::vector<std::vector<Puyo*>>::iterator EndIter = AllDestroyPuyo.end();

	for (StartIter; StartIter != EndIter; ++StartIter)
	{
		std::vector<Puyo*> PuyoVector = (*StartIter);

		std::vector<Puyo*>::iterator PuyoStartIter = PuyoVector.begin();
		std::vector<Puyo*>::iterator PuyoEndIter = PuyoVector.end();

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

	AllDestroyPuyo.clear();
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
	for (int Y = 28; Y >= 0; --Y)
	{
		for (int X = 0; X < 6; ++X)
		{
			if (nullptr != PlayerMap_[Y][X])
			{
				Puyo* FallPuyo = PlayerMap_[Y][X];

				if (28 >= FallPuyo->GetY() + 1
					&& nullptr == PlayerMap_[FallPuyo->GetY() + 2][X])
				{
					Falls_.push_back(FallPuyo);
					continue;
				}

				else
				{
					PlayerState_ = PlayerState::NewPuyo;
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

			while (28 >= FallPuyo->GetY() + 1
				&& nullptr == PlayerMap_[FallPuyo->GetY() + 2][FallPuyo->GetX()])
			{
				FallPuyo->SetMove(float4::DOWN * DownMoveDis_);

				FallPuyo->SetY(FallPuyo->GetY() + 1);
				PlayerMap_[FallPuyo->GetY() - 1][FallPuyo->GetX()] = nullptr;
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
		PlayerState_ = PlayerState::NewPuyo;
	}

	Falls_.clear();
}

