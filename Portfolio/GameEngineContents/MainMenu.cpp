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
	CreateActor<MM_BackGround>(0); //�ѿ� ���� ��� �ش� ������ �Ǹ� �Լ��� ȣ���ؼ� �ٽ� Crate
}

void MainMenu::Update()
{

}
