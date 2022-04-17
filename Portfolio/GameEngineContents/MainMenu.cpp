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
	//입력 초기화
	if (false == GameEngineInput::GetInst()->IsKey("ManiMenu_Right"))
	{
		GameEngineInput::GetInst()->CreateKey("ManiMenu_Right", VK_RIGHT);
		GameEngineInput::GetInst()->CreateKey("ManiMenu_Left", VK_LEFT);
		GameEngineInput::GetInst()->CreateKey("ManiMenu_Select", VK_RETURN);
	}

	FadeBackground_ = CreateActor<FadeInOutBackground>();
	

	MenuImageInit();
	MenuInit();
	BackgourndInit();
}

void MainMenu::Update()
{
	MenuUpdate();
	BackgroundUpdate();
	SelectMenu();
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


	GameEngineImage* PuyoImage = GameEngineImageManager::GetInst()->Find("MM_PUYO.bmp");
	PuyoImage->CutCount(1, 1);

	GameEngineImage* MoveImage = GameEngineImageManager::GetInst()->Find("MM_PUYO_MOVE.bmp");
	MoveImage->CutCount(3, 1);

	GameEngineImage* PuyoDarkImage = GameEngineImageManager::GetInst()->Find("MM_PUYO_DARK.bmp");
	PuyoDarkImage->CutCount(1, 1);

	GameEngineImage* PuyoDestroyImage = GameEngineImageManager::GetInst()->Find("MM_PUYO_DESTROY.bmp");
	PuyoDestroyImage->CutCount(2, 1);
}

