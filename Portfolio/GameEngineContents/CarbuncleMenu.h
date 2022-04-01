#pragma once

// Ό³Έν :
class CarbuncleMenu
{
public:
	// constrcuter destructer
	CarbuncleMenu();
	~CarbuncleMenu();

	// delete Function
	CarbuncleMenu(const CarbuncleMenu& _Other) = delete;
	CarbuncleMenu(CarbuncleMenu&& _Other) noexcept = delete;
	CarbuncleMenu& operator=(const CarbuncleMenu& _Other) = delete;
	CarbuncleMenu& operator=(CarbuncleMenu&& _Other) noexcept = delete;

protected:

private:

};

