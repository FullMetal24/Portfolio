#include "GameEngineImage.h"
#include "GameEngineBase/GameEngineDebug.h"
#include <GameEngineBase/GameEngineWindow.h>

GameEngineImage::GameEngineImage()
	: ImageDC_(nullptr)
{
}

GameEngineImage::~GameEngineImage() 
{
}

bool GameEngineImage::Create(float4 _Scale)
{
	if (true == _Scale.IsZero2D())
	{
		MsgBoxAssert("크기가 0인 이미지를 제작하려고 했습니다.");
		return false;
	}	

	//이미지 크기만한 비트맵 만들기
	BitMap_ = CreateCompatibleBitmap(GameEngineWindow::GetHDC(), _Scale.ix(), _Scale.iy());

	ImageDC_ = CreateCompatibleDC(nullptr);

	if (nullptr == ImageDC_)
	{
		MsgBoxAssert("ImageDC 생성에 실패했습니다.");
	}

	//이 DC에 붙어있는 비트맵을 이걸로 바꿔줘.
	OldBitMap_ = (HBITMAP)SelectObject(ImageDC_, BitMap_);

	ImageScaleCheck();

	return true;
}

void GameEngineImage::ImageScaleCheck()
{
	GetObject(BitMap_, sizeof(BITMAP), &Info_);
}