void MainMenu::MenuInit()
{
	GameEngineActor* Menu1 = CreateActor<MainMenuActor>(3);
	Menu1->SetPosition({ Menu1->GetPosition().x - 400.f, GameEngineWindow::GetScale().Half().y + 100.f });

	GameEngineRenderer* Menu1_Renerer = Menu1->CreateRenderer();
	Menu1_Renerer->CreateAnimation("MM_MENU_1_IDLE.bmp", "MM_MENU_1_IDLE", 0, 2, 0.1f, true);
	Menu1_Renerer->CreateAnimation("MM_MENU_1_IDLE_DARK.bmp", "MM_MENU_1_IDLE_DARK", 0, 2, 0.1f, true);
	Menu1_Renerer->CreateAnimation("MM_MENU_1_CLOSE.bmp", "MM_MENU_1_CLOSE", 0, 3, 0.1f, false);
	Menu1_Renerer->ChangeAnimation("MM_MENU_1_IDLE");
	Menu1_Renerer->PauseOn();

	//화살표
	{
		GameEngineActor* RightArrow = CreateActor<MainMenuActor>(4);
		RightArrow->SetPosition({ Menu1->GetPosition().x + 180.f, GameEngineWindow::GetScale().Half().y + 80.f });
		GameEngineRenderer* RightRenderer = RightArrow->CreateRenderer();
		RightRenderer->CreateAnimation("MM_ARROW_RIGHT.bmp", "MM_ARROW_RIGHT", 0, 1, 0.1f, true);
		RightRenderer->ChangeAnimation("MM_ARROW_RIGHT");

		GameEngineActor* LeftArrow = CreateActor<MainMenuActor>(4);
		LeftArrow->SetPosition({ Menu1->GetPosition().x + 140.f, GameEngineWindow::GetScale().Half().y + 80.f });
		GameEngineRenderer* LeftRenderer = LeftArrow->CreateRenderer();
		LeftRenderer->CreateAnimation("MM_ARROW_LEFT.bmp", "MM_ARROW_LEFT", 0, 1, 0.1f, true);
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
		Puyoenderer->CreateAnimation("MM_PUYO_MOVE.bmp", "MM_PUYO_MOVE", 0, 2, 0.1f, false);
		Puyoenderer->CreateAnimation("MM_PUYO_DARK.bmp", "MM_PUYO_DARK", 0, 0, 0.0f, false);
		Puyoenderer->CreateAnimation("MM_PUYO_DESTROY.bmp", "MM_PUYO_DESTROY", 0, 0, 0.0f, false);
		Puyoenderer->ChangeAnimation("MM_PUYO");

		Puyos_.push_back(Puyo);
		Puyo->SetMyRenderer(Puyoenderer);
	}


	GameEngineActor* Menu2 = CreateActor<MainMenuActor>(3);
	Menu2->SetPosition({ Menu1->GetPosition().x + 320.f, GameEngineWindow::GetScale().Half().y + 100.f });
	GameEngineRenderer* Menu2_Renerer = Menu2->GameEngineActor::CreateRenderer();
	Menu2_Renerer->CreateAnimation("MM_MENU_2_IDLE.bmp", "MM_MENU_2_IDLE", 0, 2, 0.1f, true);
	Menu2_Renerer->CreateAnimation("MM_MENU_2_IDLE_DARK.bmp", "MM_MENU_2_IDLE_DARK", 0, 2, 0.1f, true);
	Menu2_Renerer->CreateAnimation("MM_MENU_2_CLOSE.bmp", "MM_MENU_2_CLOSE", 0, 3, 0.1f, false);
	Menu2_Renerer->ChangeAnimation("MM_MENU_2_IDLE_DARK");
	Menu2_Renerer->PauseOn();

	{
		GameEngineActor* RightArrow = CreateActor<MainMenuActor>(4);
		RightArrow->SetPosition({ Menu2->GetPosition().x + 180.f, GameEngineWindow::GetScale().Half().y + 80.f });
		GameEngineRenderer* RightRenderer = RightArrow->CreateRenderer();
		RightRenderer->CreateAnimation("MM_ARROW_RIGHT.bmp", "MM_ARROW_RIGHT", 0, 1, 0.1f, true);
		RightRenderer->ChangeAnimation("MM_ARROW_RIGHT");
		RightRenderer->PauseOn();

		GameEngineActor* LeftArrow = CreateActor<MainMenuActor>(4);
		LeftArrow->SetPosition({ Menu2->GetPosition().x + 140.f, GameEngineWindow::GetScale().Half().y + 80.f });
		GameEngineRenderer* LeftRenderer = LeftArrow->CreateRenderer();
		LeftRenderer->CreateAnimation("MM_ARROW_LEFT.bmp", "MM_ARROW_LEFT", 0, 1, 0.1f, true);
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
		Puyoenderer->CreateAnimation("MM_PUYO_MOVE.bmp", "MM_PUYO_MOVE", 0, 2, 0.1f, false);
		Puyoenderer->CreateAnimation("MM_PUYO_DARK.bmp", "MM_PUYO_DARK", 0, 0, 0.0f, false);
		Puyoenderer->ChangeAnimation("MM_PUYO_DARK");
		Puyoenderer->PauseOn();

		MainMenuActor* Puyo1 = CreateActor<MainMenuActor>(5);
		Puyo1->SetPosition({ Menu2->GetPosition().x - 20.f, GameEngineWindow::GetScale().Half().y + 280.f });
		GameEngineRenderer* Puyoenderer1 = Puyo1->GameEngineActor::CreateRenderer();
		Puyoenderer1->CreateAnimation("MM_PUYO.bmp", "MM_PUYO", 0, 0, 0.0f, false);
		Puyoenderer1->CreateAnimation("MM_PUYO_MOVE.bmp", "MM_PUYO_MOVE", 0, 2, 0.1f, false);
		Puyoenderer1->CreateAnimation("MM_PUYO_DARK.bmp", "MM_PUYO_DARK", 0, 0, 0.0f, false);
		Puyoenderer1->ChangeAnimation("MM_PUYO_DARK");
		Puyoenderer1->PauseOn();

		Puyos_.push_back(Puyo);
		Puyo->SetMyRenderer(Puyoenderer);

		Puyos_.push_back(Puyo1);
		Puyo1->SetMyRenderer(Puyoenderer1);
	}


	GameEngineActor* Menu3 = CreateActor<MainMenuActor>(3);
	Menu3->SetPosition({ Menu2->GetPosition().x + 320.f, GameEngineWindow::GetScale().Half().y + 100.f });
	GameEngineRenderer* Menu3_Renerer = Menu3->CreateRenderer();
	Menu3_Renerer->CreateAnimation("MM_MENU_3_IDLE.bmp", "MM_MENU_3_IDLE", 0, 2, 0.5f, true);
	Menu3_Renerer->CreateAnimation("MM_MENU_3_IDLE_DARK.bmp", "MM_MENU_3_IDLE_DARK", 0, 2, 0.1f, true);
	Menu3_Renerer->CreateAnimation("MM_MENU_3_CLOSE.bmp", "MM_MENU_3_CLOSE", 0, 3, 0.1f, false);
	Menu3_Renerer->ChangeAnimation("MM_MENU_3_IDLE_DARK");
	Menu3_Renerer->PauseOn();

	{
		GameEngineActor* RightArrow = CreateActor<MainMenuActor>(4);
		RightArrow->SetPosition({ Menu3->GetPosition().x + 180.f, GameEngineWindow::GetScale().Half().y + 80.f });
		GameEngineRenderer* RightRenderer = RightArrow->CreateRenderer();
		RightRenderer->CreateAnimation("MM_ARROW_RIGHT.bmp", "MM_ARROW_RIGHT", 0, 1, 0.1f, true);
		RightRenderer->ChangeAnimation("MM_ARROW_RIGHT");
		RightRenderer->PauseOn();

		GameEngineActor* LeftArrow = CreateActor<MainMenuActor>(4);
		LeftArrow->SetPosition({ Menu3->GetPosition().x + 140.f, GameEngineWindow::GetScale().Half().y + 80.f });
		GameEngineRenderer* LeftRenderer = LeftArrow->CreateRenderer();
		LeftRenderer->CreateAnimation("MM_ARROW_LEFT.bmp", "MM_ARROW_LEFT", 0, 1, 0.1f, true);
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
		Puyoenderer->CreateAnimation("MM_PUYO_MOVE.bmp", "MM_PUYO_MOVE", 0, 2, 0.1f, false);
		Puyoenderer->CreateAnimation("MM_PUYO_DARK.bmp", "MM_PUYO_DARK", 0, 0, 0.0f, false);
		Puyoenderer->CreateAnimation("MM_PUYO_DESTROY.bmp", "MM_PUYO_DESTROY", 0, 0, 0.0f, false);
		Puyoenderer->ChangeAnimation("MM_PUYO_DARK");

		MainMenuActor* Puyo1 = CreateActor<MainMenuActor>(5);
		Puyo1->SetPosition({ Menu3->GetPosition().x + 85.f, GameEngineWindow::GetScale().Half().y + 280.f });
		GameEngineRenderer* Puyoenderer1 = Puyo1->GameEngineActor::CreateRenderer();
		Puyoenderer1->CreateAnimation("MM_PUYO.bmp", "MM_PUYO", 0, 0, 0.0f, false);
		Puyoenderer1->CreateAnimation("MM_PUYO_MOVE.bmp", "MM_PUYO_MOVE", 0, 2, 0.1f, false);
		Puyoenderer1->CreateAnimation("MM_PUYO_DARK.bmp", "MM_PUYO_DARK", 0, 0, 0.0f, false);
		Puyoenderer1->CreateAnimation("MM_PUYO_DESTROY.bmp", "MM_PUYO_DESTROY", 0, 0, 0.0f, false);
		Puyoenderer1->ChangeAnimation("MM_PUYO_DARK");

		Puyos_.push_back(Puyo);
		Puyo->SetMyRenderer(Puyoenderer);

		Puyos_.push_back(Puyo1);
		Puyo1->SetMyRenderer(Puyoenderer1);
	}



	GameEngineActor* Menu4 = CreateActor<MainMenuActor>(3);
	Menu4->SetPosition({ Menu3->GetPosition().x + 320.f, GameEngineWindow::GetScale().Half().y + 100.f });
	GameEngineRenderer* Menu4_Renerer = Menu4->CreateRenderer();
	Menu4_Renerer->CreateAnimation("MM_MENU_4_IDLE.bmp", "MM_MENU_4_IDLE", 0, 2, 0.5f, true);
	Menu4_Renerer->CreateAnimation("MM_MENU_4_IDLE_DARK.bmp", "MM_MENU_4_IDLE_DARK", 0, 2, 0.1f, true);
	Menu4_Renerer->CreateAnimation("MM_MENU_4_CLOSE.bmp", "MM_MENU_4_CLOSE", 0, 3, 0.1f, false);
	Menu4_Renerer->ChangeAnimation("MM_MENU_4_IDLE_DARK");
	Menu4_Renerer->PauseOn();


	{
		GameEngineActor* RightArrow = CreateActor<MainMenuActor>(4);
		RightArrow->SetPosition({ Menu4->GetPosition().x + 180.f, GameEngineWindow::GetScale().Half().y + 80.f });
		GameEngineRenderer* RightRenderer = RightArrow->CreateRenderer();
		RightRenderer->CreateAnimation("MM_ARROW_RIGHT.bmp", "MM_ARROW_RIGHT", 0, 1, 0.1f, true);
		RightRenderer->ChangeAnimation("MM_ARROW_RIGHT");
		RightRenderer->PauseOn();

		GameEngineActor* LeftArrow = CreateActor<MainMenuActor>(4);
		LeftArrow->SetPosition({ Menu4->GetPosition().x + 140.f, GameEngineWindow::GetScale().Half().y + 80.f });
		GameEngineRenderer* LeftRenderer = LeftArrow->CreateRenderer();
		LeftRenderer->CreateAnimation("MM_ARROW_LEFT.bmp", "MM_ARROW_LEFT", 0, 1, 0.1f, true);
		LeftRenderer->ChangeAnimation("MM_ARROW_LEFT");
		LeftRenderer->PauseOn();

		Arrows_.push_back(RightArrow);
		RightRenderers_.push_back(RightRenderer);
		Arrows_.push_back(LeftArrow);
		LeftRenderers_.push_back(LeftRenderer);
	}

	{
		MainMenuActor* Puyo = CreateActor<MainMenuActor>(5);
		Puyo->SetPosition({ Menu4->GetPosition().x -85.f, GameEngineWindow::GetScale().Half().y + 280.f });
		GameEngineRenderer* Puyoenderer = Puyo->GameEngineActor::CreateRenderer();
		Puyoenderer->CreateAnimation("MM_PUYO.bmp", "MM_PUYO", 0, 0, 0.0f, false);
		Puyoenderer->CreateAnimation("MM_PUYO_MOVE.bmp", "MM_PUYO_MOVE", 0, 2, 0.1f, false);
		Puyoenderer->CreateAnimation("MM_PUYO_DARK.bmp", "MM_PUYO_DARK", 0, 0, 0.0f, false);
		Puyoenderer->CreateAnimation("MM_PUYO_DESTROY.bmp", "MM_PUYO_DESTROY", 0, 0, 0.0f, false);
		Puyoenderer->ChangeAnimation("MM_PUYO_DARK");

		MainMenuActor* Puyo1 = CreateActor<MainMenuActor>(6);
		Puyo1->SetPosition({ Menu4->GetPosition().x - 45.f, GameEngineWindow::GetScale().Half().y + 290.f });
		GameEngineRenderer* Puyoenderer1 = Puyo1->GameEngineActor::CreateRenderer();
		Puyoenderer1->CreateAnimation("MM_PUYO.bmp", "MM_PUYO", 0, 0, 0.0f, false);
		Puyoenderer1->CreateAnimation("MM_PUYO_MOVE.bmp", "MM_PUYO_MOVE", 0, 2, 0.1f, false);
		Puyoenderer1->CreateAnimation("MM_PUYO_DARK.bmp", "MM_PUYO_DARK", 0, 0, 0.0f, false);
		Puyoenderer1->CreateAnimation("MM_PUYO_DESTROY.bmp", "MM_PUYO_DESTROY", 0, 0, 0.0f, false);
		Puyoenderer1->ChangeAnimation("MM_PUYO_DARK");

		MainMenuActor* Puyo2 = CreateActor<MainMenuActor>(5);
		Puyo2->SetPosition({ Menu4->GetPosition().x - 15.f, GameEngineWindow::GetScale().Half().y + 280.f });
		GameEngineRenderer* Puyoenderer2 = Puyo2->GameEngineActor::CreateRenderer();
		Puyoenderer2->CreateAnimation("MM_PUYO.bmp", "MM_PUYO", 0, 0, 0.0f, false);
		Puyoenderer2->CreateAnimation("MM_PUYO_MOVE.bmp", "MM_PUYO_MOVE", 0, 2, 0.1f, false);
		Puyoenderer2->CreateAnimation("MM_PUYO_DARK.bmp", "MM_PUYO_DARK", 0, 0, 0.0f, false);
		Puyoenderer2->CreateAnimation("MM_PUYO_DESTROY.bmp", "MM_PUYO_DESTROY", 0, 0, 0.0f, false);
		Puyoenderer2->ChangeAnimation("MM_PUYO_DARK");


		Puyos_.push_back(Puyo);
		Puyo->SetMyRenderer(Puyoenderer);

		Puyos_.push_back(Puyo1);
		Puyo1->SetMyRenderer(Puyoenderer1);

		Puyos_.push_back(Puyo2);
		Puyo2->SetMyRenderer(Puyoenderer2);
	}


	GameEngineActor* Menu5 = CreateActor<MainMenuActor>(3);
	Menu5->SetPosition({ Menu4->GetPosition().x + 320.f, GameEngineWindow::GetScale().Half().y + 100.f });
	GameEngineRenderer* Menu5_Renerer = Menu5->CreateRenderer();
	Menu5_Renerer->CreateAnimation("MM_MENU_5_IDLE.bmp", "MM_MENU_5_IDLE", 0, 2, 0.5f, true);
	Menu5_Renerer->CreateAnimation("MM_MENU_5_IDLE_DARK.bmp", "MM_MENU_5_IDLE_DARK", 0, 2, 0.1f, true);
	Menu5_Renerer->CreateAnimation("MM_MENU_5_CLOSE.bmp", "MM_MENU_5_CLOSE", 0, 3, 0.1f, false);
	Menu5_Renerer->ChangeAnimation("MM_MENU_5_IDLE_DARK");
	Menu5_Renerer->PauseOn();

	{
		MainMenuActor* Puyo = CreateActor<MainMenuActor>(5);
		Puyo->SetPosition({ Menu5->GetPosition().x - 100.f, GameEngineWindow::GetScale().Half().y + 280.f });
		GameEngineRenderer* Puyoenderer = Puyo->GameEngineActor::CreateRenderer();
		Puyoenderer->CreateAnimation("MM_PUYO.bmp", "MM_PUYO", 0, 0, 0.0f, false);
		Puyoenderer->CreateAnimation("MM_PUYO_MOVE.bmp", "MM_PUYO_MOVE", 0, 2, 0.1f, false);
		Puyoenderer->CreateAnimation("MM_PUYO_DARK.bmp", "MM_PUYO_DARK", 0, 0, 0.0f, false);
		Puyoenderer->CreateAnimation("MM_PUYO_DESTROY.bmp", "MM_PUYO_DESTROY", 0, 0, 0.0f, false);
		Puyoenderer->ChangeAnimation("MM_PUYO_DARK");

		MainMenuActor* Puyo1 = CreateActor<MainMenuActor>(5);
		Puyo1->SetPosition({ Menu5->GetPosition().x - 40.f, GameEngineWindow::GetScale().Half().y + 280.f });
		GameEngineRenderer* Puyoenderer1 = Puyo1->GameEngineActor::CreateRenderer();
		Puyoenderer1->CreateAnimation("MM_PUYO.bmp", "MM_PUYO", 0, 0, 0.0f, false);
		Puyoenderer1->CreateAnimation("MM_PUYO_MOVE.bmp", "MM_PUYO_MOVE", 0, 2, 0.1f, false);
		Puyoenderer1->CreateAnimation("MM_PUYO_DARK.bmp", "MM_PUYO_DARK", 0, 0, 0.0f, false);
		Puyoenderer1->CreateAnimation("MM_PUYO_DESTROY.bmp", "MM_PUYO_DESTROY", 0, 0, 0.0f, false);
		Puyoenderer1->ChangeAnimation("MM_PUYO_DARK");

		MainMenuActor* Puyo2 = CreateActor<MainMenuActor>(5);
		Puyo2->SetPosition({ Menu5->GetPosition().x + 17.f, GameEngineWindow::GetScale().Half().y + 280.f });
		GameEngineRenderer* Puyoenderer2 = Puyo2->GameEngineActor::CreateRenderer();
		Puyoenderer2->CreateAnimation("MM_PUYO.bmp", "MM_PUYO", 0, 0, 0.0f, false);
		Puyoenderer2->CreateAnimation("MM_PUYO_MOVE.bmp", "MM_PUYO_MOVE", 0, 2, 0.1f, false);
		Puyoenderer2->CreateAnimation("MM_PUYO_DARK.bmp", "MM_PUYO_DARK", 0, 0, 0.0f, false);
		Puyoenderer2->CreateAnimation("MM_PUYO_DESTROY.bmp", "MM_PUYO_DESTROY", 0, 0, 0.0f, false);
		Puyoenderer2->ChangeAnimation("MM_PUYO_DARK");

		MainMenuActor* Puyo3 = CreateActor<MainMenuActor>(5);
		Puyo3->SetPosition({ Menu5->GetPosition().x + 100.f, GameEngineWindow::GetScale().Half().y + 280.f });
		GameEngineRenderer* Puyoenderer3 = Puyo3->GameEngineActor::CreateRenderer();
		Puyoenderer3->CreateAnimation("MM_PUYO.bmp", "MM_PUYO", 0, 0, 0.0f, false);
		Puyoenderer3->CreateAnimation("MM_PUYO_MOVE.bmp", "MM_PUYO_MOVE", 0, 2, 0.1f, false);
		Puyoenderer3->CreateAnimation("MM_PUYO_DARK.bmp", "MM_PUYO_DARK", 0, 0, 0.0f, false);
		Puyoenderer3->CreateAnimation("MM_PUYO_DESTROY.bmp", "MM_PUYO_DESTROY", 0, 0, 0.0f, false);
		Puyoenderer3->ChangeAnimation("MM_PUYO_DARK");

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
	Back_ = GameEngineImageManager::GetInst()->Find("MM_SD0R.bmp");
	Back_->CutCount(4, 1);

	GameEngineImage* Image = GameEngineImageManager::GetInst()->Find("MM_SD5L.bmp");
	Image->CutCount(4, 1);

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
		Renderer->CreateAnimation("MM_SD5L.bmp", "MM_SD5L", 0, 3, 0.1f, true);
		Renderer->ChangeAnimation("MM_SD5L");

		Actor->SetMyRenderer(Renderer);
		SecondLine.push_back(Actor);
	}

	for (int i = 0; i < 10; i++)
	{
		MainMenuActor* Actor = CreateActor<MainMenuActor>(1);
		float4 Pos(GameEngineWindow::GetScale().x - (i * Offset), (GameEngineWindow::GetScale().Half().y / 4.f) + 224 * 2);
		Actor->SetPosition(Pos);

		GameEngineRenderer* Renderer = Actor->GameEngineActor::CreateRenderer();
		Renderer->CreateAnimation("MM_SD0R.bmp", "MM_SD0R", 0, 3, 0.1f, true);
		Renderer->ChangeAnimation("MM_SD0R");

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

			ArrowMoveToRight();	

			++MenuCount_;
			FocasMenu();
		}
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

			ArrowMoveToLeft();

			--MenuCount_;
			FocasMenu();
		}
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

	if (true == MenuRenderers_[1]->IsEndAnimation() && true == MenuSelect_[0])
	{
		FadeBackground_->FadeOn();
		FadeBackground_->GetMyRenderer()->SetOrder(20);
		FadeBackground_->SetFadeSpeed(800.f);

		if (true == FadeBackground_->GetIsChage())
		{
			GameEngine::GetInst().ChangeLevel("EnemySelect");
		}
	}

	else if (true == MenuRenderers_[2]->IsEndAnimation() && true == MenuSelect_[1])
	{
		FadeBackground_->FadeOn();
		FadeBackground_->SetOrder(20);
		FadeBackground_->SetFadeSpeed(800.f);

		if (true == FadeBackground_->GetIsChage())
		{
			GameEngine::GetInst().ChangeLevel("Title");
		}
	}

	else if (true == MenuRenderers_[3]->IsEndAnimation() && true == MenuSelect_[2])
	{
		FadeBackground_->FadeOn();
		FadeBackground_->SetOrder(20);
		FadeBackground_->SetFadeSpeed(800.f);

		if (true == FadeBackground_->GetIsChage())
		{
			GameEngine::GetInst().ChangeLevel("Title");
		}
	}

	else if (true == MenuRenderers_[4]->IsEndAnimation() && true == MenuSelect_[3])
	{
		FadeBackground_->FadeOn();
		FadeBackground_->SetOrder(20);
		FadeBackground_->SetFadeSpeed(800.f);


		if (true == FadeBackground_->GetIsChage())
		{
			GameEngine::GetInst().ChangeLevel("Title");
		}
	}

	else if (true == MenuRenderers_[0]->IsEndAnimation() && true == MenuSelect_[4])
	{
		FadeBackground_->FadeOn();
		FadeBackground_->SetOrder(20);
		FadeBackground_->SetFadeSpeed(800.f);

		if (true == FadeBackground_->GetIsChage())
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

void MainMenu::ArrowMoveToRight()
{
	for (int i = 0; i < Arrows_.size(); ++i)
	{
		Arrows_[i]->SetPosition(Arrows_[i]->GetPosition() + (float4::LEFT * 200.f));
	}

	for (int i = 0; i < RightRenderers_.size(); i++)
	{
		RightRenderers_[i]->PauseOn();
	}

	for (int i = 0; i < LeftRenderers_.size(); i++)
	{
		LeftRenderers_[i]->PauseOn();
	}


	if (RightIndex_ + 1 < RightRenderers_.size())
	{
		RightRenderers_[RightIndex_ + 1]->PauseOff();
		
		if (0 != RightIndex_ || RightRenderers_.size() != RightIndex_)
		{
			LeftRenderers_[LeftIndex_]->PauseOff();
		}

		++RightIndex_;
		++LeftIndex_;
	}

	else
	{
		LeftRenderers_[LeftIndex_]->PauseOff();
	}
}

void MainMenu::ArrowMoveToLeft()
{
	for (int i = 0; i < Arrows_.size(); ++i)
	{
		Arrows_[i]->SetPosition(Arrows_[i]->GetPosition() + (float4::RIGHT * 200.f));
	}

	for (int i = 0; i < RightRenderers_.size(); i++)
	{
		RightRenderers_[i]->PauseOn();
	}

	for (int i = 0; i < LeftRenderers_.size(); i++)
	{
		LeftRenderers_[i]->PauseOn();
	}

	if (LeftIndex_ - 1 >= 0)
	{
		LeftRenderers_[LeftIndex_ - 1]->PauseOff();

		if (0 != LeftIndex_ || LeftRenderers_.size() != LeftIndex_)
		{
			RightRenderers_[RightIndex_]->PauseOff();
		}

		--LeftIndex_;
		--RightIndex_;
	}

	else
	{
		RightRenderers_[0]->PauseOff();
	}
}

int offset_;

void MainMenu::BackgroundUpdate()
{
	for (int i = 0; i < BackGrounds_.size(); ++i)
	{
		for (int j = 0; j < BackGrounds_[i].size(); j++)
		{
			if (0 == i || 2 == i) //0, 2라인
			{
				BackGrounds_[i][j]->SetPosition(BackGrounds_[i][j]->GetPosition() + (float4::RIGHT * GameEngineTime::GetDeltaTime() * 200.f));

				if (GameEngineWindow::GetScale().x + 222.f
					< BackGrounds_[i][j]->GetPosition().x)
				{
					if (0 == j)
					{
						BackGrounds_[i][j]->SetPosition(BackGrounds_[i].back()->GetPosition() - float4{ 222.f, 0.f });
					}

					else
					{
						BackGrounds_[i][j]->SetPosition(BackGrounds_[i][j - 1]->GetPosition()
							- float4{ 222.f, 0.f });
					}
				}
			}

			if (1 == i || 3 == i) //1, 3라인
			{
				BackGrounds_[i][j]->SetPosition(BackGrounds_[i][j]->GetPosition() + (float4::LEFT * GameEngineTime::GetDeltaTime() * 200.f));

				if (0.f - 222.f > BackGrounds_[i][j]->GetPosition().x) //벗어나는 위치
				{
					if (BackGrounds_[i].size() - 1 == j)
					{
						BackGrounds_[i][j]->SetPosition(BackGrounds_[i].front()->GetPosition() + float4{ 222.f, 0.f });
					}

					else
					{
						BackGrounds_[i][j]->SetPosition(BackGrounds_[i][j + 1]->GetPosition()
							+ float4{ 222.f, 0.f });
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
}



void MainMenu::LevelChangeStart()
{
	MenuCount_ = 0;

	MainMenuBgm_ = GameEngineSound::SoundPlayControl("MainMenu.mp3");
}

void MainMenu::LevelChangeEnd()
{

}