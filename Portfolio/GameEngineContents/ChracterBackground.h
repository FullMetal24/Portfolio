#pragma once

// Ό³Έν :
class ChracterBackground
{
public:
	// constrcuter destructer
	ChracterBackground();
	~ChracterBackground();

	// delete Function
	ChracterBackground(const ChracterBackground& _Other) = delete;
	ChracterBackground(ChracterBackground&& _Other) noexcept = delete;
	ChracterBackground& operator=(const ChracterBackground& _Other) = delete;
	ChracterBackground& operator=(ChracterBackground&& _Other) noexcept = delete;

protected:

private:

};

