#include "Player.h"
#include "GameEngineBase/GameEngineInput.h"
#include "Puyo.h"
#include "PuyoPair.h"

Player::Player() 
{
}

Player::~Player() 
{
	for (size_t x = 0; x < 6; x++)
	{
		for (size_t y = 0; y < 13; y++)
		{
			if (nullptr != PlayerMap_[x][y])
			{
				delete PlayerMap_[x][y];
				PlayerMap_[x][y] = nullptr;
			}
		}
	}
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
	PuyoInput();
	//뿌요들이 바닥에 갔는지도 확인해야하며, 착지하고서 배열에 넣어주는 편이 좋다.
	//넣기 전에 요소 위치만 비교하면 되니까 굳이 배열에 넣을 필요는 없고
	//넣은 다음에 탐색 함수를 호출...

	//결론: 착지를 했는지 체크하는 함수를 만들자.
}

void Player::Render()
{

}

void Player::PuyoInput()
{
	if (true == GameEngineInput::GetInst()->IsPress("PlayerLeft"))
	{
		//뿌요좌표에서의 이동처리
		//일단 "초기값"을 정해줘야 하는데 그건 나중에 하자
		CurrnetPair_->GetCenterPuyo()->SetX(CurrnetPair_->GetCenterPuyo()->GetX() + 1);
		CurrnetPair_->GetCenterPuyo()->SetY(CurrnetPair_->GetCenterPuyo()->GetY() + 1);

		CurrnetPair_->GetSecondPuyo()->SetX(CurrnetPair_->GetSecondPuyo()->GetX() + 1);
		CurrnetPair_->GetSecondPuyo()->SetY(CurrnetPair_->GetSecondPuyo()->GetY() + 1);

		//위에서 true를 반환해줘야만 뿌요가 이미지 상에서 움직일 수 있다
		//갈 수 있을지 없을지는 각 뿌요가 정한다?<-이렇게 안하는 편이 구조적으로 괜찮을듯
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

		//다운도 결국 뿌요에서 알아야 한다..
		//아니다 여기 업데이트에서 처리해주면 되려나
	}

	if (true == GameEngineInput::GetInst()->IsPress("Rotate"))
	{
		CurrnetPair_->Rotate();

		//방향 우선순위
		//<- 0
		//↓  1
		//-> 2
		//↑  3

		//세컨드가 위
		//센터가 아래
		
		//이미지적인 처리도 해야함...

		//어느 방향이동이든 센터를 중심으로 체크한다.
		if (nullptr != PlayerMap_[CurrnetPair_->GetCenterPuyo()->GetX() - 1][CurrnetPair_->GetCenterPuyo()->GetY()]) 
		{
			//주먹구구식으로 하는 건가(이게 규칙적인거가??
			CurrnetPair_->GetSecondPuyo()->SetX(CurrnetPair_->GetCenterPuyo()->GetX() - 1);
			CurrnetPair_->GetSecondPuyo()->SetY(CurrnetPair_->GetCenterPuyo()->GetY());
		}

		else if (nullptr != PlayerMap_[CurrnetPair_->GetCenterPuyo()->GetX() + 1][CurrnetPair_->GetCenterPuyo()->GetY()])
		{
			//주먹구구식으로 하는 건가(이게 규칙적인거가??
			CurrnetPair_->GetSecondPuyo()->SetX(CurrnetPair_->GetCenterPuyo()->GetX() + 1);
			CurrnetPair_->GetSecondPuyo()->SetY(CurrnetPair_->GetCenterPuyo()->GetY());
		}

		else if (nullptr != PlayerMap_[CurrnetPair_->GetCenterPuyo()->GetX()][CurrnetPair_->GetCenterPuyo()->GetY() - 1]) //위 
		{
			//주먹구구식으로 하는 건가(이게 규칙적인거가??
			CurrnetPair_->GetSecondPuyo()->SetX(CurrnetPair_->GetCenterPuyo()->GetX());
			CurrnetPair_->GetSecondPuyo()->SetY(CurrnetPair_->GetCenterPuyo()->GetY() - 1);
		}

		else if (nullptr != PlayerMap_[CurrnetPair_->GetCenterPuyo()->GetX() + 1][CurrnetPair_->GetCenterPuyo()->GetY() + 1]) //아래
		{
			//주먹구구식으로 하는 건가(이게 규칙적인거가??
			CurrnetPair_->GetSecondPuyo()->SetX(CurrnetPair_->GetCenterPuyo()->GetX());
			CurrnetPair_->GetSecondPuyo()->SetY(CurrnetPair_->GetCenterPuyo()->GetY() - 1);
		}
	}
}

bool Player::IsLanding() //이건 뿌요에서 해줘야 할 거 같다
{
	//이건 센터뿌요만 되는 함수다...
	if (nullptr != PlayerMap_[CurrnetPair_->GetCenterPuyo()->GetX()][CurrnetPair_->GetCenterPuyo()->GetY() + 1])
	{

	}

	return false;
}

void Player::AddPuyo()
{
	int x = 6;

	//PlayerMap_
	PlayerMap_[CurrnetPair_->GetCenterPuyo()->GetX()][CurrnetPair_->GetCenterPuyo()->GetY()] = CurrnetPair_->GetCenterPuyo();
	PlayerMap_[CurrnetPair_->GetSecondPuyo()->GetX()][CurrnetPair_->GetSecondPuyo()->GetX()] = CurrnetPair_->GetSecondPuyo();

	if (nullptr != PlayerMap_[CurrnetPair_->GetCenterPuyo()->GetX()][CurrnetPair_->GetCenterPuyo()->GetY() + 1]) 
	{
		PlayerMap_[CurrnetPair_->GetCenterPuyo()->GetX()][CurrnetPair_->GetCenterPuyo()->GetY()] = CurrnetPair_->GetCenterPuyo();
	}
}


void Delete()
{
	//
}