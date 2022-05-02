#include "InGame.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngineBase/GameEngineRandom.h>
#include <GameEngineBase/GameEngineMath.h>
#include <GameEngine/GameEngineActor.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngine/GameEngine.h>
#include "FadeInOutBackground.h"
#include "InGameActor.h"
#include "Puyo.h"
#include "EnemyFSM.h"
#include "ContentsEnum.h"
#include "EnemySelect.h"
#include "GameOver.h"
#include "Player.h"
#include "EnemyProfile.h"

InGame::InGame()
	: Stages_{ }
	, Player_(nullptr)
	, EnemyFSM_(nullptr)
	, EnemyProfile_(nullptr)
	, Stage_(nullptr)
	, StageClear_(0)
	, ChangeCount_(10.f)
	, IsStart_(false) //ÀÏ´Ü Æ®·ç
	, IsEnemyFlap_(false)
{
}

InGame::~InGame()
{

}

void InGame::Loading()
{
	PuyoAnimationInit();
	InitPlayerEndEnemy();
	EnemyAnimatioInit();

	FadeBackground_ = CreateActor<FadeInOutBackground>();

	Stages_[0] = CreateActor<Stage>();

	Stages_[0]->SetPosition(GameEngineWindow::GetScale().Half());
	Stages_[0]->CreateRenderer("IG_STAGE1.bmp", 3);
	Stages_[0]->CreateRenderer("IG_STAGE1_BACK.bmp", 0);

	GameOverRenderer_ = CreateActor<InGameActor>();
	GameOverRenderer_->SetPosition({ 255, 1500 });
	GameOverRenderer_->CreateRenderer("IG_PLAYER_GAMEOVER.bmp");

	GameOverStartPos_ = GameOverRenderer_->GetPosition();
	GameOverEndPos_ = GameOverRenderer_->GetPosition() + float4{ 0, -1200.f };

	WinRenderer_ = CreateActor<InGameActor>(-1);
	WinRenderer_->SetPosition({ 255, 200 });
	WinRenderer_->SetMyRenderer(WinRenderer_->CreateRenderer("IG_YOUWIN.bmp"));

	StateBottoms_[0] = CreateActor<InGameActor>();
	StateBottoms_[1] = CreateActor<InGameActor>();
	StateBottoms_[0]->SetMyRenderer(StateBottoms_[0]->CreateRenderer("IG_STAGE1_BOTTOM_LEFT.bmp", 3));
	StateBottoms_[1]->SetMyRenderer(StateBottoms_[1]->CreateRenderer("IG_STAGE1_BOTTOM_RIGHT.bmp", 3));

	StateBottoms_[0]->SetPosition({ GameEngineWindow::GetScale().Half() + float4{-384, 389} });
	StateBottoms_[1]->SetPosition({ GameEngineWindow::GetScale().Half() + float4{384, 389} });

	GameEngineActor* NextUi = CreateActor<Stage>(3);
	NextUi->CreateRenderer("IG_NEXT.bmp")->SetPivot({ GameEngineWindow::GetScale().Half().x, GameEngineWindow::GetScale().Half().y - 360.f });

	StageRenderer_ = CreateActor<InGameActor>(3);
	StageRenderer_->SetPosition({ GameEngineWindow::GetScale().Half().x, 1000.f });
	StageRenderer_->CreateRenderer("IG_STAGE_UI.bmp");

	StageRenderStartPos_ = StageRenderer_->GetPosition();
	StageRenderEndPos_ = { GameEngineWindow::GetScale().Half().x, GameEngineWindow::GetScale().Half().y - 60.f };

	GameEngineActor* PlayerName_ = CreateActor<Stage>(1);
	PlayerName_->CreateRenderer("IG_NAME_ARLE.bmp")->SetPivot({ GameEngineWindow::GetScale().Half().x - 96.f, GameEngineWindow::GetScale().Half().y - 290.f });

	Carbuncle_ = CreateActor<InGameActor>(6);
	Carbuncle_->SetPosition({ GameEngineWindow::GetScale().Half().x - 160.f, GameEngineWindow::GetScale().Half().y + 300.f });
	GameEngineRenderer* CarbuncleRenderer = Carbuncle_->CreateRenderer();
	Carbuncle_->SetMyRenderer(CarbuncleRenderer);

	CarbuncleAnimationInit();
}


void InGame::InitPlayerEndEnemy()
{
	Player_ = CreateActor<Player>(10);
	Player_->SetPosition({ 95, 748 });

	EnemyFSM_ = CreateActor<EnemyFSM>(10);
	EnemyFSM_->SetPosition({ 860, 748 });

	Player_->SetEnemyFSM(EnemyFSM_);
	EnemyFSM_->SetPlayer(Player_);
}

