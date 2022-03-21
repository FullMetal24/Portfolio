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

	//카메라 좌우 이동
	//카방클 5개 레벨 고르기
	//enum문을 통해 고른 씬으로 이동

protected:

private:

};

