#include "Title.h"
#include "CompanyLogo.h"
#include <GameEngine/GameEngineLevel.h>
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngine/GameEngine.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineImageManager.h>

enum class TitileOrder
{
    LINE_3,
    ROLL_3,
    COIN_1,
    ARLE_BACK,
    ARLE_FACE,
    ARLE_FINGER,
    LINE_2,
    ROLL_2,
    CARBUNCLE_BACK,
    CARBUNCLE,
    LINE_1,
    ROLL_1,
    PUYO_BACK,
    PUYO_EYE,
    PUYO,
    COMPANYLOGO
};

Title::Title() 
    : TitleActors_{}
    , TransTime(0.0f)
    , TransCount_(0)
{

}

Title::~Title() 
{
}

//스크롤 배경을 두 개 만들어야 한다...
//오더가 처움부터 정해져서 바꿀 수가 없다.
//하나의 엑터에 여러 개의 렌더러 부여
void Title::Loading()
{
    InitBackground();

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
    

    if (2 == TransCount_)
    {
        TitleActors_[(int)TitileOrder::ROLL_1]->SetMove(float4::DOWN * 200.f * GameEngineTime::GetDeltaTime());
        TitleActors_[(int)TitileOrder::LINE_1]->SetMove(float4::DOWN * 1300.f * GameEngineTime::GetDeltaTime());
    }

    if (4 == TransCount_)
    {
        TitleActors_[(int)TitileOrder::ROLL_2]->SetMove(float4::DOWN * 230.f * GameEngineTime::GetDeltaTime());
        TitleActors_[(int)TitileOrder::LINE_2]->SetMove(float4::DOWN * 1300.f * GameEngineTime::GetDeltaTime());
    }

    if (5 == TransCount_ 
        && TitleActors_[(int)TitileOrder::ARLE_FINGER]->GetPosition().y > GameEngineWindow::GetScale().Half().y + 250.f)
    {
        TitleActors_[(int)TitileOrder::ARLE_FINGER]->SetMove(float4::UP * 250.f * GameEngineTime::GetDeltaTime());
    }

    if (6 == TransCount_ 
        && TitleActors_[(int)TitileOrder::ROLL_3]->GetPosition().y < GameEngineWindow::GetScale().y - 130.f)
    {
        //페이드 인 아웃해야함
        TitleActors_[(int)TitileOrder::ROLL_3]->SetMove(float4::DOWN * 230.f * GameEngineTime::GetDeltaTime());
        TitleActors_[(int)TitileOrder::LINE_3]->SetMove(float4::DOWN * 1300.f * GameEngineTime::GetDeltaTime());
    }

}

void Title::LevelChangeStart()
{
}

void Title::LevelChangeEnd()
{
}

void Title::InitBackground()
{
    for (int i = 0; i < 16; i++)
    {
        //역순
        TitleActors_[i] = CreateActor<CompanyLogo>(i);
    }

    TitleActors_[(int)TitileOrder::COMPANYLOGO]->CreateRenderer("TT_COMPANYLOGO.bmp");

    GameEngineRenderer* PuyoRenderer = TitleActors_[(int)TitileOrder::PUYO]->CreateRenderer("TT_PUYO.bmp", RenderPivot::CENTER, { 100, 100 });
    PuyoRenderer->SetTransColor(RGB(255, 255, 255));

    GameEngineRenderer* EyeRenderer = TitleActors_[(int)TitileOrder::PUYO_EYE]->CreateRenderer("TT_PUYO_EYE.bmp", RenderPivot::CENTER, { 100, 100 });
    PuyoRenderer->SetTransColor(RGB(255, 255, 255));

    TitleActors_[(int)TitileOrder::PUYO_BACK]->CreateRenderer("TT_BACK.bmp");
    GameEngineRenderer* RollRenderer = TitleActors_[(int)TitileOrder::ROLL_1]->CreateRenderer("TT_ROLL.bmp");
    TitleActors_[(int)TitileOrder::ROLL_1]->SetPosition({ TitleActors_[(int)TitileOrder::ROLL_1]->GetPosition().x, TitleActors_[(int)TitileOrder::ROLL_1]->GetPosition().y - 200.f });
    RollRenderer->SetTransColor(RGB(0, 0, 0));
    TitleActors_[(int)TitileOrder::LINE_1]->CreateRenderer("TT_LINE.bmp", RenderPivot::BOT, {0 , 400});

    GameEngineImage* Image = GameEngineImageManager::GetInst()->Find("TT_CARBUNCLE.bmp");
    Image->CutCount(5, 1);

    GameEngineRenderer* Renderer = TitleActors_[(int)TitileOrder::CARBUNCLE]->CreateRenderer();
    TitleActors_[(int)TitileOrder::CARBUNCLE]->SetMove({ -241, -20 });
    Renderer->CreateAnimation("TT_CARBUNCLE.bmp", "TT_CARBUNCLE", 0, 4, 0.1f, true);
    Renderer->ChangeAnimation("TT_CARBUNCLE");
    Renderer->SetTransColor(RGB(255, 255, 255));

    TitleActors_[(int)TitileOrder::CARBUNCLE_BACK]->CreateRenderer("TT_BACK.bmp");

    GameEngineRenderer* RollRenderer2 = TitleActors_[(int)TitileOrder::ROLL_2]->CreateRenderer("TT_ROLL.bmp");
    RollRenderer2->SetTransColor(RGB(0, 0, 0));
    TitleActors_[(int)TitileOrder::LINE_2]->CreateRenderer("TT_LINE.bmp");
    TitleActors_[(int)TitileOrder::LINE_2]->CreateRenderer("TT_LINE.bmp", RenderPivot::BOT, { 0 , 400 });

    TitleActors_[(int)TitileOrder::ARLE_FACE]->CreateRenderer("TT_ARLE_FACE.bmp")->SetTransColor(RGB(255, 255, 255));
    GameEngineRenderer* FingerRenderer = TitleActors_[(int)TitileOrder::ARLE_FINGER]->CreateRenderer("TT_ARLE_FINGER.bmp");
    TitleActors_[(int)TitileOrder::ARLE_FINGER]->SetPosition({ GameEngineWindow::GetScale().x / 2.7f, GameEngineWindow::GetScale().y + FingerRenderer->GetImage()->GetScale().y / 2});
    FingerRenderer->SetTransColor(RGB(255, 255, 255));
    TitleActors_[(int)TitileOrder::ARLE_BACK]->CreateRenderer("TT_BACK.bmp");

    //페이드 인 아웃
    GameEngineRenderer* RollRenderer3 = TitleActors_[(int)TitileOrder::ROLL_3]->CreateRenderer("TT_ROLL.bmp");
    RollRenderer3->SetTransColor(RGB(0, 0, 0));
    TitleActors_[(int)TitileOrder::LINE_3]->CreateRenderer("TT_LINE.bmp");



    GameEngineImage* CoinImage = GameEngineImageManager::GetInst()->Find("TT_CARCOIN.bmp");
    CoinImage->CutCount(11, 1);

    GameEngineRenderer* Renderer1 = TitleActors_[(int)TitileOrder::COIN_1]->CreateRenderer();
    Renderer1->CreateAnimation("TT_CARCOIN.bmp", "TT_CARCOIN", 0, 10, 0.1f, true);
    Renderer1->ChangeAnimation("TT_CARCOIN");
    Renderer1->SetTransColor(RGB(255, 255, 255));
}

