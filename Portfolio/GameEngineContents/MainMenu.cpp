#include "MainMenu.h"
#include "FadeInOutBackground.h"
#include "MainMenuActor.h"
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngineBase/GameEngineMath.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngine/GameEngine.h>
#include "ContentsEnum.h"
#include <GameEngineBase/GameEngineTime.h>

MainMenu::MainMenu()
	: Arrows_{}
	, RandomTime_(0.3f)
	, ChangeTime_{0.f}
	, MenuCount_(0)
	, RightIndex_(0)
	, LeftIndex_(0)
	, MenuSelect_{}
{
}

MainMenu::~MainMenu() 
{
}


void MainMenu::Loading()
{
	FadeBackground_ = CreateActor<FadeInOutBackground>();

	MenuImageInit();
	MenuInit();
	BackgourndInit();

	if (false == GameEngineInput::GetInst()->IsKey("ManiMenu_Right"))
	{
		GameEngineInput::GetInst()->CreateKey("ManiMenu_Right", VK_RIGHT);
		GameEngineInput::GetInst()->CreateKey("ManiMenu_Left", VK_LEFT);
		GameEngineInput::GetInst()->CreateKey("ManiMenu_Select", VK_RETURN);
	}
}

void MainMenu::MenuImageInit()
{
	GameEngineActor* SelectMenu = CreateActor<MainMenuActor>(4);
	SelectMenu->SetPosition({ GameEngineWindow::GetScale().Half().x, 150 });
	GameEngineRenderer* SelectMenuRenderer = SelectMenu->CreateRenderer("MM_SELECT_1.bmp");

	//밝은 카방클 
	{
		GameEngineImage* Image = GameEngineImageManager::GetInst()->Find("MM_MENU_1_IDLE.bmp");
		Image->CutCount(3, 1);

		GameEngineImage* Image1 = GameEngineImageManager::GetInst()->Find("MM_MENU_2_IDLE.bmp");
		Image1->CutCount(3, 1);

		GameEngineImage* Image2 = GameEngineImageManager::GetInst()->Find("MM_MENU_3_IDLE.bmp");
		Image2->CutCount(3, 1);

		GameEngineImage* Image3 = GameEngineImageManager::GetInst()->Find("MM_MENU_4_IDLE.bmp");
		Image3->CutCount(3, 1);

		GameEngineImage* Image4 = GameEngineImageManager::GetInst()->Find("MM_MENU_5_IDLE.bmp");
		Image4->CutCount(3, 1);
	}

	//어둔 카방클(Idle)
	{
		GameEngineImage* Image = GameEngineImageManager::GetInst()->Find("MM_MENU_1_IDLE_DARK.bmp");
		Image->CutCount(3, 1);

		GameEngineImage* Image1 = GameEngineImageManager::GetInst()->Find("MM_MENU_2_IDLE_DARK.bmp");
		Image1->CutCount(3, 1);

		GameEngineImage* Image2 = GameEngineImageManager::GetInst()->Find("MM_MENU_3_IDLE_DARK.bmp");
		Image2->CutCount(3, 1);

		GameEngineImage* Image3 = GameEngineImageManager::GetInst()->Find("MM_MENU_4_IDLE_DARK.bmp");
		Image3->CutCount(3, 1);

		GameEngineImage* Image4 = GameEngineImageManager::GetInst()->Find("MM_MENU_5_IDLE_DARK.bmp");
		Image4->CutCount(3, 1);
	}

	//어둔 카방클(Close)
	{
		GameEngineImage* Image = GameEngineImageManager::GetInst()->Find("MM_MENU_1_CLOSE.bmp");
		Image->CutCount(4, 1);

		GameEngineImage* Image1 = GameEngineImageManager::GetInst()->Find("MM_MENU_2_CLOSE.bmp");
		Image1->CutCount(4, 1);

		GameEngineImage* Image2 = GameEngineImageManager::GetInst()->Find("MM_MENU_3_CLOSE.bmp");
		Image2->CutCount(4, 1);

		GameEngineImage* Image3 = GameEngineImageManager::GetInst()->Find("MM_MENU_4_CLOSE.bmp");
		Image3->CutCount(4, 1);

		GameEngineImage* Image4 = GameEngineImageManager::GetInst()->Find("MM_MENU_5_CLOSE.bmp");
		Image4->CutCount(4, 1);
	}


	//화살표
	GameEngineImage* RightImage = GameEngineImageManager::GetInst()->Find("MM_ARROW_RIGHT.bmp");
	RightImage->CutCount(2, 1);

	GameEngineImage* LeftImage = GameEngineImageManager::GetInst()->Find("MM_ARROW_LEFT.bmp");
	LeftImage->CutCount(2, 1);

	GameEngineImage* RightDarkImage = GameEngineImageManager::GetInst()->Find("MM_ARROW_RIGHT_DARK.bmp");
	RightDarkImage->CutCount(1, 1);

	GameEngineImage* LeftDarkImage = GameEngineImageManager::GetInst()->Find("MM_ARROW_LEFT_DARK.bmp");
	LeftDarkImage->CutCount(1, 1);


	GameEngineImage* PuyoImage = GameEngineImageManager::GetInst()->Find("MM_PUYO.bmp");
	PuyoImage->CutCount(1, 1);

	GameEngineImage* MoveImage = GameEngineImageManager::GetInst()->Find("MM_PUYO_MOVE.bmp");
	MoveImage->CutCount(2, 1);

	GameEngineImage* PuyoDarkImage = GameEngineImageManager::GetInst()->Find("MM_PUYO_DARK.bmp");
	PuyoDarkImage->CutCount(1, 1);

	GameEngineImage* PuyoDestroyImage = GameEngineImageManager::GetInst()->Find("MM_PUYO_DESTROY.bmp");
	PuyoDestroyImage->CutCount(3, 1);
}

