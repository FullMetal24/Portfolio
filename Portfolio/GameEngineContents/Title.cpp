#include "Title.h"
#include "TitleActor.h"
#include "FadeInOutBackground.h"
#include <GameEngine/GameEngineLevel.h>
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngine/GameEngine.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineImageManager.h>

enum class TitileOrder
{
	LINE_3,
	FADE_3,
	ROLL_3,
	COIN_2,
	COIN_1, //애니메이션
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
	PUYO,
	PUYO_EYE,
	COMPANYLOGO
};

Title::Title()
	: TitleActors_{}
	, TransTime_(0.0f)
	, TransCount_(0)
	, EyeMove_(false)
	, TitleBgm_{}
{

}

Title::~Title()
{
}

void Title::Loading()
{
	BackgroundInit();

	if (false == GameEngineInput::GetInst()->IsKey("Title"))
	{
		GameEngineInput::GetInst()->CreateKey("Title", VK_SPACE);
	}
}

void Title::Update()
{
	ChangeBackground();
	FadeBackground();

	if (GameEngineInput::GetInst()->IsDown("Title") && 0 != TransCount_)
	{
		LevelChangeBackground_->FadeInOn();
		LevelChangeBackground_->GetMyRenderer()->SetOrder(20);
		LevelChangeBackground_->SetFadeSpeed(800.f);

		TitleBgm_.Stop();
	}

	if (true == LevelChangeBackground_->GetIsInChange())
	{
		GameEngine::GetInst().ChangeLevel("MainMenu");
	}

	if (1 == TransCount_ && false == EyeMove_)
	{
		if (0.5f < TransTime_)
		{
			TitleActors_[(int)TitileOrder::PUYO_EYE]->SetMove(float4::UP * 140.f);
			TitleActors_[(int)TitileOrder::PUYO_EYE]->SetMove(float4::LEFT * 120.f);

			EyeMove_ = true;
		}
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

	if (7 == TransCount_ && TitleActors_[(int)TitileOrder::COIN_1]->GetPosition().y + 150.f > GameEngineWindow::GetScale().Half().y)
	{
		TitleActors_[(int)TitileOrder::COIN_1]->SetMove(float4::UP * 600.f * GameEngineTime::GetDeltaTime());

		if (TitleActors_[(int)TitileOrder::COIN_1]->GetPosition().y + 150.f <= GameEngineWindow::GetScale().Half().y)
		{
			TitleActors_[(int)TitileOrder::COIN_2]->SetPosition(TitleActors_[(int)TitileOrder::COIN_1]->GetPosition());
			CoinRenderer_->SetOrder(8);
			TitleActors_[(int)TitileOrder::COIN_1]->Off();

			ChineseChracter_->SetPosition(TitleActors_[(int)TitileOrder::COIN_2]->GetPosition());
			ChineseChracterRenderer_->SetOrder(7);
		}

		NameActor_[0]->SetPosition(TitleActors_[(int)TitileOrder::COIN_2]->GetPosition() + float4{ 0, 50.f });
		NameActor_[1]->SetPosition(TitleActors_[(int)TitileOrder::COIN_2]->GetPosition() + float4{ 0, 50.f });
		NameActor_[2]->SetPosition(TitleActors_[(int)TitileOrder::COIN_2]->GetPosition() + float4{ 0, 50.f });
		NameActor_[3]->SetPosition(TitleActors_[(int)TitileOrder::COIN_2]->GetPosition() + float4{ 0, 50.f });
	}

	if (8 == TransCount_)
	{
		NameRenderer_[0]->SetOrder(2);
		NameRenderer_[1]->SetOrder(2);
		NameRenderer_[2]->SetOrder(2);
		NameRenderer_[3]->SetOrder(2);

		NameActor_[0]->SetMove(float4::LEFT * GameEngineTime::GetDeltaTime() * 500.f);
		NameActor_[2]->SetMove(float4::RIGHT * GameEngineTime::GetDeltaTime() * 500.f);

		if (400.f > NameActor_[0]->GetPosition().x)
		{
			NameActor_[1]->SetMove(float4::LEFT * GameEngineTime::GetDeltaTime() * 600.f);
		}

		if (900.f < NameActor_[2]->GetPosition().x)
		{
			NameActor_[3]->SetMove(float4::RIGHT * GameEngineTime::GetDeltaTime() * 600.f);
		}


		if (250.f > NameActor_[0]->GetPosition().x && 270.f > NameActor_[1]->GetPosition().x
			&& 450.f < NameActor_[2]->GetPosition().x && 470.f < NameActor_[3]->GetPosition().x)
		{
			NameRenderer_[0]->SetOrder(10);
			NameRenderer_[1]->SetOrder(9);
			NameRenderer_[2]->SetOrder(10);
			NameRenderer_[3]->SetOrder(9);

			++TransCount_;
		}

	}

	if (9 == TransCount_)
	{
		if (NameActor_[0]->GetPosition().x < 640.f)
		{
			NameActor_[0]->SetMove(float4::RIGHT * GameEngineTime::GetDeltaTime() * 1000.f);
		}

		if (NameActor_[1]->GetPosition().x < 870.f)
		{
			NameActor_[1]->SetMove(float4::RIGHT * GameEngineTime::GetDeltaTime() * 700.f);
		}

		if (NameActor_[2]->GetPosition().x > 200.f)
		{
			NameActor_[2]->SetMove(float4::LEFT * GameEngineTime::GetDeltaTime() * 1000.f);
		}

		if (NameActor_[3]->GetPosition().x > 420.f)
		{
			NameActor_[3]->SetMove(float4::LEFT * GameEngineTime::GetDeltaTime() * 700.f);
		}

		if (1050.f > ChineseChracter_->GetPosition().x && NameActor_[3]->GetPosition().x <= 420.f)
		{
			ChineseChracter_->SetMove(float4::RIGHT * GameEngineTime::GetDeltaTime() * 800.f);
		}

		else if (NameActor_[0]->GetPosition().x > 640.f && NameActor_[1]->GetPosition().x > 870.f
			&& NameActor_[2]->GetPosition().x < 200.f && NameActor_[3]->GetPosition().x < 420.f && 1050.f < ChineseChracter_->GetPosition().x)
		{
			++TransCount_;
		}


	}
	
	if (10 == TransCount_)
	{
		RedRenderer_->SetOrder(11);
		GreenRenderer_->SetOrder(11);
		RedRenderer1_->SetOrder(11);

		if (280.f > RedPuyo_->GetPosition().y)
		{
			RedPuyo_->SetMove(float4::DOWN * GameEngineTime::GetDeltaTime() * 700.f);
		}

		else
		{
			RedRenderer1_->PauseOff();
			RedRenderer_->PauseOff();
		}

		if (200.f > GreenPuyo_->GetPosition().y)
		{
			GreenPuyo_->SetMove(float4::DOWN * GameEngineTime::GetDeltaTime() * 700.f);
		}

		else
		{
			GreenRenderer_->PauseOff();
		}

		if (false == GreenRenderer_->GetPause()
			&& false == RedRenderer_->GetPause())
		{
			++TransCount_;
		}
	}

	if (11 == TransCount_)
	{
		if (TitleActors_[(int)TitileOrder::ROLL_3]->GetPosition().y > 600.f)
		{
			TitleActors_[(int)TitileOrder::ROLL_3]->SetMove(float4::UP * GameEngineTime::GetDeltaTime() * 700.f);
		}

		else
		{
			TitleActors_[(int)TitileOrder::ROLL_3]->CreateRenderer("TT_ROLL_GRAY.bmp")->SetOrder(2);
			GameEngineRenderer* LogoRenderer = TitleActors_[(int)TitileOrder::ROLL_3]->CreateRenderer("TT_GAMELOGO.bmp");
			LogoRenderer->SetOrder(5);
			++TransCount_;
		}

	}

}



void Title::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
}

