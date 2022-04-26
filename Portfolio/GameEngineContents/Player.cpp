#include "Player.h"
#include "GameEngineBase/GameEngineInput.h"

Player::Player() 
	: PlayerMap_{nullptr}
	, PlayerState_(PlayerState::NewPuyo)
{
}

Player::~Player() 
{
}

void Player::Start()
{
	if (false == GameEngineInput::GetInst()->IsKey("Create"))
	{
		GameEngineInput::GetInst()->CreateKey("Create", VK_SPACE);
		GameEngineInput::GetInst()->CreateKey("Right", VK_RIGHT);
		GameEngineInput::GetInst()->CreateKey("Left", VK_LEFT);
		GameEngineInput::GetInst()->CreateKey("Down", VK_DOWN);
	}

	InitNextPair();
}

void Player::Update()
{
	InputCreatePuyo();

	switch (PlayerState_)
	{
	case PlayerState::NewPuyo:
		NewPuyoPair();
		break;
	case PlayerState::MovePuyo:
		InputPuyoMove();
		AutoDown();
		break;
	case PlayerState::LandPuyo:
		break;
	case PlayerState::PuyoLandEnd:
		break;
	case PlayerState::HindranceCheck:
		break;
	case PlayerState::PuyoCheck:
		break;
	case PlayerState::PuyoDestroy:
		break;
	case PlayerState::PuyoDestroyEnd:
		break;
	case PlayerState::Win:
		break;
	case PlayerState::Lose:
		break;
	}
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

void Player::InputCreatePuyo()
{
	if (GameEngineInput::GetInst()->IsDown("Create"))
	{
		if (nullptr == PlayerMap_[0][0]
 			&& nullptr == PlayerMap_[1][0])
		{
			Puyo* CenterPuyo = GetLevel()->CreateActor<Puyo>(10);
			Puyo* SecondPuyo = GetLevel()->CreateActor<Puyo>(10);

			PlayerMap_[0][0] = CenterPuyo;
			PlayerMap_[1][0] = SecondPuyo;

			SecondPuyo->SetColor(PuyoColor::BLUE);
			CenterPuyo->SetColor(PuyoColor::RED);

			CenterPuyo->InitAnimation(CenterPuyo->GetColor());
			SecondPuyo->InitAnimation(SecondPuyo->GetColor());

			CenterPuyo->SetPosition({ GameEngineWindow::GetScale().Half() + float4{-550, 300} });
			SecondPuyo->SetPosition({ GameEngineWindow::GetScale().Half() + float4{-550, 240} });
		}
	}
}


void Player::InputPuyoMove()
{
	if (GameEngineInput::GetInst()->IsDown("Left"))
	{
		CenterPuyo_->LeftPuyo(PlayerMap_);
		SecondPuyo_->LeftPuyo(PlayerMap_);
	}

	if (GameEngineInput::GetInst()->IsDown("Right"))
	{
		CenterPuyo_->RightPuyo(PlayerMap_);
		SecondPuyo_->RightPuyo(PlayerMap_);
	}

	if (GameEngineInput::GetInst()->IsDown("Down"))
	{
		CenterPuyo_->DownPuyo(PlayerMap_);
		SecondPuyo_->DownPuyo(PlayerMap_);
	}
}

void Player::AutoDown()
{
	DownTime += GameEngineTime::GetDeltaTime();

	if (0.5f <= DownTime)
	{
		DownTime = 0.f;
		CenterPuyo_->DownPuyo(PlayerMap_);
		SecondPuyo_->DownPuyo(PlayerMap_);
	}
}