void MainMenu::MenuInit()
{
	MainMenuActor* Menu1 = CreateActor<MainMenuActor>(3);
	Menu1->SetPosition({ Menu1->GetPosition().x - 400.f, GameEngineWindow::GetScale().Half().y + 100.f });

	GameEngineRenderer* Menu1_Renerer = Menu1->CreateRenderer();
	Menu1_Renerer->CreateAnimation("MM_MENU_1_IDLE.bmp", "MM_MENU_1_IDLE", 0, 2, 0.15f, false);
	Menu1_Renerer->CreateAnimation("MM_MENU_1_IDLE_DARK.bmp", "MM_MENU_1_IDLE_DARK", 0, 2, 0.15f, false);
	Menu1_Renerer->CreateAnimation("MM_MENU_1_CLOSE.bmp", "MM_MENU_1_CLOSE", 0, 3, 0.1f, false);
	Menu1_Renerer->ChangeAnimation("MM_MENU_1_IDLE");

	Menu1->SetMyRenderer(Menu1_Renerer);

	//화살표
	{
		GameEngineActor* RightArrow = CreateActor<MainMenuActor>(4);
		RightArrow->SetPosition({ Menu1->GetPosition().x + 180.f, GameEngineWindow::GetScale().Half().y + 80.f });
		GameEngineRenderer* RightRenderer = RightArrow->CreateRenderer();
		RightRenderer->CreateAnimation("MM_ARROW_RIGHT.bmp", "MM_ARROW_RIGHT", 0, 1, 0.1f, true);
		RightRenderer->CreateAnimation("MM_ARROW_RIGHT_DARK.bmp", "MM_ARROW_RIGHT_DARK", 0, 0, 0.f, false);
		RightRenderer->ChangeAnimation("MM_ARROW_RIGHT");

		GameEngineActor* LeftArrow = CreateActor<MainMenuActor>(4);
		LeftArrow->SetPosition({ Menu1->GetPosition().x + 140.f, GameEngineWindow::GetScale().Half().y + 80.f });
		GameEngineRenderer* LeftRenderer = LeftArrow->CreateRenderer();
		LeftRenderer->CreateAnimation("MM_ARROW_LEFT.bmp", "MM_ARROW_LEFT", 0, 1, 0.1f, true);
		LeftRenderer->CreateAnimation("MM_ARROW_LEFT_DARK.bmp", "MM_ARROW_LEFT_DARK", 0, 0, 0.f, false);
		LeftRenderer->ChangeAnimation("MM_ARROW_LEFT");
		LeftRenderer->PauseOn();

		Arrows_.push_back(RightArrow);
		RightRenderers_.push_back(RightRenderer);
		Arrows_.push_back(LeftArrow);
		LeftRenderers_.push_back(LeftRenderer);
	}

	//뿌요
	{
		MainMenuActor* Puyo = CreateActor<MainMenuActor>(5);
		Puyo->SetPosition({ Menu1->GetPosition().x - 80.f, GameEngineWindow::GetScale().Half().y + 280.f });
		GameEngineRenderer* Puyoenderer = Puyo->GameEngineActor::CreateRenderer();
		Puyoenderer->CreateAnimation("MM_PUYO.bmp", "MM_PUYO", 0, 0, 0.0f, false);
		Puyoenderer->CreateAnimation("MM_PUYO_MOVE.bmp", "MM_PUYO_MOVE", 0, 1, 0.02f, false);
		Puyoenderer->CreateAnimation("MM_PUYO_DARK.bmp", "MM_PUYO_DARK", 0, 0, 0.0f, false);
		Puyoenderer->CreateAnimation("MM_PUYO_DESTROY.bmp", "MM_PUYO_DESTROY", 0, 2, 0.1f, false);
		Puyoenderer->ChangeAnimation("MM_PUYO");
		Puyoenderer->PauseOn();

		Puyos_.push_back(Puyo);
		Puyo->SetMyRenderer(Puyoenderer);
	}


	MainMenuActor* Menu2 = CreateActor<MainMenuActor>(3);
	Menu2->SetPosition({ Menu1->GetPosition().x + 320.f, GameEngineWindow::GetScale().Half().y + 100.f });
	GameEngineRenderer* Menu2_Renerer = Menu2->GameEngineActor::CreateRenderer();
	Menu2_Renerer->CreateAnimation("MM_MENU_2_IDLE.bmp", "MM_MENU_2_IDLE", 0, 2, 0.15f, false);
	Menu2_Renerer->CreateAnimation("MM_MENU_2_IDLE_DARK.bmp", "MM_MENU_2_IDLE_DARK", 0, 2, 0.15f, false);
	Menu2_Renerer->CreateAnimation("MM_MENU_2_CLOSE.bmp", "MM_MENU_2_CLOSE", 0, 3, 0.1f, false);
	Menu2_Renerer->ChangeAnimation("MM_MENU_2_IDLE_DARK");
	Menu2_Renerer->PauseOn();

	Menu2->SetMyRenderer(Menu2_Renerer);

	{
		GameEngineActor* RightArrow = CreateActor<MainMenuActor>(4);
		RightArrow->SetPosition({ Menu2->GetPosition().x + 180.f, GameEngineWindow::GetScale().Half().y + 80.f });
		GameEngineRenderer* RightRenderer = RightArrow->CreateRenderer();
		RightRenderer->CreateAnimation("MM_ARROW_RIGHT.bmp", "MM_ARROW_RIGHT", 0, 1, 0.1f, true);
		RightRenderer->CreateAnimation("MM_ARROW_RIGHT_DARK.bmp", "MM_ARROW_RIGHT_DARK", 0, 0, 0.f, false);
		RightRenderer->ChangeAnimation("MM_ARROW_RIGHT");
		RightRenderer->PauseOn();

		GameEngineActor* LeftArrow = CreateActor<MainMenuActor>(4);
		LeftArrow->SetPosition({ Menu2->GetPosition().x + 140.f, GameEngineWindow::GetScale().Half().y + 80.f });
		GameEngineRenderer* LeftRenderer = LeftArrow->CreateRenderer();
		LeftRenderer->CreateAnimation("MM_ARROW_LEFT.bmp", "MM_ARROW_LEFT", 0, 1, 0.1f, true);
		LeftRenderer->CreateAnimation("MM_ARROW_LEFT_DARK.bmp", "MM_ARROW_LEFT_DARK", 0, 0, 0.f, false);
		LeftRenderer->ChangeAnimation("MM_ARROW_LEFT");
		LeftRenderer->PauseOn();

		Arrows_.push_back(RightArrow);
		RightRenderers_.push_back(RightRenderer);
		Arrows_.push_back(LeftArrow);
		LeftRenderers_.push_back(LeftRenderer);
	}

	{
		MainMenuActor* Puyo = CreateActor<MainMenuActor>(5);
		Puyo->SetPosition({ Menu2->GetPosition().x - 80.f, GameEngineWindow::GetScale().Half().y + 280.f });
		GameEngineRenderer* Puyoenderer = Puyo->GameEngineActor::CreateRenderer();
		Puyoenderer->CreateAnimation("MM_PUYO.bmp", "MM_PUYO", 0, 0, 0.0f, false);
		Puyoenderer->CreateAnimation("MM_PUYO_MOVE.bmp", "MM_PUYO_MOVE", 0, 1, 0.02f, false);
		Puyoenderer->CreateAnimation("MM_PUYO_DARK.bmp", "MM_PUYO_DARK", 0, 0, 0.0f, false);
		Puyoenderer->CreateAnimation("MM_PUYO_DESTROY.bmp", "MM_PUYO_DESTROY", 0, 2, 0.1f, false);
		Puyoenderer->ChangeAnimation("MM_PUYO_DARK");
		Puyoenderer->PauseOn();

		MainMenuActor* Puyo1 = CreateActor<MainMenuActor>(5);
		Puyo1->SetPosition({ Menu2->GetPosition().x - 20.f, GameEngineWindow::GetScale().Half().y + 280.f });
		GameEngineRenderer* Puyoenderer1 = Puyo1->GameEngineActor::CreateRenderer();
		Puyoenderer1->CreateAnimation("MM_PUYO.bmp", "MM_PUYO", 0, 0, 0.0f, false);
		Puyoenderer1->CreateAnimation("MM_PUYO_MOVE.bmp", "MM_PUYO_MOVE", 0, 1, 0.02f, false);
		Puyoenderer1->CreateAnimation("MM_PUYO_DARK.bmp", "MM_PUYO_DARK", 0, 0, 0.0f, false);
		Puyoenderer1->CreateAnimation("MM_PUYO_DESTROY.bmp", "MM_PUYO_DESTROY", 0, 2, 0.1f, false);
		Puyoenderer1->ChangeAnimation("MM_PUYO_DARK");
		Puyoenderer1->PauseOn();

		Puyos_.push_back(Puyo);
		Puyo->SetMyRenderer(Puyoenderer);

		Puyos_.push_back(Puyo1);
		Puyo1->SetMyRenderer(Puyoenderer1);
	}


	MainMenuActor* Menu3 = CreateActor<MainMenuActor>(3);
	Menu3->SetPosition({ Menu2->GetPosition().x + 320.f, GameEngineWindow::GetScale().Half().y + 100.f });
	GameEngineRenderer* Menu3_Renerer = Menu3->CreateRenderer();
	Menu3_Renerer->CreateAnimation("MM_MENU_3_IDLE.bmp", "MM_MENU_3_IDLE", 0, 2, 0.15f, false);
	Menu3_Renerer->CreateAnimation("MM_MENU_3_IDLE_DARK.bmp", "MM_MENU_3_IDLE_DARK", 0, 2, 0.15f, false);
	Menu3_Renerer->CreateAnimation("MM_MENU_3_CLOSE.bmp", "MM_MENU_3_CLOSE", 0, 3, 0.1f, false);
	Menu3_Renerer->ChangeAnimation("MM_MENU_3_IDLE_DARK");
	Menu3_Renerer->PauseOn();

	Menu3->SetMyRenderer(Menu3_Renerer);

	{
		GameEngineActor* RightArrow = CreateActor<MainMenuActor>(4);
		RightArrow->SetPosition({ Menu3->GetPosition().x + 180.f, GameEngineWindow::GetScale().Half().y + 80.f });
		GameEngineRenderer* RightRenderer = RightArrow->CreateRenderer();
		RightRenderer->CreateAnimation("MM_ARROW_RIGHT.bmp", "MM_ARROW_RIGHT", 0, 1, 0.1f, true);
		RightRenderer->CreateAnimation("MM_ARROW_RIGHT_DARK.bmp", "MM_ARROW_RIGHT_DARK", 0, 0, 0.f, false);
		RightRenderer->ChangeAnimation("MM_ARROW_RIGHT");
		RightRenderer->PauseOn();

		GameEngineActor* LeftArrow = CreateActor<MainMenuActor>(4);
		LeftArrow->SetPosition({ Menu3->GetPosition().x + 140.f, GameEngineWindow::GetScale().Half().y + 80.f });
		GameEngineRenderer* LeftRenderer = LeftArrow->CreateRenderer();
		LeftRenderer->CreateAnimation("MM_ARROW_LEFT.bmp", "MM_ARROW_LEFT", 0, 1, 0.1f, true);
		LeftRenderer->CreateAnimation("MM_ARROW_LEFT_DARK.bmp", "MM_ARROW_LEFT_DARK", 0, 0, 0.f, false);
		LeftRenderer->ChangeAnimation("MM_ARROW_LEFT");
		LeftRenderer->PauseOn();

		Arrows_.push_back(RightArrow);
		RightRenderers_.push_back(RightRenderer);
		Arrows_.push_back(LeftArrow);
		LeftRenderers_.push_back(LeftRenderer);
	}

	{
		MainMenuActor* Puyo = CreateActor<MainMenuActor>(5);
		Puyo->SetPosition({ Menu3->GetPosition().x - 85.f, GameEngineWindow::GetScale().Half().y + 280.f });
		GameEngineRenderer* Puyoenderer = Puyo->GameEngineActor::CreateRenderer();
		Puyoenderer->CreateAnimation("MM_PUYO.bmp", "MM_PUYO", 0, 0, 0.0f, false);
		Puyoenderer->CreateAnimation("MM_PUYO_MOVE.bmp", "MM_PUYO_MOVE", 0, 1, 0.02f, false);
		Puyoenderer->CreateAnimation("MM_PUYO_DARK.bmp", "MM_PUYO_DARK", 0, 0, 0.0f, false);
		Puyoenderer->CreateAnimation("MM_PUYO_DESTROY.bmp", "MM_PUYO_DESTROY", 0, 2, 0.1f, false);
		Puyoenderer->ChangeAnimation("MM_PUYO_DARK");
		Puyoenderer->PauseOn();

		MainMenuActor* Puyo1 = CreateActor<MainMenuActor>(5);
		Puyo1->SetPosition({ Menu3->GetPosition().x + 85.f, GameEngineWindow::GetScale().Half().y + 280.f });
		GameEngineRenderer* Puyoenderer1 = Puyo1->GameEngineActor::CreateRenderer();
		Puyoenderer1->CreateAnimation("MM_PUYO.bmp", "MM_PUYO", 0, 0, 0.0f, false);
		Puyoenderer1->CreateAnimation("MM_PUYO_MOVE.bmp", "MM_PUYO_MOVE", 0, 1, 0.02f, false);
		Puyoenderer1->CreateAnimation("MM_PUYO_DARK.bmp", "MM_PUYO_DARK", 0, 0, 0.0f, false);
		Puyoenderer1->CreateAnimation("MM_PUYO_DESTROY.bmp", "MM_PUYO_DESTROY", 0, 2, 0.1f, false);
		Puyoenderer1->ChangeAnimation("MM_PUYO_DARK");
		Puyoenderer1->PauseOn();

		Puyos_.push_back(Puyo);
		Puyo->SetMyRenderer(Puyoenderer);

		Puyos_.push_back(Puyo1);
		Puyo1->SetMyRenderer(Puyoenderer1);
	}



	MainMenuActor* Menu4 = CreateActor<MainMenuActor>(3);
	Menu4->SetPosition({ Menu3->GetPosition().x + 320.f, GameEngineWindow::GetScale().Half().y + 100.f });
	GameEngineRenderer* Menu4_Renerer = Menu4->CreateRenderer();
	Menu4_Renerer->CreateAnimation("MM_MENU_4_IDLE.bmp", "MM_MENU_4_IDLE", 0, 2, 0.15f, false);
	Menu4_Renerer->CreateAnimation("MM_MENU_4_IDLE_DARK.bmp", "MM_MENU_4_IDLE_DARK", 0, 2, 0.15f, false);
	Menu4_Renerer->CreateAnimation("MM_MENU_4_CLOSE.bmp", "MM_MENU_4_CLOSE", 0, 3, 0.1f, false);
	Menu4_Renerer->ChangeAnimation("MM_MENU_4_IDLE_DARK");
	Menu4_Renerer->PauseOn();

	Menu4->SetMyRenderer(Menu4_Renerer);


	{
		GameEngineActor* RightArrow = CreateActor<MainMenuActor>(4);
		RightArrow->SetPosition({ Menu4->GetPosition().x + 180.f, GameEngineWindow::GetScale().Half().y + 80.f });
		GameEngineRenderer* RightRenderer = RightArrow->CreateRenderer();
		RightRenderer->CreateAnimation("MM_ARROW_RIGHT.bmp", "MM_ARROW_RIGHT", 0, 1, 0.1f, true);
		RightRenderer->CreateAnimation("MM_ARROW_RIGHT_DARK.bmp", "MM_ARROW_RIGHT_DARK", 0, 0, 0.f, false);
		RightRenderer->ChangeAnimation("MM_ARROW_RIGHT");
		RightRenderer->PauseOn();

		GameEngineActor* LeftArrow = CreateActor<MainMenuActor>(4);
		LeftArrow->SetPosition({ Menu4->GetPosition().x + 140.f, GameEngineWindow::GetScale().Half().y + 80.f });
		GameEngineRenderer* LeftRenderer = LeftArrow->CreateRenderer();
		LeftRenderer->CreateAnimation("MM_ARROW_LEFT.bmp", "MM_ARROW_LEFT", 0, 1, 0.1f, true);
		LeftRenderer->CreateAnimation("MM_ARROW_LEFT_DARK.bmp", "MM_ARROW_LEFT_DARK", 0, 0, 0.f, false);
		LeftRenderer->ChangeAnimation("MM_ARROW_LEFT");
		LeftRenderer->PauseOn();

		Arrows_.push_back(RightArrow);
		RightRenderers_.push_back(RightRenderer);
		Arrows_.push_back(LeftArrow);
		LeftRenderers_.push_back(LeftRenderer);
	} 

	{
		MainMenuActor* Puyo = CreateActor<MainMenuActor>(5);
		Puyo->SetPosition({ Menu4->GetPosition().x - 85.f, GameEngineWindow::GetScale().Half().y + 280.f });
		GameEngineRenderer* Puyoenderer = Puyo->GameEngineActor::CreateRenderer();
		Puyoenderer->CreateAnimation("MM_PUYO.bmp", "MM_PUYO", 0, 0, 0.0f, false);
		Puyoenderer->CreateAnimation("MM_PUYO_MOVE.bmp", "MM_PUYO_MOVE", 0, 1, 0.02f, false);
		Puyoenderer->CreateAnimation("MM_PUYO_DARK.bmp", "MM_PUYO_DARK", 0, 0, 0.0f, false);
		Puyoenderer->CreateAnimation("MM_PUYO_DESTROY.bmp", "MM_PUYO_DESTROY", 0, 2, 0.1f, false);
		Puyoenderer->ChangeAnimation("MM_PUYO_DARK");
		Puyoenderer->PauseOn();

		MainMenuActor* Puyo1 = CreateActor<MainMenuActor>(6);
		Puyo1->SetPosition({ Menu4->GetPosition().x - 45.f, GameEngineWindow::GetScale().Half().y + 290.f });
		GameEngineRenderer* Puyoenderer1 = Puyo1->GameEngineActor::CreateRenderer();
		Puyoenderer1->CreateAnimation("MM_PUYO.bmp", "MM_PUYO", 0, 0, 0.0f, false);
		Puyoenderer1->CreateAnimation("MM_PUYO_MOVE.bmp", "MM_PUYO_MOVE", 0, 1, 0.02f, false);
		Puyoenderer1->CreateAnimation("MM_PUYO_DARK.bmp", "MM_PUYO_DARK", 0, 0, 0.0f, false);
		Puyoenderer1->CreateAnimation("MM_PUYO_DESTROY.bmp", "MM_PUYO_DESTROY", 0, 2, 0.1f, false);
		Puyoenderer1->ChangeAnimation("MM_PUYO_DARK");
		Puyoenderer1->PauseOn();

		MainMenuActor* Puyo2 = CreateActor<MainMenuActor>(5);
		Puyo2->SetPosition({ Menu4->GetPosition().x - 15.f, GameEngineWindow::GetScale().Half().y + 280.f });
		GameEngineRenderer* Puyoenderer2 = Puyo2->GameEngineActor::CreateRenderer();
		Puyoenderer2->CreateAnimation("MM_PUYO.bmp", "MM_PUYO", 0, 0, 0.0f, false);
		Puyoenderer2->CreateAnimation("MM_PUYO_MOVE.bmp", "MM_PUYO_MOVE", 0, 1, 0.02f, false);
		Puyoenderer2->CreateAnimation("MM_PUYO_DARK.bmp", "MM_PUYO_DARK", 0, 0, 0.0f, false);
		Puyoenderer2->CreateAnimation("MM_PUYO_DESTROY.bmp", "MM_PUYO_DESTROY", 0, 2, 0.1f, false);
		Puyoenderer2->ChangeAnimation("MM_PUYO_DARK");
		Puyoenderer2->PauseOn();


		Puyos_.push_back(Puyo);
		Puyo->SetMyRenderer(Puyoenderer);

		Puyos_.push_back(Puyo1);
		Puyo1->SetMyRenderer(Puyoenderer1);

		Puyos_.push_back(Puyo2);
		Puyo2->SetMyRenderer(Puyoenderer2);
	}


	MainMenuActor* Menu5 = CreateActor<MainMenuActor>(3);
	Menu5->SetPosition({ Menu4->GetPosition().x + 320.f, GameEngineWindow::GetScale().Half().y + 100.f });
	GameEngineRenderer* Menu5_Renerer = Menu5->CreateRenderer();
	Menu5_Renerer->CreateAnimation("MM_MENU_5_IDLE.bmp", "MM_MENU_5_IDLE", 0, 2, 0.15f, false);
	Menu5_Renerer->CreateAnimation("MM_MENU_5_IDLE_DARK.bmp", "MM_MENU_5_IDLE_DARK", 0, 2, 0.15f, false);
	Menu5_Renerer->CreateAnimation("MM_MENU_5_CLOSE.bmp", "MM_MENU_5_CLOSE", 0, 3, 0.1f, false);
	Menu5_Renerer->ChangeAnimation("MM_MENU_5_IDLE_DARK");
	Menu5_Renerer->PauseOn();

	Menu5->SetMyRenderer(Menu5_Renerer);

	{
		MainMenuActor* Puyo = CreateActor<MainMenuActor>(5);
		Puyo->SetPosition({ Menu5->GetPosition().x - 100.f, GameEngineWindow::GetScale().Half().y + 280.f });
		GameEngineRenderer* Puyoenderer = Puyo->GameEngineActor::CreateRenderer();
		Puyoenderer->CreateAnimation("MM_PUYO.bmp", "MM_PUYO", 0, 0, 0.0f, false);
		Puyoenderer->CreateAnimation("MM_PUYO_MOVE.bmp", "MM_PUYO_MOVE", 0, 1, 0.02f, false);
		Puyoenderer->CreateAnimation("MM_PUYO_DARK.bmp", "MM_PUYO_DARK", 0, 0, 0.0f, false);
		Puyoenderer->CreateAnimation("MM_PUYO_DESTROY.bmp", "MM_PUYO_DESTROY", 0, 2, 0.1f, false);
		Puyoenderer->ChangeAnimation("MM_PUYO_DARK");
		Puyoenderer->PauseOn();

		MainMenuActor* Puyo1 = CreateActor<MainMenuActor>(5);
		Puyo1->SetPosition({ Menu5->GetPosition().x - 40.f, GameEngineWindow::GetScale().Half().y + 280.f });
		GameEngineRenderer* Puyoenderer1 = Puyo1->GameEngineActor::CreateRenderer();
		Puyoenderer1->CreateAnimation("MM_PUYO.bmp", "MM_PUYO", 0, 0, 0.0f, false);
		Puyoenderer1->CreateAnimation("MM_PUYO_MOVE.bmp", "MM_PUYO_MOVE", 0, 1, 0.02f, false);
		Puyoenderer1->CreateAnimation("MM_PUYO_DARK.bmp", "MM_PUYO_DARK", 0, 0, 0.0f, false);
		Puyoenderer1->CreateAnimation("MM_PUYO_DESTROY.bmp", "MM_PUYO_DESTROY", 0, 2, 0.1f, false);
		Puyoenderer1->ChangeAnimation("MM_PUYO_DARK");
		Puyoenderer1->PauseOn();

		MainMenuActor* Puyo2 = CreateActor<MainMenuActor>(5);
		Puyo2->SetPosition({ Menu5->GetPosition().x + 17.f, GameEngineWindow::GetScale().Half().y + 280.f });
		GameEngineRenderer* Puyoenderer2 = Puyo2->GameEngineActor::CreateRenderer();
		Puyoenderer2->CreateAnimation("MM_PUYO.bmp", "MM_PUYO", 0, 0, 0.0f, false);
		Puyoenderer2->CreateAnimation("MM_PUYO_MOVE.bmp", "MM_PUYO_MOVE", 0, 1, 0.02f, false);
		Puyoenderer2->CreateAnimation("MM_PUYO_DARK.bmp", "MM_PUYO_DARK", 0, 0, 0.0f, false);
		Puyoenderer2->CreateAnimation("MM_PUYO_DESTROY.bmp", "MM_PUYO_DESTROY", 0, 2, 0.1f, false);
		Puyoenderer2->ChangeAnimation("MM_PUYO_DARK");
		Puyoenderer2->PauseOn();

		MainMenuActor* Puyo3 = CreateActor<MainMenuActor>(5);
		Puyo3->SetPosition({ Menu5->GetPosition().x + 100.f, GameEngineWindow::GetScale().Half().y + 280.f });
		GameEngineRenderer* Puyoenderer3 = Puyo3->GameEngineActor::CreateRenderer();
		Puyoenderer3->CreateAnimation("MM_PUYO.bmp", "MM_PUYO", 0, 0, 0.0f, false);
		Puyoenderer3->CreateAnimation("MM_PUYO_MOVE.bmp", "MM_PUYO_MOVE", 0, 1, 0.02f, false);
		Puyoenderer3->CreateAnimation("MM_PUYO_DARK.bmp", "MM_PUYO_DARK", 0, 0, 0.0f, false);
		Puyoenderer3->CreateAnimation("MM_PUYO_DESTROY.bmp", "MM_PUYO_DESTROY", 0, 2, 0.1f, false);
		Puyoenderer3->ChangeAnimation("MM_PUYO_DARK");
		Puyoenderer3->PauseOn();

		Puyos_.push_back(Puyo);
		Puyo->SetMyRenderer(Puyoenderer);

		Puyos_.push_back(Puyo1);
		Puyo1->SetMyRenderer(Puyoenderer1);

		Puyos_.push_back(Puyo2);
		Puyo2->SetMyRenderer(Puyoenderer2);

		Puyos_.push_back(Puyo3);
		Puyo3->SetMyRenderer(Puyoenderer3);
	}

	Menus_.push_back(Menu1);
	Menus_.push_back(Menu2);
	Menus_.push_back(Menu3);
	Menus_.push_back(Menu4);
	Menus_.push_back(Menu5);

	MenuRenderers_.push_back(Menu1_Renerer);
	MenuRenderers_.push_back(Menu2_Renerer);
	MenuRenderers_.push_back(Menu3_Renerer);
	MenuRenderers_.push_back(Menu4_Renerer);
	MenuRenderers_.push_back(Menu5_Renerer);
}

