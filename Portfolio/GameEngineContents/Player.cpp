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
	, DestroyFallTime_(0)
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


void Player::Render()
{
}


void Player::Update()
{
	++LimitTime_;

	if (false == CurrentPair_->GetCenterPuyo()->GetLanding() && false == CurrentPair_->GetSecondPuyo()->GetLanding())
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

		if (true == GameEngineInput::GetInst()->IsPress("PuyoDown") && 0 == 20 / LimitTime_)
		{
			MoveDown();
			Score_ += 1;
			LimitTime_ = 0;
		}
	}

	DownTime_ -= GameEngineTime::GetDeltaTime();

	if (0.0f >= DownTime_ && false == CurrentPair_->GetCenterPuyo()->GetLanding()
		|| 0.0f >= DownTime_ && false == CurrentPair_->GetSecondPuyo()->GetLanding())
	{
		MoveDown();
		DownTime_ = 0.5f;
	}

	if (true == CurrentPair_->GetCenterPuyo()->GetLanding()
		&& true == CurrentPair_->GetSecondPuyo()->GetLanding())
	{
		IsAllLanding_ = true;
	}

	DestroyPuyo();
	FallAfterLanding();

	DigitScore(Score_);
	RenderToScore();

	FallPuyo();
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

	LandCheck();
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
			if (nullptr == PlayerMap_[CenterY_][CenterX_ + 1] && nullptr == PlayerMap_[CenterY_ + 1][CenterX_ + 1]
				&& 5 > SecondX_)
			{
				PlayerMap_[SecondY_][SecondX_] = nullptr;

				SecondY_ = CenterY_;
				SecondX_ = CenterX_ + 1;

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

				PlayerMap_[CenterY_][CenterX_ - 1] = CurrentPair_->GetSecondPuyo();
				CurrentPair_->GetSecondPuyo()->SetPosition(CurrentPair_->GetCenterPuyo()->GetPosition() + float4{ -65.0f, 0.0f });

				PuyoDir_ = PuyoDir::LEFT;

			}
			break;
		}
		break;
	}
}


void Player::BfsPuyo(Puyo* _Puyo)
{
	std::queue<Puyo*> PuyoQueue; //Å½»öÇÒ »Ñ¿ä¸¦ ´ã´Â Å¥
	PuyoQueue.push(_Puyo);

	Visited_.push_back(_Puyo); //¹æ¹®ÇÑ »Ñ¿ä¸¦ ´ã¾ÆµÎ´Â º¤ÅÍ
	_Puyo->Visit();

	std::list<Puyo*>::iterator StartVisited = Visited_.begin();
	std::list<Puyo*>::iterator EndVisited = Visited_.end();

	int Dx[4] = { 0, 0, -1, 1 }; //ÁÂ¿ì Å½»ö
	int Dy[4] = { -2, 2, 0, 0 }; //À§¾Æ·¡ Å½»ö

	while (false == PuyoQueue.empty())
	{
		Puyo* NodePuyo = PuyoQueue.front();
		PuyoQueue.pop();

		for (int i = 0; i < 4; i++)
		{
			int X = NodePuyo->GetX() + Dx[i];
			int Y = NodePuyo->GetY() + Dy[i];

			if (X < 0 || Y < 0 || X >= 6 || Y >= 30)
			{
				continue;
			}

			if (nullptr != PlayerMap_[Y][X]
				&& false == PlayerMap_[Y][X]->GetVisited()
				&& PlayerMap_[Y][X]->GetColor() == _Puyo->GetColor())
			{
				PuyoQueue.push(PlayerMap_[Y][X]);
				Visited_.push_back(PlayerMap_[Y][X]);
				PlayerMap_[Y][X]->Visit();

				ConvertPuyoAnimtion(Dx[i], Dy[i], PlayerMap_[Y][X]);
			}
		}
	}

	if (4 <= Visited_.size())
	{
		for (; StartVisited != EndVisited; ++StartVisited)
		{
			if (nullptr != (*StartVisited))
			{
				(*StartVisited)->SetIsDestroy(true);
			}
		}
	}

	for (; StartVisited != EndVisited; ++StartVisited)
	{
		if (nullptr != (*StartVisited))
		{
			(*StartVisited)->Exit();
		}
	}

	Visited_.clear();
}


