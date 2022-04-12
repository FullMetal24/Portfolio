#pragma once
#include "GameEngine/GameEngineLevel.h"
#include "ContentsEnum.h"
#include "CarbuncleMenu.h"
#include <vector>
#include <list>

class GameEngineRenderer;
class GameEngineActor;
class GameEngineImage;
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

	void MenuInit();
	void BackgourndInit();

	void MenuUpdate();
	void BackgroundUpdate();

protected:

private:
	std::vector<GameEngineActor*> Menus_;

	std::vector<std::list<GameEngineActor*>> BackGrounds_;
	std::vector<GameEngineRenderer*> Actors_;
	
	GameEngineImage* Back_;

	int MenuCount_;
};

