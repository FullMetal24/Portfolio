#pragma once
#include "GameEngine/GameEngineLevel.h"
#include "GameEngineContents/GlobalEnum.h"
#include "CarbuncleMenu.h"
#include <vector>

class GameEngineRenderer;
class GameEngineActor;
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
	void LevelChangeStart() override;
	void LevelChangeEnd() override;

	void BackgourndInit();

protected:

private:
	std::vector<GameEngineActor*> Menus_;
	std::vector<std::vector<GameEngineActor*>> BackGrounds_;
	std::vector<GameEngineRenderer*> Actors_;
	
	int MenuCount_;
};

