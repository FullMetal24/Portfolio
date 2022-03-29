#include "GameEngineRenderer.h"
#include "GameEngineImageManager.h"
#include <GameEngineBase/GameEngineDebug.h>
#include "GameEngine.h"
#include <GameEngineBase/GameEngineTime.h>

#pragma comment(lib, "msimg32.lib")

GameEngineRenderer::GameEngineRenderer()
	: Image_(nullptr)
	, PivotType_(RenderPivot::CENTER)
	, ScaleMode_(RenderScaleMode::Image)
	, TransColor_(RGB(255, 0, 255))
{
}

GameEngineRenderer::~GameEngineRenderer() 
{
}


void GameEngineRenderer::SetImageScale()
{
	if (nullptr == Image_)
	{
		MsgBoxAssert("�������� �ʴ� �̹����� ũ�⸦ �����Ϸ��� �߽��ϴ�.");
		return;
	}

	ScaleMode_ = RenderScaleMode::Image;
	RenderScale_ = Image_->GetScale(); //�̹��� ũ���� ũ�� ����
	RenderImageScale_ = Image_->GetScale();
}


void GameEngineRenderer::SetImage(const std::string& _Name)
{
	GameEngineImage* FindeImage = GameEngineImageManager::GetInst()->Find(_Name);

	if (nullptr == FindeImage)
	{
		MsgBoxAssertString(_Name + "�������� �ʴ� �̹����� �������� �����Ϸ��� �߽��ϴ�.");
		return;
	}

	Image_ = FindeImage;
	SetImageScale();
}


void GameEngineRenderer::Render()
{
	if (nullptr != CurrentAnimation_)
	{
		CurrentAnimation_->Update(); //�ִϸ��̼� ���
	}

	if (nullptr == Image_)
	{
		MsgBoxAssert("�������� �̹����� ���õǾ� ���� ������ �������� �ȵ˴ϴ�.");
		return;
	}
	
	float4 RenderPos = GetActor()->GetPosition() + RenderPivot_;

	switch (PivotType_)
	{
		case RenderPivot::CENTER:
			GameEngine::BackBufferImage()->TransCopy(Image_, RenderPos - RenderScale_.Half(), RenderScale_, RenderImagePivot_, RenderImageScale_, TransColor_);
			break;												
		case RenderPivot::BOT:									
			//GameEngine::BackBufferImage()->TransCopyCenterScale(Image_, RenderPos, RenderScale_, TransColor_);
			break;
		default:
			break;
	}
}

void GameEngineRenderer::SetIndex(size_t _Index, float4 _Scale)
{
	if (false == Image_->IsCut())
	{
		MsgBoxAssert("�̹����� �κ������� ����� �� �ְ� �߷����� ���� �̹����Դϴ�.");
		return;
	}

	RenderImagePivot_ = Image_->GetCutPivot(_Index);

	if (-1.0f == _Scale.x || -1.0f == _Scale.y)
	{
		RenderScale_ = Image_->GetCutScale(_Index);
	}

	else //�ڸ� ũ�� �״�� ������ ���ص� ��
	{
		RenderScale_ = _Scale; //�� ũ��
	}

	RenderImageScale_ = Image_->GetCutScale(_Index);

}


//�ִϸ��̼�

void GameEngineRenderer::CreateAnimation(const std::string& _Image, const std::string& _Name, int _StartIndex, int _EndIndex, float _InterTime, bool _Loop)
{
	GameEngineImage* FindeImage = GameEngineImageManager::GetInst()->Find(_Image);

	if (nullptr == FindeImage)
	{
		MsgBoxAssert("�����ϴ� �̹����� �ִϸ��̼��� ������� �߽��ϴ�.");
		return;
	}

	if (Animations_.end() != Animations_.find(_Name))
	{
		MsgBoxAssert("�̹� �����ϴ� �ִϸ��̼��� �� ������� �߽��ϴ�.");
		return;
	}

	FrameAnimation& NewAnimation =Animations_[_Name];

	NewAnimation.Renderer = this;
	NewAnimation._Image = FindeImage;
	NewAnimation.CurrentFrame_ = _StartIndex;
	NewAnimation.StartFrame_ = _StartIndex;
	NewAnimation.EndFrame_ = _EndIndex;
	NewAnimation.CurrentInterTime_ = _InterTime;
	NewAnimation.InterTime_ = _InterTime;
	NewAnimation.Loop_ = _Loop;
}

void GameEngineRenderer::ChangeAnimation(const std::string& _Name)
{
	std::map<std::string, FrameAnimation>::iterator FindIter = Animations_.find(_Name);

	if (Animations_.end() == FindIter)
	{
		MsgBoxAssert("�������� �ʴ� �ִϸ��̼��� ü�����Ϸ��� �߽��ϴ�.");
		return;
	}

	CurrentAnimation_ = &FindIter->second;

}

void GameEngineRenderer::FrameAnimation::Update()
{
	CurrentInterTime_ -= GameEngineTime::GetDeltaTime();

	if (0 >= CurrentInterTime_)	
	{
		CurrentInterTime_ = InterTime_;
		++CurrentFrame_;

		if (EndFrame_ < CurrentFrame_)
		{
			if (true == Loop_)
			{
				CurrentFrame_ = StartFrame_;
			}

			else
			{
				CurrentFrame_ = EndFrame_;
			}
		}
	}

	Renderer->Image_ = _Image;
	Renderer->SetIndex(CurrentFrame_);

}



