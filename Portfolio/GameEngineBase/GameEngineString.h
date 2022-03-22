#pragma once
#include <string>
#include <algorithm>

//��Ʈ���� ���õ� �Լ����� Ŭ����
class GameEngineString
{
public:
	static void ToUpper(std::string& _Text)
	{
		std::transform(_Text.begin(), _Text.end(), _Text.begin(), std::toupper);
	}

	static std::string ToUpperReturn(const std::string& _Text)
	{
		std::string NewText = _Text;

		std::transform(NewText.begin(), NewText.end(), NewText.begin(), std::toupper);

		return NewText;
	}


protected:

private:
	GameEngineString();
	~GameEngineString();

	GameEngineString(const GameEngineString& _Other) = delete;
	GameEngineString(GameEngineString&& _Other) noexcept = delete;
	GameEngineString& operator=(const GameEngineString& _Other) = delete;
	GameEngineString& operator=(GameEngineString&& _Other) noexcept = delete;

};

