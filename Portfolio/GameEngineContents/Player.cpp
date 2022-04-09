#include "Player.h"
#include "GameEngineBase/GameEngineInput.h"
#include <GameEngineBase/GameEngineWindow.h>
#include "Puyo.h"
#include "PuyoPair.h"
#include "InGame.h"

Player::Player()
	: PuyoDir_(PuyoDir::UP)
	, CenterX_(0)
	, CenterY_(0)
	, SecondX_(0)
	, SecondY_(0)
	, DownMoveDis_(30.0f) 
	, SideMoveDis_(65.0f)
	, DownTime(0.5f)
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
}


void Player::Render()
{
}

void Player::Update()
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


	
	DownTime -= GameEngineTime::GetDeltaTime();

	if (0.0f >= DownTime && false == CurrentPair_->GetCenterPuyo()->GetLandiung()
		|| 0.0f >= DownTime && false == CurrentPair_->GetSecondPuyo()->GetLandiung())
	{
		MoveDown();
		DownTime = 0.5f;
	
		LandCheck();
	}

}

void Player::MoveLeft()
{
	if (SecondX_ < CenterX_)
	{
		if (0 <= SecondX_ - 1 && nullptr == PlayerMap_[SecondY_][SecondX_ - 1])
		{
			PlayerMap_[SecondY_][SecondX_ - 1] = CurrentPair_->GetSecondPuyo();
			PlayerMap_[SecondY_][SecondX_] = nullptr;

			CurrentPair_->GetSecondPuyo()->SetMove(float4::LEFT * SideMoveDis_);
			CurrentPair_->GetSecondPuyo()->SetX(SecondX_ - 1);
			SecondX_ = CurrentPair_->GetSecondPuyo()->GetX();
		}

		if (0 <= CenterX_ - 1 && nullptr == PlayerMap_[CenterY_][CenterX_ - 1])
		{
			PlayerMap_[CenterY_][CenterX_ - 1] = CurrentPair_->GetCenterPuyo();
			PlayerMap_[CenterY_][CenterX_] = nullptr;

			CurrentPair_->GetCenterPuyo()->SetMove(float4::LEFT * SideMoveDis_);
			CurrentPair_->GetCenterPuyo()->SetX(CenterX_ - 1);
			CenterX_ = CurrentPair_->GetCenterPuyo()->GetX();
		}
	}
	
	else
	{
		if (0 <= CenterX_ - 1 && nullptr == PlayerMap_[CenterY_][CenterX_ - 1])
		{
			PlayerMap_[CenterY_][CenterX_ - 1] = CurrentPair_->GetCenterPuyo();
			PlayerMap_[CenterY_][CenterX_] = nullptr;

			CurrentPair_->GetCenterPuyo()->SetMove(float4::LEFT * SideMoveDis_);
			CurrentPair_->GetCenterPuyo()->SetX(CenterX_ - 1);
			CenterX_ = CurrentPair_->GetCenterPuyo()->GetX();
		}

		if (0 <= SecondX_ - 1  && nullptr == PlayerMap_[SecondY_][SecondX_ - 1])
		{
			PlayerMap_[SecondY_][SecondX_ - 1] = CurrentPair_->GetSecondPuyo();
			PlayerMap_[SecondY_][SecondX_] = nullptr;

			CurrentPair_->GetSecondPuyo()->SetMove(float4::LEFT * SideMoveDis_);
			CurrentPair_->GetSecondPuyo()->SetX(SecondX_ - 1);
			SecondX_ = CurrentPair_->GetSecondPuyo()->GetX();
		}
	}
}