void MainMenu::BackgourndInit()
{
	GameEngineImage* Image = GameEngineImageManager::GetInst()->Find("MM_SD0R.bmp");
	Image->CutCount(4, 1);

	GameEngineImage* Image1 = GameEngineImageManager::GetInst()->Find("MM_SD7L.bmp");
	Image1->CutCount(4, 1);

	GameEngineImage* Image2 = GameEngineImageManager::GetInst()->Find("MM_SD3R.bmp");
	Image2->CutCount(4, 1);

	GameEngineImage* Image3 = GameEngineImageManager::GetInst()->Find("MM_SD5L.bmp");
	Image3->CutCount(4, 1);

	std::vector<MainMenuActor*> FirstLine;
	std::vector<MainMenuActor*> SecondLine;
	std::vector<MainMenuActor*> ThirdLine;
	std::vector<MainMenuActor*> LastLine;

	float Offset;
	Offset = 220.f;

	for (int i = 0; i < 10; i++)
	{
		MainMenuActor* Actor = CreateActor<MainMenuActor>(0);
		float4 Pos(GameEngineWindow::GetScale().x - (i * Offset), (GameEngineWindow::GetScale().Half().y / 4.f));
		Actor->SetPosition(Pos);

		GameEngineRenderer* Renderer = Actor->GameEngineActor::CreateRenderer();
		Renderer->CreateAnimation("MM_SD0R.bmp", "MM_SD0R", 0, 3, 0.1f, true);
		Renderer->ChangeAnimation("MM_SD0R");

		Actor->SetMyRenderer(Renderer);
		FirstLine.push_back(Actor);
	}

	for (int i = 0; i < 10; i++)
	{
		MainMenuActor* Actor = CreateActor<MainMenuActor>(1);
		float4 Pos(GameEngineWindow::GetScale().x - (i * Offset), (GameEngineWindow::GetScale().Half().y / 4.f) + 224);
		Actor->SetPosition(Pos);

		GameEngineRenderer* Renderer = Actor->GameEngineActor::CreateRenderer();
		Renderer->CreateAnimation("MM_SD7L.bmp", "MM_SD7L", 0, 3, 0.1f, true);
		Renderer->ChangeAnimation("MM_SD7L");

		Actor->SetMyRenderer(Renderer);
		SecondLine.push_back(Actor);
	}

	for (int i = 0; i < 10; i++)
	{
		MainMenuActor* Actor = CreateActor<MainMenuActor>(1);
		float4 Pos(GameEngineWindow::GetScale().x - (i * Offset), (GameEngineWindow::GetScale().Half().y / 4.f) + 224 * 2);
		Actor->SetPosition(Pos);

		GameEngineRenderer* Renderer = Actor->GameEngineActor::CreateRenderer();
		Renderer->CreateAnimation("MM_SD3R.bmp", "MM_SD3R", 0, 3, 0.1f, true);
		Renderer->ChangeAnimation("MM_SD3R");

		Actor->SetMyRenderer(Renderer);
		ThirdLine.push_back(Actor);
	}

	for (int i = 0; i < 10; i++)
	{
		MainMenuActor* Actor = CreateActor<MainMenuActor>(1);
		float4 Pos(GameEngineWindow::GetScale().x - (i * Offset), (GameEngineWindow::GetScale().Half().y / 4.f) + 224 * 3);
		Actor->SetPosition(Pos);

		GameEngineRenderer* Renderer = Actor->GameEngineActor::CreateRenderer();
		Renderer->CreateAnimation("MM_SD5L.bmp", "MM_SD5L", 0, 3, 0.1f, true);
		Renderer->ChangeAnimation("MM_SD5L");

		Actor->SetMyRenderer(Renderer);
		LastLine.push_back(Actor);
	}

	BackGrounds_.push_back(FirstLine);
	BackGrounds_.push_back(SecondLine);
	BackGrounds_.push_back(ThirdLine);
	BackGrounds_.push_back(LastLine);
}


