#pragma once
#include <GameEngine/GameEngineActor.h>
#include "ContentsEnum.h"


class Puyo : public GameEngineActor
{

public:
	Puyo();
	~Puyo();

	Puyo(const Puyo& _Other) = delete;
	Puyo(Puyo&& _Other) noexcept = delete;
	Puyo& operator=(const Puyo& _Other) = delete;
	Puyo& operator=(Puyo&& _Other) noexcept = delete;

	void Start() override;
	void Update() override;

	//내부 좌표 이동 관련 처리
	inline bool GetLanding()
	{
		return IsLanding_;
	}

	inline void SetLanding(bool _Land)
	{
		IsLanding_ = _Land;
	}

	inline bool GetLandPlay()
	{
		return IsLandPlay_;
	}

	inline void SetDestroy(bool _IsDestroy)
	{
		IsDestroy_ = _IsDestroy;
	}

	inline bool GetDestroy()
	{
		return IsDestroy_;
	}

	inline int GetX()
	{
		return X_;
	}

	inline int GetY()
	{
		return Y_;
	}

	inline void SetX(int _X)
	{
		X_ = _X;
	}

	inline void SetY(int _Y)
	{
		Y_ = _Y;
	}

	inline GameEngineRenderer* GetMyRenderer()
	{
		return MyRenderer_;
	}

	inline void SetMyRenderer(GameEngineRenderer* _Renderer)
	{
		MyRenderer_ = _Renderer;
	}

	inline void SetColor(PuyoColor _Color)
	{
		MyColor_ = _Color;
	}

	inline PuyoColor GetColor()
	{
		return MyColor_;
	}

	inline void Visit()
	{
		IsVisited_ = true;
	}

	inline void Exit()
	{
		IsVisited_ = false;
	}

	inline bool GetVisited()
	{
		return IsVisited_;
	}

	inline bool* GetConnect()
	{
		return IsConnect_;
	}

	inline void SetConnect(int _Index, bool _Value)
	{
		if (4 <= _Index)
		{
			return;
		}

		IsConnect_[_Index] = _Value;
	}

	void RenderToNormal();

	//애니메이션 관련 처리
	void RenderToLeft();
	void RenderToRight();
	void RenderToUp();
	void RenderToDown();

	void RenderToLeftRight(); 
	void RenderToLeftRightDown();
	void RenderToLefttUp(); 
	void RenderToLeftRightUp(); 
	void RenderToLeftUpDown();
	void RenderToLeftDown(); 
	
	void RenderToRightUp(); 
	void RenderToRightUpDown();
	void RenderToRightDown(); 
	
	void RenderToUpDown(); 
	void RenderToLeftRightUpDown();

	void RenderToDestroy();
	//void RenderToLand();

	void RenderToIdle();
	void RenderToOtherIdle();

	void LandAnimation();
	void LandToNormal();

protected:

private:
	GameEngineRenderer* MyRenderer_;

	PuyoColor MyColor_;
	int X_;
	int Y_;

	bool IsLandPlay_;
	bool IsLanding_;
	bool IsVisited_;
	bool IsDestroy_;

	//연결 상태 확인
	bool IsConnect_[4];
};