void InGame::PuyoAnimationInit()
{
	{
		GameEngineImage* NomalImage = GameEngineImageManager::GetInst()->Find("IG_RED_PUYO.bmp");
		NomalImage->CutCount(1, 1);

		GameEngineImage* CenterImage = GameEngineImageManager::GetInst()->Find("IG_RED_CENTER.bmp");
		CenterImage->CutCount(2, 1);

		GameEngineImage* DestroyImage = GameEngineImageManager::GetInst()->Find("IG_RED_DESTROY.bmp");
		DestroyImage->CutCount(6, 1);

		GameEngineImage* LandImage = GameEngineImageManager::GetInst()->Find("IG_RED_LAND.bmp");
		LandImage->CutCount(4, 1);

		GameEngineImage* IdleImage = GameEngineImageManager::GetInst()->Find("IG_RED_IDLE.bmp");
		IdleImage->CutCount(3, 1);

		GameEngineImage* IdleImage1 = GameEngineImageManager::GetInst()->Find("IG_RED_IDLE1.bmp");
		IdleImage1->CutCount(6, 1);



		GameEngineImage* LeftImage = GameEngineImageManager::GetInst()->Find("IG_RED_LEFT.bmp");
		LeftImage->CutCount(1, 1);

		GameEngineImage* RightImage = GameEngineImageManager::GetInst()->Find("IG_RED_RIGHT.bmp");
		RightImage->CutCount(1, 1);

		GameEngineImage* UpImage = GameEngineImageManager::GetInst()->Find("IG_RED_UP.bmp");
		UpImage->CutCount(1, 1);

		GameEngineImage* DownImage = GameEngineImageManager::GetInst()->Find("IG_RED_DOWN.bmp");
		DownImage->CutCount(1, 1);



		GameEngineImage* LefeDownImage = GameEngineImageManager::GetInst()->Find("IG_RED_LEFT_DOWN.bmp");
		LefeDownImage->CutCount(1, 1);

		GameEngineImage* LefeUpImage = GameEngineImageManager::GetInst()->Find("IG_RED_LEFT_UP.bmp");
		LefeUpImage->CutCount(1, 1);

		GameEngineImage* LefeRightImage = GameEngineImageManager::GetInst()->Find("IG_RED_LEFT_RIGHT.bmp");
		LefeRightImage->CutCount(1, 1);

		GameEngineImage* LeftRightDownImage = GameEngineImageManager::GetInst()->Find("IG_RED_LEFT_RIGHT_DOWN.bmp");
		LeftRightDownImage->CutCount(1, 1);

		GameEngineImage* LeftRightUpImage = GameEngineImageManager::GetInst()->Find("IG_RED_LEFT_RIGHT_UP.bmp");
		LeftRightUpImage->CutCount(1, 1);

		GameEngineImage* LeftRightUpDownImage = GameEngineImageManager::GetInst()->Find("IG_RED_LEFT_RIGHT_UP_DOWN.bmp");
		LeftRightUpDownImage->CutCount(1, 1);

		GameEngineImage* LeftUpDownImage = GameEngineImageManager::GetInst()->Find("IG_RED_LEFT_UP_DOWN.bmp");
		LeftUpDownImage->CutCount(1, 1);

		GameEngineImage* RightDownImage = GameEngineImageManager::GetInst()->Find("IG_RED_RIGHT_DOWN.bmp");
		RightDownImage->CutCount(1, 1);

		GameEngineImage* RightUPDownImage = GameEngineImageManager::GetInst()->Find("IG_RED_RIGHT_UP_DOWN.bmp");
		RightUPDownImage->CutCount(1, 1);

		GameEngineImage* UpDownImage = GameEngineImageManager::GetInst()->Find("IG_RED_UP_DOWN.bmp");
		UpDownImage->CutCount(1, 1);
	}

	{
		GameEngineImage* NomalImage = GameEngineImageManager::GetInst()->Find("IG_BLUE_PUYO.bmp");
		NomalImage->CutCount(1, 1);

		GameEngineImage* CenterImage = GameEngineImageManager::GetInst()->Find("IG_BLUE_CENTER.bmp");
		CenterImage->CutCount(2, 1);

		GameEngineImage* DestroyImage = GameEngineImageManager::GetInst()->Find("IG_BLUE_DESTROY.bmp");
		DestroyImage->CutCount(6, 1);

		GameEngineImage* LandImage = GameEngineImageManager::GetInst()->Find("IG_BLUE_LAND.bmp");
		LandImage->CutCount(4, 1);


		GameEngineImage* IdleImage = GameEngineImageManager::GetInst()->Find("IG_BLUE_IDLE.bmp");
		IdleImage->CutCount(6, 1);

		GameEngineImage* IdleImage1 = GameEngineImageManager::GetInst()->Find("IG_BLUE_IDLE1.bmp");
		IdleImage1->CutCount(8, 1);

		GameEngineImage* LeftImage = GameEngineImageManager::GetInst()->Find("IG_BLUE_LEFT.bmp");
		LeftImage->CutCount(1, 1);

		GameEngineImage* RightImage = GameEngineImageManager::GetInst()->Find("IG_BLUE_RIGHT.bmp");
		RightImage->CutCount(1, 1);

		GameEngineImage* UpImage = GameEngineImageManager::GetInst()->Find("IG_BLUE_UP.bmp");
		UpImage->CutCount(1, 1);

		GameEngineImage* DownImage = GameEngineImageManager::GetInst()->Find("IG_BLUE_DOWN.bmp");
		DownImage->CutCount(1, 1);



		GameEngineImage* LefeDownImage = GameEngineImageManager::GetInst()->Find("IG_BLUE_LEFT_DOWN.bmp");
		LefeDownImage->CutCount(1, 1);

		GameEngineImage* LefeUpImage = GameEngineImageManager::GetInst()->Find("IG_BLUE_LEFT_UP.bmp");
		LefeUpImage->CutCount(1, 1);

		GameEngineImage* LefeRightImage = GameEngineImageManager::GetInst()->Find("IG_BLUE_LEFT_RIGHT.bmp");
		LefeRightImage->CutCount(1, 1);

		GameEngineImage* LeftRightDownImage = GameEngineImageManager::GetInst()->Find("IG_BLUE_LEFT_RIGHT_DOWN.bmp");
		LeftRightDownImage->CutCount(1, 1);

		GameEngineImage* LeftRightUpImage = GameEngineImageManager::GetInst()->Find("IG_BLUE_LEFT_RIGHT_UP.bmp");
		LeftRightUpImage->CutCount(1, 1);

		GameEngineImage* LeftRightUpDownImage = GameEngineImageManager::GetInst()->Find("IG_BLUE_LEFT_RIGHT_UP_DOWN.bmp");
		LeftRightUpDownImage->CutCount(1, 1);

		GameEngineImage* LeftUpDownImage = GameEngineImageManager::GetInst()->Find("IG_BLUE_LEFT_UP_DOWN.bmp");
		LeftUpDownImage->CutCount(1, 1);

		GameEngineImage* RightDownImage = GameEngineImageManager::GetInst()->Find("IG_BLUE_RIGHT_DOWN.bmp");
		RightDownImage->CutCount(1, 1);

		GameEngineImage* RightUPDownImage = GameEngineImageManager::GetInst()->Find("IG_BLUE_RIGHT_UP_DOWN.bmp");
		RightUPDownImage->CutCount(1, 1);

		GameEngineImage* UpDownImage = GameEngineImageManager::GetInst()->Find("IG_BLUE_UP_DOWN.bmp");
		UpDownImage->CutCount(1, 1);
	}

	{
		GameEngineImage* NomalImage = GameEngineImageManager::GetInst()->Find("IG_GREEN_PUYO.bmp");
		NomalImage->CutCount(1, 1);

		GameEngineImage* CenterImage = GameEngineImageManager::GetInst()->Find("IG_GREEN_CENTER.bmp");
		CenterImage->CutCount(2, 1);

		GameEngineImage* DestroyImage = GameEngineImageManager::GetInst()->Find("IG_GREEN_DESTROY.bmp");
		DestroyImage->CutCount(6, 1);

		GameEngineImage* LandImage = GameEngineImageManager::GetInst()->Find("IG_GREEN_LAND.bmp");
		LandImage->CutCount(4, 1);

		GameEngineImage* IdleImage = GameEngineImageManager::GetInst()->Find("IG_GREEN_IDLE.bmp");
		IdleImage->CutCount(8, 1);

		GameEngineImage* IdleImage1 = GameEngineImageManager::GetInst()->Find("IG_GREEN_IDLE1.bmp");
		IdleImage1->CutCount(8, 1);



		GameEngineImage* LeftImage = GameEngineImageManager::GetInst()->Find("IG_GREEN_LEFT.bmp");
		LeftImage->CutCount(1, 1);

		GameEngineImage* RightImage = GameEngineImageManager::GetInst()->Find("IG_GREEN_RIGHT.bmp");
		RightImage->CutCount(1, 1);

		GameEngineImage* UpImage = GameEngineImageManager::GetInst()->Find("IG_GREEN_UP.bmp");
		UpImage->CutCount(1, 1);

		GameEngineImage* DownImage = GameEngineImageManager::GetInst()->Find("IG_GREEN_DOWN.bmp");
		DownImage->CutCount(1, 1);




		GameEngineImage* LefeDownImage = GameEngineImageManager::GetInst()->Find("IG_GREEN_LEFT_DOWN.bmp");
		LefeDownImage->CutCount(1, 1);

		GameEngineImage* LefeUpImage = GameEngineImageManager::GetInst()->Find("IG_GREEN_LEFT_UP.bmp");
		LefeUpImage->CutCount(1, 1);

		GameEngineImage* LefeRightImage = GameEngineImageManager::GetInst()->Find("IG_GREEN_LEFT_RIGHT.bmp");
		LefeRightImage->CutCount(1, 1);

		GameEngineImage* LeftRightDownImage = GameEngineImageManager::GetInst()->Find("IG_GREEN_LEFT_RIGHT_DOWN.bmp");
		LeftRightDownImage->CutCount(1, 1);

		GameEngineImage* LeftRightUpImage = GameEngineImageManager::GetInst()->Find("IG_GREEN_LFET_RIGHT_UP.bmp");
		LeftRightUpImage->CutCount(1, 1);

		GameEngineImage* LeftRightUpDownImage = GameEngineImageManager::GetInst()->Find("IG_GREEN_LEFT_RIGHT_UP_DOWN.bmp");
		LeftRightUpDownImage->CutCount(1, 1);

		GameEngineImage* LeftUpDownImage = GameEngineImageManager::GetInst()->Find("IG_GREEN_LEFT_UP_DOWN.bmp");
		LeftUpDownImage->CutCount(1, 1);

		GameEngineImage* RightDownImage = GameEngineImageManager::GetInst()->Find("IG_GREEN_RIGHT_DOWN.bmp");
		RightDownImage->CutCount(1, 1);

		GameEngineImage* RightUPDownImage = GameEngineImageManager::GetInst()->Find("IG_GREEN_RIGHT_UP_DOWN.bmp");
		RightUPDownImage->CutCount(1, 1);

		GameEngineImage* UpDownImage = GameEngineImageManager::GetInst()->Find("IG_GREEN_UP_DOWN.bmp");
		UpDownImage->CutCount(1, 1);
	}

	{
		GameEngineImage* NomalImage = GameEngineImageManager::GetInst()->Find("IG_YELLOW_PUYO.bmp");
		NomalImage->CutCount(1, 1);

		GameEngineImage* CenterImage = GameEngineImageManager::GetInst()->Find("IG_YELLOW_CENTER.bmp");
		CenterImage->CutCount(2, 1);

		GameEngineImage* DestroyImage = GameEngineImageManager::GetInst()->Find("IG_YELLOW_DESTROY.bmp");
		DestroyImage->CutCount(6, 1);

		GameEngineImage* LandImage = GameEngineImageManager::GetInst()->Find("IG_YELLOW_LAND.bmp");
		LandImage->CutCount(4, 1);

		GameEngineImage* IdleImage = GameEngineImageManager::GetInst()->Find("IG_YELLOW_IDLE.bmp");
		IdleImage->CutCount(8, 1);

		GameEngineImage* IdleImage1 = GameEngineImageManager::GetInst()->Find("IG_YELLOW_IDLE1.bmp");
		IdleImage1->CutCount(3, 1);



		GameEngineImage* LeftImage = GameEngineImageManager::GetInst()->Find("IG_YELLOW_LEFT.bmp");
		LeftImage->CutCount(1, 1);

		GameEngineImage* RightImage = GameEngineImageManager::GetInst()->Find("IG_YELLOW_RIGHT.bmp");
		RightImage->CutCount(1, 1);

		GameEngineImage* UpImage = GameEngineImageManager::GetInst()->Find("IG_YELLOW_UP.bmp");
		UpImage->CutCount(1, 1);

		GameEngineImage* DownImage = GameEngineImageManager::GetInst()->Find("IG_YELLOW_DOWN.bmp");
		DownImage->CutCount(1, 1);


		GameEngineImage* LefeDownImage = GameEngineImageManager::GetInst()->Find("IG_YELLOW_LEFT_DOWN.bmp");
		LefeDownImage->CutCount(1, 1);

		GameEngineImage* LefeUpImage = GameEngineImageManager::GetInst()->Find("IG_YELLOW_LEFT_UP.bmp");
		LefeUpImage->CutCount(1, 1);

		GameEngineImage* LefeRightImage = GameEngineImageManager::GetInst()->Find("IG_YELLOW_LEFT_RIGHT.bmp");
		LefeRightImage->CutCount(1, 1);

		GameEngineImage* LeftRightDownImage = GameEngineImageManager::GetInst()->Find("IG_YELLOW_LEFT_RIGHT_DOWN.bmp");
		LeftRightDownImage->CutCount(1, 1);

		GameEngineImage* LeftRightUpImage = GameEngineImageManager::GetInst()->Find("IG_YELLOW_LEFT_RIGHT_UP.bmp");
		LeftRightUpImage->CutCount(1, 1);

		GameEngineImage* LeftRightUpDownImage = GameEngineImageManager::GetInst()->Find("IG_YELLOW_LEFT_RIGHT_UP_DOWN.bmp");
		LeftRightUpDownImage->CutCount(1, 1);

		GameEngineImage* LeftUpDownImage = GameEngineImageManager::GetInst()->Find("IG_YELLOW_LEFT_UP_DOWN.bmp");
		LeftUpDownImage->CutCount(1, 1);

		GameEngineImage* RightDownImage = GameEngineImageManager::GetInst()->Find("IG_YELLOW_RIGHT_DOWN.bmp");
		RightDownImage->CutCount(1, 1);

		GameEngineImage* RightUPDownImage = GameEngineImageManager::GetInst()->Find("IG_YELLOW_RIGHT_UP_DOWN.bmp");
		RightUPDownImage->CutCount(1, 1);

		GameEngineImage* UpDownImage = GameEngineImageManager::GetInst()->Find("IG_YELLOW_UP_DOWN.bmp");
		UpDownImage->CutCount(1, 1);
	}

	{
		GameEngineImage* NomalImage = GameEngineImageManager::GetInst()->Find("IG_PURPLE_PUYO.bmp");
		NomalImage->CutCount(1, 1);

		GameEngineImage* CenterImage = GameEngineImageManager::GetInst()->Find("IG_PURPLE_CENTER.bmp");
		CenterImage->CutCount(2, 1);

		GameEngineImage* DestroyImage = GameEngineImageManager::GetInst()->Find("IG_PURPLE_DESTROY.bmp");
		DestroyImage->CutCount(6, 1);

		GameEngineImage* LandImage = GameEngineImageManager::GetInst()->Find("IG_PURPLE_LAND.bmp");
		LandImage->CutCount(4, 1);

		GameEngineImage* IdleImage = GameEngineImageManager::GetInst()->Find("IG_PURPLE_IDLE.bmp");
		IdleImage->CutCount(5, 1);

		GameEngineImage* IdleImage1 = GameEngineImageManager::GetInst()->Find("IG_PURPLE_IDLE1.bmp");
		IdleImage1->CutCount(5, 1);


		GameEngineImage* LeftImage = GameEngineImageManager::GetInst()->Find("IG_PURPLE_LEFT.bmp");
		LeftImage->CutCount(1, 1);

		GameEngineImage* RightImage = GameEngineImageManager::GetInst()->Find("IG_PURPLE_RIGHT.bmp");
		RightImage->CutCount(1, 1);

		GameEngineImage* UpImage = GameEngineImageManager::GetInst()->Find("IG_PURPLE_UP.bmp");
		UpImage->CutCount(1, 1);

		GameEngineImage* DownImage = GameEngineImageManager::GetInst()->Find("IG_PURPLE_DOWN.bmp");
		DownImage->CutCount(1, 1);



		GameEngineImage* LefeDownImage = GameEngineImageManager::GetInst()->Find("IG_PURPLE_LEFT_DOWN.bmp");
		LefeDownImage->CutCount(1, 1);

		GameEngineImage* LefeUpImage = GameEngineImageManager::GetInst()->Find("IG_PURPLE_LEFT_UP.bmp");
		LefeUpImage->CutCount(1, 1);

		GameEngineImage* LefeRightImage = GameEngineImageManager::GetInst()->Find("IG_PURPLE_LEFT_RIGHT.bmp");
		LefeRightImage->CutCount(1, 1);

		GameEngineImage* LeftRightDownImage = GameEngineImageManager::GetInst()->Find("IG_PURPLE_LEFT_RIGHT_DOWN.bmp");
		LeftRightDownImage->CutCount(1, 1);

		GameEngineImage* LeftRightUpImage = GameEngineImageManager::GetInst()->Find("IG_PURPLE_LEFT_RIGHT_UP.bmp");
		LeftRightUpImage->CutCount(1, 1);

		GameEngineImage* LeftRightUpDownImage = GameEngineImageManager::GetInst()->Find("IG_PURPLE_LEFT_RIGHT_UP_DOWN.bmp");
		LeftRightUpDownImage->CutCount(1, 1);

		GameEngineImage* LeftUpDownImage = GameEngineImageManager::GetInst()->Find("IG_PURPLE_LEFT_UP_DOWN.bmp");
		LeftUpDownImage->CutCount(1, 1);

		GameEngineImage* RightDownImage = GameEngineImageManager::GetInst()->Find("IG_PURPLE_RIGHT_DOWN.bmp");
		RightDownImage->CutCount(1, 1);

		GameEngineImage* RightUPDownImage = GameEngineImageManager::GetInst()->Find("IG_PURPLE_RIGHT_UP_DOWN.bmp");
		RightUPDownImage->CutCount(1, 1);

		GameEngineImage* UpDownImage = GameEngineImageManager::GetInst()->Find("IG_PURPLE_UP_DOWN.bmp");
		UpDownImage->CutCount(1, 1);
	}

	GameEngineImage* HindrancePuyo = GameEngineImageManager::GetInst()->Find("IG_HINDRANCE_PUYO.bmp");
	HindrancePuyo->CutCount(1, 1);

	GameEngineImage* HindranceDestroy = GameEngineImageManager::GetInst()->Find("IG_HINDRANCE_PUYO_DESTROY.bmp");
	HindranceDestroy->CutCount(4, 1);

	GameEngineImage* HindranceIdle = GameEngineImageManager::GetInst()->Find("IG_HINDRANCE_PUYO_IDLE.bmp");
	HindranceIdle->CutCount(3, 1);

	GameEngineImage* OffsetStarImage = GameEngineImageManager::GetInst()->Find("IG_OffsetStar.bmp");
	OffsetStarImage->CutCount(5, 1);

}

