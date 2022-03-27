#pragma once

// Ό³Έν :
class Red_Puyo
{
public:
	// constrcuter destructer
	Red_Puyo();
	~Red_Puyo();

	// delete Function
	Red_Puyo(const Red_Puyo& _Other) = delete;
	Red_Puyo(Red_Puyo&& _Other) noexcept = delete;
	Red_Puyo& operator=(const Red_Puyo& _Other) = delete;
	Red_Puyo& operator=(Red_Puyo&& _Other) noexcept = delete;

protected:

private:

};

