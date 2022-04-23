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
	: Visited_{}
	, PuyoDir_(PuyoDir::UP)
	, Score_(0)
	, CurrentPair_(nullptr)
	, NextPair_(nullptr)
	, NextNextPair_(nullptr)
	, CenterX_(0)
	, CenterY_(0)
	, SecondX_(0)
	, SecondY_(0)
	, Chain_(0)
	, DownMoveDis_(30.0f)
	, SideMoveDis_(65.0f)
	, DownTime_(0.5f)
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
	if (false == GameEngineInput::GetInst()->IsKey("PuyoLeft"))
	{
		GameEngineInput::GetInst()->CreateKey("PuyoLeft", VK_LEFT);
		GameEngineInput::GetInst()->CreateKey("PuyoRight", VK_RIGHT);
		GameEngineInput::GetInst()->CreateKey("PuyoDown", VK_DOWN);
		GameEngineInput::GetInst()->CreateKey("PuyoRotate", VK_SPACE);
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

void Player::Update()
{
	switch (PlayerState_)
	{
	case PlayerState::NewPuyo:
		break;
	case PlayerState::MovePuyo:
		PlayerInput();
		CurrentPuyoLandCheck();
		FallAlonePuyo();
		AutoFall();
		break;
	case PlayerState::LandPuyo:
		LandPuyo();
		break;
	case PlayerState::PuyoLandEnd:
		LandEndPuyo();
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
	case PlayerState::Win:
		break;
	case PlayerState::Lose:
		break;
	}

	DigitScore(Score_);
	RenderToScore();

	int a = static_cast<int>(PlayerState_);

	int b = 0;
}

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


///////////////////////»Ñ¿ä ÀÌµ¿ °ü·Ã
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


////////////////////////»Ñ¿ä Ãß°¡ °ü·Ã
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
		PlayerState_ = PlayerState::PuyoCheck;
	}
}

void Player::AutoFall()
{
	DownTime_ -= GameEngineTime::GetDeltaTime();

	if (0.0f >= DownTime_ && false == CurrentPair_->GetCenterPuyo()->GetLand()
		|| 0.0f >= DownTime_ && false == CurrentPair_->GetSecondPuyo()->GetLand())
	{
		MoveDown();
		DownTime_ = 0.5f;
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




void Player::SearchPuyo()
{
	while (PlayerState_ == PlayerState::PuyoCheck)
	{
		for (int Y = 0; Y < 30; ++Y)
		{
			for (int X = 0; X < 6; ++X)
			{
				if (nullptr != PlayerMap_[Y][X]
					&& false == PlayerMap_[Y][X]->GetVisited())
				{
					BfsPuyo(PlayerMap_[Y][X]); 
				}

				std::list<Puyo*>::iterator StartIter = Visited_.begin();
				std::list<Puyo*>::iterator EndIter = Visited_.end();

				if (4 <= Visited_.size())
				{
					PlayerState_ = PlayerState::PuyoDestroy;
					return;
				}

				for (; StartIter != EndIter; ++StartIter)
				{ 
					if (nullptr != (*StartIter))
					{
					 	(*StartIter)->Exit();
					} 
				}

				Visited_.clear();
			}
		}

		PlayerState_ = PlayerState::NewPuyo;
	}
}

void Player::BfsPuyo(Puyo* _Puyo)
{
	int Dx[4] = { 0, 0, 1, -1 };
	int Dy[4] = { 2, -2, 0, 0 };

	Visited_.push_back(_Puyo);
	_Puyo->Visit();

	std::queue<Puyo*> PuyoQueue;
	PuyoQueue.push(_Puyo);

	while (false == PuyoQueue.empty())
	{
		Puyo* NodePuyo = PuyoQueue.front();
		PuyoQueue.pop();

		for (int i = 0; i < 4; i++)
		{
			int X = NodePuyo->GetX() + Dx[i];
			int Y = NodePuyo->GetY() + Dy[i];

			if (0 > X || X >= 6 ||
				0 > Y || Y >= 30)
			{
				continue;
			}

			if (nullptr != PlayerMap_[Y][X])
			{
				Puyo* OtherPuyo = PlayerMap_[Y][X];

				if (false == OtherPuyo->GetVisited())
				{
					if (NodePuyo->GetColor() == OtherPuyo->GetColor())
					{
						Visited_.push_back(OtherPuyo);
						PuyoQueue.push(OtherPuyo);
						OtherPuyo->Visit();

						ConvertPuyoAnimtion(Dx[i], Dy[i], OtherPuyo);
					}
				}
			}
		}
	}
}

void Player::DestroyPuyo()
{
	std::list<Puyo*>::iterator StartIter = Visited_.begin();
	std::list<Puyo*>::iterator EndIter = Visited_.end();

	for (StartIter; StartIter != EndIter; ++StartIter)
	{
		if (nullptr != (*StartIter))
		{
			PlayerMap_[(*StartIter)->GetY()][(*StartIter)->GetX()] = nullptr;
			(*StartIter)->RenderToDestroy();
		}
	}

	Visited_.clear();
	PlayerState_ = PlayerState::PuyoDestroyEnd;
}

void Player::DestroyEndPuyo()
{
	for (int Y = 0; Y < 30; Y++)
	{
		for (int X = 0; X < 6; X++)
		{
			if (nullptr != PlayerMap_[Y][X]
				&& true == PlayerMap_[Y][X]->GetDestroy())
			{
				if (false == PlayerMap_[Y][X]->GetDestroyAnimationEnd())
				{
					return;
				}
			}
		}
	}

	PlayerState_ = PlayerState::LandPuyo;
}

void Player::LandPuyo()
{
	for (int Y = 0; Y < 30; Y++)
	{
		for (int X = 0; X < 6; X++)
		{
			if (nullptr != PlayerMap_[Y][X])
			{
				Puyo* FallPuyo_ = PlayerMap_[Y][X];

				if (28 >= FallPuyo_->GetY() + 1
					&& nullptr == PlayerMap_[FallPuyo_->GetY() + 2][X])
				{
					Falls_.push_back(FallPuyo_);
					//FallPuyo_->SetFall(true);
				}
			}
		}
	}

	if (0 < Falls_.size())
	{
		PlayerState_ = PlayerState::PuyoLandEnd;
	}

	else if (0 == Falls_.size())
	{
		PlayerState_ = PlayerState::PuyoCheck;
	}
}

void Player::LandEndPuyo()
{
	std::vector<Puyo*>::iterator StartIter = Falls_.begin();
	std::vector<Puyo*>::iterator EndIter = Falls_.end();

	for (; StartIter != EndIter; ++StartIter)
	{
		if (nullptr != (*StartIter))
		{
			while (28 >= (*StartIter)->GetY() + 1
				&& nullptr == PlayerMap_[(*StartIter)->GetY() + 2][(*StartIter)->GetX()])
			{
				(*StartIter)->SetFall(false);
				(*StartIter)->SetMove(float4::DOWN * DownMoveDis_);
				(*StartIter)->SetY((*StartIter)->GetY() + 1);

				PlayerMap_[(*StartIter)->GetY() + 1][(*StartIter)->GetX()] = (*StartIter);
				PlayerMap_[(*StartIter)->GetY() - 1][(*StartIter)->GetX()] = nullptr;
			}

		}
	}
	Falls_.clear();
	PlayerState_ = PlayerState::LandPuyo;
}

