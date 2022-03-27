#pragma once
#include <map>
#include <string>
#include <Windows.h>

// ���� :
class GameEngineInput
{
private:
	static GameEngineInput* Inst_;

public:
	static GameEngineInput* GetInst()
	{
		return Inst_;
	}

	static void Destroy()
	{
		if (nullptr != Inst_)
		{
			delete Inst_;
			Inst_ = nullptr;
		}
	}

	void CreateKey(const std::string& _Name, int _Key);
	void Update();

	bool IsDown(const std::string& _Name);
	bool IsPress(const std::string& _Name);
	bool IsUp(const std::string& _Name);
	bool IsFree(const std::string& _Name);

	bool IsKey(const std::string& _Name);

private:
	class GameEngineKey
	{
		friend GameEngineInput;

		bool Down_; //���� �Է�
		bool Press_; //��� �Է�
		bool Up_; //�Է� �ߴ�
		bool Free_; //�Է� ����

		int Key_;

		bool KeyCheck()
		{
			return 0 != GetAsyncKeyState(Key_);
		}

		void Update();

		void Reset()
		{
			Down_ = false;
			Press_ = false;
			Up_ = false;
			Free_ = true;
		}

	public:
		GameEngineKey()
			: Down_(false)
			, Press_(false)
			, Up_(false)
			, Free_(true)
			, Key_(0)
		{
		}
	};

protected:

private:
	//���� �����Ҵ��� �ʿ������ ����
	std::map<std::string, GameEngineKey> AllInputKey_;

	GameEngineInput();
	~GameEngineInput();

	GameEngineInput(const GameEngineInput& _Other) = delete;
	GameEngineInput(GameEngineInput&& _Other) noexcept = delete;
	GameEngineInput& operator=(const GameEngineInput& _Other) = delete;
	GameEngineInput& operator=(GameEngineInput&& _Other) noexcept = delete;

};