void InGame::EnemyAnimatioInit()
{
	{
		GameEngineImage* Image = GameEngineImageManager::GetInst()->Find("IG_LV1_IDLE.bmp");
		Image->CutCount(4, 1);

		GameEngineImage* Image1 = GameEngineImageManager::GetInst()->Find("IG_LV1_LOSE.bmp");
		Image1->CutCount(4, 1);

		GameEngineImage* Image2 = GameEngineImageManager::GetInst()->Find("IG_LV1_EXCITED.bmp");
		Image2->CutCount(6, 1);

		GameEngineImage* Image3 = GameEngineImageManager::GetInst()->Find("IG_LV1_WIN.bmp");
		Image3->CutCount(1, 1);

		GameEngineImage* Image4 = GameEngineImageManager::GetInst()->Find("IG_LV1_DANGER.bmp");
		Image4->CutCount(4, 1);
	}

	{
		GameEngineImage* Image = GameEngineImageManager::GetInst()->Find("IG_LV2_IDLE.bmp");
		Image->CutCount(1, 1);

		GameEngineImage* Image1 = GameEngineImageManager::GetInst()->Find("IG_LV2_LOSE.bmp");
		Image1->CutCount(4, 1);

		GameEngineImage* Image2 = GameEngineImageManager::GetInst()->Find("IG_LV2_EXCITED.bmp");
		Image2->CutCount(1, 1);

		GameEngineImage* Image3 = GameEngineImageManager::GetInst()->Find("IG_LV2_WIN.bmp");
		Image3->CutCount(1, 1);

		GameEngineImage* Image4 = GameEngineImageManager::GetInst()->Find("IG_LV2_DANGER.bmp");
		Image4->CutCount(1, 1);
	}

	{
		GameEngineImage* Image = GameEngineImageManager::GetInst()->Find("IG_LV3_IDLE.bmp");
		Image->CutCount(4, 1);

		GameEngineImage* Image1 = GameEngineImageManager::GetInst()->Find("IG_LV3_LOSE.bmp");
		Image1->CutCount(4, 1);

		GameEngineImage* Image2 = GameEngineImageManager::GetInst()->Find("IG_LV3_EXCITED.bmp");
		Image2->CutCount(4, 1);

		GameEngineImage* Image3 = GameEngineImageManager::GetInst()->Find("IG_LV3_WIN.bmp");
		Image3->CutCount(2, 1);

		GameEngineImage* Image4 = GameEngineImageManager::GetInst()->Find("IG_LV3_DANGER.bmp");
		Image4->CutCount(4, 1);
	}

	{
		GameEngineImage* Image = GameEngineImageManager::GetInst()->Find("IG_LV4_IDLE.bmp");
		Image->CutCount(4, 1);

		GameEngineImage* Image1 = GameEngineImageManager::GetInst()->Find("IG_LV4_LOSE.bmp");
		Image1->CutCount(4, 1);

		GameEngineImage* Image2 = GameEngineImageManager::GetInst()->Find("IG_LV4_WIN.bmp");
		Image2->CutCount(1, 1);

		GameEngineImage* Image3 = GameEngineImageManager::GetInst()->Find("IG_LV4_EXCITED.bmp");
		Image3->CutCount(4, 1);

		GameEngineImage* Image4 = GameEngineImageManager::GetInst()->Find("IG_LV4_DANGER.bmp");
		Image4->CutCount(4, 1);
	}

	{
		GameEngineImage* Image = GameEngineImageManager::GetInst()->Find("IG_LV5_IDLE.bmp");
		Image->CutCount(11, 1);

		GameEngineImage* Image1 = GameEngineImageManager::GetInst()->Find("IG_LV5_LOSE.bmp");
		Image1->CutCount(3, 1);

		GameEngineImage* Image3 = GameEngineImageManager::GetInst()->Find("IG_LV5_WIN.bmp");
		Image3->CutCount(1, 1);
	}

	{
		GameEngineImage* Image = GameEngineImageManager::GetInst()->Find("IG_LV6_IDLE.bmp");
		Image->CutCount(4, 1);

		GameEngineImage* Image1 = GameEngineImageManager::GetInst()->Find("IG_LV6_LOSE.bmp");
		Image1->CutCount(4, 1);

		GameEngineImage* Image2 = GameEngineImageManager::GetInst()->Find("IG_LV6_WIN.bmp");
		Image2->CutCount(4, 1);

		GameEngineImage* Image3 = GameEngineImageManager::GetInst()->Find("IG_LV6_EXCITED.bmp");
		Image3->CutCount(4, 1);

		GameEngineImage* Image4 = GameEngineImageManager::GetInst()->Find("IG_LV6_DANGER.bmp");
		Image4->CutCount(4, 1);
	}

	{
		GameEngineImage* Image = GameEngineImageManager::GetInst()->Find("IG_LV7_IDLE.bmp");
		Image->CutCount(5, 1);

		GameEngineImage* Image1 = GameEngineImageManager::GetInst()->Find("IG_LV7_LOSE.bmp");
		Image1->CutCount(1, 1);

		GameEngineImage* Image2 = GameEngineImageManager::GetInst()->Find("IG_LV7_WIN.bmp");
		Image2->CutCount(4, 1);

		GameEngineImage* Image3 = GameEngineImageManager::GetInst()->Find("IG_LV7_DANGER.bmp");
		Image3->CutCount(4, 1);

		GameEngineImage* Image4 = GameEngineImageManager::GetInst()->Find("IG_LV7_EXCITED.bmp");
		Image4->CutCount(4, 1);
	}

	{
		GameEngineImage* Image = GameEngineImageManager::GetInst()->Find("IG_LV8_IDLE.bmp");
		Image->CutCount(4, 1);

		GameEngineImage* Image1 = GameEngineImageManager::GetInst()->Find("IG_LV8_LOSE.bmp");
		Image1->CutCount(4, 1);

		GameEngineImage* Image2 = GameEngineImageManager::GetInst()->Find("IG_LV8_WIN.bmp");
		Image2->CutCount(3, 1);

		GameEngineImage* Image3 = GameEngineImageManager::GetInst()->Find("IG_LV8_EXCITED.bmp");
		Image3->CutCount(3, 1);

		GameEngineImage* Image4 = GameEngineImageManager::GetInst()->Find("IG_LV8_DANGER.bmp");
		Image4->CutCount(4, 1);
	}
}