void Title::LevelChangeEnd(GameEngineLevel* _NextLevel)
{
	ResetOn();
}

void Title::UserResetEnd()
{
	BackgroundInit();

	if (false == GameEngineInput::GetInst()->IsKey("Title"))
	{
		GameEngineInput::GetInst()->CreateKey("Title", VK_SPACE);
	}

	TransCount_ = 0;
	TransTime_ = 0.f;
	EyeMove_ = false;
}


void Title::BackgroundInit()
{
	FadeInOutBackground_ = CreateActor<FadeInOutBackground>();
	LevelChangeBackground_ = CreateActor<FadeInOutBackground>();

	NameActor_[0] = CreateActor<TitleActor>(0);
	NameRenderer_[0] = NameActor_[0]->CreateRenderer("TT_PU.bmp");
	NameActor_[1] = CreateActor<TitleActor>(0);
	NameRenderer_[1] = NameActor_[1]->CreateRenderer("TT_YO.bmp");
	NameActor_[2] = CreateActor<TitleActor>(0);
	NameRenderer_[2] = NameActor_[2]->CreateRenderer("TT_PU.bmp");
	NameActor_[3] = CreateActor<TitleActor>(0);
	NameRenderer_[3] = NameActor_[3]->CreateRenderer("TT_YO.bmp");

	ChineseChracter_ = CreateActor<TitleActor>(0);
	ChineseChracterRenderer_ = ChineseChracter_->CreateRenderer("TT_CHINESECHARACTER.bmp");

	RedPuyo_ = CreateActor<TitleActor>(0);
	GreenPuyo_ = CreateActor<TitleActor>(0);
	RedPuyo_->SetPosition({ 290.f, -20.f });
	GreenPuyo_->SetPosition({ 920.f, -20.f });

	GameEngineImage* RedImage = GameEngineImageManager::GetInst()->Find("TT_SMALL_PUYO1.bmp");
	RedImage->CutCount(3, 1);

	RedRenderer_ = RedPuyo_->CreateRenderer();
	RedRenderer1_ = RedPuyo_->CreateRenderer(0, RenderPivot::CENTER, { 420.f, 0 });

	RedRenderer_->PauseOn();
	RedRenderer1_->PauseOn();

	RedRenderer_->CreateAnimation("TT_SMALL_PUYO1.bmp", "TT_SMALL_PUYO1", 0, 2, 0.1f, true);
	RedRenderer_->ChangeAnimation("TT_SMALL_PUYO1");
	RedRenderer1_->CreateAnimation("TT_SMALL_PUYO1.bmp", "TT_SMALL_PUYO1", 0, 2, 0.1f, true);
	RedRenderer1_->ChangeAnimation("TT_SMALL_PUYO1");

	GameEngineImage* GreenImage = GameEngineImageManager::GetInst()->Find("TT_SMALL_PUYO.bmp");
	GreenImage->CutCount(3, 1);

	GreenRenderer_ = GreenPuyo_->CreateRenderer();
	GreenRenderer_->PauseOn();
	GreenRenderer_->CreateAnimation("TT_SMALL_PUYO.bmp", "TT_SMALL_PUYO", 0, 2, 0.1f, true);
	GreenRenderer_->ChangeAnimation("TT_SMALL_PUYO");

	for (int i = 0; i < 20; i++)
	{
		//역순
		TitleActors_[i] = CreateActor<TitleActor>(i);
	}

	TitleRenderers_[(int)TitileOrder::COMPANYLOGO] = TitleActors_[(int)TitileOrder::COMPANYLOGO]->CreateRenderer("TT_COMPANYLOGO.bmp");

	GameEngineRenderer* PuyoRenderer = TitleActors_[(int)TitileOrder::PUYO]->CreateRenderer("TT_PUYO.bmp", (int)TitileOrder::PUYO, RenderPivot::CENTER);

	GameEngineRenderer* EyeRenderer = TitleActors_[(int)TitileOrder::PUYO_EYE]->CreateRenderer("TT_PUYO_EYE.bmp", (int)TitileOrder::PUYO_EYE, RenderPivot::CENTER, { 150, 150 });
	GameEngineRenderer* EyeRenderer1 = TitleActors_[(int)TitileOrder::PUYO_EYE]->CreateRenderer("TT_PUYO_EYE.bmp", (int)TitileOrder::PUYO_EYE, RenderPivot::CENTER, { 580, 420 });

	TitleActors_[(int)TitileOrder::PUYO_BACK]->CreateRenderer("TT_BACK.bmp");

	{
		GameEngineImage* Image = GameEngineImageManager::GetInst()->Find("TT_BACK1.bmp");
		Image->CutCount(6, 1);

		GameEngineRenderer* Renderer = TitleActors_[(int)TitileOrder::PUYO_BACK]->CreateRenderer();
		Renderer->CreateAnimation("TT_BACK1.bmp", "TT_BACK1", 0, 5, 0.05f, true);
		Renderer->ChangeAnimation("TT_BACK1");
	}

	GameEngineRenderer* RollRenderer = TitleActors_[(int)TitileOrder::ROLL_1]->CreateRenderer("TT_ROLL.bmp");
	RollRenderer->SetTransColor(RGB(0, 0, 0));
	TitleActors_[(int)TitileOrder::ROLL_1]->SetPosition({ TitleActors_[(int)TitileOrder::ROLL_1]->GetPosition().x, TitleActors_[(int)TitileOrder::ROLL_1]->GetPosition().y - 200.f });
	TitleActors_[(int)TitileOrder::LINE_1]->CreateRenderer("TT_LINE.bmp", (int)TitileOrder::LINE_1, RenderPivot::BOT, { 0 , 500 });

	GameEngineImage* Image = GameEngineImageManager::GetInst()->Find("TT_CARBUNCLE.bmp");
	Image->CutCount(5, 1);

	GameEngineRenderer* Renderer = TitleActors_[(int)TitileOrder::CARBUNCLE]->CreateRenderer();
	TitleActors_[(int)TitileOrder::CARBUNCLE]->SetMove({ -241, -20 });
	Renderer->CreateAnimation("TT_CARBUNCLE.bmp", "TT_CARBUNCLE", 0, 4, 0.1f, true);
	Renderer->ChangeAnimation("TT_CARBUNCLE");

	{
		GameEngineImage* Image = GameEngineImageManager::GetInst()->Find("TT_BACK2.bmp");
		Image->CutCount(6, 1);

		GameEngineRenderer* Renderer = TitleActors_[(int)TitileOrder::CARBUNCLE_BACK]->CreateRenderer();
		Renderer->CreateAnimation("TT_BACK2.bmp", "TT_BACK2", 0, 5, 0.05f, true);
		Renderer->ChangeAnimation("TT_BACK2");
	}

	GameEngineRenderer* RollRenderer2 = TitleActors_[(int)TitileOrder::ROLL_2]->CreateRenderer("TT_ROLL.bmp");
	RollRenderer2->SetTransColor(RGB(0, 0, 0));
	TitleActors_[(int)TitileOrder::LINE_2]->CreateRenderer("TT_LINE.bmp", (int)TitileOrder::LINE_2, RenderPivot::BOT, { 0 , 500 });

	TitleRenderers_[(int)TitileOrder::ARLE_FACE] = TitleActors_[(int)TitileOrder::ARLE_FACE]->CreateRenderer("TT_ARLE_FACE.bmp");
	GameEngineRenderer* FingerRenderer = TitleActors_[(int)TitileOrder::ARLE_FINGER]->CreateRenderer("TT_ARLE_FINGER.bmp");
	TitleActors_[(int)TitileOrder::ARLE_FINGER]->SetPosition({ GameEngineWindow::GetScale().x / 2.7f, GameEngineWindow::GetScale().y + FingerRenderer->GetImage()->GetScale().y / 2 });

	{
		GameEngineImage* Image = GameEngineImageManager::GetInst()->Find("TT_BACK3.bmp");
		Image->CutCount(6, 1);

		GameEngineRenderer* Renderer = TitleActors_[(int)TitileOrder::ARLE_BACK]->CreateRenderer();
		Renderer->CreateAnimation("TT_BACK3.bmp", "TT_BACK3", 0, 5, 0.05f, true);
		Renderer->ChangeAnimation("TT_BACK3");
	}

	//페이드 인 아웃
	GameEngineRenderer* RollRenderer3 = TitleActors_[(int)TitileOrder::ROLL_3]->CreateRenderer("TT_ROLL.bmp");
	RollRenderer3->SetTransColor(RGB(0, 0, 0));
	TitleRenderers_[(int)TitileOrder::LINE_3] = TitleActors_[(int)TitileOrder::LINE_3]->CreateRenderer("TT_LINE.bmp");

	GameEngineImage* CoinImage = GameEngineImageManager::GetInst()->Find("TT_CARCOIN.bmp");
	CoinImage->CutCount(11, 1);

	GameEngineRenderer* CoinRenderer = TitleActors_[(int)TitileOrder::COIN_1]->CreateRenderer();
	TitleActors_[(int)TitileOrder::COIN_1]->SetPosition({ GameEngineWindow::GetScale().Half().x, GameEngineWindow::GetScale().y + CoinImage->GetScale().y / 2 });
	CoinRenderer->CreateAnimation("TT_CARCOIN.bmp", "TT_CARCOIN", 0, 10, 0.05f, true);
	CoinRenderer->ChangeAnimation("TT_CARCOIN");

	CoinRenderer_ = TitleActors_[(int)TitileOrder::COIN_2]->CreateRenderer("TT_COIN.bmp", -1);
}

