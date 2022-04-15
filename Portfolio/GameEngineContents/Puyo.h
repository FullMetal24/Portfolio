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

	//진짜 움직임은 SetMove에서 

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

	void RenderToLand();
	void RenderToDestroy();

	void RenderToIdle();
	void RenderToOtherIdle();




protected:

private:
	GameEngineRenderer* MyRenderer_;

	PuyoColor MyColor_;
	bool IsVisited_;
	int X_;
	int Y_;

	bool IsLanding_;

	//색
	//뿌요페어를 알아선 안됨
	//하지만 뿌요벡터는 알아야 한다.

};

