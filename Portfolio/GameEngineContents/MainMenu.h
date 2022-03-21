#pragma once
#include "GameEngine/GameEngineLevel.h"

class MainMenu : public GameEngineLevel
{
public:
	MainMenu();
	~MainMenu();

	MainMenu(const MainMenu& _Other) = delete;
	MainMenu(MainMenu&& _Other) noexcept = delete;
	MainMenu& operator=(const MainMenu& _Other) = delete;
	MainMenu& operator=(MainMenu&& _Other) noexcept = delete;

	void Loading() override; 
	void Update()  override;

	//ī�޶� �¿� �̵�
	//ī��Ŭ 5�� ���� ����
	//enum���� ���� �� ������ �̵�

protected:

private:

};

