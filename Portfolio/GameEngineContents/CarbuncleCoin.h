#pragma once

// Ό³Έν :
class CarbuncleCoin
{
public:
	// constrcuter destructer
	CarbuncleCoin();
	~CarbuncleCoin();

	// delete Function
	CarbuncleCoin(const CarbuncleCoin& _Other) = delete;
	CarbuncleCoin(CarbuncleCoin&& _Other) noexcept = delete;
	CarbuncleCoin& operator=(const CarbuncleCoin& _Other) = delete;
	CarbuncleCoin& operator=(CarbuncleCoin&& _Other) noexcept = delete;

protected:

private:

};

