#pragma once
#include "GameEngine/GameEngineLevel.h"
#include "ContentsEnum.h"
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
	void MenuImageInit();
	void BackgourndInit();

	void MenuUpdate();
	void SelectMenu();
	void FocasMenu();
	void ArrowMoveToRight();
	void ArrowMoveToLeft();
	void BackgroundUpdate();

	void MenuRendererPause();

protected:

private:
	std::vector<GameEngineActor*> Menus_;
	std::vector<GameEngineRenderer*> MenuRenderers_;
	std::vector<GameEngineActor*> Puyos_;
	std::vector<GameEngineRenderer*> PuyoRenderers_;

	std::vector<GameEngineActor*> Arrows_;
	std::vector<GameEngineRenderer*> RightRenderers_;
	std::vector<GameEngineRenderer*> LeftRenderers_;

	std::vector<std::vector<GameEngineActor*>> BackGrounds_;
	
	GameEngineImage* Back_;

	int MenuCount_;

	int RightIndex_;
	int LeftIndex_;

	bool MenuSelect_[5];
};

