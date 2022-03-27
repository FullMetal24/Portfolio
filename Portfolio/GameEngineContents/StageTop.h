#pragma once

// Ό³Έν :
class StageTop
{
public:
	// constrcuter destructer
	StageTop();
	~StageTop();

	// delete Function
	StageTop(const StageTop& _Other) = delete;
	StageTop(StageTop&& _Other) noexcept = delete;
	StageTop& operator=(const StageTop& _Other) = delete;
	StageTop& operator=(StageTop&& _Other) noexcept = delete;

protected:

private:

};

