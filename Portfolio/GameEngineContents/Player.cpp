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
		//AutoDown();
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
	SecondPuyo_ = CreatePuyo(2, 12, PuyoColor::RED);
	CenterPuyo_ = CreatePuyo(2, 11, PuyoColor::BLUE);

	//static bool Check = false;
	//if (true == Check)
	//{
	//	return;
	//}

	//for (int i = 0; i < 15; i++)
	//{
	//	CreatePuyo(0, i, PuyoColor::RED);
	//	CreatePuyo(1, i, PuyoColor::RED);
	//	CreatePuyo(2, i, PuyoColor::RED);
	//	CreatePuyo(3, i, PuyoColor::RED);
	//	CreatePuyo(4, i, PuyoColor::GREEN);
	//	CreatePuyo(5, i, PuyoColor::GREEN);

	//}

	PlayerState_ = PlayerState::MovePuyo;
	//Check = true;
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

