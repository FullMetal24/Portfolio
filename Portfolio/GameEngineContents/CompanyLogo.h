#pragma once
#include <GameEngine/GameEngineActor.h>


class CompanyLogo : public GameEngineActor
{
public:
	// constrcuter destructer
	CompanyLogo();
	~CompanyLogo();

	// delete Function
	CompanyLogo(const CompanyLogo& _Other) = delete;
	CompanyLogo(CompanyLogo&& _Other) noexcept = delete;
	CompanyLogo& operator=(const CompanyLogo& _Other) = delete;
	CompanyLogo& operator=(CompanyLogo&& _Other) noexcept = delete;

	void Start() override;
	void Update() override;
	void Render() override;


protected:

private:

};

