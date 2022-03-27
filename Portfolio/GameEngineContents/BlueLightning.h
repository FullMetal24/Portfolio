#pragma once
#include "GameEngine/GameEngineActor.h"

class BlueLightning : public GameEngineActor
{
public:
	// constrcuter destructer
	BlueLightning();
	~BlueLightning();

	// delete Function
	BlueLightning(const BlueLightning& _Other) = delete;
	BlueLightning(BlueLightning&& _Other) noexcept = delete;
	BlueLightning& operator=(const BlueLightning& _Other) = delete;
	BlueLightning& operator=(BlueLightning&& _Other) noexcept = delete;

	void Start() override;
	void Update() override;
	void Render() override;


protected:

private:

};