void InGame::CarbuncleAnimationInit()
{
	GameEngineImage* IdleImage = GameEngineImageManager::GetInst()->Find("IG_CARBUNCLE_IDLE.bmp");
	IdleImage->CutCount(2, 1);

	GameEngineImage* StartImage = GameEngineImageManager::GetInst()->Find("IG_CARBUNCLE_START.bmp");
	StartImage->CutCount(9, 1);

	Carbuncle_->GetMyRenderer()->CreateAnimation("IG_CARBUNCLE_IDLE.bmp", "IG_CARBUNCLE_IDLE", 0, 1, 0.1f, true);
	Carbuncle_->GetMyRenderer()->CreateAnimation("IG_CARBUNCLE_START.bmp", "IG_CARBUNCLE_START", 0, 8, 0.2f, false);
	Carbuncle_->GetMyRenderer()->ChangeAnimation("IG_CARBUNCLE_IDLE");


	for (size_t i = 0; i < 36; i++)
	{
		Stars_[i] = CreateActor<InGameActor>(0);
		Stars_[i]->SetPosition(Carbuncle_->GetPosition());
		Stars_[i]->SetMyRenderer(Stars_[i]->CreateRenderer("IG_CARBUNCLE_STAR.bmp"));
	}
}



void InGame::Update()
{
	CarbuncleUpdate();

	if (true == IsStart_)
	{
		SpewStar();
	}

	GameOverCheck();

	if (false == IsStateUp_)
	{
		StageAlpha_ += GameEngineTime::GetDeltaTime();

		StageRenderer_->SetPosition(float4::Lerp(StageRenderStartPos_, StageRenderEndPos_, StageAlpha_));

		if (1.f <= StageAlpha_)
		{
			StageAlpha_ = 0.f;
			IsStateUp_ = true;
		}
	}
}

