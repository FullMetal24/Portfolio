#pragma once
#include <map>
#include <string>
#include <GameEngineBase/GameEngineDebug.h>

class GameEngineLevel;
class GameEngineImage;

//�߻� Ŭ����
class GameEngine
{
public:
	GameEngine();
	~GameEngine();

	GameEngine(const GameEngine& _Other) = delete;
	GameEngine(GameEngine&& _Other) noexcept = delete;
	GameEngine& operator=(const GameEngine& _Other) = delete;
	GameEngine& operator=(GameEngine&& _Other) noexcept = delete;

	static inline GameEngineImage* BackBufferImage()
	{
		return BackBufferImage_; //����� ����
	}

	static HDC BackBufferDC();
		 
	virtual void GameInit() = 0;
	virtual void GameLoop() = 0;
	virtual void GameEnd() = 0;

	template<typename GameType>
	static void Start()
	{
		GameEngineDebug::LeakCheckOn();

		GameType UserGame;
		UserContents_ = &UserGame;
		WindowCreate();

		EngineEnd();
	}

	static GameEngine& GlobalEngine()
	{
		if (nullptr == UserContents_)
		{
			MsgBoxAssert("GEngine Error Engine is not Start");
		}

		return *UserContents_;
	}

	void ChangeLevel(const std::string& _Name); //�̰� �� �� ���� �־�� �ұ�?

protected:
	template<typename LevelType>
	void CreateLevel(const std::string& _Name)
	{
		LevelType* NewLevel = new LevelType();
		GameEngineLevel* Level = NewLevel; //���ӿ����� ���ӿ��������� �ε��Լ��� ȣ���� �� �ִ�(friend)
		NewLevel->SetName(_Name);
		Level->Loading(); 
		AllLevel_.insert(std::make_pair(_Name, NewLevel));
	}

private:
	static std::map<std::string, GameEngineLevel*> AllLevel_;
	static GameEngineLevel* CurrentLevel_;
	static GameEngineLevel* NextLevel_;
	static GameEngine* UserContents_;
	static GameEngineImage* BackBufferImage_;

	static void WindowCreate();

	//�Լ� �����͸� �ޱ� ���� �����Լ�
	static void EngineInit();
	static void EngineLoop();
	static void EngineEnd();
};