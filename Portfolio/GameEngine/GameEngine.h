#pragma once
#include <map>
#include <string>
#include <GameEngineBase/GameEngineDebug.h>

class GameEngineLevel;
class GameEngineImage;

//추상 클래스
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
		return BackBufferImage_; //백버퍼 전달
	}

	static HDC BackBufferDC();

	//내가 만든 함수
	static GameEngineLevel* GetCurrentLevel()
	{
		return CurrentLevel_;
	}

	static GameEngineLevel* GetNextLevel()
	{
		return NextLevel_;
	}
		 
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

	static GameEngine& GetInst()
	{
		if (nullptr == UserContents_)
		{
			MsgBoxAssert("GEngine Error Engine is not Start");
		}

		return *UserContents_;
	}

	void ChangeLevel(const std::string& _Name);

protected:
	template<typename LevelType>
	void CreateLevel(const std::string& _Name)
	{
		LevelType* NewLevel = new LevelType();
		GameEngineLevel* Level = NewLevel; //게임엔진은 게임엔진레벌의 로딩함수를 호출할 수 있다(friend)
		NewLevel->SetName(_Name);
		Level->Loading(); 
		AllLevel_.insert(std::make_pair(_Name, NewLevel));
	}

private:
	static std::map<std::string, GameEngineLevel*> AllLevel_;
	static GameEngineLevel* CurrentLevel_;
	static GameEngineLevel* NextLevel_;
	static GameEngine* UserContents_;

	static GameEngineImage* WindowMainImage_; // 그려지면 화면에 진짜 나오게 되는 이미지
	static GameEngineImage* BackBufferImage_; // 깜빡임을 해결하려고 버퍼로 사용하는 이미지

	static void WindowCreate();

	//함수 포인터를 받기 위한 전역함수
	static void EngineInit();
	static void EngineLoop();
	static void EngineEnd();
};