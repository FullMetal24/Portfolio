#pragma once

// Ό³Έν :
class Carbuncle
{
public:
	// constrcuter destructer
	Carbuncle();
	~Carbuncle();

	// delete Function
	Carbuncle(const Carbuncle& _Other) = delete;
	Carbuncle(Carbuncle&& _Other) noexcept = delete;
	Carbuncle& operator=(const Carbuncle& _Other) = delete;
	Carbuncle& operator=(Carbuncle&& _Other) noexcept = delete;

protected:

private:

};

