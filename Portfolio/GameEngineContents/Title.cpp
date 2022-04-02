#include "Title.h"
#include "CompanyLogo.h"
#include <GameEngine/GameEngineLevel.h>
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngine/GameEngine.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineImageManager.h>

Title::Title() 
    : TransTime(0.0f)
{
}

Title::~Title() 
{
}

//스크롤 배경을 두 개 만들어야 한다...
//오더가 처움부터 정해져서 바꿀 수가 없다.
void Title::Loading()
{
    CompanyLogo_ = CreateActor<CompanyLogo>(10);
    Puyo_ = CreateActor<CompanyLogo>(9);
    Background_ = CreateActor<CompanyLogo>(8);
    Roll_ = CreateActor<CompanyLogo>(7);
    Carbuncle_ = CreateActor<CompanyLogo>(6);
    Background1_ = CreateActor<CompanyLogo>(5);





    GameEngineRenderer* LogoRenderer = CompanyLogo_->CreateRenderer("TT_COMPANYLOGO.bmp");

    GameEngineRenderer* PuyoRenderer = Puyo_->CreateRenderer("TT_PUYO.bmp", RenderPivot::CENTER, { 100, 100 });
    PuyoRenderer->SetTransColor(RGB(255, 255, 255));

    GameEngineRenderer* BackRenderer = Background_->CreateRenderer("TT_BACK.bmp");

    GameEngineRenderer* RollRenderer = Roll_->CreateRenderer("TT_ROLL.bmp");

    //카방클 애니메이션
    GameEngineImage* Image = GameEngineImageManager::GetInst()->Find("TT_CARBUNCLE.bmp");
    Image->CutCount(3, 1);

    GameEngineRenderer* Renderer = Carbuncle_->CreateRenderer();
    Carbuncle_->SetMove({ -241, -20 });
    Renderer->CreateAnimation("TT_CARBUNCLE.bmp", "TT_CARBUNCLE", 0, 2, 0.1f, true);
    Renderer->ChangeAnimation("TT_CARBUNCLE");
    Renderer->SetTransColor(RGB(255, 85, 170));

    GameEngineRenderer* BackRenderer1 = Background1_->CreateRenderer("TT_BACK.bmp");


    //입력 초기화
    if (false == GameEngineInput::GetInst()->IsKey("Title"))
    {
        GameEngineInput::GetInst()->CreateKey("Title", VK_SPACE);
    }
}

void Title::Update()
{
    ChangeBackground();

    if (GameEngineInput::GetInst()->IsDown("Title"))
    {
        GameEngine::GetInst().ChangeLevel("MainMenu");
    }
}

void Title::LevelChangeStart()
{
}

void Title::LevelChangeEnd()
{
}

void Title::ChangeBackground()
{
    TransTime += GameEngineTime::GetDeltaTime();


    if (3.0f < TransTime && 0 == TransCount_)
    {
        CompanyLogo_->Death();

        ++TransCount_;
        TransTime = 0.0f;
    }

    if (1.0f < TransTime && 1 == TransCount_)
    {
        Puyo_->Death();
        Background_->Death();

        ++TransCount_;
        TransTime = 0.0f;
    }

    if (2.0f < TransTime && 2 == TransCount_)
    {
        Roll_->Death();

        ++TransCount_;
        TransTime = 0.0f;
    }


    //컴퍼니 로고 3초
    //뿌요 번개 노랑 검정
    //카방클 파랑 
    //아르르
    //게임 로고
}
