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
	Path_ = std::filesystem::current_path(); //���� ����
}

bool GameEnginePath::IsExits()
{
	//��ΰ� �����ϴ��� Ȯ��
	return std::filesystem::exists(Path_);
}

std::string GameEnginePath::GetExtension()
{
	//Ȯ���� �˾Ƴ��� �Լ�
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

