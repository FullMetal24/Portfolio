#pragma once
#include "GameEngine/GameEngineLevel.h"
//#include "PlayGame.h"

class CharacterSelect : public GameEngineLevel
{
public:
	CharacterSelect();
	~CharacterSelect();

	CharacterSelect(const CharacterSelect& _Other) = delete;
	CharacterSelect(CharacterSelect&& _Other) noexcept = delete;
	CharacterSelect& operator=(const CharacterSelect& _Other) = delete;
	CharacterSelect& operator=(CharacterSelect&& _Other) noexcept = delete;

	void Loading() override; //캐릭터 이미지 생성
	void Update() override; //상대 캐릭터 고르기

protected:

private:
	//고른 캐릭터를 PlayGame에 전달해야함
};

