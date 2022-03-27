#pragma once
#include "GameEnginePath.h"

class GameEngineFile;
class GameEngineDirectory : public GameEnginePath
{
public:
	GameEngineDirectory();
	~GameEngineDirectory();

	GameEngineDirectory(const GameEngineDirectory& _Other) = delete;
	GameEngineDirectory(GameEngineDirectory&& _Other) noexcept = delete;
	GameEngineDirectory& operator=(const GameEngineDirectory& _Other) = delete;
	GameEngineDirectory& operator=(GameEngineDirectory&& _Other) noexcept = delete;

	void MoveParent();
	void MoveParent(const std::string& _Name);

	bool IsRoot();

	void Move(const std::string& _Nam);

	std::vector<GameEngineFile> GetAllFile(const std::string _Ext = "");

protected:


private:

};