void InGame::GameOverCheck()
{
	if (Player_->GetState() == PlayerState::Lose)
	{
		EnemyFSM_->SetState(EnemyState::Win);

		InGameBgm_.Stop();
		StateBottoms_[0]->SetMove(float4::DOWN * GameEngineTime::GetDeltaTime() * 300.f);
		ChangeCount_ -= GameEngineTime::GetDeltaTime();

		Alpha_ += GameEngineTime::GetDeltaTime() * 0.5f;

		if (1.f <= Alpha_)
		{
			Alpha_ = 1.f;
		}

		GameOverRenderer_->SetPosition(float4::Lerp(GameOverStartPos_, GameOverEndPos_, Alpha_));

		if (0 >= ChangeCount_)
		{
			FadeBackground_->FadeInOn();
			FadeBackground_->GetMyRenderer()->SetOrder(20);
			FadeBackground_->SetFadeSpeed(500.f);
		}

		if (true == FadeBackground_->GetIsInChange())
		{
			ChangeCount_ = 7.f;

			GameEngine::GetInst().ChangeLevel("GameOver");

			GameEngineLevel* NextLevel = GameEngine::GetNextLevel();
			GameOver* GameOver_ = dynamic_cast<GameOver*>(NextLevel);

			GameOver_->SetEnemyProfile(EnemyProfile_);
		}
	}

	else if (EnemyFSM_->GetState() == EnemyState::Lose)
	{
		WinRenderer_->GetMyRenderer()->SetOrder(10);
		Player_->SetState(PlayerState::Win);

		InGameBgm_.Stop();
		ChangeCount_ -= GameEngineTime::GetDeltaTime();
		StateBottoms_[1]->SetMove(float4::DOWN * GameEngineTime::GetDeltaTime() * 300.f);

		if (0 >= ChangeCount_)
		{
			FadeBackground_->FadeInOn();
			FadeBackground_->GetMyRenderer()->SetOrder(20);
			FadeBackground_->SetFadeSpeed(500.f);
		}

		if (true == FadeBackground_->GetIsInChange())
		{
			ChangeCount_ = 7.f;
			GameEngine::GetInst().ChangeLevel("EnemySelect");

			GameEngineLevel* NextLevel = GameEngine::GetNextLevel();
			EnemySelect* EnemySelect_ = dynamic_cast<EnemySelect*>(NextLevel);

			EnemySelect_->LockLoseEnemyIcon(EnemyProfile_->GetMyLevel());
		}
	}
}