void MainMenu::Update()
{
	MenuUpdate();

	if (false == FadeBackground_->GetIsIn())
	{
		RandomAnimation();
		ResetMenuAnimation();

		for (int i = 0; i < Puyos_.size(); i++)
		{
			ResetPuyoAnimation(i);
		}
	}

	BackgroundUpdate();
	SelectMenu();
}


void MainMenu::MenuUpdate()
{
	if (GameEngineInput::GetInst()->IsDown("ManiMenu_Right"))
	{
		if (MenuCount_ < static_cast<int>(MenuType::OPTION))
		{
			//카방클 좌로 이동
			for (int i = 0; i < Menus_.size(); ++i)
			{
				Menus_[i]->SetPosition(Menus_[i]->GetPosition() + (float4::LEFT * 200.f));				
			}

			for (int i = 0; i < Puyos_.size(); i++)
			{
				Puyos_[i]->SetPosition(Puyos_[i]->GetPosition() + (float4::LEFT * 200.f));
				Puyos_[i]->GetMyRenderer()->ChangeAnimation("MM_PUYO_DARK");
			}

			for (int i = 0; i < Arrows_.size(); ++i)
			{
				Arrows_[i]->SetPosition(Arrows_[i]->GetPosition() + (float4::LEFT * 200.f));
			}

			for (int i = 0; i < RightRenderers_.size(); i++)
			{
				RightRenderers_[i]->ChangeAnimation("MM_ARROW_RIGHT_DARK");
				LeftRenderers_[i]->ChangeAnimation("MM_ARROW_LEFT_DARK");
			}

			++MenuCount_;
			FocasMenu();
		}

		ChangeArrowAnimation();
	}

	if (GameEngineInput::GetInst()->IsDown("ManiMenu_Left"))
	{
		if (MenuCount_ > static_cast<int>(MenuType::ALONE))
		{
			//카방클 우로 이동 
			for (int i = 0; i < Menus_.size(); ++i)
			{
				Menus_[i]->SetPosition(Menus_[i]->GetPosition() + (float4::RIGHT * 200.f));
			}

			for (int i = 0; i < Puyos_.size(); i++)
			{
				Puyos_[i]->SetPosition(Puyos_[i]->GetPosition() + (float4::RIGHT * 200.f));
				Puyos_[i]->GetMyRenderer()->ChangeAnimation("MM_PUYO_DARK");
			}

			for (int i = 0; i < Arrows_.size(); ++i)
			{
				Arrows_[i]->SetPosition(Arrows_[i]->GetPosition() + (float4::RIGHT * 200.f));
			}

			for (int i = 0; i < RightRenderers_.size(); i++)
			{
				RightRenderers_[i]->ChangeAnimation("MM_ARROW_RIGHT_DARK");
				LeftRenderers_[i]->ChangeAnimation("MM_ARROW_LEFT_DARK");
			}

			--MenuCount_;
			FocasMenu();
		}

		ChangeArrowAnimation();
	}


}

