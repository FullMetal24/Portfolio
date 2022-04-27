#pragma once
#include <GameEngine/GameEngineActor.h>
#include "ContentsEnum.h"

class Player;
class EnemyFSM;
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
	inline bool GetLand()
	{
		return IsLand_;
	}

	inline void SetLand(bool _Land)
	{
		IsLand_ = _Land;
	}

	inline void SetFall(bool _Fall)
	{
		IsFall_ = _Fall;
	}

	inline bool GetFall()
	{
		return IsFall_;
	}

	inline void SetLandPlay(bool _IsPlay)
	{
		IsLandPlay_ = _IsPlay;
	}

	inline bool GetLandPlay()
	{
		return IsLandPlay_;
	}

	inline bool GetDestroy()
	{
		return IsDestroy_;
	}

	inline float4 GetIndex()
	{
		return float4(static_cast<float>(X_), static_cast<float>(Y_));
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

	void SetIndex(int _X, int _Y);
	void InitAllAnimation();
	void SetColorImage(PuyoColor _Color);

	void ChangeState(PuyoState _State);

	void Init(Player* _Player, int x, int y, PuyoColor _Color);
	void Init(EnemyFSM* _Enemy, int x, int y, PuyoColor _Color);
	void CoordinateMove(Player* _Player, int x, int y);
	void CoordinateMove(EnemyFSM* _Enemy, int x, int y);
	float4 CoordinatePos(Player* _Player, int x, int y);
	float4 CoordinatePos(EnemyFSM* _Enemy, int x, int y);

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

	inline void ResetConnect()
	{
		IsConnect_[0] = false;
		IsConnect_[1] = false;
		IsConnect_[2] = false;
		IsConnect_[3] = false;
	}

	inline void SetDir(PuyoDir _Dir)
	{
		CurDir_ = _Dir;
	}

	inline PuyoState GetState()
	{
		return PuyoState_;
	}

	//이동 관련 함수
	Puyo* LeftPuyo(Puyo* Map[15][6], Puyo* _Other);
	Puyo* RightPuyo(Puyo* Map[15][6], Puyo* _Other);
	Puyo* DownPuyo(Puyo* Map[15][6], Puyo* _Other);
	Puyo* RotatePuyo(Puyo* Map[15][6], Puyo* _Center);
	void LandPuyo(Puyo* Map[15][6], Puyo* _Other);
	void AloneFallPuyo(Puyo* Map[15][6]);
	void FallPuyo(Puyo* Map[15][6], Player* _Player);
	void FallPuyo(Puyo* Map[15][6], EnemyFSM* _Enemy);
	float4 LerpPuyo(float4 A, float4 B, float Alpha);

	//애니메이션 관련 처리
	void RenderToNormal();
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
	void RenderToLand();

	void RenderToIdle();
	void RenderToOtherIdle();

	void LandAnimation();
	void LandToNormal();

	void SelfDestroy();

	void InitAnimation(PuyoColor color);
	void LinkedPuyoAnimtaion(Puyo* Map[15][6]);
	int GradeLinkAnimation(Puyo* Map[15][6]);

protected:

private:
	PuyoState PuyoState_;

	GameEngineRenderer* MyRenderer_;
	Player* Player_;
	EnemyFSM* Enemy_;

	PuyoColor MyColor_;
	PuyoDir CurDir_;
	int X_;
	int Y_;

	int OffsetX_;

	float4 StartPos_;
	float4 EndPos_;
	float Alpha_;

	bool IsLandPlay_;
	bool IsLand_;
	bool IsVisited_;
	bool IsDestroy_;
	bool IsFall_;

	//상하좌우
	bool IsConnect_[4];

};