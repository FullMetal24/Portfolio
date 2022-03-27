#include "GameEngineRenderer.h"
#include "GameEngineImageManager.h"
#include <GameEngineBase/GameEngineDebug.h>
#include "GameEngine.h"


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
}


void GameEngineRenderer::Render()
{
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

void GameEngineRenderer::SetIndex(size_t _Index)
{
	if (false == Image_->IsCut())
	{
		MsgBoxAssert("�̹����� �κ������� ����� �� �ְ� �߷����� ���� �̹����Դϴ�.");
		return;
	}

	RenderImagePivot_ = Image_->GetCutPivot(_Index);
	RenderScale_ = Image_->GetCutScale(_Index);
	RenderImageScale_ = Image_->GetCutScale(_Index);

}
