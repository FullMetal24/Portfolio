#include "GameEngine.h"
#include <GameEngineBase/GameEngineWindow.h>
#include "GameEngineLevel.h"
#include "GameEngineImageManager.h"
#include "GameEngineImage.h"
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngineBase/GameEngineTime.h>

std::map<std::string, GameEngineLevel*> GameEngine::AllLevel_;
GameEngineLevel* GameEngine::CurrentLevel_ = nullptr;
GameEngineLevel* GameEngine::NextLevel_ = nullptr;
GameEngine* GameEngine::UserContents_ = nullptr;
GameEngineImage* GameEngine::BackBufferImage_ = nullptr;
GameEngineImage* GameEngine::WindowMainImage_ = nullptr;

HDC GameEngine::BackBufferDC()
{
    return BackBufferImage_->ImageDC(); //백버퍼 전달
}

GameEngine::GameEngine() 
{
}

GameEngine::~GameEngine() 
{
}

void GameEngine::GameLoop()
{

}

void GameEngine::GameInit()
{

}

void GameEngine::GameEnd()
{

}

void GameEngine::WindowCreate()
{
    GameEngineWindow::GetInst().CreateGameWindow(nullptr, "GameWindow");
    GameEngineWindow::GetInst().ShowGameWindow();
    GameEngineWindow::GetInst().MessageLoop(EngineInit, EngineLoop);
}


void GameEngine::EngineInit()
{
    UserContents_->GameInit();

    // 백버퍼를 만들어 낸다.
    WindowMainImage_ = GameEngineImageManager::GetInst()->Create("WindowMain", GameEngineWindow::GetHDC());
    BackBufferImage_ = GameEngineImageManager::GetInst()->Create("BackBuffer", GameEngineWindow::GetScale());

    if (false == GameEngineInput::GetInst()->IsKey("Title"))
    {
        GameEngineInput::GetInst()->CreateKey("Title", 'T');
        GameEngineInput::GetInst()->CreateKey("Mainmenu", 'M');
        GameEngineInput::GetInst()->CreateKey("ChracterSelect", 'C');
        GameEngineInput::GetInst()->CreateKey("PlayGame", 'P');
        GameEngineInput::GetInst()->CreateKey("GameOver", 'G');
    }
}


void GameEngine::ChangeLevel(const std::string& _Name)
{
    std::map<std::string, GameEngineLevel*>::iterator FindIter = AllLevel_.find(_Name);

    if (AllLevel_.end() == FindIter)
    {
        MsgBoxAssert("Level Find Error");
        return;
    }

    NextLevel_ = FindIter->second;
}

void GameEngine::EngineLoop()
{
    GameEngineInput::GetInst()->Update();
    GameEngineTime::GetInst()->Update();

    if (GameEngineInput::GetInst()->IsDown("Title"))
    {
        UserContents_->ChangeLevel("Title"); //생성한 타이틀 씬을 현재 씬으로 바꾼다
    }
 
    if (GameEngineInput::GetInst()->IsDown("Mainmenu"))
    {
        UserContents_->ChangeLevel("MainMenu"); //생성한 타이틀 씬을 현재 씬으로 바꾼다
    }

    if (GameEngineInput::GetInst()->IsDown("ChracterSelect"))
    {
        UserContents_->ChangeLevel("ChracterSelect"); //생성한 타이틀 씬을 현재 씬으로 바꾼다
    }

    if (GameEngineInput::GetInst()->IsDown("PlayGame"))
    {
        UserContents_->ChangeLevel("InGame"); //생성한 타이틀 씬을 현재 씬으로 바꾼다
    }

    if (GameEngineInput::GetInst()->IsDown("GameOver"))
    {
        UserContents_->ChangeLevel("GameOver"); //생성한 타이틀 씬을 현재 씬으로 바꾼다
    }

    //엔진 수준에서 매 프레임 체크
    UserContents_->GameLoop();

    //update에서 화면을 깔끔하게 그리고 끝난 뒤 다음 레벨로 바뀌어야 하는지 체크
    if (nullptr != NextLevel_)
    {
        if (nullptr != CurrentLevel_)
        {

            CurrentLevel_->LevelChangeEnd();
        }

        CurrentLevel_ = NextLevel_;

        if (nullptr != CurrentLevel_)
        {
            CurrentLevel_->LevelChangeStart();
        }
   
        NextLevel_ = nullptr;
        GameEngineTime::GetInst()->Reset();

        Rectangle(WindowMainImage_->ImageDC(), 0, 0, WindowMainImage_->GetScale().ix(), WindowMainImage_->GetScale().iy());
        Rectangle(BackBufferImage_->ImageDC(), 0, 0, BackBufferImage_->GetScale().ix(), BackBufferImage_->GetScale().iy());
    }

    if (nullptr == CurrentLevel_)
    {
        MsgBoxAssert("Level is nullptr => GameEngine Loop Error");
    }

    //레벨 수준(엑터 등) 매 프레임 체크
    CurrentLevel_->Update();
    CurrentLevel_->ActorUpdate();
    CurrentLevel_->ActorRender();

    WindowMainImage_->BitCopy(BackBufferImage_);
}

void GameEngine::EngineEnd()
{
    UserContents_->GameEnd();

    std::map<std::string, GameEngineLevel*>::iterator StartIter = AllLevel_.begin();
    std::map<std::string, GameEngineLevel*>::iterator EndIter = AllLevel_.end();

    for (; StartIter != EndIter; ++StartIter)
    {
        if (nullptr == StartIter->second)
        {
            continue;
        }

        delete StartIter->second;
    }

    GameEngineImageManager::Destroy();
    GameEngineTime::Destroy();
    GameEngineInput::Destroy();
    GameEngineWindow::Destroy();
}
