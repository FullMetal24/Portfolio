#include "Player.h"
#include "GameEngineBase/GameEngineInput.h"
#include <GameEngineBase/GameEngineWindow.h>
#include "Puyo.h"
#include "PuyoPair.h"
#include <cmath>

Player::Player()
	: PuyoDir_(PuyoDir::UP)
	, CenterX_(0)
	, CenterY_(0)
	, SecondX_(0)
	, SecondY_(0)
	, DownMoveDis_(30.0f) 
	, SideMoveDis_(65.0f)
	, DownTime(0.5f)
	, IsAllLanding_(false)
	, IsLose_(false)
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
	if (false == CurrentPair_->GetCenterPuyo()->GetLandiung() && false == CurrentPair_->GetSecondPuyo()->GetLandiung())
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

		if (true == GameEngineInput::GetInst()->IsPress("PuyoDown"))
		{
			MoveDown();
		}
	}


	DownTime -= GameEngineTime::GetDeltaTime();

	if (0.0f >= DownTime && false == CurrentPair_->GetCenterPuyo()->GetLandiung()
		|| 0.0f >= DownTime && false == CurrentPair_->GetSecondPuyo()->GetLandiung())
	{
		MoveDown();
		DownTime = 0.5f;
	
		LandCheck();
	}


	if (true == CurrentPair_->GetCenterPuyo()->GetLandiung() 
		&& true == CurrentPair_->GetSecondPuyo()->GetLandiung())
	{
   		IsAllLanding_ = true;
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

	else if(SecondX_ > CenterX_ || SecondY_ < CenterY_)
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

	else if(SecondX_ > CenterX_ || SecondY_ > CenterY_)
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
						CurrentPair_->GetCenterPuyo()->SetPosition(CurrentPair_->GetCenterPuyo()->GetPosition() - float4{ 0.f, 65.0f });
						SecondY_ -= 2;
						CenterY_ -= 2;
					}

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

					PlayerMap_[CenterY_ - 2][CenterX_] = CurrentPair_->GetSecondPuyo();
					CurrentPair_->GetSecondPuyo()->SetPosition(CurrentPair_->GetCenterPuyo()->GetPosition() + float4{ 0.f, -65.0f });

					PuyoDir_ = PuyoDir::UP;
				}
				break;  

			case PuyoDir::DOWN:
   				if (nullptr == PlayerMap_[CenterY_][CenterX_ + 1] && nullptr == PlayerMap_[CenterY_ + 1][CenterX_ + 1])
				{
					PlayerMap_[SecondY_][SecondX_] = nullptr;

					SecondY_ = CenterY_;
					SecondX_ = CenterX_ + 1;

					if (5 < SecondX_)
					{
 						if (nullptr != PlayerMap_[CenterY_][CenterX_ - 1] || nullptr != PlayerMap_[CenterY_ + 1][CenterX_ - 1] || 0 > SecondX_ - 1)
						{
							PuyoDir_ = PuyoDir::RIGHT;
							continue;
						}

						CurrentPair_->GetCenterPuyo()->SetPosition(CurrentPair_->GetCenterPuyo()->GetPosition() - float4{ 65.0f, 0.0f });
					  	SecondX_ -= 1;
						CenterX_ -= 1;
					}

					PlayerMap_[CenterY_][CenterX_ + 1] = CurrentPair_->GetSecondPuyo();
					CurrentPair_->GetSecondPuyo()->SetPosition(CurrentPair_->GetCenterPuyo()->GetPosition() + float4{ 65.0f, 0.0f });

					PuyoDir_ = PuyoDir::RIGHT;
				}

				else
				{
					if (nullptr != PlayerMap_[CenterY_][CenterX_ + 1] && nullptr != PlayerMap_[CenterY_ + 1][CenterX_ + 1])
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

					PlayerMap_[CenterY_][CenterX_ + 1] = CurrentPair_->GetSecondPuyo();
					CurrentPair_->GetSecondPuyo()->SetPosition(CurrentPair_->GetCenterPuyo()->GetPosition() + float4{ 65.0f, 0.0f });

					PuyoDir_ = PuyoDir::RIGHT;
				}
				break;
				
			case PuyoDir::UP:
  				if (nullptr == PlayerMap_[CenterY_][CenterX_ - 1] && nullptr == PlayerMap_[CenterY_ + 1][CenterX_ - 1])
				{
					PlayerMap_[SecondY_][SecondX_] = nullptr;

					SecondY_ = CenterY_;
					SecondX_ = CenterX_ - 1;

  					if (0 > SecondX_)
					{
						if (nullptr != PlayerMap_[CenterY_][CenterX_ + 1] || nullptr != PlayerMap_[CenterY_ + 1][CenterX_ + 1] || 5 < SecondX_ + 1)
						{
 							PuyoDir_ = PuyoDir::LEFT;
							continue;
						}
						
						CurrentPair_->GetCenterPuyo()->SetPosition(CurrentPair_->GetCenterPuyo()->GetPosition() + float4{ 65.0f, 0.0f });
						SecondX_ += 1;
						CenterX_ += 1;
					}

					PlayerMap_[CenterY_][CenterX_ - 1] = CurrentPair_->GetSecondPuyo();
					CurrentPair_->GetSecondPuyo()->SetPosition(CurrentPair_->GetCenterPuyo()->GetPosition() + float4{ -65.0f, 0.0f });

					PuyoDir_ = PuyoDir::LEFT;
				}		

				else
				{
					if (nullptr != PlayerMap_[CenterY_][CenterX_ + 1] && nullptr != PlayerMap_[CenterY_ + 1][CenterX_ + 1])
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

					PlayerMap_[CenterY_][CenterX_ - 1] = CurrentPair_->GetSecondPuyo();
					CurrentPair_->GetSecondPuyo()->SetPosition(CurrentPair_->GetCenterPuyo()->GetPosition() + float4{ -65.0f, 0.0f });

					PuyoDir_ = PuyoDir::LEFT;
				}
				break;
		}
		break;
	}
 }



////////////////////////»Ñ¿ä Ãß°¡
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

}

void Player::AddPuyoPair(PuyoPair* _Pair)
{
	if (nullptr != PlayerMap_[4][2])
	{
		IsLose_ = true; 

		return;
	}

	//±íÀº º¹»ç? ¾èÀº º¹»ç?
	//nullptr·Î ÇØÁà¾ß ÇÏ³ª? 
	CurrentPair_ = NextPair_;
	NextPair_ = NextNextPair_;
	NextNextPair_ = _Pair;

	PuyoDir_ = PuyoDir::UP;

	IsAllLanding_ = false;

	CurrentPairInit();
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
			if (nullptr != PlayerMap_[CenterY_ + 2][CenterX_])
			{
				CurrentPair_->GetCenterPuyo()->SetLanding(true);
			}
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
			if (nullptr != PlayerMap_[SecondY_ + 2][SecondX_])
			{
				CurrentPair_->GetSecondPuyo()->SetLanding(true);
			}
		}
	}
}
