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
	//�ѿ���� �ٴڿ� �������� Ȯ���ؾ��ϸ�, �����ϰ� �迭�� �־��ִ� ���� ����.
	//�ֱ� ���� ��� ��ġ�� ���ϸ� �Ǵϱ� ���� �迭�� ���� �ʿ�� ����
	//���� ������ Ž�� �Լ��� ȣ��...

	//���: ������ �ߴ��� üũ�ϴ� �Լ��� ������.
}

void Player::Render()
{

}

void Player::PuyoInput()
{
	if (true == GameEngineInput::GetInst()->IsPress("PlayerLeft"))
	{
		//�ѿ���ǥ������ �̵�ó��
		//�ϴ� "�ʱⰪ"�� ������� �ϴµ� �װ� ���߿� ����
		CurrnetPair_->GetCenterPuyo()->SetX(CurrnetPair_->GetCenterPuyo()->GetX() + 1);
		CurrnetPair_->GetCenterPuyo()->SetY(CurrnetPair_->GetCenterPuyo()->GetY() + 1);

		CurrnetPair_->GetSecondPuyo()->SetX(CurrnetPair_->GetSecondPuyo()->GetX() + 1);
		CurrnetPair_->GetSecondPuyo()->SetY(CurrnetPair_->GetSecondPuyo()->GetY() + 1);

		//������ true�� ��ȯ����߸� �ѿ䰡 �̹��� �󿡼� ������ �� �ִ�
		//�� �� ������ �������� �� �ѿ䰡 ���Ѵ�?<-�̷��� ���ϴ� ���� ���������� ��������
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

		//�ٿ �ᱹ �ѿ信�� �˾ƾ� �Ѵ�..
		//�ƴϴ� ���� ������Ʈ���� ó�����ָ� �Ƿ���
	}

	if (true == GameEngineInput::GetInst()->IsPress("Rotate"))
	{
		CurrnetPair_->Rotate();

		//���� �켱����
		//<- 0
		//��  1
		//-> 2
		//��  3

		//�����尡 ��
		//���Ͱ� �Ʒ�
		
		//�̹������� ó���� �ؾ���...

		//��� �����̵��̵� ���͸� �߽����� üũ�Ѵ�.
		if (nullptr != PlayerMap_[CurrnetPair_->GetCenterPuyo()->GetX() - 1][CurrnetPair_->GetCenterPuyo()->GetY()]) 
		{
			//�ָԱ��������� �ϴ� �ǰ�(�̰� ��Ģ���ΰŰ�??
			CurrnetPair_->GetSecondPuyo()->SetX(CurrnetPair_->GetCenterPuyo()->GetX() - 1);
			CurrnetPair_->GetSecondPuyo()->SetY(CurrnetPair_->GetCenterPuyo()->GetY());
		}

		else if (nullptr != PlayerMap_[CurrnetPair_->GetCenterPuyo()->GetX() + 1][CurrnetPair_->GetCenterPuyo()->GetY()])
		{
			//�ָԱ��������� �ϴ� �ǰ�(�̰� ��Ģ���ΰŰ�??
			CurrnetPair_->GetSecondPuyo()->SetX(CurrnetPair_->GetCenterPuyo()->GetX() + 1);
			CurrnetPair_->GetSecondPuyo()->SetY(CurrnetPair_->GetCenterPuyo()->GetY());
		}

		else if (nullptr != PlayerMap_[CurrnetPair_->GetCenterPuyo()->GetX()][CurrnetPair_->GetCenterPuyo()->GetY() - 1]) //�� 
		{
			//�ָԱ��������� �ϴ� �ǰ�(�̰� ��Ģ���ΰŰ�??
			CurrnetPair_->GetSecondPuyo()->SetX(CurrnetPair_->GetCenterPuyo()->GetX());
			CurrnetPair_->GetSecondPuyo()->SetY(CurrnetPair_->GetCenterPuyo()->GetY() - 1);
		}

		else if (nullptr != PlayerMap_[CurrnetPair_->GetCenterPuyo()->GetX() + 1][CurrnetPair_->GetCenterPuyo()->GetY() + 1]) //�Ʒ�
		{
			//�ָԱ��������� �ϴ� �ǰ�(�̰� ��Ģ���ΰŰ�??
			CurrnetPair_->GetSecondPuyo()->SetX(CurrnetPair_->GetCenterPuyo()->GetX());
			CurrnetPair_->GetSecondPuyo()->SetY(CurrnetPair_->GetCenterPuyo()->GetY() - 1);
		}
	}
}

bool Player::IsLanding() //�̰� �ѿ信�� ����� �� �� ����
{
	//�̰� ���ͻѿ丸 �Ǵ� �Լ���...
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