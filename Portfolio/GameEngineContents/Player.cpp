#include "Player.h"
#include "GameEngineBase/GameEngineInput.h"
#include "Puyo.h"
#include "PuyoPair.h"

Player::Player() 
{
}

Player::~Player() 
{
}

void Player::Start()
{
	if (false == GameEngineInput::GetInst()->IsKey("PlayerLeft"))
	{
		GameEngineInput::GetInst()->CreateKey("PlayerLeft", VK_LEFT);
		GameEngineInput::GetInst()->CreateKey("PlayerRight", VK_RIGHT);
		GameEngineInput::GetInst()->CreateKey("PlayerDown", VK_DOWN);
		GameEngineInput::GetInst()->CreateKey("Rotate", VK_SPACE);
	}
}

void Player::Update()
{
	if (true == GameEngineInput::GetInst()->IsPress("PlayerLeft"))
	{
		//갈 수 있을지 없을지는 각 뿌요가 정한다.
		CurrnetPair_->GetCenterPuyo()->Left();
		CurrnetPair_->GetSecondPuyo()->Left();
	}

	if (true == GameEngineInput::GetInst()->IsPress("PlayerRight"))
	{
		CurrnetPair_->GetCenterPuyo()->Right();
		CurrnetPair_->GetSecondPuyo()->Right();
	}

	if (true == GameEngineInput::GetInst()->IsPress("PlayerDown"))
	{
		CurrnetPair_->GetCenterPuyo()->Down();
		CurrnetPair_->GetSecondPuyo()->Down();
	}

	if (true == GameEngineInput::GetInst()->IsPress("Rotate"))
	{
		CurrnetPair_->Rotate();
	}
}

void Player::Render()
{

}

void Player::AddPuyo()
{
	int x = 6;

	//PlayerMap_
	PlayerMap_[CurrnetPair_->GetX()][CurrnetPair_->GetY()] = CurrnetPair_->GetCenterPuyo();
	PlayerMap_[CurrnetPair_->GetX()][CurrnetPair_->GetY()] = CurrnetPair_->GetSecondPuyo();

	if (nullptr != PlayerMap_[CurrnetPair_->GetX()][CurrnetPair_->GetY() + 1])
	{

	}
}