void InGame::CarbuncleUpdate()
{
	if (false == IsStart_)
	{
		Carbuncle_->GetMyRenderer()->ChangeAnimation("IG_CARBUNCLE_START");
	}

	if (true == Carbuncle_->GetMyRenderer()->IsAnimationName("IG_CARBUNCLE_START")
		&& true == Carbuncle_->GetMyRenderer()->IsEndAnimation())
	{
		IsStart_ = true;

		for (int i = 0; i < 36; ++i)
		{
			Stars_[i]->GetMyRenderer()->SetOrder(10);
		}
		Carbuncle_->GetMyRenderer()->ChangeAnimation("IG_CARBUNCLE_IDLE");
	}
}

void InGame::SpewStar()
{
	float Speed = 1000.f;

	float4 Dir = float4::RadianToDirectionFloat4(0);
	Stars_[0]->SetMove(Dir * Speed * GameEngineTime::GetDeltaTime());

	Dir = float4::RadianToDirectionFloat4(0.2f);
	Stars_[1]->SetMove(Dir * Speed * 1.1f * GameEngineTime::GetDeltaTime());

	Dir = float4::RadianToDirectionFloat4(0.4f);
	Stars_[2]->SetMove(Dir * Speed * GameEngineTime::GetDeltaTime());

	Dir = float4::RadianToDirectionFloat4(0.6f);
	Stars_[3]->SetMove(Dir * Speed * 1.14f * GameEngineTime::GetDeltaTime());

	Dir = float4::RadianToDirectionFloat4(GameEngineMath::PIE / 4);
	Stars_[4]->SetMove(Dir * Speed * GameEngineTime::GetDeltaTime());

	Dir = float4::RadianToDirectionFloat4(1.0f);
	Stars_[5]->SetMove(Dir * Speed * GameEngineTime::GetDeltaTime());

	Dir = float4::RadianToDirectionFloat4(1.2f);
	Stars_[6]->SetMove(Dir * Speed * 0.95f * GameEngineTime::GetDeltaTime());

	Dir = float4::RadianToDirectionFloat4(1.4f);
	Stars_[7]->SetMove(Dir * Speed * 0.99f * GameEngineTime::GetDeltaTime());

	Dir = float4::RadianToDirectionFloat4(GameEngineMath::PIE / 2);
	Stars_[8]->SetMove(Dir * Speed * GameEngineTime::GetDeltaTime());

	Dir = float4::RadianToDirectionFloat4(1.8f);
	Stars_[9]->SetMove(Dir * Speed * 1.2f * GameEngineTime::GetDeltaTime());

	Dir = float4::RadianToDirectionFloat4(2.0f);
	Stars_[10]->SetMove(Dir * Speed * GameEngineTime::GetDeltaTime());

	Dir = float4::RadianToDirectionFloat4(2.2f);
	Stars_[11]->SetMove(Dir * Speed * GameEngineTime::GetDeltaTime());

	Dir = float4::RadianToDirectionFloat4((3 * GameEngineMath::PIE) / 4);
	Stars_[12]->SetMove(Dir * Speed * 0.99f * GameEngineTime::GetDeltaTime());

	Dir = float4::RadianToDirectionFloat4(2.5f);
	Stars_[13]->SetMove(Dir * Speed * GameEngineTime::GetDeltaTime());

	Dir = float4::RadianToDirectionFloat4(2.8f);
	Stars_[14]->SetMove(Dir * Speed * GameEngineTime::GetDeltaTime());

	Dir = float4::RadianToDirectionFloat4(3.0f);
	Stars_[15]->SetMove(Dir * Speed * 1.1f * GameEngineTime::GetDeltaTime());

	Dir = float4::RadianToDirectionFloat4(GameEngineMath::PIE);
	Stars_[16]->SetMove(Dir * Speed * GameEngineTime::GetDeltaTime());

	Dir = float4::RadianToDirectionFloat4(3.3f);
	Stars_[17]->SetMove(Dir * Speed * GameEngineTime::GetDeltaTime());

	Dir = float4::RadianToDirectionFloat4(3.5f);
	Stars_[18]->SetMove(Dir * Speed * 0.9f * GameEngineTime::GetDeltaTime());

	Dir = float4::RadianToDirectionFloat4((7 * GameEngineMath::PIE) / 6);
	Stars_[19]->SetMove(Dir * Speed * GameEngineTime::GetDeltaTime());

	Dir = float4::RadianToDirectionFloat4(3.8f);
	Stars_[20]->SetMove(Dir * Speed * 0.97f * GameEngineTime::GetDeltaTime());

	Dir = float4::RadianToDirectionFloat4((5 * GameEngineMath::PIE) / 4);
	Stars_[21]->SetMove(Dir * Speed * GameEngineTime::GetDeltaTime());

	Dir = float4::RadianToDirectionFloat4(4.1f);
	Stars_[22]->SetMove(Dir * Speed * GameEngineTime::GetDeltaTime());

	Dir = float4::RadianToDirectionFloat4((4 * GameEngineMath::PIE) / 3);
	Stars_[23]->SetMove(Dir * Speed * 1.12f * GameEngineTime::GetDeltaTime());

	Dir = float4::RadianToDirectionFloat4(4.4f);
	Stars_[24]->SetMove(Dir * Speed * 0.94f * GameEngineTime::GetDeltaTime());

	Dir = float4::RadianToDirectionFloat4(4.6f);
	Stars_[25]->SetMove(Dir * Speed * 0.99f * GameEngineTime::GetDeltaTime());

	Dir = float4::RadianToDirectionFloat4((3 * GameEngineMath::PIE) / 2);
	Stars_[26]->SetMove(Dir * Speed * 0.9f * GameEngineTime::GetDeltaTime());

	Dir = float4::RadianToDirectionFloat4(4.9f);
	Stars_[27]->SetMove(Dir * Speed * 1.1f * GameEngineTime::GetDeltaTime());

	Dir = float4::RadianToDirectionFloat4(5.1f);
	Stars_[28]->SetMove(Dir * Speed * GameEngineTime::GetDeltaTime());

	Dir = float4::RadianToDirectionFloat4((5 * GameEngineMath::PIE) / 3);
	Stars_[29]->SetMove(Dir * Speed * GameEngineTime::GetDeltaTime());

	Dir = float4::RadianToDirectionFloat4(5.4f);
	Stars_[30]->SetMove(Dir * Speed * GameEngineTime::GetDeltaTime());

	Dir = float4::RadianToDirectionFloat4((7 * GameEngineMath::PIE) / 4);
	Stars_[31]->SetMove(Dir * Speed * 1.2f * GameEngineTime::GetDeltaTime());

	Dir = float4::RadianToDirectionFloat4(5.65f);
	Stars_[32]->SetMove(Dir * Speed * 0.89f * GameEngineTime::GetDeltaTime());

	Dir = float4::RadianToDirectionFloat4((11 * GameEngineMath::PIE) / 6);
	Stars_[33]->SetMove(Dir * Speed * 1.15f * GameEngineTime::GetDeltaTime());

	Dir = float4::RadianToDirectionFloat4(5.9f);
	Stars_[34]->SetMove(Dir * Speed * 0.98f * GameEngineTime::GetDeltaTime());

	Dir = float4::RadianToDirectionFloat4(6.1f);
	Stars_[35]->SetMove(Dir * Speed * 1.1f * GameEngineTime::GetDeltaTime());

	for (int i = 0; i < 35; ++i)
	{
		if (GameEngineWindow::GetScale().x < Stars_[i]->GetPosition().x
			&& GameEngineWindow::GetScale().y < Stars_[i]->GetPosition().y)
		{
			Stars_[i]->Death();
		}
	}
}



