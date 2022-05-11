#include "Option.h"
#include "OptionActor.h"
#include <GameEngine/GameEngineRenderer.h>

Option::Option()
{
}

Option::~Option()
{
}

void Option::Loading()
{
	OptionActor* Actor = CreateActor<OptionActor>();
	Actor->SetPosition(GameEngineWindow::GetScale().Half());
	Actor->CreateRenderer("OP_BACK.bmp");

	GameEngineRenderer* OptionMenu = Actor->CreateRenderer("OP_MENU.bmp");
	OptionMenu->SetPivot({ -190.f, -360.f });
	GameEngineRenderer* GoToTitle = Actor->CreateRenderer("OP_GOTOTITLE.bmp");
	GoToTitle->SetPivot({ -310.f, -250.f });
	GameEngineRenderer* GameLevel = Actor->CreateRenderer("OP_GAMELEVEL.bmp");
	GameLevel->SetPivot({ -435.f , -120.f });
	GameEngineRenderer* ChangeRule = Actor->CreateRenderer("OP_CHANGERULE.bmp");
	ChangeRule->SetPivot({ -450.f , 10.f });
	GameEngineRenderer* Offset = Actor->CreateRenderer("OP_OFFSET.bmp");
	Offset->SetPivot({ -500.f , 130.f });
	GameEngineRenderer* Alre = Actor->CreateRenderer("OP_ARLE.bmp");
	Alre->SetPivot({ -270.f , 250.f });
	GameEngineRenderer* GameQuit = Actor->CreateRenderer("OP_GAMEQUIT.bmp");
	GameQuit->SetPivot({ -440.f , 370.f });
}

void Option::Update()
{

}

