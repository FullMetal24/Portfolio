#include "MyGame.h"
#include "Title.h"
#include "Play.h"
#include "MainMenu.h"
#include "GameOver.h"
#include <GameEngineBase/GameEngineWindow.h>

MyGame::MyGame() 
{
}

MyGame::~MyGame() 
{
}

void MyGame::GameInit()
{
	GameEngineWindow::GetInst().SetWindowScaleAndPosition({ 100, 100 }, { 1280, 720 });

	CreateLevel<Title>("Title");
	CreateLevel<Play>("Play");
	CreateLevel<MainMenu>("MainMenu");
	CreateLevel<GameOver>("GameOver");

	ChangeLevel("Title");
}

void MyGame::GameLoop()
{

}

void MyGame::GameEnd()
{

}
