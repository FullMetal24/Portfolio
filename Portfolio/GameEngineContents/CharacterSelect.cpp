#include "CharacterSelect.h"
#include "CS_BackGround.h"
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngineBase/GameEngineWindow.h>

CharacterSelect::CharacterSelect() 
{
}

CharacterSelect::~CharacterSelect() 
{
}

void CharacterSelect::Loading()
{
	GameEngineActor* Actor_ = CreateActor<CS_BackGround>();
	Actor_->SetPosition(GameEngineWindow::GetScale().Half());

	Actor_->CreateRenderer("CS_BACKGROUND.bmp");
}


void CharacterSelect::Update()
{

}


void CharacterSelect::LevelChangeStart()
{

}

void CharacterSelect::LevelChangeEnd()
{

}
