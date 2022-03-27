#include "GameEnginePath.h"

GameEnginePath::GameEnginePath() 
{
}

GameEnginePath::GameEnginePath(const std::filesystem::path& _Path)
	: Path_(_Path)
{

}

GameEnginePath::~GameEnginePath() 
{
}

void GameEnginePath::SetCurrnetPath()
{
	Path_ = std::filesystem::current_path(); //현재 폴더
}

bool GameEnginePath::IsExits()
{
	//경로가 존재하는지 확인
	return std::filesystem::exists(Path_);
}

std::string GameEnginePath::GetExtension()
{
	//확장자 알아내는 함수
	return Path_.extension().string();
}

std::string GameEnginePath::GetFileName()
{
	return Path_.filename().string();
}

std::string GameEnginePath::GetFullPath()
{
	return Path_.string();
}

