#include "Title.h"
#include "BlueLightning.h"
#include "CompanyLogo.h"
#include "Puyo.h"
#include <GameEngine/GameEngineLevel.h>
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngine/GameEngine.h>

Title::Title() 
{
}

Title::~Title() 
{
}

void Title::Loading()
{
	CreateActor<CompanyLogo>(0, "CompanyLogo");


    if (false == GameEngineInput::GetInst()->IsKey("Title"))
    {
        GameEngineInput::GetInst()->CreateKey("Title", VK_SPACE);
    }
}

void Title::Update()
{
    if (GameEngineInput::GetInst()->IsDown("Title"))
    {
        GameEngine::GlobalEngine().ChangeLevel("MainMenu"); //������ Ÿ��Ʋ ���� ���� ������ �ٲ۴�
    }

}

void Title::LevelChangeStart()
{
}

void Title::LevelChangeEnd()
{
}


