#pragma once
#include "GameEngine/GameEngineLevel.h"
#include <GameEngineBase/GameEngineSound.h>
#include <GameEngineBase/GameEngineRandom.h>
#include "FadeInOutBackground.h"
#include "ContentsEnum.h"
#include <vector>
#include <list>

class GameEngineRenderer;
class GameEngineActor;
class GameEngineImage;
class MainMenuActor;
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
	void UserResetEnd() override;

	void LevelChangeStart(GameEngineLevel* _PrevLevel) override;
	void LevelChangeEnd(GameEngineLevel* _NextLevel) override;

	void MenuInit();
	void MenuImageInit();
	void BackgourndInit();

	void MenuUpdate();
	void RandomAnimation();
	void ResetMenuAnimation();
	void ResetPuyoAnimation(int _Index);

	void ChangeArrowAnimation();
	void SelectMenu();
	void FocusMenu();
	void BackgroundUpdate();

	void MenuRendererPause();

protected:

private:
	std::vector<MainMenuActor*> Menus_;
	std::vector<GameEngineRenderer*> MenuRenderers_;

	GameEngineRandom Random_;
	float RandomTime_;

	std::vector<MainMenuActor*> Puyos_;

	std::vector<GameEngineActor*> Arrows_;
	std::vector<GameEngineRenderer*> RightRenderers_;
	std::vector<GameEngineRenderer*> LeftRenderers_;

	std::vector<std::vector<MainMenuActor*>> BackGrounds_;
	
	FadeInOutBackground* FadeBackground_;

	GameEngineSoundPlayer MainMenuBgm_;
	GameEngineSound EffectSound_;

	float ChangeTime_;

	int MenuCount_;

	int RightIndex_;
	int LeftIndex_;

	bool MenuSelect_[5];
};

