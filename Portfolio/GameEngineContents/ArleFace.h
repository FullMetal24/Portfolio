#pragma once

// Ό³Έν :
class ArleFace
{
public:
	// constrcuter destructer
	ArleFace();
	~ArleFace();

	// delete Function
	ArleFace(const ArleFace& _Other) = delete;
	ArleFace(ArleFace&& _Other) noexcept = delete;
	ArleFace& operator=(const ArleFace& _Other) = delete;
	ArleFace& operator=(ArleFace&& _Other) noexcept = delete;

protected:

private:

};