void Player::DestroyPuyo()
{
	for (int Y = 0; Y < 30; ++Y)
	{
		for (int X = 0; X < 6; X++)
		{
			if (nullptr != PlayerMap_[Y][X])
			{
				if (true == PlayerMap_[Y][X]->GetIsDestroy() &&
					true == PlayerMap_[Y][X]->GetMyRenderer()->IsEndAnimation())
				{
					PlayerMap_[Y][X]->RenderToDestroy();
				}

				if (true == PlayerMap_[Y][X]->GetMyRenderer()->IsAnimationName("IG_RED_DESTROY")
					&& true == PlayerMap_[Y][X]->GetMyRenderer()->IsEndAnimation())
				{
					PlayerMap_[Y][X]->Death();
					PlayerMap_[Y][X] = nullptr;
				}

				else if (true == PlayerMap_[Y][X]->GetMyRenderer()->IsAnimationName("IG_BLUE_DESTROY")
					&& true == PlayerMap_[Y][X]->GetMyRenderer()->IsEndAnimation())
				{
					PlayerMap_[Y][X]->Death();
					PlayerMap_[Y][X] = nullptr;
				}

				else if (true == PlayerMap_[Y][X]->GetMyRenderer()->IsAnimationName("IG_GREEN_DESTROY")
					&& true == PlayerMap_[Y][X]->GetMyRenderer()->IsEndAnimation())
				{
					PlayerMap_[Y][X]->Death();
					PlayerMap_[Y][X] = nullptr;
				}

				else if (true == PlayerMap_[Y][X]->GetMyRenderer()->IsAnimationName("IG_YELLOW_DESTROY")
					&& true == PlayerMap_[Y][X]->GetMyRenderer()->IsEndAnimation())
				{
					PlayerMap_[Y][X]->Death();
					PlayerMap_[Y][X] = nullptr;
				}

				else if (true == PlayerMap_[Y][X]->GetMyRenderer()->IsAnimationName("IG_PURPLE_DESTROY")
					&& true == PlayerMap_[Y][X]->GetMyRenderer()->IsEndAnimation())
				{
					PlayerMap_[Y][X]->Death();
					PlayerMap_[Y][X] = nullptr;
				}
			}
		}
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
	if (false == CurrentPair_->GetCenterPuyo()->GetLanding())
	{
		if (CenterY_ >= 28)
		{
			CurrentPair_->GetCenterPuyo()->SetLanding(true);
		}

		else if (CurrentPair_->GetSecondPuyo() != PlayerMap_[CenterY_ + 2][CenterX_]
			&& nullptr != PlayerMap_[CenterY_ + 2][CenterX_])
		{
			CurrentPair_->GetCenterPuyo()->SetLanding(true);

		}

		else if (true == CurrentPair_->GetSecondPuyo()->GetLanding()
			&& nullptr != PlayerMap_[CenterY_ + 2][CenterX_])
		{
			CurrentPair_->GetCenterPuyo()->SetLanding(true);
		}

		if (true == CurrentPair_->GetCenterPuyo()->GetLanding())
		{
			BfsPuyo(CurrentPair_->GetCenterPuyo());
		}
	}

	if (false == CurrentPair_->GetSecondPuyo()->GetLanding())
	{
		if (SecondY_ >= 28)
		{
			CurrentPair_->GetSecondPuyo()->SetLanding(true);
		}

		else if (CurrentPair_->GetCenterPuyo() != PlayerMap_[SecondY_ + 2][SecondX_]
			&& nullptr != PlayerMap_[SecondY_ + 2][SecondX_])
		{
			CurrentPair_->GetSecondPuyo()->SetLanding(true);
		}

		else if (true == CurrentPair_->GetCenterPuyo()->GetLanding()
			&& nullptr != PlayerMap_[SecondY_ + 2][SecondX_])
		{
			CurrentPair_->GetSecondPuyo()->SetLanding(true);
		}

		if (true == CurrentPair_->GetSecondPuyo()->GetLanding())
		{
			BfsPuyo(CurrentPair_->GetSecondPuyo());
		}
	}
}

void Player::FallPuyo()
{
	++FallTime_;

	if (15 == FallTime_)
	{
		if (false == CurrentPair_->GetCenterPuyo()->GetLanding()
			&& true == CurrentPair_->GetSecondPuyo()->GetLanding())
		{
			MoveDown();
		}

		else if (false == CurrentPair_->GetSecondPuyo()->GetLanding()
			&& true == CurrentPair_->GetCenterPuyo()->GetLanding())
		{
			MoveDown();
		}

		FallTime_ = 0;
	}
}

void Player::FallAfterLanding()
{
	for (int Y = 0; Y < 30; ++Y)
	{
		for (int X = 0; X < 6; ++X)
		{
			if (nullptr != PlayerMap_[Y][X])
			{
				if (CurrentPair_->GetCenterPuyo() != PlayerMap_[Y][X]
					&& CurrentPair_->GetSecondPuyo() != PlayerMap_[Y][X])
				{
					Puyo* FallPuyo_ = PlayerMap_[Y][X];
					FallPuyo_->SetLanding(false);

					while (28 >= FallPuyo_->GetY() + 1 && nullptr == PlayerMap_[FallPuyo_->GetY() + 2][X])
					{
						FallPuyo_->SetMove(float4::DOWN * DownMoveDis_);
						FallPuyo_->SetY(FallPuyo_->GetY() + 1);
						PlayerMap_[FallPuyo_->GetY()][X] = FallPuyo_;

						PlayerMap_[FallPuyo_->GetY() - 1][X] = nullptr;
						FallPuyo_->SetLanding(true);
					}

					if (true == FallPuyo_->GetLanding()) //
					{
						BfsPuyo(FallPuyo_);
					}
				}
			}
		}
	}
}

int Player::GradePuyoAnimation(int _Dx, int _Dy, Puyo* _Puyo)
{
	int INumber = 0; //½Äº° ¹øÈ£
	bool* ConnectPtr = _Puyo->GetConnect();

	if (-1 == _Dx)
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

	else if (1 == _Dx)
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


//»Ñ¿ä ¾Ö´Ï¸ÞÀÌ¼Ç º¯È¯
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
