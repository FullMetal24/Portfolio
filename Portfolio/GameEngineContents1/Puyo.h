#pragma once
#include "GameEngine/GameEngineActor.h"

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
	void Render() override;

protected:

private:


};

