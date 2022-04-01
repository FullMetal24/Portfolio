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
	//GameEngineActor* SelectMenu = CreateActor<MM_BackGround>(3);
	//SelectMenu->SetPosition({ GameEngineWindow::GetScale().Half().x, 100 });
	//GameEngineRenderer* SelectMenuRenderer = SelectMenu->CreateRenderer("MENU_RO.bmp");

	GameEngineImage* Image = GameEngineImageManager::GetInst()->Find("MENU_SD0R.bmp");
	Image->CutCount(4, 1);

	GameEngineImage* Image1 = GameEngineImageManager::GetInst()->Find("MENU_SD5L.bmp");
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
		Renderer->CreateAnimation("MENU_SD0R.bmp", "MENU_SD0R", 0, 3, 0.1f, true);
		Renderer->ChangeAnimation("MENU_SD0R");


		FirstLine.push_back(Actor);
	}

	for (int i = 0; i < 10; i++)
	{
		GameEngineActor* Actor = CreateActor<MM_BackGround>(1);
		float4 Pos(GameEngineWindow::GetScale().x - (i * Offset), (GameEngineWindow::GetScale().Half().y / 4.f) + 224);
		Actor->SetPosition(Pos);

		GameEngineRenderer* Renderer = Actor->CreateRenderer();
		Renderer->CreateAnimation("MENU_SD5L.bmp", "MENU_SD5L", 0, 3, 0.1f, true);
		Renderer->ChangeAnimation("MENU_SD5L");

		SecondLine.push_back(Actor);
	}

	for (int i = 0; i < 10; i++)
	{
		GameEngineActor* Actor = CreateActor<MM_BackGround>(1);
		float4 Pos(GameEngineWindow::GetScale().x - (i * Offset), (GameEngineWindow::GetScale().Half().y / 4.f) + 224 * 2);
		Actor->SetPosition(Pos);

		GameEngineRenderer* Renderer = Actor->CreateRenderer();
		Renderer->CreateAnimation("MENU_SD0R.bmp", "MENU_SD0R", 0, 3, 0.1f, true);
		Renderer->ChangeAnimation("MENU_SD0R");

		ThirdLine.push_back(Actor);
	}

	for (int i = 0; i < 10; i++)
	{
		GameEngineActor* Actor = CreateActor<MM_BackGround>(1);
		float4 Pos(GameEngineWindow::GetScale().x - (i * Offset), (GameEngineWindow::GetScale().Half().y / 4.f) + 224 * 3);
		Actor->SetPosition(Pos);

		GameEngineRenderer* Renderer = Actor->CreateRenderer();
		Renderer->CreateAnimation("MENU_SD5L.bmp", "MENU_SD5L", 0, 3, 0.1f, true);
		Renderer->ChangeAnimation("MENU_SD5L");

		LastLine.push_back(Actor);
	}

	BackGrounds_.push_back(FirstLine);
	BackGrounds_.push_back(SecondLine);
	BackGrounds_.push_back(ThirdLine);
	BackGrounds_.push_back(LastLine);


	{
		//카방클 메뉴

		GameEngineActor* Menu1 = CreateActor<MM_BackGround>(1);
		Menu1->SetPosition(float4{ Menu1->GetPosition().x + 250.f, GameEngineWindow::GetScale().Half().y });
		GameEngineRenderer* Menu1_Renerer = Menu1->CreateRenderer("MENU_1.bmp");
		Menu1_Renerer->SetTransColor(RGB(255, 255, 255));

		GameEngineActor* Menu2 = CreateActor<MM_BackGround>(1);
		Menu2->SetPosition(float4{ Menu1->GetPosition().x + Menu1_Renerer->GetImage()->GetScale().x, GameEngineWindow::GetScale().Half().y });
		GameEngineRenderer* Menu2_Renerer = Menu2->CreateRenderer("1-1.bmp");
		Menu2_Renerer->SetTransColor(RGB(255, 255, 255));

		GameEngineActor* Menu3 = CreateActor<MM_BackGround>(1);
		Menu3->SetPosition(float4{ Menu2->GetPosition().x + Menu2_Renerer->GetImage()->GetScale().x, GameEngineWindow::GetScale().Half().y });
		GameEngineRenderer* Menu3_Renerer = Menu3->CreateRenderer("2.bmp");
		Menu3_Renerer->SetTransColor(RGB(255, 255, 255));

		GameEngineActor* Menu4 = CreateActor<MM_BackGround>(1);
		Menu4->SetPosition(float4{ Menu3->GetPosition().x + Menu3_Renerer->GetImage()->GetScale().x, GameEngineWindow::GetScale().Half().y });
		GameEngineRenderer* Menu4_Renerer = Menu4->CreateRenderer("3.bmp");
		Menu4_Renerer->SetTransColor(RGB(255, 255, 255));

		GameEngineActor* Menu5 = CreateActor<MM_BackGround>(1);
		Menu5->SetPosition(float4{ Menu4->GetPosition().x + Menu4_Renerer->GetImage()->GetScale().x, GameEngineWindow::GetScale().Half().y });
		GameEngineRenderer* Menu5_Renerer = Menu5->CreateRenderer("4.bmp");
		Menu5_Renerer->SetTransColor(RGB(255, 255, 255));

		Menus_.push_back(Menu1);
		Menus_.push_back(Menu2);
		Menus_.push_back(Menu3);
		Menus_.push_back(Menu4);
		Menus_.push_back(Menu5);
	}

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
				GameEngine::GlobalEngine().ChangeLevel("CharacterSelect");
				break;
			case static_cast<int>(MenuType::TOGETHER):
				GameEngine::GlobalEngine().ChangeLevel("Title");
				break;
			case static_cast<int>(MenuType::TRAINING):
				GameEngine::GlobalEngine().ChangeLevel("Title");
				break;
			case static_cast<int>(MenuType::PUZZLE):
				GameEngine::GlobalEngine().ChangeLevel("Title");
				break;
			case static_cast<int>(MenuType::OPTION):
				GameEngine::GlobalEngine().ChangeLevel("Title");
				break;
			default:
				MenuCount_ = 0;
				break;
		}
	}


	//리스트가 나을까?

	for (int i = 0; i < BackGrounds_.size(); ++i)
	{
		for (int j = 0; j < BackGrounds_[i].size(); j++)
		{
			if (0 == i || 2 == i) //0, 2라인
			{
				BackGrounds_[i][j]->SetPosition(BackGrounds_[i][j]->GetPosition() + (float4::RIGHT * GameEngineTime::GetDeltaTime() * 100.f));

				//if (GameEngineWindow::GetScale().x < BackGrounds_[i][j]->GetPosition().x)
				//{
				//	BackGrounds_[i][j]->SetPosition({ 0.0f - BackGrounds_[i][j]->GetScale().x, BackGrounds_[i][j]->GetPosition().y});
				//}
			}

			if (1 == i || 3 == i) //1, 3라인
			{
				BackGrounds_[i][j]->SetPosition(BackGrounds_[i][j]->GetPosition() + (float4::LEFT * GameEngineTime::GetDeltaTime() * 100.f));

				//if (0.0f > BackGrounds_[i][j]->GetPosition().x) //벗어나는 위치
				//{
				//	BackGrounds_[i][j]->SetPosition({ GameEngineWindow::GetScale().x + BackGrounds_[i][j]->GetScale().x , BackGrounds_[i][j]->GetPosition().y }); //다시 붙여주는 위치
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


