#pragma once

// Ό³Έν :
class GameEngineReadFile
{
public:
	// constrcuter destructer
	GameEngineReadFile();
	~GameEngineReadFile();

	// delete Function
	GameEngineReadFile(const GameEngineReadFile& _Other) = delete;
	GameEngineReadFile(GameEngineReadFile&& _Other) noexcept = delete;
	GameEngineReadFile& operator=(const GameEngineReadFile& _Other) = delete;
	GameEngineReadFile& operator=(GameEngineReadFile&& _Other) noexcept = delete;

protected:

private:

};

