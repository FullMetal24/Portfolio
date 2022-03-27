#pragma once

// Ό³Έν :
class Menus
{
public:
	// constrcuter destructer
	Menus();
	~Menus();

	// delete Function
	Menus(const Menus& _Other) = delete;
	Menus(Menus&& _Other) noexcept = delete;
	Menus& operator=(const Menus& _Other) = delete;
	Menus& operator=(Menus&& _Other) noexcept = delete;

protected:

private:

};

