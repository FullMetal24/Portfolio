#include "Player.h"
#include "GameEngineBase/GameEngineInput.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineImageManager.h>
#include "ContentsEnum.h"
#include "Puyo.h"
#include "PuyoPair.h"


bool IsOver(float4 _Index) 
{
	if (0 > _Index.ix())
	{
		return true;
	}

	if (0 > _Index.iy())
	{
		return true;
	}

	if (6 <= _Index.ix())
	{
		return true;
	}

	if (30 <= _Index.iy())
	{
		return true;
	}

	return false;
}

void Player::OnePuyoSearch(Puyo* _Puyo, std::vector<Puyo*>& _Out)
{
	if (FindAllDestroy.end() !=  FindAllDestroy.find(_Puyo))
	{
		return;
	}

	FindAllDestroy.insert(_Puyo);
	_Out.push_back(_Puyo);

	static float4 ArrDir[4] = {
		float4::LEFT,
		float4::RIGHT,
		float4::UP * 2,
		float4::DOWN * 2,
	};

	float4 Index = _Puyo->GetIndex();

	for (size_t i = 0; i < 4; i++)
	{
		float4 CheckIndex = ArrDir[i] + Index;

		if (IsOver(ArrDir[i] + Index))
		{
			continue;
		}

		Puyo* Other = PlayerMap_[CheckIndex.iy()][CheckIndex.ix()];

		if (nullptr == Other)
		{
			continue;
		}

		if (Other->GetColor() == _Puyo->GetColor())
		{
			OnePuyoSearch(Other, _Out);
		}
	}
}

void Player::SearchPuyo()
{
	for (int Y = 29; Y >= 0; --Y)
	{
		for (int X = 0; X < 6; ++X)
		{
			Puyo* Current = PlayerMap_[Y][X];

			if (nullptr == Current)
			{
				continue;
			}

			if (FindAllDestroy.end() != FindAllDestroy.find(Current))
			{
				continue;
			}

			if (NextPair_->GetSecondPuyo()== Current
				&& NextPair_->GetCenterPuyo() == Current)
			{
				continue;
			}

			if (NextNextPair_->GetSecondPuyo() == Current
				&& NextNextPair_->GetCenterPuyo() == Current)
			{
				continue;
			}

			std::vector<Puyo*> Check;

			OnePuyoSearch(Current, Check);

			if (4 > Check.size())
			{
				continue;
			}

			for (size_t i = 0; i < Check.size(); i++)
			{
				FindAllDestroy.insert(Check[i]);
			}

			AllDestroyPuyo.push_back(Check);
		}
	}

	FindAllDestroy.clear();
	PlayerState_ = PlayerState::PuyoDestroy;
}
