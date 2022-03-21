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

	void Loading() override; //ĳ���� �̹��� ����
	void Update() override; //��� ĳ���� ����

protected:

private:
	//�� ĳ���͸� PlayGame�� �����ؾ���
};

