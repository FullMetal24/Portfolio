#include "MainMenu.h"
#include "MM_BackGround.h"
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngineBase/GameEngineMath.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngine/GameEngine.h>
#include "GameEngineContents/GlobalEnum.h"
#include <GameEngineBase/GameEngineTime.h>

MainMenu::MainMenu()
	: Actors_{}
	, MenuCount_(0)
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

	//백그라운드 엑터들은 크기가 없다.
	//게다가 렌더러 정보도 알 수가 없다.
	for (int i = 0; i < BackGrounds_.size(); ++i)
	{
		for (int j = 0; j < BackGrounds_[i].size(); j++)
		{
			if (0 == i || 2 == i) //0, 2라인
			{
				BackGrounds_[i][j]->SetPosition(BackGrounds_[i][j]->GetPosition() + (float4::RIGHT * GameEngineTime::GetDeltaTime() * 200.f));

				if (GameEngineWindow::GetScale().x + 500.f < BackGrounds_[i][j]->GetPosition().x)
				{
					BackGrounds_[i][j]->SetPosition({ 0.0f, BackGrounds_[i][j]->GetPosition().y});
				}
			}

			if (1 == i || 3 == i) //1, 3라인
			{
				BackGrounds_[i][j]->SetPosition(BackGrounds_[i][j]->GetPosition() + (float4::LEFT * GameEngineTime::GetDeltaTime() * 200.f));

				if (0.0f - 500.f > BackGrounds_[i][j]->GetPosition().x) //벗어나는 위치
				{
					BackGrounds_[i][j]->SetPosition({ GameEngineWindow::GetScale().x, BackGrounds_[i][j]->GetPosition().y }); //다시 붙여주는 위치
				}
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

void MainMenu::MenuInit()
{
	GameEngineActor* SelectMenu = CreateActor<MM_BackGround>(3);
	SelectMenu->SetPosition({ GameEngineWindow::GetScale().Half().x, 150 });
	GameEngineRenderer* SelectMenuRenderer = SelectMenu->CreateRenderer("MM_SELECT-1.bmp");


	GameEngineImage* Image = GameEngineImageManager::GetInst()->Find("MENU_1.bmp");
	Image->CutCount(3, 1);

	GameEngineImage* Image1 = GameEngineImageManager::GetInst()->Find("MENU_2.bmp");
	Image1->CutCount(3, 1);

	GameEngineImage* Image2 = GameEngineImageManager::GetInst()->Find("MENU_3.bmp");
	Image2->CutCount(3, 1);

	GameEngineImage* Image3 = GameEngineImageManager::GetInst()->Find("MENU_4.bmp");
	Image3->CutCount(3, 1);

	GameEngineImage* Image4 = GameEngineImageManager::GetInst()->Find("MENU_5.bmp");
	Image4->CutCount(3, 1);


	//카방클 메뉴
	{
		GameEngineActor* Menu1 = CreateActor<MM_BackGround>(3);
		Menu1->SetPosition({ Menu1->GetPosition().x + 250.f, GameEngineWindow::GetScale().Half().y + 100.f});
		GameEngineRenderer* Menu1_Renerer = Menu1->CreateRenderer();
		Menu1_Renerer->CreateAnimation("MENU_1.bmp", "MENU_1", 0, 2, 1.f, true);
		Menu1_Renerer->ChangeAnimation("MENU_1");
		Menu1_Renerer->SetTransColor(RGB(255, 255, 255));


		GameEngineActor* Menu2 = CreateActor<MM_BackGround>(3);
		Menu2->SetPosition({ Menu1->GetPosition().x + 320.f, GameEngineWindow::GetScale().Half().y + 100.f });
		GameEngineRenderer* Menu2_Renerer = Menu2->CreateRenderer();
		Menu2_Renerer->CreateAnimation("MENU_2.bmp", "MENU_2", 0, 2, 1.f, false);
		Menu2_Renerer->ChangeAnimation("MENU_2");
		Menu2_Renerer->SetTransColor(RGB(255, 255, 255));


		GameEngineActor* Menu3 = CreateActor<MM_BackGround>(3);
		Menu3->SetPosition({ Menu2->GetPosition().x + 320.f, GameEngineWindow::GetScale().Half().y + 100.f});
		GameEngineRenderer* Menu3_Renerer = Menu3->CreateRenderer();
		Menu3_Renerer->CreateAnimation("MENU_3.bmp", "MENU_3", 0, 2, 1.f, false);
		Menu3_Renerer->ChangeAnimation("MENU_3");
		Menu3_Renerer->SetTransColor(RGB(255, 255, 255));


		GameEngineActor* Menu4 = CreateActor<MM_BackGround>(3);
		Menu4->SetPosition({ Menu3->GetPosition().x + 320.f, GameEngineWindow::GetScale().Half().y + 100.f });
		GameEngineRenderer* Menu4_Renerer = Menu4->CreateRenderer();
		Menu4_Renerer->CreateAnimation("MENU_4.bmp", "MENU_4", 0, 2, 1.f, false);
		Menu4_Renerer->ChangeAnimation("MENU_4");
		Menu4_Renerer->SetTransColor(RGB(255, 255, 255));


		GameEngineActor* Menu5 = CreateActor<MM_BackGround>(3);
		Menu5->SetPosition({ Menu4->GetPosition().x + 320.f, GameEngineWindow::GetScale().Half().y + 100.f });
		GameEngineRenderer* Menu5_Renerer = Menu5->CreateRenderer();
		Menu5_Renerer->CreateAnimation("MENU_5.bmp", "MENU_5", 0, 2, 1.f, false);
		Menu5_Renerer->ChangeAnimation("MENU_5");
		Menu5_Renerer->SetTransColor(RGB(255, 255, 255));


		Menus_.push_back(Menu1);
		Menus_.push_back(Menu2);
		Menus_.push_back(Menu3);
		Menus_.push_back(Menu4);
		Menus_.push_back(Menu5);
	}
}

void MainMenu::BackgourndInit()
{
	GameEngineImage* Image = GameEngineImageManager::GetInst()->Find("MM_SD0R.bmp");
	Image->CutCount(4, 1);

	GameEngineImage* Image1 = GameEngineImageManager::GetInst()->Find("MM_SD5L.bmp");
	Image1->CutCount(4, 1);

	std::vector<GameEngineActor*> FirstLine;
	std::vector<GameEngineActor*> SecondLine;
	std::vector<GameEngineActor*> ThirdLine;
	std::vector<GameEngineActor*> LastLine;

	float Offset;
	Offset = 220.f;

	for (int i = 0; i < 10; i++)
	{
		GameEngineActor* Actor = CreateActor<MM_BackGround>(1);
		float4 Pos(GameEngineWindow::GetScale().x - (i * Offset), (GameEngineWindow::GetScale().Half().y / 4.f));
		Actor->SetPosition(Pos);

		GameEngineRenderer* Renderer = Actor->CreateRenderer();
		Renderer->CreateAnimation("MM_SD0R.bmp", "MM_SD0R", 0, 3, 0.3f, true);
		Renderer->ChangeAnimation("MM_SD0R");

		FirstLine.push_back(Actor);
	}

	for (int i = 0; i < 10; i++)
	{
		GameEngineActor* Actor = CreateActor<MM_BackGround>(1);
		float4 Pos(GameEngineWindow::GetScale().x - (i * Offset), (GameEngineWindow::GetScale().Half().y / 4.f) + 224);
		Actor->SetPosition(Pos);

		GameEngineRenderer* Renderer = Actor->CreateRenderer();
		Renderer->CreateAnimation("MM_SD5L.bmp", "MM_SD5L", 0, 3, 0.3f, true);
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
				float4 Offset = (Menus_[i]->GetPosition() + (float4::LEFT * 200.f));
				Menus_[i]->SetPosition(Offset);
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
				float4 Offset = (Menus_[i]->GetPosition() + (float4::RIGHT * 200.f));
				Menus_[i]->SetPosition(Offset);
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