void MainMenu::RandomAnimation()
{
	RandomTime_ -= GameEngineTime::GetDeltaTime();

	if (RandomTime_ < 0.0f)
	{
		int Random = Random_.RandomInt(0, 1);

		if (Random == 0)
		{
			int MenuRan = Random_.RandomInt(0, 4);
			Menus_[MenuRan]->GetMyRenderer()->PauseOff();
		}

		int PuyoRan = Random_.RandomInt(0, static_cast<int>(Puyos_.size() - 1));

		if (false == Puyos_[PuyoRan]->GetMyRenderer()->IsAnimationName("MM_PUYO_DARK"))
		{
			Puyos_[PuyoRan]->GetMyRenderer()->ChangeAnimation("MM_PUYO_MOVE");
			Puyos_[PuyoRan]->GetMyRenderer()->PauseOff();
		}

		RandomTime_ = 0.3f;
	}
}

void MainMenu::ResetMenuAnimation()
{
	if (true == Menus_[0]->GetMyRenderer()->IsEndAnimation())
	{
		Menus_[0]->GetMyRenderer()->PauseOn();

		Menus_[0]->GetMyRenderer()->ChangeAnimation("MM_MENU_1_IDLE");
		Menus_[0]->GetMyRenderer()->ChangeAnimation("MM_MENU_1_IDLE_DARK");

		if (0 == MenuCount_)
		{
			Puyos_[0]->GetMyRenderer()->ChangeAnimation("MM_PUYO");
			Menus_[0]->GetMyRenderer()->ChangeAnimation("MM_MENU_1_IDLE");
		}
	}

	if (true == Menus_[1]->GetMyRenderer()->IsEndAnimation())
	{
		Menus_[1]->GetMyRenderer()->PauseOn();

		Menus_[1]->GetMyRenderer()->ChangeAnimation("MM_MENU_2_IDLE");
		Menus_[1]->GetMyRenderer()->ChangeAnimation("MM_MENU_2_IDLE_DARK");

		if (1 == MenuCount_)
		{
			Menus_[1]->GetMyRenderer()->ChangeAnimation("MM_MENU_2_IDLE");
		}
	}

	if (true == Menus_[2]->GetMyRenderer()->IsEndAnimation())
	{
		Menus_[2]->GetMyRenderer()->PauseOn();

		Puyos_[3]->GetMyRenderer()->PauseOn();
		Puyos_[4]->GetMyRenderer()->PauseOn();

		Puyos_[3]->GetMyRenderer()->ChangeAnimation("MM_PUYO");
		Puyos_[4]->GetMyRenderer()->ChangeAnimation("MM_PUYO");

		Puyos_[3]->GetMyRenderer()->ChangeAnimation("MM_PUYO_DARK");
		Puyos_[4]->GetMyRenderer()->ChangeAnimation("MM_PUYO_DARK");

		Menus_[2]->GetMyRenderer()->ChangeAnimation("MM_MENU_3_IDLE");
		Menus_[2]->GetMyRenderer()->ChangeAnimation("MM_MENU_3_IDLE_DARK");
		if (2 == MenuCount_)
		{
			Puyos_[3]->GetMyRenderer()->ChangeAnimation("MM_PUYO");
			Puyos_[4]->GetMyRenderer()->ChangeAnimation("MM_PUYO");

			Menus_[2]->GetMyRenderer()->ChangeAnimation("MM_MENU_3_IDLE");
		}
	}
	if (true == Menus_[3]->GetMyRenderer()->IsEndAnimation())
	{
		Menus_[3]->GetMyRenderer()->PauseOn();

		Puyos_[5]->GetMyRenderer()->PauseOn();
		Puyos_[6]->GetMyRenderer()->PauseOn();
		Puyos_[7]->GetMyRenderer()->PauseOn();

		Puyos_[5]->GetMyRenderer()->ChangeAnimation("MM_PUYO");
		Puyos_[6]->GetMyRenderer()->ChangeAnimation("MM_PUYO");
		Puyos_[7]->GetMyRenderer()->ChangeAnimation("MM_PUYO");

		Puyos_[5]->GetMyRenderer()->ChangeAnimation("MM_PUYO_DARK");
		Puyos_[6]->GetMyRenderer()->ChangeAnimation("MM_PUYO_DARK");
		Puyos_[7]->GetMyRenderer()->ChangeAnimation("MM_PUYO_DARK");

		Menus_[3]->GetMyRenderer()->ChangeAnimation("MM_MENU_4_IDLE");
		Menus_[3]->GetMyRenderer()->ChangeAnimation("MM_MENU_4_IDLE_DARK");
		if (3 == MenuCount_)
		{
			Puyos_[5]->GetMyRenderer()->ChangeAnimation("MM_PUYO");
			Puyos_[6]->GetMyRenderer()->ChangeAnimation("MM_PUYO");
			Puyos_[7]->GetMyRenderer()->ChangeAnimation("MM_PUYO");

			Menus_[3]->GetMyRenderer()->ChangeAnimation("MM_MENU_4_IDLE");
		}

	}
	if (true == Menus_[4]->GetMyRenderer()->IsEndAnimation())
	{
		Menus_[4]->GetMyRenderer()->PauseOn();

		Puyos_[8]->GetMyRenderer()->PauseOn();
		Puyos_[9]->GetMyRenderer()->PauseOn();
		Puyos_[10]->GetMyRenderer()->PauseOn();
		Puyos_[11]->GetMyRenderer()->PauseOn();

		Puyos_[8]->GetMyRenderer()->ChangeAnimation("MM_PUYO");
		Puyos_[9]->GetMyRenderer()->ChangeAnimation("MM_PUYO");
		Puyos_[10]->GetMyRenderer()->ChangeAnimation("MM_PUYO");
		Puyos_[11]->GetMyRenderer()->ChangeAnimation("MM_PUYO");

		Puyos_[8]->GetMyRenderer()->ChangeAnimation("MM_PUYO_DARK");
		Puyos_[9]->GetMyRenderer()->ChangeAnimation("MM_PUYO_DARK");
		Puyos_[10]->GetMyRenderer()->ChangeAnimation("MM_PUYO_DARK");
		Puyos_[11]->GetMyRenderer()->ChangeAnimation("MM_PUYO_DARK");


		Menus_[4]->GetMyRenderer()->ChangeAnimation("MM_MENU_5_IDLE");
		Menus_[4]->GetMyRenderer()->ChangeAnimation("MM_MENU_5_IDLE_DARK");

		if (4 == MenuCount_)
		{
			Puyos_[8]->GetMyRenderer()->ChangeAnimation("MM_PUYO");
			Puyos_[9]->GetMyRenderer()->ChangeAnimation("MM_PUYO");
			Puyos_[10]->GetMyRenderer()->ChangeAnimation("MM_PUYO");
			Puyos_[11]->GetMyRenderer()->ChangeAnimation("MM_PUYO");

			Menus_[4]->GetMyRenderer()->ChangeAnimation("MM_MENU_5_IDLE");
		}
	}
}

