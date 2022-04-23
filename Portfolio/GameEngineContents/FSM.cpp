#include "FSM.h"
#include "PuyoPair.h"
#include <GameEngine/GameEngineRenderer.h>
#include "Puyo.h"
#include <queue>

FSM::FSM() 
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
	, LimitTime_(0)
	, FallTime_(0)
	, IsLose_(false)
	, IsWin_(false)
{
}

FSM::~FSM() 
{
}

void FSM::Start()
{
	for (int i = 0; i < 9; ++i)
	{
		ScoreRenderers_[i] = CreateRenderer("IG_ENEMY_NUMBER_0.bmp");
		ScoreRenderers_[i]->SetOrder(-1);
		ScoreRenderers_[i]->SetPivot({ GameEngineWindow::GetScale().Half().x + 140.f - (33.f * i), GameEngineWindow::GetScale().Half().y + 300.f });
	}
}

void FSM::Update()
{
	switch (FSMState_)
	{
	case PlayerState::NewPuyo:
		break;
	case PlayerState::MovePuyo:
		AutoFall();
		CurrentPuyoLandCheck();
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

	DigitScore(0);
	RenderToScore();
}

void FSM::AddPuyoPair(PuyoPair* _Pair)
{
	if (nullptr != FSMMap_[4][2])
	{
		FSMState_ = PlayerState::Lose;
		return;
	}

	CurrentPair_ = NextPair_;
	NextPair_ = NextNextPair_;
	NextNextPair_ = _Pair;

	FSMState_ = PlayerState::MovePuyo;
	PuyoDir_ = PuyoDir::UP;

	CurrentPairInit();
}

void FSM::CurrentPairInit()
{
	Puyo* SecondPuyo = CurrentPair_->GetSecondPuyo();
	Puyo* CenterPuyo = CurrentPair_->GetCenterPuyo();

	FSMMap_[0][2] = SecondPuyo;
	FSMMap_[2][2] = CenterPuyo;

	CenterPuyo->SetY(2);
	CenterPuyo->SetX(2);

	CenterX_ = CenterPuyo->GetX();
	CenterY_ = CenterPuyo->GetY();

	SecondPuyo->SetY(0);
	SecondPuyo->SetX(2);

	SecondX_ = SecondPuyo->GetX();
	SecondY_ = SecondPuyo->GetY();

	SecondPuyo->SetPosition({ 990.f, -90.f });
	CenterPuyo->SetPosition({ 990.f, -30.f });

	NextPair_->GetCenterPuyo()->SetPosition({ 735.f, 270.f });
	NextPair_->GetSecondPuyo()->SetPosition({ 735.f, 210.f });

	NextNextPair_->GetCenterPuyo()->SetPosition({ 670.f, 330.f });
	NextNextPair_->GetSecondPuyo()->SetPosition({ 670.f, 270.f });

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


void FSM::PlayerInput()
{
}

void FSM::MoveLeft()
{
	if (SecondX_ < CenterX_ || SecondY_ > CenterY_)
	{
		if (0 <= SecondX_ - 1 && nullptr == FSMMap_[SecondY_][SecondX_ - 1] && nullptr == FSMMap_[SecondY_ + 1][SecondX_ - 1])
		{
			FSMMap_[SecondY_][SecondX_ - 1] = CurrentPair_->GetSecondPuyo();
			FSMMap_[SecondY_][SecondX_] = nullptr;

			CurrentPair_->GetSecondPuyo()->SetMove(float4::LEFT * SideMoveDis_);
			CurrentPair_->GetSecondPuyo()->SetX(SecondX_ - 1);
			SecondX_ = CurrentPair_->GetSecondPuyo()->GetX();
		}

		if (0 <= CenterX_ - 1 && nullptr == FSMMap_[CenterY_][CenterX_ - 1]
			&& nullptr == FSMMap_[CenterY_ + 1][CenterX_ - 1]
			&& nullptr == FSMMap_[CenterY_ + 3][CenterX_ - 1])
		{
			if (nullptr == FSMMap_[SecondY_ + 2][SecondX_ - 1] || CurrentPair_->GetSecondPuyo() == FSMMap_[SecondY_ + 2][SecondX_ - 1])
			{
				FSMMap_[CenterY_][CenterX_ - 1] = CurrentPair_->GetCenterPuyo();
				FSMMap_[CenterY_][CenterX_] = nullptr;

				CurrentPair_->GetCenterPuyo()->SetMove(float4::LEFT * SideMoveDis_);
				CurrentPair_->GetCenterPuyo()->SetX(CenterX_ - 1);
				CenterX_ = CurrentPair_->GetCenterPuyo()->GetX();
			}
		}
	}

	else if (SecondX_ > CenterX_ || SecondY_ < CenterY_)
	{
		if (0 <= CenterX_ - 1 && nullptr == FSMMap_[CenterY_][CenterX_ - 1] && nullptr == FSMMap_[CenterY_ + 1][CenterX_ - 1])
		{
			FSMMap_[CenterY_][CenterX_ - 1] = CurrentPair_->GetCenterPuyo();
			FSMMap_[CenterY_][CenterX_] = nullptr;

			CurrentPair_->GetCenterPuyo()->SetMove(float4::LEFT * SideMoveDis_);
			CurrentPair_->GetCenterPuyo()->SetX(CenterX_ - 1);
			CenterX_ = CurrentPair_->GetCenterPuyo()->GetX();
		}

		if (0 <= SecondX_ - 1 && nullptr == FSMMap_[SecondY_][SecondX_ - 1]
			&& nullptr == FSMMap_[SecondY_ + 1][SecondX_ - 1]
			&& nullptr == FSMMap_[SecondY_ + 3][SecondX_ - 1])
		{
			if (nullptr == FSMMap_[SecondY_ + 2][SecondX_ - 1] || CurrentPair_->GetCenterPuyo() == FSMMap_[SecondY_ + 2][SecondX_ - 1])
			{
				FSMMap_[SecondY_][SecondX_ - 1] = CurrentPair_->GetSecondPuyo();
				FSMMap_[SecondY_][SecondX_] = nullptr;

				CurrentPair_->GetSecondPuyo()->SetMove(float4::LEFT * SideMoveDis_);
				CurrentPair_->GetSecondPuyo()->SetX(SecondX_ - 1);
				SecondX_ = CurrentPair_->GetSecondPuyo()->GetX();
			}
		}
	}
}

void FSM::MoveRight()
{
	if (SecondX_ < CenterX_ || SecondY_ < CenterY_)
	{
		if (5 >= CenterX_ + 1 && nullptr == FSMMap_[CenterY_][CenterX_ + 1] && nullptr == FSMMap_[CenterY_ + 1][CenterX_ + 1])
		{
			FSMMap_[CenterY_][CenterX_ + 1] = CurrentPair_->GetCenterPuyo();
			FSMMap_[CenterY_][CenterX_] = nullptr;

			CurrentPair_->GetCenterPuyo()->SetMove(float4::RIGHT * SideMoveDis_);
			CurrentPair_->GetCenterPuyo()->SetX(CenterX_ + 1);
			CenterX_ = CurrentPair_->GetCenterPuyo()->GetX();
		}

		if (5 >= SecondX_ + 1 && nullptr == FSMMap_[SecondY_][SecondX_ + 1]
			&& nullptr == FSMMap_[SecondY_ + 1][SecondX_ + 1]
			&& nullptr == FSMMap_[SecondY_ + 3][SecondX_ + 1])
		{
			if (nullptr == FSMMap_[SecondY_ + 2][SecondX_ + 1] || CurrentPair_->GetCenterPuyo() == FSMMap_[SecondY_ + 2][SecondX_ + 1])
			{
				FSMMap_[SecondY_][SecondX_ + 1] = CurrentPair_->GetSecondPuyo();
				FSMMap_[SecondY_][SecondX_] = nullptr;

				CurrentPair_->GetSecondPuyo()->SetMove(float4::RIGHT * SideMoveDis_);
				CurrentPair_->GetSecondPuyo()->SetX(SecondX_ + 1);
				SecondX_ = CurrentPair_->GetSecondPuyo()->GetX();
			}
		}
	}

	else if (SecondX_ > CenterX_ || SecondY_ > CenterY_)
	{
		if (5 >= SecondX_ + 1 && nullptr == FSMMap_[SecondY_][SecondX_ + 1] && nullptr == FSMMap_[SecondY_ + 1][SecondX_ + 1])
		{
			FSMMap_[SecondY_][SecondX_ + 1] = CurrentPair_->GetSecondPuyo();
			FSMMap_[SecondY_][SecondX_] = nullptr;

			CurrentPair_->GetSecondPuyo()->SetMove(float4::RIGHT * SideMoveDis_);
			CurrentPair_->GetSecondPuyo()->SetX(SecondX_ + 1);
			SecondX_ = CurrentPair_->GetSecondPuyo()->GetX();
		}

		if (5 >= CenterX_ + 1 && nullptr == FSMMap_[CenterY_][CenterX_ + 1]
			&& nullptr == FSMMap_[CenterY_ + 1][CenterX_ + 1]
			&& nullptr == FSMMap_[CenterY_ + 3][CenterX_ + 1])
		{
			if (nullptr == FSMMap_[CenterY_ + 2][CenterX_ + 1] || CurrentPair_->GetSecondPuyo() == FSMMap_[CenterY_ + 2][CenterX_ + 1])
			{
				FSMMap_[CenterY_][CenterX_ + 1] = CurrentPair_->GetCenterPuyo();
				FSMMap_[CenterY_][CenterX_] = nullptr;

				CurrentPair_->GetCenterPuyo()->SetMove(float4::RIGHT * SideMoveDis_);
				CurrentPair_->GetCenterPuyo()->SetX(CenterX_ + 1);
				CenterX_ = CurrentPair_->GetCenterPuyo()->GetX();
			}
		}
	}
}

void FSM::MoveDown()
{
	if (SecondY_ > CenterY_)
	{
		if (28 >= SecondY_ + 1 && nullptr == FSMMap_[SecondY_ + 2][SecondX_])
		{
			FSMMap_[SecondY_ + 1][SecondX_] = CurrentPair_->GetSecondPuyo();
			FSMMap_[SecondY_][SecondX_] = nullptr;

			CurrentPair_->GetSecondPuyo()->SetMove(float4::DOWN * DownMoveDis_);
			CurrentPair_->GetSecondPuyo()->SetY(SecondY_ + 1);
			SecondY_ = CurrentPair_->GetSecondPuyo()->GetY();
		}

		if (28 >= CenterY_ + 1 && nullptr == FSMMap_[CenterY_ + 2][CenterX_])
		{
			FSMMap_[CenterY_ + 1][CenterX_] = CurrentPair_->GetCenterPuyo();
			FSMMap_[CenterY_][CenterX_] = nullptr;

			CurrentPair_->GetCenterPuyo()->SetMove(float4::DOWN * DownMoveDis_);
			CurrentPair_->GetCenterPuyo()->SetY(CenterY_ + 1);
			CenterY_ = CurrentPair_->GetCenterPuyo()->GetY();
		}
	}

	else
	{
		if (28 >= CenterY_ + 1 && nullptr == FSMMap_[CenterY_ + 2][CenterX_])
		{
			FSMMap_[CenterY_ + 1][CenterX_] = CurrentPair_->GetCenterPuyo();
			FSMMap_[CenterY_][CenterX_] = nullptr;

			CurrentPair_->GetCenterPuyo()->SetMove(float4::DOWN * DownMoveDis_);
			CurrentPair_->GetCenterPuyo()->SetY(CenterY_ + 1);
			CenterY_ = CurrentPair_->GetCenterPuyo()->GetY();
		}

		if (28 >= SecondY_ + 1 && nullptr == FSMMap_[SecondY_ + 2][SecondX_])
		{
			FSMMap_[SecondY_ + 1][SecondX_] = CurrentPair_->GetSecondPuyo();
			FSMMap_[SecondY_][SecondX_] = nullptr;

			CurrentPair_->GetSecondPuyo()->SetMove(float4::DOWN * DownMoveDis_);
			CurrentPair_->GetSecondPuyo()->SetY(SecondY_ + 1);
			SecondY_ = CurrentPair_->GetSecondPuyo()->GetY();
		}
	}
}

void FSM::Rotate()
{
	while (true)
	{
		switch (PuyoDir_)
		{
		case PuyoDir::LEFT:
			if (nullptr == FSMMap_[CenterY_ + 2][CenterX_] && nullptr == FSMMap_[CenterY_ + 3][CenterX_])
			{
				FSMMap_[SecondY_][SecondX_] = nullptr;

				SecondY_ = CenterY_ + 2;
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

				FSMMap_[CenterY_ + 2][CenterX_] = CurrentPair_->GetSecondPuyo();
				CurrentPair_->GetSecondPuyo()->SetPosition(CurrentPair_->GetCenterPuyo()->GetPosition() + float4{ 0.f, 65.0f });

				PuyoDir_ = PuyoDir::DOWN;
			}
			else
			{
				FSMMap_[SecondY_][SecondX_] = nullptr;

				SecondY_ = CenterY_ + 2;
				SecondX_ = CenterX_;

				CurrentPair_->GetCenterPuyo()->SetPosition(CurrentPair_->GetCenterPuyo()->GetPosition() - float4{ 0.f, 65.0f });
				SecondY_ -= 2;
				CenterY_ -= 2;

				CurrentPair_->GetSecondPuyo()->SetX(SecondX_);
				CurrentPair_->GetSecondPuyo()->SetY(SecondY_);

				CurrentPair_->GetCenterPuyo()->SetX(CenterX_);
				CurrentPair_->GetCenterPuyo()->SetY(CenterY_);

				FSMMap_[CenterY_ + 2][CenterX_] = CurrentPair_->GetSecondPuyo();
				CurrentPair_->GetSecondPuyo()->SetPosition(CurrentPair_->GetCenterPuyo()->GetPosition() + float4{ 0.f, 65.0f });

				PuyoDir_ = PuyoDir::DOWN;
			}
			break;

		case PuyoDir::RIGHT:
			if (nullptr == FSMMap_[CenterY_ - 2][CenterX_] && nullptr == FSMMap_[CenterY_ - 3][CenterX_])
			{
				FSMMap_[SecondY_][SecondX_] = nullptr;

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

				FSMMap_[CenterY_ - 2][CenterX_] = CurrentPair_->GetSecondPuyo();
				CurrentPair_->GetSecondPuyo()->SetPosition(CurrentPair_->GetCenterPuyo()->GetPosition() + float4{ 0.f, -65.0f });

				PuyoDir_ = PuyoDir::UP;
			}
			else
			{
				FSMMap_[SecondY_][SecondX_] = nullptr;

				SecondY_ = CenterY_ - 2;
				SecondX_ = CenterX_;

				CurrentPair_->GetCenterPuyo()->SetPosition(CurrentPair_->GetCenterPuyo()->GetPosition() + float4{ 0.f, 65.0f });
				SecondY_ -= 2;
				CenterY_ -= 2;

				CurrentPair_->GetSecondPuyo()->SetX(SecondX_);
				CurrentPair_->GetSecondPuyo()->SetY(SecondY_);

				CurrentPair_->GetCenterPuyo()->SetX(CenterX_);
				CurrentPair_->GetCenterPuyo()->SetY(CenterY_);

				FSMMap_[CenterY_ - 2][CenterX_] = CurrentPair_->GetSecondPuyo();
				CurrentPair_->GetSecondPuyo()->SetPosition(CurrentPair_->GetCenterPuyo()->GetPosition() + float4{ 0.f, -65.0f });

				PuyoDir_ = PuyoDir::UP;
			}
			break;

		case PuyoDir::DOWN:
			if (nullptr == FSMMap_[CenterY_][CenterX_ + 1] && nullptr == FSMMap_[CenterY_ + 1][CenterX_ + 1]
				&& 5 > SecondX_)
			{
				FSMMap_[SecondY_][SecondX_] = nullptr;

				SecondY_ = CenterY_;
				SecondX_ = CenterX_ + 1;

				CurrentPair_->GetSecondPuyo()->SetX(SecondX_);
				CurrentPair_->GetSecondPuyo()->SetY(SecondY_);

				FSMMap_[CenterY_][CenterX_ + 1] = CurrentPair_->GetSecondPuyo();
				CurrentPair_->GetSecondPuyo()->SetPosition(CurrentPair_->GetCenterPuyo()->GetPosition() + float4{ 65.0f, 0.0f });

				PuyoDir_ = PuyoDir::RIGHT;
			}

			else
			{
				if (nullptr != FSMMap_[CenterY_][CenterX_ - 1] || nullptr != FSMMap_[CenterY_ + 1][CenterX_ - 1]
					|| 0 > SecondX_ - 1 || 0 > CenterX_)
				{
					PuyoDir_ = PuyoDir::RIGHT;
					continue;
				}

				FSMMap_[SecondY_][SecondX_] = nullptr;

				SecondY_ = CenterY_;
				SecondX_ = CenterX_ + 1;

				CurrentPair_->GetCenterPuyo()->SetPosition(CurrentPair_->GetCenterPuyo()->GetPosition() - float4{ 65.0f, 0.0f });
				SecondX_ -= 1;
				CenterX_ -= 1;

				CurrentPair_->GetSecondPuyo()->SetX(SecondX_);
				CurrentPair_->GetSecondPuyo()->SetY(SecondY_);

				FSMMap_[CenterY_][CenterX_ + 1] = CurrentPair_->GetSecondPuyo();
				CurrentPair_->GetSecondPuyo()->SetPosition(CurrentPair_->GetCenterPuyo()->GetPosition() + float4{ 65.0f, 0.0f });

				PuyoDir_ = PuyoDir::RIGHT;

			}
			break;

		case PuyoDir::UP:
			if (nullptr == FSMMap_[CenterY_][CenterX_ - 1] && nullptr == FSMMap_[CenterY_ + 1][CenterX_ - 1]
				&& 0 <= SecondX_ - 1)
			{
				FSMMap_[SecondY_][SecondX_] = nullptr;

				SecondY_ = CenterY_;
				SecondX_ = CenterX_ - 1;

				CurrentPair_->GetSecondPuyo()->SetX(SecondX_);
				CurrentPair_->GetSecondPuyo()->SetY(SecondY_);

				FSMMap_[CenterY_][CenterX_ - 1] = CurrentPair_->GetSecondPuyo();
				CurrentPair_->GetSecondPuyo()->SetPosition(CurrentPair_->GetCenterPuyo()->GetPosition() + float4{ -65.0f, 0.0f });

				PuyoDir_ = PuyoDir::LEFT;
			}

			else
			{
				if (nullptr != FSMMap_[CenterY_][CenterX_ + 1] || nullptr != FSMMap_[CenterY_ + 1][CenterX_ + 1]
					|| 5 < SecondX_ || 5 < CenterX_ + 1)
				{
					PuyoDir_ = PuyoDir::LEFT;
					continue;
				}

				FSMMap_[SecondY_][SecondX_] = nullptr;

				SecondY_ = CenterY_;
				SecondX_ = CenterX_ - 1;

				CurrentPair_->GetCenterPuyo()->SetPosition(CurrentPair_->GetCenterPuyo()->GetPosition() + float4{ 65.0f, 0.0f });
				SecondX_ += 1;
				CenterX_ += 1;

				CurrentPair_->GetSecondPuyo()->SetX(SecondX_);
				CurrentPair_->GetSecondPuyo()->SetY(SecondY_);

				FSMMap_[CenterY_][CenterX_ - 1] = CurrentPair_->GetSecondPuyo();
				CurrentPair_->GetSecondPuyo()->SetPosition(CurrentPair_->GetCenterPuyo()->GetPosition() + float4{ -65.0f, 0.0f });

				PuyoDir_ = PuyoDir::LEFT;

			}
			break;
		}
		break;
	}
}


void FSM::CurrentPuyoLandCheck()
{
	if (false == CurrentPair_->GetCenterPuyo()->GetLand())
	{
		if (CenterY_ >= 28)
		{
			CurrentPair_->GetCenterPuyo()->SetLand(true);
		}

		else if (CurrentPair_->GetSecondPuyo() != FSMMap_[CenterY_ + 2][CenterX_]
			&& nullptr != FSMMap_[CenterY_ + 2][CenterX_])
		{
			CurrentPair_->GetCenterPuyo()->SetLand(true);
		}

		else if (true == CurrentPair_->GetSecondPuyo()->GetLand()
			&& nullptr != FSMMap_[CenterY_ + 2][CenterX_])
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

		else if (CurrentPair_->GetCenterPuyo() != FSMMap_[SecondY_ + 2][SecondX_]
			&& nullptr != FSMMap_[SecondY_ + 2][SecondX_])
		{
			CurrentPair_->GetSecondPuyo()->SetLand(true);
		}

		else if (true == CurrentPair_->GetCenterPuyo()->GetLand()
			&& nullptr != FSMMap_[SecondY_ + 2][SecondX_])
		{
			CurrentPair_->GetSecondPuyo()->SetLand(true);
		}
	}

	if (true == CurrentPair_->GetCenterPuyo()->GetLand()
		&& true == CurrentPair_->GetSecondPuyo()->GetLand())
	{
		FSMState_ = PlayerState::PuyoCheck;
	}

}

void FSM::AutoFall()
{
	DownTime_ -= GameEngineTime::GetDeltaTime();

	if (0.0f >= DownTime_ && false == CurrentPair_->GetCenterPuyo()->GetLand()
		|| 0.0f >= DownTime_ && false == CurrentPair_->GetSecondPuyo()->GetLand())
	{
		MoveDown();
		DownTime_ = 0.5f;
	}
}

void FSM::FallAlonePuyo()
{
}

int FSM::GradePuyoAnimation(int _Dx, int _Dy, Puyo* _Puyo)
{
	return 0;
}

void FSM::ConvertPuyoAnimtion(int _Dx, int _Dy, Puyo* _Puyo)
{
}

void FSM::SearchPuyo()
{
	while (FSMState_ == PlayerState::PuyoCheck)
	{
		for (int Y = 0; Y < 30; ++Y)
		{
			for (int X = 0; X < 6; ++X)
			{
				if (nullptr != FSMMap_[Y][X]
					&& false == FSMMap_[Y][X]->GetVisited())
				{
					BfsPuyo(FSMMap_[Y][X]);
				}

				std::list<Puyo*>::iterator StartIter = Visited_.begin();
				std::list<Puyo*>::iterator EndIter = Visited_.end();

				if (4 <= Visited_.size())
				{
					FSMState_ = PlayerState::PuyoDestroy;
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

		FSMState_ = PlayerState::NewPuyo;
	}
}

void FSM::BfsPuyo(Puyo* _Puyo)
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

			if (nullptr != FSMMap_[Y][X])
			{
				Puyo* OtherPuyo = FSMMap_[Y][X];

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

void FSM::DestroyPuyo()
{
	std::list<Puyo*>::iterator StartIter = Visited_.begin();
	std::list<Puyo*>::iterator EndIter = Visited_.end();

	for (StartIter; StartIter != EndIter; ++StartIter)
	{
		if (nullptr != (*StartIter))
		{
			FSMMap_[(*StartIter)->GetY()][(*StartIter)->GetX()] = nullptr;
			(*StartIter)->RenderToDestroy();
		}
	}

	Visited_.clear();
	FSMState_ = PlayerState::PuyoDestroyEnd;
}

void FSM::DestroyEndPuyo()
{

	for (int Y = 0; Y < 30; Y++)
	{
		for (int X = 0; X < 6; X++)
		{
			if (nullptr != FSMMap_[Y][X]
				&& true == FSMMap_[Y][X]->GetDestroy())
			{
				if (false == FSMMap_[Y][X]->GetDestroyAnimationEnd())
				{
					return;
				}
			}
		}
	}

	FSMState_ = PlayerState::LandPuyo;
}

void FSM::LandPuyo()
{
	for (int Y = 0; Y < 30; Y++)
	{
		for (int X = 0; X < 6; X++)
		{
			if (nullptr != FSMMap_[Y][X])
			{
				Puyo* FallPuyo_ = FSMMap_[Y][X];

				if (28 >= FallPuyo_->GetY() + 1
					&& nullptr == FSMMap_[FallPuyo_->GetY() + 2][X])
				{
					Falls_.push_back(FallPuyo_);
					//FallPuyo_->SetFall(true);
				}
			}
		}
	}

	if (0 < Falls_.size())
	{
		FSMState_ = PlayerState::PuyoLandEnd;
	}

	else if (0 == Falls_.size())
	{
		FSMState_ = PlayerState::PuyoCheck;
	}
}

void FSM::LandEndPuyo()
{
	std::vector<Puyo*>::iterator StartIter = Falls_.begin();
	std::vector<Puyo*>::iterator EndIter = Falls_.end();

	for (; StartIter != EndIter; ++StartIter)
	{
		if (nullptr != (*StartIter))
		{
			while (28 >= (*StartIter)->GetY() + 1
				&& nullptr == FSMMap_[(*StartIter)->GetY() + 2][(*StartIter)->GetX()])
			{
				(*StartIter)->SetFall(false);
				(*StartIter)->SetMove(float4::DOWN * DownMoveDis_);
				(*StartIter)->SetY((*StartIter)->GetY() + 1);

				FSMMap_[(*StartIter)->GetY() + 1][(*StartIter)->GetX()] = (*StartIter);
				FSMMap_[(*StartIter)->GetY() - 1][(*StartIter)->GetX()] = nullptr;
			}
		}
	}
	Falls_.clear();
	FSMState_ = PlayerState::LandPuyo;
}



void FSM::DigitScore(int _Score)
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

void FSM::RenderToScore()
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