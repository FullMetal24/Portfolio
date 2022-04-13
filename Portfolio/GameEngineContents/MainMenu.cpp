#include "MainMenu.h"
#include "MM_BackGround.h"
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngineBase/GameEngineMath.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngine/GameEngine.h>
#include "ContentsEnum.h"
#include <GameEngineBase/GameEngineTime.h>

MainMenu::MainMenu()
	: Arrows_{}
	, MenuCount_(0)
	, RightIndex_(0)
	, LeftIndex_(0)
{
}

MainMenu::~MainMenu() 
{
}


void MainMenu::Loading()
{
	MenuInit();
	BackgourndInit();

	//입력 초기화
	if (false == GameEngineInput::GetInst()->IsKey("ManiMenu_Right"))
	{
		GameEngineInput::GetInst()->CreateKey("ManiMenu_Right", VK_RIGHT);
		GameEngineInput::GetInst()->CreateKey("ManiMenu_Left", VK_LEFT);
		GameEngineInput::GetInst()->CreateKey("ManiMenu_Select", VK_RETURN);
	}
}

void MainMenu::Update()
{
	MenuUpdate();
	BackgroundUpdate();
}


void MainMenu::MenuInit()
{

	GameEngineActor* SelectMenu = CreateActor<MM_BackGround>(3);
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
		Image1->CutCount(4, 1);

		GameEngineImage* Image2 = GameEngineImageManager::GetInst()->Find("MM_MENU_3_IDLE_DARK.bmp");
		Image2->CutCount(4, 1);

		GameEngineImage* Image3 = GameEngineImageManager::GetInst()->Find("MM_MENU_4_IDLE_DARK.bmp");
		Image3->CutCount(4, 1);

		GameEngineImage* Image4 = GameEngineImageManager::GetInst()->Find("MM_MENU_5_IDLE_DARK.bmp");
		Image4->CutCount(4, 1);
	}

	//어둔 카방클(Close)
	{
		GameEngineImage* Image = GameEngineImageManager::GetInst()->Find("MM_MENU_1_CLOSE.bmp");
		Image->CutCount(3, 1);

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


	//카방클 메뉴
	{
		GameEngineActor* Menu1 = CreateActor<MM_BackGround>(3);
		Menu1->SetPosition({ Menu1->GetPosition().x + 250.f, GameEngineWindow::GetScale().Half().y + 100.f });

		GameEngineRenderer* Menu1_Renerer = Menu1->CreateRenderer();
		Menu1_Renerer->CreateAnimation("MM_MENU_1_IDLE.bmp", "MM_MENU_1_IDLE", 0, 2, 0.5f, true);
		Menu1_Renerer->CreateAnimation("MM_MENU_1_IDLE_DARK.bmp", "MM_MENU_1_IDLE_DARK", 0, 2, 0.1f, true);
		Menu1_Renerer->CreateAnimation("MM_MENU_1_CLOSE.bmp", "MM_MENU_1_CLOSE", 0, 2, 0.1f, true);
		Menu1_Renerer->ChangeAnimation("MM_MENU_1_IDLE");

		//화살표
		{
			GameEngineActor* RightArrow = CreateActor<MM_BackGround>(4);
			RightArrow->SetPosition({ Menu1->GetPosition().x + 180.f, GameEngineWindow::GetScale().Half().y + 80.f });
			GameEngineRenderer* RightRenderer = RightArrow->CreateRenderer();
			RightRenderer->CreateAnimation("MM_ARROW_RIGHT.bmp", "MM_ARROW_RIGHT", 0, 1, 0.1f, true);
			RightRenderer->ChangeAnimation("MM_ARROW_RIGHT");

			GameEngineActor* LeftArrow = CreateActor<MM_BackGround>(4);
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

		
		GameEngineActor* Menu2 = CreateActor<MM_BackGround>(3);
		Menu2->SetPosition({ Menu1->GetPosition().x + 320.f, GameEngineWindow::GetScale().Half().y + 100.f });
		GameEngineRenderer* Menu2_Renerer = Menu2->CreateRenderer();
		Menu2_Renerer->CreateAnimation("MM_MENU_2_IDLE.bmp", "MM_MENU_2_IDLE", 0, 2, 0.5f, false);
		Menu2_Renerer->CreateAnimation("MM_MENU_2_IDLE_DARK.bmp", "MM_MENU_2_IDLE_DARK", 0, 2, 0.1f, true);
		Menu2_Renerer->CreateAnimation("MM_MENU_2_CLOSE.bmp", "MM_MENU_2_CLOSE", 0, 2, 0.1f, true);
		Menu2_Renerer->ChangeAnimation("MM_MENU_2_IDLE");

		{
			GameEngineActor* RightArrow = CreateActor<MM_BackGround>(4);
			RightArrow->SetPosition({ Menu2->GetPosition().x + 180.f, GameEngineWindow::GetScale().Half().y + 80.f });
			GameEngineRenderer* RightRenderer = RightArrow->CreateRenderer();
			RightRenderer->CreateAnimation("MM_ARROW_RIGHT.bmp", "MM_ARROW_RIGHT", 0, 1, 0.1f, true);
			RightRenderer->ChangeAnimation("MM_ARROW_RIGHT");
			RightRenderer->PauseOn();

			GameEngineActor* LeftArrow = CreateActor<MM_BackGround>(4);
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

		GameEngineActor* Menu3 = CreateActor<MM_BackGround>(3);
		Menu3->SetPosition({ Menu2->GetPosition().x + 320.f, GameEngineWindow::GetScale().Half().y + 100.f});
		GameEngineRenderer* Menu3_Renerer = Menu3->CreateRenderer();
		Menu3_Renerer->CreateAnimation("MM_MENU_3_IDLE.bmp", "MM_MENU_3_IDLE", 0, 2, 0.5f, false);
		Menu3_Renerer->CreateAnimation("MM_MENU_3_IDLE_DARK.bmp", "MM_MENU_3_IDLE_DARK", 0, 2, 0.1f, true);
		Menu3_Renerer->CreateAnimation("MM_MENU_3_CLOSE.bmp", "MM_MENU_3_CLOSE", 0, 2, 0.1f, true);
		Menu3_Renerer->ChangeAnimation("MM_MENU_3_IDLE");
		Menu3_Renerer->PauseOn();

		{
			GameEngineActor* RightArrow = CreateActor<MM_BackGround>(4);
			RightArrow->SetPosition({ Menu3->GetPosition().x + 180.f, GameEngineWindow::GetScale().Half().y + 80.f });
			GameEngineRenderer* RightRenderer = RightArrow->CreateRenderer();
			RightRenderer->CreateAnimation("MM_ARROW_RIGHT.bmp", "MM_ARROW_RIGHT", 0, 1, 0.1f, true);
			RightRenderer->ChangeAnimation("MM_ARROW_RIGHT");
			RightRenderer->PauseOn();

			GameEngineActor* LeftArrow = CreateActor<MM_BackGround>(4);
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


		GameEngineActor* Menu4 = CreateActor<MM_BackGround>(3);
		Menu4->SetPosition({ Menu3->GetPosition().x + 320.f, GameEngineWindow::GetScale().Half().y + 100.f });
		GameEngineRenderer* Menu4_Renerer = Menu4->CreateRenderer();
		Menu4_Renerer->CreateAnimation("MM_MENU_4_IDLE.bmp", "MM_MENU_4_IDLE", 0, 2, 0.5f, false);
		Menu4_Renerer->CreateAnimation("MM_MENU_4_IDLE_DARK.bmp", "MM_MENU_4_IDLE_DARK", 0, 2, 0.1f, true);
		Menu4_Renerer->CreateAnimation("MM_MENU_4_CLOSE.bmp", "MM_MENU_4_CLOSE", 0, 2, 0.1f, true);
		Menu4_Renerer->ChangeAnimation("MM_MENU_4_IDLE");
		Menu4_Renerer->PauseOn();


		{
			GameEngineActor* RightArrow = CreateActor<MM_BackGround>(4);
			RightArrow->SetPosition({ Menu4->GetPosition().x + 180.f, GameEngineWindow::GetScale().Half().y + 80.f });
			GameEngineRenderer* RightRenderer = RightArrow->CreateRenderer();
			RightRenderer->CreateAnimation("MM_ARROW_RIGHT.bmp", "MM_ARROW_RIGHT", 0, 1, 0.1f, true);
			RightRenderer->ChangeAnimation("MM_ARROW_RIGHT");
			RightRenderer->PauseOn();

			GameEngineActor* LeftArrow = CreateActor<MM_BackGround>(4);
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


		GameEngineActor* Menu5 = CreateActor<MM_BackGround>(3);
		Menu5->SetPosition({ Menu4->GetPosition().x + 320.f, GameEngineWindow::GetScale().Half().y + 100.f });
		GameEngineRenderer* Menu5_Renerer = Menu5->CreateRenderer();
		Menu5_Renerer->CreateAnimation("MM_MENU_5_IDLE.bmp", "MM_MENU_5_IDLE", 0, 2, 0.5f, false);
		Menu5_Renerer->CreateAnimation("MM_MENU_5_IDLE_DARK.bmp", "MM_MENU_5_IDLE_DARK", 0, 2, 0.1f, true);
		Menu5_Renerer->CreateAnimation("MM_MENU_5_CLOSE.bmp", "MM_MENU_5_CLOSE", 0, 2, 0.1f, true);
		Menu5_Renerer->ChangeAnimation("MM_MENU_5_IDLE");
		Menu5_Renerer->PauseOn();

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
}

void MainMenu::BackgourndInit()
{
	Back_ = GameEngineImageManager::GetInst()->Find("MM_SD0R.bmp");
	Back_->CutCount(4, 1);

	GameEngineImage* Image1 = GameEngineImageManager::GetInst()->Find("MM_SD5L.bmp");
	Image1->CutCount(4, 1);

	std::list<GameEngineActor*> FirstLine;
	std::list<GameEngineActor*> SecondLine;
	std::list<GameEngineActor*> ThirdLine;
	std::list<GameEngineActor*> LastLine;

	float Offset;
	Offset = 220.f;

	for (int i = 0; i < 10; i++)
	{
		GameEngineActor* Actor = CreateActor<MM_BackGround>(1);
		float4 Pos(GameEngineWindow::GetScale().x - (i * Offset), (GameEngineWindow::GetScale().Half().y / 4.f));
		Actor->SetPosition(Pos);

		GameEngineRenderer* Renderer = Actor->CreateRenderer();
		Renderer->CreateAnimation("MM_SD0R.bmp", "MM_SD0R", 0, 3, 0.1f, true);
		Renderer->ChangeAnimation("MM_SD0R");

		FirstLine.push_back(Actor);
	}

	for (int i = 0; i < 10; i++)
	{
		GameEngineActor* Actor = CreateActor<MM_BackGround>(1);
		float4 Pos(GameEngineWindow::GetScale().x - (i * Offset), (GameEngineWindow::GetScale().Half().y / 4.f) + 224);
		Actor->SetPosition(Pos);

		GameEngineRenderer* Renderer = Actor->CreateRenderer();
		Renderer->CreateAnimation("MM_SD5L.bmp", "MM_SD5L", 0, 3, 0.1f, true);
		Renderer->ChangeAnimation("MM_SD5L");

		SecondLine.push_back(Actor);
	}

	for (int i = 0; i < 10; i++)
	{
		GameEngineActor* Actor = CreateActor<MM_BackGround>(1);
		float4 Pos(GameEngineWindow::GetScale().x - (i * Offset), (GameEngineWindow::GetScale().Half().y / 4.f) + 224 * 2);
		Actor->SetPosition(Pos);

		GameEngineRenderer* Renderer = Actor->CreateRenderer();
		Renderer->CreateAnimation("MM_SD0R.bmp", "MM_SD0R", 0, 3, 0.3f, true);
		Renderer->ChangeAnimation("MM_SD0R");

		ThirdLine.push_back(Actor);
	}

	for (int i = 0; i < 10; i++)
	{
		GameEngineActor* Actor = CreateActor<MM_BackGround>(1);
		float4 Pos(GameEngineWindow::GetScale().x - (i * Offset), (GameEngineWindow::GetScale().Half().y / 4.f) + 224 * 3);
		Actor->SetPosition(Pos);

		GameEngineRenderer* Renderer = Actor->CreateRenderer();
		Renderer->CreateAnimation("MM_SD5L.bmp", "MM_SD5L", 0, 3, 0.3f, true);
		Renderer->ChangeAnimation("MM_SD5L");

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
				//MenuRenderers_[0]->ChangeAnimation("MM_1-1");
				//MenuRenderers_[1]->ChangeAnimation("MM_2");
			}

			for (int i = 0; i < Arrows_.size(); ++i)
			{
				Arrows_[i]->SetPosition(Arrows_[i]->GetPosition() + (float4::LEFT * 200.f));
			}

			RightRenderers_[RightIndex_]->PauseOn();

			if (RightIndex_ + 1 < RightRenderers_.size())
			{
				RightRenderers_[RightIndex_ + 1]->PauseOff();
				++RightIndex_;
				++LeftIndex_;
			}

			++MenuCount_;
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

			for (int i = 0; i < Arrows_.size(); ++i)
			{
				Arrows_[i]->SetPosition(Arrows_[i]->GetPosition() + (float4::RIGHT * 200.f));
			}

			LeftRenderers_[LeftIndex_]->PauseOn();

			if (LeftIndex_ - 1 > 0)
			{
				LeftRenderers_[LeftIndex_ - 1]->PauseOff();
				--LeftIndex_;
			}

			--MenuCount_;
		}
	}

	if (GameEngineInput::GetInst()->IsDown("ManiMenu_Select"))
	{
		switch (MenuCount_)
		{
		case static_cast<int>(MenuType::ALONE):
			GameEngine::GetInst().ChangeLevel("EnemySelect");
			break;
		case static_cast<int>(MenuType::TOGETHER):
			GameEngine::GetInst().ChangeLevel("Title");
			break;
		case static_cast<int>(MenuType::TRAINING):
			GameEngine::GetInst().ChangeLevel("Title");
			break;
		case static_cast<int>(MenuType::PUZZLE):
			GameEngine::GetInst().ChangeLevel("Title");
			break;
		case static_cast<int>(MenuType::OPTION):
			GameEngine::GetInst().ChangeLevel("Title");
			break;
		default:
			MenuCount_ = 0;
			break;
		}
	}

}

void MainMenu::BackgroundUpdate()
{
	for (int i = 0; i < BackGrounds_.size(); ++i)
	{
		std::list<GameEngineActor*>::iterator StartIter = BackGrounds_[i].begin();
		std::list<GameEngineActor*>::iterator EndIter = BackGrounds_[i].end();

		if (0 == i || 2 == i)
		{
			for (; StartIter != EndIter; ++StartIter)
			{
				//(*StartIter)->SetPosition((*StartIter)->GetPosition() + (float4::RIGHT * GameEngineTime::GetDeltaTime() * 200.f));

				//if (GameEngineWindow::GetScale().x < (*StartIter)->GetPosition().x)
				//{

				//}
			}
		}

		if (1 == i || 3 == i) //1, 3라인
		{
			for (; StartIter != EndIter; ++StartIter)
			{
				//(*StartIter)->SetPosition((*StartIter)->GetPosition() + (float4::LEFT * GameEngineTime::GetDeltaTime() * 2.f));

				//if (0.0f > (*StartIter)->GetPosition().x)
				//{
				//	GameEngineActor* NextActor = BackGrounds_[i].back();
				//	(*StartIter)->SetPosition(NextActor->GetPosition());
				//	BackGrounds_[i].push_back(*StartIter);
				//}
			}
		}

	}


}



void MainMenu::LevelChangeStart()
{
	MenuCount_ = 0;
}

void MainMenu::LevelChangeEnd()
{

}