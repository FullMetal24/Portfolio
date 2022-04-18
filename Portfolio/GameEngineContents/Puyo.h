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

	//郴何 谅钎 捞悼 包访 贸府
	inline bool GetLandiung()
	{
		return IsLanding_;
	}

	inline void SetLanding(bool _Land)
	{
		IsLanding_ = _Land;
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

	//局聪皋捞记 包访 贸府
	void RenderToLeft();
	void RenderToRight();
	void RenderToUp();
	void RenderToDown();

	void RenderToLeftRight(); 
	void RenderToLeftRightDown();
	void RenderToLefttUp(); 
	void RenderToLeftUpRight(); 
	void RenderToLeftUpDown();
	void RenderToLeftDown(); 
	
	void RenderToRightUp(); 
	void RenderToRightUpDown();
	void RenderToRightDown(); 
	
	void RenderToUpDown(); 
	void RenderToLeftRightUpDown();

	void RenderToDestroy();
	void RenderToLand();

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
};

