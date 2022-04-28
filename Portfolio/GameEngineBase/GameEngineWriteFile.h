#pragma once

// Ό³Έν :
class GameEngineWriteFile
{
public:
	// constrcuter destructer
	GameEngineWriteFile();
	~GameEngineWriteFile();

	// delete Function
	GameEngineWriteFile(const GameEngineWriteFile& _Other) = delete;
	GameEngineWriteFile(GameEngineWriteFile&& _Other) noexcept = delete;
	GameEngineWriteFile& operator=(const GameEngineWriteFile& _Other) = delete;
	GameEngineWriteFile& operator=(GameEngineWriteFile&& _Other) noexcept = delete;

protected:

private:

};

