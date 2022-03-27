#pragma once

// Ό³Έν :
class YellowLightning
{
public:
	// constrcuter destructer
	YellowLightning();
	~YellowLightning();

	// delete Function
	YellowLightning(const YellowLightning& _Other) = delete;
	YellowLightning(YellowLightning&& _Other) noexcept = delete;
	YellowLightning& operator=(const YellowLightning& _Other) = delete;
	YellowLightning& operator=(YellowLightning&& _Other) noexcept = delete;

protected:

private:

};