void InGame::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	InGameBgm_ = GameEngineSound::SoundPlayControl("INGAME.mp3");

	EffectSound_.SoundPlayOneShot("ARLE_START.mp3");

	if (nullptr != _PrevLevel)
	{
		if ("EnemySelect" == _PrevLevel->GetNameConstRef())
		{
			GameEngineLevel* PrevLevel = _PrevLevel;
			EnemySelect* EnemySelect_ = dynamic_cast<EnemySelect*>(PrevLevel);
			EnemyProfile_ = EnemySelect_->GetEnemyProfile();
			EnemyProfile_->SetPosition({ GameEngineWindow::GetScale().Half() });

			EnemyFSM_->SetMyProfile(EnemyProfile_);
		}

		else if ("GameOver" == _PrevLevel->GetNameConstRef())
		{
			GameEngineLevel* PrevLevel = _PrevLevel;
			GameOver* GameOver_ = dynamic_cast<GameOver*>(PrevLevel);
			EnemyProfile_ = GameOver_->GetEnemyProfile();
			EnemyProfile_->SetPosition({ GameEngineWindow::GetScale().Half() });

			EnemyFSM_->SetMyProfile(EnemyProfile_);
		}
	}
}

void InGame::LevelChangeEnd(GameEngineLevel* _PrevLevel)
{
	ResetOn();
}