void Title::ChangeBackground()
{
	TransTime_ += GameEngineTime::GetDeltaTime();

	if (3.0f < TransTime_ && 0 == TransCount_)
	{
		FadeInOutBackground_->Reset();

		TitleActors_[(int)TitileOrder::COMPANYLOGO]->Off();

		TitleBgm_ = GameEngineSound::SoundPlayControl("Title.mp3");

		++TransCount_;
		TransTime_ = 0.0f;
	}

	if (1.5f < TransTime_ && 1 == TransCount_)
	{
		FadeInOutBackground_->Reset();

		TitleActors_[(int)TitileOrder::PUYO]->Off();
		TitleActors_[(int)TitileOrder::PUYO_EYE]->Off();
		TitleActors_[(int)TitileOrder::PUYO_BACK]->Off();

		++TransCount_;
		TransTime_ = 0.0f;
	}

	if (1.0f < TransTime_ && 2 == TransCount_)
	{
		FadeInOutBackground_->Reset();

		TitleActors_[(int)TitileOrder::ROLL_1]->Off();
		TitleActors_[(int)TitileOrder::LINE_1]->Off();
		TitleActors_[(int)TitileOrder::ROLL_2]->SetPosition({ TitleActors_[(int)TitileOrder::ROLL_2]->GetPosition().x, TitleActors_[(int)TitileOrder::ROLL_2]->GetPosition().y - 100.f });

		++TransCount_;
		TransTime_ = 0.0f;
	}


	if (1.0f < TransTime_ && 3 == TransCount_)
	{
		FadeInOutBackground_->Reset();

		TitleActors_[(int)TitileOrder::CARBUNCLE]->Off();
		TitleActors_[(int)TitileOrder::CARBUNCLE_BACK]->Off();

		++TransCount_;
		TransTime_ = 0.0f;
	}

	if (2.0f < TransTime_ && 4 == TransCount_)
	{
		FadeInOutBackground_->Reset();

		TitleActors_[(int)TitileOrder::ROLL_2]->Off();
		TitleActors_[(int)TitileOrder::LINE_2]->Off();
		TitleActors_[(int)TitileOrder::ROLL_3]->SetPosition({ TitleActors_[(int)TitileOrder::ROLL_2]->GetPosition().x, TitleActors_[(int)TitileOrder::ROLL_2]->GetPosition().y - 250.f });

		++TransCount_;
		TransTime_ = 0.0f;
	}

	if (2.0f < TransTime_ && 5 == TransCount_)
	{
		FadeInOutBackground_->Reset();

		TitleActors_[(int)TitileOrder::ARLE_FACE]->Off();
		TitleActors_[(int)TitileOrder::ARLE_FINGER]->Off();
		TitleActors_[(int)TitileOrder::ARLE_BACK]->Off();

		++TransCount_;
		TransTime_ = 0.0f;

	}

	if (2.0f < TransTime_ && 6 == TransCount_)
	{
		++TransCount_;
		TransTime_ = 0.0f;
	}

	if (2.0f < TransTime_ && 7 == TransCount_)
	{
		++TransCount_;
		TransTime_ = 0.0f;
	}

	if (12 == TransCount_)
	{
		FadeInOutBackground_->Reset();
	}
}