void Player::MoveRight()
{
	if (SecondX_ < CenterX_)
	{
		if (5 >= CenterX_ + 1 && nullptr == PlayerMap_[CenterY_][CenterX_ + 1])
		{
			PlayerMap_[CenterY_][CenterX_ + 1] = CurrentPair_->GetCenterPuyo();
			PlayerMap_[CenterY_][CenterX_] = nullptr;

			CurrentPair_->GetCenterPuyo()->SetMove(float4::RIGHT * SideMoveDis_);
			CurrentPair_->GetCenterPuyo()->SetX(CenterX_ + 1);
			CenterX_ = CurrentPair_->GetCenterPuyo()->GetX();
		}

		if (5 >= SecondX_ + 1 && nullptr == PlayerMap_[SecondY_][SecondX_ + 1])
		{
			PlayerMap_[SecondY_][SecondX_ + 1] = CurrentPair_->GetSecondPuyo();
			PlayerMap_[SecondY_][SecondX_] = nullptr;

			CurrentPair_->GetSecondPuyo()->SetMove(float4::RIGHT * SideMoveDis_);
			CurrentPair_->GetSecondPuyo()->SetX(SecondX_ + 1);
			SecondX_ = CurrentPair_->GetSecondPuyo()->GetX();
		}
	}

	else
	{
	 	if (5 >= SecondX_ + 1 && nullptr == PlayerMap_[SecondY_][SecondX_ + 1])
		{
 			PlayerMap_[SecondY_][SecondX_ + 1] = CurrentPair_->GetSecondPuyo();
			PlayerMap_[SecondY_][SecondX_] = nullptr;

			CurrentPair_->GetSecondPuyo()->SetMove(float4::RIGHT * SideMoveDis_);
			CurrentPair_->GetSecondPuyo()->SetX(SecondX_ + 1);
			SecondX_ = CurrentPair_->GetSecondPuyo()->GetX();
		}

		if (5 >= CenterX_ + 1 && nullptr == PlayerMap_[CenterY_][CenterX_ + 1])
		{
			PlayerMap_[CenterY_][CenterX_ + 1] = CurrentPair_->GetCenterPuyo();
			PlayerMap_[CenterY_][CenterX_] = nullptr;

			CurrentPair_->GetCenterPuyo()->SetMove(float4::RIGHT * SideMoveDis_);
			CurrentPair_->GetCenterPuyo()->SetX(CenterX_ + 1);
			CenterX_ = CurrentPair_->GetCenterPuyo()->GetX();
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
	switch (PuyoDir_)
	{
		case PuyoDir::LEFT:
		{
			PlayerMap_[SecondY_][SecondX_] = nullptr;

			SecondY_ = CenterY_ + 2;
			SecondX_ = CenterX_;

			if (29 <= SecondY_)
			{
				CurrentPair_->GetCenterPuyo()->SetPosition(CurrentPair_->GetCenterPuyo()->GetPosition() - float4{ 0.f, 60.0f });	
				SecondY_ -= 2;
				CenterY_ -= 2;
			}

			PlayerMap_[CenterY_ + 2][CenterX_] = CurrentPair_->GetSecondPuyo();
			CurrentPair_->GetSecondPuyo()->SetPosition(CurrentPair_->GetCenterPuyo()->GetPosition() + float4{ 0.f, 60.0f });
			PuyoDir_ = PuyoDir::DOWN;
		}
		break;

		case PuyoDir::RIGHT:
		{
			PlayerMap_[SecondY_][SecondX_] = nullptr;

			SecondY_ = CenterY_ - 2;
			SecondX_ = CenterX_;

			if (29 <= SecondY_)
			{
				CurrentPair_->GetCenterPuyo()->SetPosition(CurrentPair_->GetCenterPuyo()->GetPosition() + float4{ 0.f, 60.0f });
				SecondY_ -= 2;
				CenterY_ -= 2;
			}

			PlayerMap_[CenterY_ - 2][CenterX_] = CurrentPair_->GetSecondPuyo();
			CurrentPair_->GetSecondPuyo()->SetPosition(CurrentPair_->GetCenterPuyo()->GetPosition() - float4{ 0.f, 60.0f });
			PuyoDir_ = PuyoDir::UP;
		}
		break;

		case PuyoDir::DOWN:
		{
			PlayerMap_[SecondY_][SecondX_] = nullptr;

			SecondY_ = CenterY_;
			SecondX_ = CenterX_ + 1;

			if (5 < SecondX_)
			{
				CurrentPair_->GetCenterPuyo()->SetPosition(CurrentPair_->GetCenterPuyo()->GetPosition() - float4{ 60.0f, 0.0f });
				SecondX_ -= 1;
				CenterX_ -= 1;
			}

			PlayerMap_[CenterY_][CenterX_ + 1] = CurrentPair_->GetSecondPuyo();
			CurrentPair_->GetSecondPuyo()->SetPosition(CurrentPair_->GetCenterPuyo()->GetPosition() + float4{ 60.0f, 0.0f });
			PuyoDir_ = PuyoDir::RIGHT;
		}
		break;

		case PuyoDir::UP:
		{
			PlayerMap_[SecondY_][SecondX_] = nullptr;

			SecondY_ = CenterY_;
			SecondX_ = CenterX_ - 1;

			if (0 > SecondX_)
			{
				CurrentPair_->GetCenterPuyo()->SetPosition(CurrentPair_->GetCenterPuyo()->GetPosition() + float4{ 60.0f, 0.0f });
				SecondX_ += 1;
				CenterX_ += 1;
			}

			PlayerMap_[CenterY_][CenterX_ - 1] = CurrentPair_->GetSecondPuyo();
			CurrentPair_->GetSecondPuyo()->SetPosition(CurrentPair_->GetCenterPuyo()->GetPosition() - float4{ 60.0f, 0.0f });
			PuyoDir_ = PuyoDir::LEFT;
		}
		break;
	}
 }





////////////////////////»Ñ¿ä Ãß°¡

void Player::AddPuyoPair(PuyoPair* _Pair)
{
	CurrentPair_ = _Pair;

	Puyo* CenterPuyo = _Pair->GetCenterPuyo();
	Puyo* SecondPuyo = _Pair->GetSecondPuyo();

	CurrentPair_->SetCenterPuyo(CenterPuyo);
	CurrentPair_->SetSecondPuyo(SecondPuyo);

	PlayerMap_[2][2] = CurrentPair_->GetCenterPuyo();
	PlayerMap_[0][2] = CurrentPair_->GetSecondPuyo();

	CurrentPair_->GetCenterPuyo()->SetY(2);
	CurrentPair_->GetCenterPuyo()->SetX(2);

	CenterX_ = CurrentPair_->GetCenterPuyo()->GetX();
	CenterY_ = CurrentPair_->GetCenterPuyo()->GetY();

	CurrentPair_->GetSecondPuyo()->SetY(0);
	CurrentPair_->GetSecondPuyo()->SetX(2);

	SecondX_ = CurrentPair_->GetSecondPuyo()->GetX();
	SecondY_ = CurrentPair_->GetSecondPuyo()->GetY();
}

void Player::LandCheck()
{
	//¼¾ÅÍ »Ñ¿ä
	{
		if (CenterY_ >= 28)
		{
			CurrentPair_->GetCenterPuyo()->SetLanding(true);
		}

		if (CurrentPair_->GetSecondPuyo() != PlayerMap_[CenterY_ + 2][CenterX_]
			&& nullptr != PlayerMap_[CenterY_ + 2][CenterX_])
		{
			CurrentPair_->GetCenterPuyo()->SetLanding(true);
		}

		if (true == CurrentPair_->GetSecondPuyo()->GetLandiung())
		{
			CurrentPair_->GetCenterPuyo()->SetLanding(true);
		}
	}


	//¼¼ÄÁµå »Ñ¿ä
	{
		if (SecondY_ >= 28)
		{
			CurrentPair_->GetSecondPuyo()->SetLanding(true);
		}

		if (CurrentPair_->GetCenterPuyo() != PlayerMap_[SecondY_ + 2][SecondX_]
			&& nullptr != PlayerMap_[SecondY_ + 2][SecondX_])
		{
			CurrentPair_->GetSecondPuyo()->SetLanding(true);
		}

		if (true == CurrentPair_->GetCenterPuyo()->GetLandiung())
		{
			CurrentPair_->GetSecondPuyo()->SetLanding(true);
		}
	}
}