void MainMenu::ResetPuyoAnimation(int _Index)
{
	if (true == Puyos_[_Index]->GetMyRenderer()->IsEndAnimation())
	{
		Puyos_[_Index]->GetMyRenderer()->PauseOn();
		Puyos_[_Index]->GetMyRenderer()->ChangeAnimation("MM_PUYO");

		if (_Index == MenuCount_)
		{
			Puyos_[_Index]->GetMyRenderer()->ChangeAnimation("MM_PUYO");
		}
	}
}


void MainMenu::ChangeArrowAnimation()
{
	switch (MenuCount_)
	{
	case 0:
		RightRenderers_[0]->ChangeAnimation("MM_ARROW_RIGHT");
		RightRenderers_[0]->PauseOff();

		//뿌요
		Puyos_[0]->GetMyRenderer()->ChangeAnimation("MM_PUYO");
		break;

	case 1:
		RightRenderers_[1]->ChangeAnimation("MM_ARROW_RIGHT");
		RightRenderers_[1]->PauseOff();

		LeftRenderers_[0]->ChangeAnimation("MM_ARROW_LEFT");
		LeftRenderers_[0]->PauseOff();

		Puyos_[1]->GetMyRenderer()->ChangeAnimation("MM_PUYO");
		Puyos_[2]->GetMyRenderer()->ChangeAnimation("MM_PUYO");
		break;

	case 2:
		RightRenderers_[2]->ChangeAnimation("MM_ARROW_RIGHT");
		RightRenderers_[2]->PauseOff();

		LeftRenderers_[1]->ChangeAnimation("MM_ARROW_LEFT");
		LeftRenderers_[1]->PauseOff();

		Puyos_[3]->GetMyRenderer()->ChangeAnimation("MM_PUYO");
		Puyos_[4]->GetMyRenderer()->ChangeAnimation("MM_PUYO");
		break;

	case 3:
		RightRenderers_[3]->ChangeAnimation("MM_ARROW_RIGHT");
		RightRenderers_[3]->PauseOff();

		LeftRenderers_[2]->ChangeAnimation("MM_ARROW_LEFT");
		LeftRenderers_[2]->PauseOff();

		Puyos_[5]->GetMyRenderer()->ChangeAnimation("MM_PUYO");
		Puyos_[6]->GetMyRenderer()->ChangeAnimation("MM_PUYO");
		Puyos_[7]->GetMyRenderer()->ChangeAnimation("MM_PUYO");
		break;

	case 4:
		LeftRenderers_[3]->ChangeAnimation("MM_ARROW_LEFT");
		LeftRenderers_[3]->PauseOff();

		Puyos_[8]->GetMyRenderer()->ChangeAnimation("MM_PUYO");
		Puyos_[9]->GetMyRenderer()->ChangeAnimation("MM_PUYO");
		Puyos_[10]->GetMyRenderer()->ChangeAnimation("MM_PUYO");
		Puyos_[11]->GetMyRenderer()->ChangeAnimation("MM_PUYO");
		break;
	}
}