void Title::FadeBackground()
{
	if (2.0f < TransTime_ && 0 == TransCount_)
	{
		FadeInOutBackground_->GetMyRenderer()->SetOrder((int)TitileOrder::COMPANYLOGO);
		FadeInOutBackground_->SetFadeSpeed(400.f);
		FadeInOutBackground_->FadeInOn();
	}

	if (1.3f < TransTime_ && 1 == TransCount_)
	{
		FadeInOutBackground_->GetMyRenderer()->SetOrder((int)TitileOrder::COMPANYLOGO);
		FadeInOutBackground_->SetFadeSpeed(1000.f);
		FadeInOutBackground_->FadeInOn();
	}


	if (0.8f < TransTime_ && 2 == TransCount_)
	{
		FadeInOutBackground_->GetMyRenderer()->SetOrder((int)TitileOrder::COMPANYLOGO);
		FadeInOutBackground_->SetFadeSpeed(1000.f);
		FadeInOutBackground_->FadeInOn();
	}

	if (0.8f < TransTime_ && 3 == TransCount_)
	{
		FadeInOutBackground_->GetMyRenderer()->SetOrder((int)TitileOrder::COMPANYLOGO);
		FadeInOutBackground_->SetFadeSpeed(1000.f);
		FadeInOutBackground_->FadeInOn();
	}


	if (1.8f < TransTime_ && 4 == TransCount_)
	{
		FadeInOutBackground_->GetMyRenderer()->SetOrder((int)TitileOrder::COMPANYLOGO);
		FadeInOutBackground_->SetFadeSpeed(1000.f);
		FadeInOutBackground_->FadeInOn();
	}


	if (1.8f < TransTime_ && 5 == TransCount_)
	{
		FadeInOutBackground_->GetMyRenderer()->SetOrder((int)TitileOrder::COMPANYLOGO);
		FadeInOutBackground_->SetFadeSpeed(1000.f);
		FadeInOutBackground_->FadeInOn();
	}

	if (1.9f < TransTime_ && 6 == TransCount_)
	{
		FadeInOutBackground_->GetMyRenderer()->SetOrder((int)TitileOrder::FADE_3);
		FadeInOutBackground_->SetFadeSpeed(200.f);
		FadeInOutBackground_->FadeInOn();
	}

	if (6 == TransCount_)
	{
		FadeInOutBackground_->GetMyRenderer()->SetOrder((int)TitileOrder::FADE_3);
		FadeInOutBackground_->SetFadeSpeed(200.f);
		FadeInOutBackground_->FadeInOn();
	}
}