void InGame::UserResetEnd()
{
	StageClear_ = 0;
	ChangeCount_ = 10.f;
	Alpha_ = 0.f;
	IsStart_ = false;
	IsEnemyFlap_ = false;

	PuyoAnimationInit();
	InitPlayerEndEnemy();

	FadeBackground_ = CreateActor<FadeInOutBackground>();

	Stages_[0] = CreateActor<Stage>();

	Stages_[0]->SetPosition(GameEngineWindow::GetScale().Half());
	Stages_[0]->CreateRenderer("IG_STAGE1.bmp", 3);
	Stages_[0]->CreateRenderer("IG_STAGE1_BACK.bmp", 0);

	GameOverRenderer_ = CreateActor<InGameActor>();
	GameOverRenderer_->SetPosition({ 255, 1500 });
	GameOverRenderer_->CreateRenderer("IG_PLAYER_GAMEOVER.bmp");

	GameOverStartPos_ = GameOverRenderer_->GetPosition();
	GameOverEndPos_ = GameOverRenderer_->GetPosition() + float4{ 0, -1300.f };

	StateBottoms_[0] = CreateActor<InGameActor>();
	StateBottoms_[1] = CreateActor<InGameActor>();
	StateBottoms_[0]->SetMyRenderer(StateBottoms_[0]->CreateRenderer("IG_STAGE1_BOTTOM_LEFT.bmp", 3));
	StateBottoms_[1]->SetMyRenderer(StateBottoms_[1]->CreateRenderer("IG_STAGE1_BOTTOM_RIGHT.bmp", 3));

	StateBottoms_[0]->SetPosition({ GameEngineWindow::GetScale().Half() + float4{-384, 389} });
	StateBottoms_[1]->SetPosition({ GameEngineWindow::GetScale().Half() + float4{384, 389} });

	GameEngineActor* NextUi = CreateActor<Stage>(3);
	NextUi->CreateRenderer("IG_NEXT.bmp")->SetPivot({ GameEngineWindow::GetScale().Half().x, GameEngineWindow::GetScale().Half().y - 360.f });

	GameEngineActor* Stage1Ui = CreateActor<Stage>(3);
	Stage1Ui->CreateRenderer("IG_STAGE_UI.bmp")->SetPivot({ GameEngineWindow::GetScale().Half().x, GameEngineWindow::GetScale().Half().y - 60.f });

	GameEngineActor* PlayerName_ = CreateActor<Stage>(1);
	PlayerName_->CreateRenderer("IG_NAME_ARLE.bmp")->SetPivot({ GameEngineWindow::GetScale().Half().x - 96.f, GameEngineWindow::GetScale().Half().y - 290.f });

	Carbuncle_ = CreateActor<InGameActor>(6);
	Carbuncle_->SetPosition({ GameEngineWindow::GetScale().Half().x - 160.f, GameEngineWindow::GetScale().Half().y + 300.f });
	GameEngineRenderer* CarbuncleRenderer = Carbuncle_->CreateRenderer();
	Carbuncle_->SetMyRenderer(CarbuncleRenderer);

	CarbuncleAnimationInit();
}