void MainMenu::SelectMenu()
{
	if (GameEngineInput::GetInst()->IsDown("ManiMenu_Select"))
	{
		switch (MenuCount_)
		{
		case static_cast<int>(MenuType::ALONE): 

			MenuRendererPause();

			MenuRenderers_[1]->ChangeAnimation("MM_MENU_2_CLOSE");
			MenuRenderers_[2]->ChangeAnimation("MM_MENU_3_CLOSE");
			MenuRenderers_[3]->ChangeAnimation("MM_MENU_4_CLOSE");
			MenuRenderers_[4]->ChangeAnimation("MM_MENU_5_CLOSE");

			MenuSelect_[0] = true;
			break;

		case static_cast<int>(MenuType::TOGETHER): 

			MenuRendererPause();

			MenuRenderers_[0]->ChangeAnimation("MM_MENU_1_CLOSE");
			MenuRenderers_[2]->ChangeAnimation("MM_MENU_3_CLOSE");
			MenuRenderers_[3]->ChangeAnimation("MM_MENU_4_CLOSE");
			MenuRenderers_[4]->ChangeAnimation("MM_MENU_5_CLOSE");

			MenuSelect_[1] = true;
			break;

		case static_cast<int>(MenuType::TRAINING):

			MenuRendererPause();

			MenuRenderers_[0]->ChangeAnimation("MM_MENU_1_CLOSE");
			MenuRenderers_[1]->ChangeAnimation("MM_MENU_2_CLOSE");
			MenuRenderers_[3]->ChangeAnimation("MM_MENU_4_CLOSE");
			MenuRenderers_[4]->ChangeAnimation("MM_MENU_5_CLOSE");

			MenuSelect_[2] = true;
			break;

		case static_cast<int>(MenuType::PUZZLE):

			MenuRendererPause();

			MenuRenderers_[0]->ChangeAnimation("MM_MENU_1_CLOSE");
			MenuRenderers_[1]->ChangeAnimation("MM_MENU_2_CLOSE");
			MenuRenderers_[2]->ChangeAnimation("MM_MENU_3_CLOSE");
			MenuRenderers_[4]->ChangeAnimation("MM_MENU_5_CLOSE");

			MenuSelect_[3] = true;
			break;

		case static_cast<int>(MenuType::OPTION):

			MenuRendererPause();

			MenuRenderers_[0]->ChangeAnimation("MM_MENU_1_CLOSE");
			MenuRenderers_[1]->ChangeAnimation("MM_MENU_2_CLOSE");
			MenuRenderers_[2]->ChangeAnimation("MM_MENU_3_CLOSE");
			MenuRenderers_[3]->ChangeAnimation("MM_MENU_4_CLOSE");

			MenuSelect_[4] = true;
			break;

		default:
			MenuCount_ = 0;
			break;
		}

		MainMenuBgm_.Stop();
	}


	if (true == MenuSelect_[0])
	{
		Puyos_[0]->GetMyRenderer()->PauseOff();
		Puyos_[0]->GetMyRenderer()->ChangeAnimation("MM_PUYO_DESTROY");

		if ( true == Puyos_[0]->GetMyRenderer()->IsEndAnimation())
		{
			Puyos_[0]->Off();
		}

		FadeBackground_->FadeInOn();
		FadeBackground_->GetMyRenderer()->SetOrder(20);
		FadeBackground_->SetFadeSpeed(700.f);

		ChangeTime_ += GameEngineTime::GetDeltaTime();

		if (2.f < ChangeTime_ && true == FadeBackground_->GetIsInChange())
		{
			GameEngine::GetInst().ChangeLevel("EnemySelect");
		}
	}

	else if (true == MenuSelect_[1])
	{
		FadeBackground_->FadeInOn();
		FadeBackground_->GetMyRenderer()->SetOrder(20);
		FadeBackground_->SetFadeSpeed(700.f);

		Puyos_[1]->GetMyRenderer()->PauseOff();
		Puyos_[2]->GetMyRenderer()->PauseOff();
		Puyos_[1]->GetMyRenderer()->ChangeAnimation("MM_PUYO_DESTROY");
		Puyos_[2]->GetMyRenderer()->ChangeAnimation("MM_PUYO_DESTROY");

		if (true == Puyos_[1]->GetMyRenderer()->IsEndAnimation()
			&& true == Puyos_[2]->GetMyRenderer()->IsEndAnimation())
		{
			Puyos_[1]->Off();
			Puyos_[2]->Off();
		}

		ChangeTime_ += GameEngineTime::GetDeltaTime();

		if (2.f < ChangeTime_ && true == FadeBackground_->GetIsInChange())
		{
			GameEngine::GetInst().ChangeLevel("Title");
		}
	}

	else if (true == MenuSelect_[2])
	{
		FadeBackground_->FadeInOn();
		FadeBackground_->GetMyRenderer()->SetOrder(20);
		FadeBackground_->SetFadeSpeed(700.f);

		Puyos_[3]->GetMyRenderer()->PauseOff();
		Puyos_[4]->GetMyRenderer()->PauseOff();
		Puyos_[3]->GetMyRenderer()->ChangeAnimation("MM_PUYO_DESTROY");
		Puyos_[4]->GetMyRenderer()->ChangeAnimation("MM_PUYO_DESTROY");

		if (true == Puyos_[3]->GetMyRenderer()->IsEndAnimation()
			&& true == Puyos_[4]->GetMyRenderer()->IsEndAnimation())
		{
			Puyos_[3]->Off();
			Puyos_[4]->Off();
		}

		ChangeTime_ += GameEngineTime::GetDeltaTime();

		if (2.f < ChangeTime_ && true == FadeBackground_->GetIsInChange())
		{
			GameEngine::GetInst().ChangeLevel("Title");
		}
	}

	else if (true == MenuSelect_[3])
	{
		FadeBackground_->FadeInOn();
		FadeBackground_->GetMyRenderer()->SetOrder(20);
		FadeBackground_->SetFadeSpeed(700.f);

		Puyos_[5]->GetMyRenderer()->PauseOff();
		Puyos_[6]->GetMyRenderer()->PauseOff();
		Puyos_[7]->GetMyRenderer()->PauseOff();
		Puyos_[5]->GetMyRenderer()->ChangeAnimation("MM_PUYO_DESTROY");
		Puyos_[6]->GetMyRenderer()->ChangeAnimation("MM_PUYO_DESTROY");
		Puyos_[7]->GetMyRenderer()->ChangeAnimation("MM_PUYO_DESTROY");

		if (true == Puyos_[5]->GetMyRenderer()->IsEndAnimation()
			&& true == Puyos_[6]->GetMyRenderer()->IsEndAnimation()
			&& true == Puyos_[7]->GetMyRenderer()->IsEndAnimation())
		{
			Puyos_[5]->Off();
			Puyos_[6]->Off();
			Puyos_[7]->Off();
		}

		ChangeTime_ += GameEngineTime::GetDeltaTime();

		if (2.f < ChangeTime_ && true == FadeBackground_->GetIsInChange())
		{
			GameEngine::GetInst().ChangeLevel("Title");
		}
	}

	else if (true == MenuSelect_[4])
	{
		FadeBackground_->FadeInOn();
		FadeBackground_->GetMyRenderer()->SetOrder(20);
		FadeBackground_->SetFadeSpeed(700.f);

		Puyos_[8]->GetMyRenderer()->PauseOff();
		Puyos_[9]->GetMyRenderer()->PauseOff();
		Puyos_[10]->GetMyRenderer()->PauseOff();
		Puyos_[11]->GetMyRenderer()->PauseOff();

		Puyos_[8]->GetMyRenderer()->ChangeAnimation("MM_PUYO_DESTROY");
		Puyos_[9]->GetMyRenderer()->ChangeAnimation("MM_PUYO_DESTROY");
		Puyos_[10]->GetMyRenderer()->ChangeAnimation("MM_PUYO_DESTROY");
		Puyos_[11]->GetMyRenderer()->ChangeAnimation("MM_PUYO_DESTROY");

		if (true == Puyos_[8]->GetMyRenderer()->IsEndAnimation()
			&& true == Puyos_[9]->GetMyRenderer()->IsEndAnimation()
			&& true == Puyos_[10]->GetMyRenderer()->IsEndAnimation()
			&& true == Puyos_[11]->GetMyRenderer()->IsEndAnimation())
		{
			Puyos_[8]->Off();
			Puyos_[9]->Off();
			Puyos_[10]->Off();
			Puyos_[11]->Off();
		}

		ChangeTime_ += GameEngineTime::GetDeltaTime();

		if (2.f < ChangeTime_ && true == FadeBackground_->GetIsInChange())
		{ 
			GameEngine::GetInst().ChangeLevel("Title");
		}
	}
}

