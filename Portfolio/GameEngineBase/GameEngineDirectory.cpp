#include "GameEngineDirectory.h"
#include "GameEngineDebug.h"
#include "GameEngineFile.h"
#include "GameEngineString.h"

GameEngineDirectory::GameEngineDirectory() 
{
	SetCurrnetPath();
}

GameEngineDirectory::GameEngineDirectory(const std::string& _Path)
{
	Path_ = _Path;
	if (false == IsExits())
	{
		MsgBoxAssert("존재하지 않는 폴더로 디렉토리를 초기화하려고 했습니다.");
	}
}

GameEngineDirectory::~GameEngineDirectory() 
{
}

void GameEngineDirectory::MoveParent()
{
	Path_ = Path_.parent_path();
}

bool GameEngineDirectory::IsRoot()
{
	return Path_ == Path_.root_directory();
}

void GameEngineDirectory::MoveParent(const std::string& _Name)
{
	while (false == IsRoot())
	{
		Path_ = Path_.parent_path();

		if (GetFileName() == _Name)
		{
			break;
		}
	}
}

void GameEngineDirectory::Move(const std::string& _Name)
{
	//유효한 경로인지 확인
	std::filesystem::path CheckPath = Path_;
	CheckPath.append(_Name);

	if (false == std::filesystem::exists(CheckPath))
	{
		MsgBoxAssertString(_Name + "Path is not exists");
	}


	Path_ = CheckPath;
}

std::vector<GameEngineFile> GameEngineDirectory::GetAllFile(const std::string _Ext)
{
	std::filesystem::directory_iterator DirIter(Path_);

	std::string Ext = _Ext;

	if (Ext != ".")
	{
		GameEngineString::ToUpper(Ext);

		if (std::string::npos == Ext.find("."))
		{
			Ext = "." + Ext; //점이 없다면 점을 붙인다
		}
	}

	std::vector<GameEngineFile> Return;

	for (const std::filesystem::directory_entry& Entry : DirIter)
	{
		if (true == Entry.is_directory())
		{
			continue;
		}

		if (Ext != ".")
		{
			GameEnginePath NewPath = Entry.path();

			std::string OtherExt = NewPath.GetExtension();
			GameEngineString::ToUpper(OtherExt);

			if (NewPath.GetExtension() == Ext)
			{
				continue;
			}
		}

		Return.push_back(GameEngineFile(Entry.path()));
	}

	return Return;
}