void Title::ChangeBackground()
{
    TransTime += GameEngineTime::GetDeltaTime();


    if (3.0f < TransTime && 0 == TransCount_)
    {
        TitleActors_[(int)TitileOrder::COMPANYLOGO]->Death();

        ++TransCount_;
        TransTime = 0.0f;
    }

    else if (1.5f < TransTime && 1 == TransCount_)
    {
        TitleActors_[(int)TitileOrder::PUYO]->Death();
        TitleActors_[(int)TitileOrder::PUYO_EYE]->Death();
        TitleActors_[(int)TitileOrder::PUYO_BACK]->Death();

        ++TransCount_;
        TransTime = 0.0f;
    }

    else if (1.0f < TransTime && 2 == TransCount_)
    {
        TitleActors_[(int)TitileOrder::ROLL_1]->Death();
        TitleActors_[(int)TitileOrder::LINE_1]->Death();
        TitleActors_[(int)TitileOrder::ROLL_2]->SetPosition({ TitleActors_[(int)TitileOrder::ROLL_2]->GetPosition().x, TitleActors_[(int)TitileOrder::ROLL_2]->GetPosition().y - 100.f });

        ++TransCount_;
        TransTime = 0.0f;
    }

    else if (1.0f < TransTime && 3 == TransCount_)
    {
        TitleActors_[(int)TitileOrder::CARBUNCLE]->Death();
        TitleActors_[(int)TitileOrder::CARBUNCLE_BACK]->Death();

        ++TransCount_;
        TransTime = 0.0f;
    }

    else if (2.0f < TransTime && 4 == TransCount_)
    {
        TitleActors_[(int)TitileOrder::ROLL_2]->Death();
        TitleActors_[(int)TitileOrder::LINE_2]->Death();
        TitleActors_[(int)TitileOrder::ROLL_3]->SetPosition({ TitleActors_[(int)TitileOrder::ROLL_2]->GetPosition().x, TitleActors_[(int)TitileOrder::ROLL_2]->GetPosition().y - 250.f});

        ++TransCount_;
        TransTime = 0.0f;
    }

    //카운트가 3일 때 2초 동안의 유예가 있음
    else if (2.0f < TransTime && 5 == TransCount_)
    {
        TitleActors_[(int)TitileOrder::ARLE_FACE]->Death();
        TitleActors_[(int)TitileOrder::ARLE_FINGER]->Death();
        TitleActors_[(int)TitileOrder::ARLE_BACK]->Death();

        ++TransCount_;
        TransTime = 0.0f;
    }

    //else if (10.0f < TransTime && 6 == TransCount_)
    //{
    //    TitleActors_[(int)TitileOrder::ROLL_3]->Death();
    //    TitleActors_[(int)TitileOrder::LINE_3]->Death();

    //    ++TransCount_;
    //    TransTime = 0.0f;
    //}

    //컴퍼니 로고 3초
    //뿌요 번개 노랑 검정
    //카방클 파랑 
    //아르르
    //게임 로고
}
