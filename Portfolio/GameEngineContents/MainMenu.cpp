#include "MainMenu.h"
#include "MM_BackGround.h"
//#include "BackGround.h"


MainMenu::MainMenu() 
{
}

MainMenu::~MainMenu() 
{
}


void MainMenu::Loading()
{
	CreateActor<MM_BackGround>(0); //뿌요 같은 경우 해당 조건이 되면 함수를 호출해서 다시 Crate
}

void MainMenu::Update()
{

}
