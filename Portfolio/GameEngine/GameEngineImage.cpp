#include "GameEngineImage.h"
#include "GameEngineBase/GameEngineDebug.h"
#include <GameEngineBase/GameEngineWindow.h>

GameEngineImage::GameEngineImage()
	: ImageDC_(nullptr)
	, BitMap_(nullptr)
	, OldBitMap_(nullptr)
	, Info_{0}
{
}

GameEngineImage::~GameEngineImage() 
{
	if (nullptr != BitMap_)
	{
		DeleteObject(BitMap_);
		BitMap_ = nullptr;
	}

	if (nullptr != OldBitMap_)
	{
		DeleteObject(OldBitMap_);
		OldBitMap_ = nullptr;
	}

	if (nullptr != ImageDC_)
	{
		DeleteDC(ImageDC_);
		ImageDC_ = nullptr;
	}
}

bool GameEngineImage::Create(HDC _DC)
{
	ImageDC_ = _DC;
	ImageScaleCheck();
	return true;
}

bool GameEngineImage::Load(const std::string& _Path)
{
	BitMap_ = static_cast<HBITMAP>(LoadImageA(nullptr, _Path.c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE));

	if (nullptr == BitMap_)
	{
		MsgBoxAssertString(_Path + "�̹��� �ε�� �����߽��ϴ�. �������� ��������� ���� 1. ��δ� ����� �Ƴ���? 2. ������� ����� �ó���?");
	}

	ImageDC_ = CreateCompatibleDC(nullptr);

	if (nullptr == ImageDC_)
	{
		MsgBoxAssert("ImageDC ������ �����߽��ϴ�.");
	}

	//�� DC�� �پ��ִ� ��Ʈ���� �̰ɷ� �ٲ���.
	OldBitMap_ = (HBITMAP)SelectObject(ImageDC_, BitMap_);

	ImageScaleCheck();

	return true;
}

bool GameEngineImage::Create(float4 _Scale)
{
	if (true == _Scale.IsZero2D())
	{
		MsgBoxAssert("ũ�Ⱑ 0�� �̹����� �����Ϸ��� �߽��ϴ�.");
		return false;
	}	

	//�̹��� ũ�⸸�� ��Ʈ�� �����
	BitMap_ = CreateCompatibleBitmap(GameEngineWindow::GetHDC(), _Scale.ix(), _Scale.iy());

	ImageDC_ = CreateCompatibleDC(nullptr);

	if (nullptr == ImageDC_)
	{
		MsgBoxAssert("ImageDC ������ �����߽��ϴ�.");
	}

	//�� DC�� �پ��ִ� ��Ʈ���� �̰ɷ� �ٲ���.
	OldBitMap_ = (HBITMAP)SelectObject(ImageDC_, BitMap_);

	ImageScaleCheck();

	return true;
}


void GameEngineImage::BitCopy(GameEngineImage* _Other)
{
	//�������� ��Ʈ�� �������� �˾Ƴ�
	BitCopy(_Other, { 0, 0 }, { 0, 0 }, _Other->GetScale());
}

void GameEngineImage::BitCopy(GameEngineImage* _Other, const float4& _CopyPos)
{
	BitCopy(_Other, _CopyPos, float4{ 0, 0 }, _Other->GetScale());
}

void GameEngineImage::BitCopyCenter(GameEngineImage* _Other, const float4& _CopyPos)
{
	BitCopy(_Other, _CopyPos - _Other->GetScale().Half(), float4{0, 0}, _Other->GetScale());
}

void GameEngineImage::BitCopyCenterPivot(GameEngineImage* _Other, const float4& _CopyPos, const float4& _CopyPivot)
{
	BitCopy(_Other, _CopyPos - _Other->GetScale().Half() + _CopyPivot, float4{ 0, 0 }, _Other->GetScale());
}

void GameEngineImage::BitCopyBot(GameEngineImage* _Other, const float4& _CopyPos)
{
	float4 ImagePivot = _Other->GetScale().Half();
	ImagePivot.y = _Other->GetScale().y;

	BitCopy(_Other, _CopyPos - ImagePivot, float4{ 0, 0 }, _Other->GetScale());
}

void GameEngineImage::BitCopyBotPivot(GameEngineImage* _Other, const float4& _CopyPos, const float4& _CopyPivot)
{
	float4 ImagePivot = _Other->GetScale().Half();
	ImagePivot.y = _Other->GetScale().y;

	BitCopy(_Other, _CopyPos - ImagePivot + _CopyPivot, float4{ 0, 0 }, _Other->GetScale());
}

void GameEngineImage::BitCopy(GameEngineImage* _Other, const float4& _CopyPos, const float4& _OtherPivot, const float4& _OtherPivotScale)
{
	// �����쿡�� �������ִ� �Ϲ����� dc vs dc�� �����Լ��Դϴ�.
	BitBlt(
		ImageDC_, // ���⿡ �����ض�.
		_CopyPos.ix(), // �� �̹����� �� �κ� x
		_CopyPos.iy(), // �� �̹����� �� �κ� y �� �����ض�
		_OtherPivotScale.ix(), // �� �̹����� �� ũ�⸸ŭ x
		_OtherPivotScale.iy(), // �� �̹����� �� ũ�⸸ŭ y
		_Other->ImageDC_, // �����Ϸ��� �����
		_OtherPivot.ix(), // �����Ϸ��� ����� ������X
		_OtherPivot.iy(),// �����Ϸ��� ����� ������Y
		SRCCOPY // �����϶�� ���
	);
}

void GameEngineImage::ImageScaleCheck()
{
	HBITMAP CurrentBitMap = (HBITMAP)GetCurrentObject(ImageDC_, OBJ_BITMAP);
	GetObject(BitMap_, sizeof(BITMAP), &Info_);
}

