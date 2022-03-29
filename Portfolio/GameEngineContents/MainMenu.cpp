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

void MainMenu::LevelChangeStart()
{
}

void MainMenu::LevelChangeEnd()
{
}


//선생님이 말한 건 하나의 이미지를 하나의 클래스가 바꿔쓰는 식
//내가 생긱하는 건 하나의 엑터가 여러 이미지를 가지고 전부 화면에 그려내는 식