#include "Player.h"
#include "GameEngineBase/GameEngineInput.h"
#include "Puyo.h"
#include "PuyoPair.h"
#include "InGame.h"

Player::Player()
	: PuyoDir_(PuyoDir::UP)
	, CenterX_(0)
	, CenterY_(0)
	, SecondX_(0)
	, SecondY_(0)
	, DownMoveDis_(60.0f) //원작은 반씩 내려간다!!!!
	, SideMoveDis_(65.0f)
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
}

void Player::MoveLeft()
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

void Player::MoveRight()
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

void Player::MoveDown()
{
	int Y = CenterY_;

	Puyo* Puyo_ = PlayerMap_[CenterY_ + 1][CenterX_];

	if (14 >= CenterY_ + 1 && nullptr == PlayerMap_[CenterY_ + 1][CenterX_])
	{
		PlayerMap_[CenterY_ + 1][CenterX_] = CurrentPair_->GetCenterPuyo();
		PlayerMap_[CenterY_][CenterX_] = nullptr;

		CurrentPair_->GetCenterPuyo()->SetMove(float4::DOWN * DownMoveDis_);
		CurrentPair_->GetCenterPuyo()->SetY(CenterY_ + 1);
		CenterY_ = CurrentPair_->GetCenterPuyo()->GetY();
	}

	if (14 >= SecondY_ + 1 && nullptr == PlayerMap_[SecondY_ + 1][SecondX_])
	{
		PlayerMap_[SecondY_ + 1][SecondX_] = CurrentPair_->GetSecondPuyo();
		PlayerMap_[SecondY_][SecondX_] = nullptr;

		CurrentPair_->GetSecondPuyo()->SetMove(float4::DOWN * DownMoveDis_);
		CurrentPair_->GetSecondPuyo()->SetY(SecondY_ + 1);
		SecondY_ = CurrentPair_->GetSecondPuyo()->GetY();
	}
}


void Player::Rotate()
{
	switch (PuyoDir_)
	{
	case PuyoDir::LEFT:
   		if (0 < CenterY_ && 14 > CenterY_)
		{
			if (nullptr == PlayerMap_[CenterY_ + 1][CenterX_])
			{
				PlayerMap_[SecondY_][SecondX_] = nullptr;
				PlayerMap_[CenterY_ + 1][CenterX_] = CurrentPair_->GetSecondPuyo();

				float4 Pos = CurrentPair_->GetSecondPuyo()->GetPosition();
				CurrentPair_->GetSecondPuyo()->SetPosition(CurrentPair_->GetCenterPuyo()->GetPosition() + float4{ 0.f, 60.0f });

				SecondY_ = CenterY_ + 1;
				SecondX_ = CenterX_;

				PuyoDir_ = PuyoDir::DOWN;
			}
		}
		break;
	case PuyoDir::RIGHT:
		if (0 < CenterY_ && 14 > CenterY_)
		{
			if (nullptr == PlayerMap_[CenterY_ - 1][CenterX_])
			{
				PlayerMap_[SecondY_][SecondX_] = nullptr;
				PlayerMap_[CenterY_ - 1][CenterX_] = CurrentPair_->GetSecondPuyo();

				float4 Pos = CurrentPair_->GetSecondPuyo()->GetPosition();
				CurrentPair_->GetSecondPuyo()->SetPosition(CurrentPair_->GetCenterPuyo()->GetPosition() + float4{ 0.f, -60.0f });

				SecondY_ = CenterY_ - 1;
				SecondX_ = CenterX_;

				PuyoDir_ = PuyoDir::UP;
			}
		}
		break;
	case PuyoDir::DOWN:
		if (0 < CenterX_ && 6 > CenterX_)
		{
			if (nullptr == PlayerMap_[CenterY_][CenterX_ + 1])
			{
				PlayerMap_[SecondY_][SecondX_] = nullptr;
				PlayerMap_[CenterY_][CenterX_ + 1] = CurrentPair_->GetSecondPuyo();

				float4 Pos = CurrentPair_->GetSecondPuyo()->GetPosition();
				CurrentPair_->GetSecondPuyo()->SetPosition(CurrentPair_->GetCenterPuyo()->GetPosition() + float4{ 60.f, 0.0f });

				SecondY_ = CenterY_;
				SecondX_ = CenterX_ + 1;

				PuyoDir_ = PuyoDir::RIGHT;
			}
		}
		break;
	case PuyoDir::UP:
    		if (0 < CenterX_ && 6 > CenterX_)
		{
			if (nullptr == PlayerMap_[CenterY_][CenterX_ - 1])
			{
				PlayerMap_[SecondY_][SecondX_] = nullptr;
				PlayerMap_[CenterY_][CenterX_ - 1] = CurrentPair_->GetSecondPuyo();

				float4 Pos = CurrentPair_->GetSecondPuyo()->GetPosition();
				CurrentPair_->GetSecondPuyo()->SetPosition(CurrentPair_->GetCenterPuyo()->GetPosition() + float4{ -60.f, 0.0f });

				SecondY_ = CenterY_;
				SecondX_ = CenterX_ - 1;

				PuyoDir_ = PuyoDir::LEFT;
			}
		}
		break;
	}
}





////////////////////////뿌요 추가

void Player::AddPuyoPair(PuyoPair* _Pair)
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
