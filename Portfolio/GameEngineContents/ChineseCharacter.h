#pragma once

// Ό³Έν :
class ChineseCharacter
{
public:
	// constrcuter destructer
	ChineseCharacter();
	~ChineseCharacter();

	// delete Function
	ChineseCharacter(const ChineseCharacter& _Other) = delete;
	ChineseCharacter(ChineseCharacter&& _Other) noexcept = delete;
	ChineseCharacter& operator=(const ChineseCharacter& _Other) = delete;
	ChineseCharacter& operator=(ChineseCharacter&& _Other) noexcept = delete;

protected:

private:

};

