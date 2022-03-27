#pragma once

// Ό³Έν :
class CharacterSelectWindow
{
public:
	// constrcuter destructer
	CharacterSelectWindow();
	~CharacterSelectWindow();

	// delete Function
	CharacterSelectWindow(const CharacterSelectWindow& _Other) = delete;
	CharacterSelectWindow(CharacterSelectWindow&& _Other) noexcept = delete;
	CharacterSelectWindow& operator=(const CharacterSelectWindow& _Other) = delete;
	CharacterSelectWindow& operator=(CharacterSelectWindow&& _Other) noexcept = delete;

protected:

private:

};