void MainMenu::FocasMenu()
{
	MenuRenderers_[0]->ChangeAnimation("MM_MENU_1_IDLE_DARK");
	MenuRenderers_[1]->ChangeAnimation("MM_MENU_2_IDLE_DARK");
	MenuRenderers_[2]->ChangeAnimation("MM_MENU_3_IDLE_DARK");
	MenuRenderers_[3]->ChangeAnimation("MM_MENU_4_IDLE_DARK");
	MenuRenderers_[4]->ChangeAnimation("MM_MENU_5_IDLE_DARK");

	switch (MenuCount_)
	{
	case 0:
		MenuRenderers_[0]->ChangeAnimation("MM_MENU_1_IDLE");
		break;

	case 1:
		MenuRenderers_[1]->ChangeAnimation("MM_MENU_2_IDLE");
		break;

	case 2:
		MenuRenderers_[2]->ChangeAnimation("MM_MENU_3_IDLE");
		break;

	case 3:
		MenuRenderers_[3]->ChangeAnimation("MM_MENU_4_IDLE");
		break;

	case 4:
		MenuRenderers_[4]->ChangeAnimation("MM_MENU_5_IDLE");
		break;
	}
}

void MainMenu::BackgroundUpdate()
{
	for (int i = 0; i < BackGrounds_.size(); ++i)
	{
		for (int j = 0; j < BackGrounds_[i].size(); j++)
		{
			if (0 == i || 2 == i) //0, 2라인
			{
				BackGrounds_[i][j]->SetPosition(BackGrounds_[i][j]->GetPosition() + (float4::RIGHT * GameEngineTime::GetDeltaTime() * 200.f));

				if (GameEngineWindow::GetScale().x + 220.f < BackGrounds_[i][j]->GetPosition().x)
				{
					if (0 == j)
					{
						BackGrounds_[i][j]->SetPosition(BackGrounds_[i].back()->GetPosition() - float4{ 220.f, 0.f });
					}

					else
					{
						BackGrounds_[i][j]->SetPosition(BackGrounds_[i][j - 1]->GetPosition() - float4{ 220.f, 0.f });
					}
				}
			}

			if (1 == i || 3 == i) //1, 3라인
			{
				BackGrounds_[i][j]->SetPosition(BackGrounds_[i][j]->GetPosition() + (float4::LEFT * GameEngineTime::GetDeltaTime() * 200.f));

				if (0.f - 220.f > BackGrounds_[i][j]->GetPosition().x) //벗어나는 위치
				{
					if (BackGrounds_[i].size() - 1 == j)
					{
						BackGrounds_[i][j]->SetPosition(BackGrounds_[i].front()->GetPosition() + float4{ 220.f, 0.f });
					}

					else
					{
						BackGrounds_[i][j]->SetPosition(BackGrounds_[i][j + 1]->GetPosition() + float4{ 220.f, 0.f });
					}
				}
			}

		}
	}
}

void MainMenu::MenuRendererPause()
{
	for (int i = 0; i < MenuRenderers_.size(); ++i)
	{
		MenuRenderers_[i]->PauseOff();
	}

	for (int i = 0; i < Puyos_.size(); ++i)
	{
		Puyos_[i]->GetMyRenderer()->PauseOff();
	}
}



void MainMenu::LevelChangeStart(GameEngineLevel* _PrevLevel) 
{
	MainMenuBgm_ = GameEngineSound::SoundPlayControl("MainMenu.mp3", -1);
}

void MainMenu::LevelChangeEnd(GameEngineLevel* _NextLevel)
{
	Reset();
}

void MainMenu::UserResetEnd()
{
	FadeBackground_ = CreateActor<FadeInOutBackground>();

	MenuImageInit();
	MenuInit();
	BackgourndInit();

	MenuCount_ = 0;
	ChangeTime_ = 0.f;
	RandomTime_ = 1.f;
	RightIndex_ = 0;
	LeftIndex_ = 0;
}

